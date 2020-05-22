#include "shader_snake.h"
#include "common_defs.h"
#include <fstream>


const int BUFFER_LENGTH = 10000;
const int DEF_SNAKE_LEN = 1000;
const string snake_title("Shader snake");

void ShaderSnake::Reset()
{
	Cleanup();
	m_size = 0;
}

void ShaderSnake::Cleanup()
{
	//чистим точки
	delete m_points_1;
	m_points_1 = NULL;

	delete m_points_2;
	m_points_2 = NULL;
	//фрейм буферы
	delete m_FBO_1;
	m_FBO_1 = NULL;

	delete m_FBO_2;
	m_FBO_2 = NULL;
}



void ShaderSnake::AddSeed_Rect(int x1, int y1, int x2, int y2 )
{
	Texture2D *points;
	if (m_odd_iter)
	{
		points = m_points_2;
	}
	else
	{
		points = m_points_1;
	}
	//m_size = Pts.size();
	int forx=abs(x1-x2)/(m_params.window-1);
	int fory=abs(y2-y1)/(m_params.window-1);

	m_size=forx*2+fory*2;


	for (int i=0; i<forx; i++)
	{
		points->Data->Pixel<Vector3D>(i,0)=Vector3D(x1+i*(m_params.window-1), y1, 0.0);
	}

	for (int i=forx; i<forx+fory; ++i)
	{
		points->Data->Pixel<Vector3D>(i,0)=Vector3D(x2, y1-(i-forx)*(m_params.window), 0.0);
	}

	for (int i=forx+fory; i<2*forx+fory; ++i)
	{
		points->Data->Pixel<Vector3D>(i,0)=Vector3D(x2-(i-forx-fory)*(m_params.window-1), y2, 0.0);
	}

	for (int i=2*forx+fory; i<2*forx+2*fory; ++i)
	{
		points->Data->Pixel<Vector3D>(i,0)=Vector3D(x1, y2-(i-2*forx+fory)*(m_params.window-1), 0.0);
	}

	points->Setup();
}
void ShaderSnake::AddSeed_Ell(int x, int y, int a, int b)
{
	Texture2D *points;
	if (m_odd_iter)
	{
		points = m_points_2;
	}
	else
	{
		points = m_points_1;
	}
	//m_size = Pts.size();
	m_size=2*(a+b);
	float step=2*3.14/m_size;
	for (float i=0; i<m_size; i++)
		points->Data->Pixel<Vector3D>(i,0)=Vector3D((int)a*cos(i*step)+x, (int)b*sin(i*step)+y, 0.0);
	points->Setup();
}



bool ShaderSnake::Init()
{
	if (m_shader)
	{
		// already initialized
		return true;
	}

	//грузим и компиляем шейдеры
	m_shader = new ShaderManager();
	if (!m_shader)
	{
		MessageBoxA(0, "Failed to initialize shader manager for shader snake!", "Fatal!", 0);
		return false;
	}

	string current_file = "shader_snake\\Common.vs";
	if (!m_shader->LoadVertexShader(current_file.c_str()))
	{
		// Display error info
		char szBuf[BUFFER_LENGTH];
		int dummy;
		glGetShaderInfoLog(m_shader->GetVertexHandle(), BUFFER_LENGTH, &dummy, szBuf);
		if (szBuf[0] == 0)
		{
			strcpy(szBuf, "File not found!");
		}
		MessageBoxA(0, szBuf, current_file.c_str(), 0);

		delete m_shader;
		m_shader = NULL;

		return false;
	}

	current_file = "shader_snake\\SingleSnake.fs";
	if (!m_shader->LoadFragmentShader(current_file.c_str()))
	{
		// Display error info
		char szBuf[BUFFER_LENGTH];
		int dummy;
		glGetShaderInfoLog(m_shader->GetFragmentHandle(), BUFFER_LENGTH, &dummy, szBuf);
		if (szBuf[0] == 0)
		{
			strcpy(szBuf, "File not found!");
		}
		MessageBoxA(0, szBuf, current_file.c_str(),0);

		delete m_shader;
		m_shader = NULL;

		return false;
	}
	//линкуем шейдеры
	if (!m_shader->BuildProgram())
	{
		// Display error info
		char szBuf[BUFFER_LENGTH];
		int dummy;
		glGetShaderInfoLog(m_shader->GetProgramHandle(), BUFFER_LENGTH, &dummy, szBuf);
		if (szBuf[0] == 0)
		{
			strcpy(szBuf, "Error building 'shader snake' shader program.");
		}
		MessageBoxA(0, szBuf, "Fatal!", 0);

		delete m_shader;
		m_shader = NULL;

		return false;
	}			

	return true;
}

bool ShaderSnake::GetReady()
{
	if (IsReady()) 
	{
		// Already initialized
		return true;
	}

	// Reset and clear all previous data
	Reset();

	TextureData2D* data_1 = new TextureData2D(DEF_SNAKE_LEN, 1);
	if (!data_1)
	{
		MessageBoxA(0, lpszSnakeInitFailed, "'Shader snake'", MB_ICONWARNING);
		Cleanup();
		return false;
	}

	m_points_1 = new Texture2D(data_1, SNAKE_POINTS_FBO_1, GL_TEXTURE_RECTANGLE_ARB);
	if (!m_points_1)
	{
		MessageBoxA(0, lpszSnakeInitFailed, "'Shader snake'", MB_ICONWARNING);
		delete data_1;
		Cleanup();
		return false;
	}
	m_points_1->Setup();

	TextureData2D* data_2 = new TextureData2D(DEF_SNAKE_LEN, 1);
	if (!data_2)
	{
		MessageBoxA(0, lpszSnakeInitFailed, "'Shader snake'", MB_ICONWARNING);
		Cleanup();
		return false;
	}

	m_points_2 = new Texture2D(data_2, SNAKE_POINTS_FBO_2, GL_TEXTURE_RECTANGLE_ARB);
	if (!m_points_2)
	{
		MessageBoxA(0, lpszSnakeInitFailed, "'Shader snake'", MB_ICONWARNING);
		delete data_2;
		Cleanup();
		return false;
	}
	m_points_2->Setup();

	// Setup FBOs
	m_FBO_1 = new FrameBuffer();
	if (!m_FBO_1)
	{
		MessageBoxA(0, lpszSnakeInitFailed, "'Shader snake'", MB_ICONWARNING);
		Cleanup();
		return false;
	}

	m_FBO_2 = new FrameBuffer();
	if (!m_FBO_2)
	{
		MessageBoxA(0, lpszSnakeInitFailed, "'Shader snake'", MB_ICONWARNING);
		Cleanup();
		return false;
	}

	m_FBO_1->ColorBuffers.push_back(m_points_2);
	m_FBO_1->Setup();

	m_FBO_2->ColorBuffers.push_back(m_points_1);
	m_FBO_2->Setup();

	m_odd_iter = false;

	return true;
}

bool ShaderSnake::IsReady() const
{
	return ((m_points_1 != NULL) && (m_points_2 != NULL));
}

void ShaderSnake::AddSeed(int x, int y)
{
	Texture2D *points;
	if (m_odd_iter)
	{
		points = m_points_2;
	}
	else
	{
		points = m_points_1;
	}

	// Set 4 points around the given point
	m_size = 4;

	points->Data->Pixel<Vector3D>(0, 0) = Vector3D(x - m_params.window - 1, y, 0.0);
	points->Data->Pixel<Vector3D>(1, 0) = Vector3D(x, y - m_params.window - 1, 0.0);
	points->Data->Pixel<Vector3D>(2, 0) = Vector3D(x + m_params.window + 1, y, 0.0);
	points->Data->Pixel<Vector3D>(3, 0) = Vector3D(x, y + m_params.window + 1, 0.0);
	points->Setup();
}

bool ShaderSnake::FixParams(Texture2D* &image, SnakeParams& params)
{
	if (!image)
	{
		return false;
	}

	m_params = params;
	inum=0;

	// Prepare image(convert to normalized single-channel)

//	TextureData2D* data  = new TextureData2D(image->Data->GetWidth(), image->Data->GetHeight());
//	m_image = new Texture2D(data, SNAKE_IMAGE_FBO, GL_TEXTURE_RECTANGLE_ARB);
	m_image=image;
	int w = image->Data->GetWidth();
	int h = image->Data->GetHeight();

	float e_max = 0.0, e_min = FLT_MAX;
	float* img = new float[w * h];

	int i, j;
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			//Vector3D pixel = image->Data->Pixel<Vector3D>(j, i);
			Vector3D pixel = m_image->Data->Pixel<Vector3D>(j, i);
			float e = Dot(pixel, Vector3D(1.0, 1.0, 1.0));
			if (e > e_max)
			{
				e_max = e;
			}
			if (e < e_min)
			{
				e_min = e;
			}
			img[i * w + j] = e;
		}
	}

	float delta_e = e_max - e_min;
	if (delta_e > 0.0)
	{
		delta_e = 1.0 / delta_e;
	}
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			m_image->Data->Pixel<Vector3D>(j, i) = (img[i * w + j] - e_min) * delta_e;
		}
	}
	m_image->Setup();

	delete[] img;
	return true;
}

Texture2D* ShaderSnake::Output() const
{
	if (m_odd_iter)
	{
		return m_points_2;
	}
	else
	{
		return m_points_1;	
	}

//	output->m_count = m_size;
//	output->m_window = pow(2.0 * (float)m_params.window + 1.0, 2);
}

void ShaderSnake::Resample()
{
	TextureData2D* points;
	if (m_odd_iter)
	{
		points = m_points_1->Data;
	}
	else
	{
		points = m_points_2->Data;
	}

	// Adds or deletes points in order to maintain snake evenly spaced
	int w = m_params.window;
	int i, j, k;
	int p;
	for (i = 0; i < m_size; i += k)
	{
		j = (i + 1) % m_size;
		k = 1;
		Vector3D delta = points->Pixel<Vector3D>(i, 0) - points->Pixel<Vector3D>(j, 0);
		if (fabs(delta.X) <= w && fabs(delta.Y) <= w)
		{
			if (j != 0)
			{
				for (p = j; p < m_size; p++)
				{
					points->Pixel<Vector3D>(p, 0) = points->Pixel<Vector3D>(p + 1, 0);
				}
			}
			m_size--;
			k = 0;
		}
	}

	for (i = 0; i < m_size; i += k)
	{
		if (m_size == DEF_SNAKE_LEN - 1)
		{
			return;
		}
		j = (i + 1) % m_size;
		k = 1;
		Vector3D delta = points->Pixel<Vector3D>(i, 0) - points->Pixel<Vector3D>(j, 0);
		if (fabs(delta.X) > 2 * (w + 1) || fabs(delta.Y) > 2 * (w + 1))
		{
			if (j == 0 || j == m_size)
			{
				points->Pixel<Vector3D>(m_size, 0) = 0.5 * (points->Pixel<Vector3D>(i, 0) +
					points->Pixel<Vector3D>(0, 0));
			}
			else
			{
				for (p = m_size; p > j; p--)
				{
					points->Pixel<Vector3D>(p, 0) = points->Pixel<Vector3D>(p - 1, 0);
				}
				points->Pixel<Vector3D>(j, 0) = 0.5 * (points->Pixel<Vector3D>(i, 0) +
					points->Pixel<Vector3D>(j + 1, 0));
			}
			m_size++;
			k = 0;
		}
	}

	if (m_odd_iter)
	{
		m_points_1->Setup();
	}
	else
	{
		m_points_2->Setup();
	}
}

int ShaderSnake::Iterate()
{
	if (!IsReady())
	{
		return -1;
	}

	// 4 points is a minimal amount
	if (m_size < 4)
	{
		return -1;
	}

	m_odd_iter = !m_odd_iter;

	Resample();

	// Calc average distance
	TextureData2D* in_points;
	if (m_odd_iter)
	{
		in_points = m_points_1->Data;
	}
	else
	{
		in_points = m_points_2->Data;
	}

	float avg_dist = 0.0;
	int i, j;
	for(i = 0, j = 1; i < m_size; i++, j = (j + 1) % m_size)
	{
		avg_dist += Distance(in_points->Pixel<Vector3D>(i, 0), in_points->Pixel<Vector3D>(j, 0));
	}
	avg_dist *= 1.0 / m_size;

	// Setup input and output buffers
	m_shader->Bind();
	
	m_shader->SetUniformInteger("iSize", m_size);
	m_shader->SetUniformInteger("iWindow", m_params.window);
	m_shader->SetUniformInteger("iWidth", m_image->Data->GetWidth());
	m_shader->SetUniformInteger("iHeight", m_image->Data->GetHeight());
	m_shader->SetUniformFloat("fGamma", m_params.gamma);
	m_shader->SetUniformFloat("fAvgDist", avg_dist);
	m_shader->SetUniformVector("vParam", Vector3D(m_params.alpha, 
												  m_params.beta, 
												  m_params.kappa));

	m_image->Bind();
	m_points_1->Bind();
	m_points_2->Bind();

	m_shader->SetTexture("Image", m_image);

	if (m_odd_iter)
	{
		m_FBO_1->Bind();
		m_shader->SetTexture("Points", m_points_1);
	}
	else
	{
		m_FBO_2->Bind();
		m_shader->SetTexture("Points", m_points_2);
	}


	std::ofstream ofs("Testing_Project_out.txt",std::ios_base::app);
	ofs<<std::endl<<"Iteration #"<<inum<<" before"<<std::endl;
	for (int f=0; f<m_size; f++)
		ofs<<in_points->Pixel<Vector3D>(f,0).X<<"	"<<in_points->Pixel<Vector3D>(f,0).Y<<std::endl;
	ofs<<std::endl;

	RunShader(m_size, 1);
	
	if (m_odd_iter)
	{
		m_FBO_1->FetchOutcome();
		m_FBO_1->Unbind();
	}
	else
	{
		m_FBO_2->FetchOutcome();
		m_FBO_2->Unbind();
	}

	m_points_1->Unbind();
	m_points_2->Unbind();

	m_shader->Unbind();


	ofs<<std::endl<<"Iteration #"<<inum<<" after"<<std::endl;
	for (int f=0; f<m_size; f++)
		if (m_odd_iter)
			ofs<<m_points_2->Data->Pixel<Vector3D>(f,0).X<<"	"<<m_points_2->Data->Pixel<Vector3D>(f,0).Y<<std::endl;
		else
			ofs<<m_points_1->Data->Pixel<Vector3D>(f,0).X<<"	"<<m_points_1->Data->Pixel<Vector3D>(f,0).Y<<std::endl;
	ofs<<std::endl;
	inum++;
	ofs.close();
	
	return 0;
}

int ShaderSnake::GetSize()
{
	return m_size;
}

ShaderSnake::ShaderSnake()
{
	inum=0;

	m_points_1 = NULL;
	m_points_2 = NULL;
	m_size = 0;

	m_shader = NULL;
	m_FBO_1 = NULL;
	m_FBO_2 = NULL;
	
	m_odd_iter = false;

	// Default params
	m_params.alpha = 1.0;
	m_params.beta = 2.0;
	m_params.gamma = 15.0;
	m_params.kappa = 4.0;
	m_params.window = 2;
}

ShaderSnake::~ShaderSnake()
{
	Cleanup();

	delete m_shader;
	m_shader = NULL;

//	if (m_image)
//		m_image->~Texture2D();
}
