#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv/cvaux.h"
#include "common_defs.h"
#include "shader_snake.h"
#include <conio.h>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

struct Parameters
{
	char* winname;
	Mat image, wind, image_backup;		//исходное изображение и окно, которое видит пользователь
	int brushSize, numslices;			
	Point	Center;						//центр исходного контура (не нужен)
	int Xmod, Ymod;						//модификаторы для точек
	int resX, resY;						//храним разрешение 
	vector <Point> points;				//исходные точки контура
	vector <vector <Point> > ResPoints;	//все результаты сразу
	vector <char *> FNames;				//имена файлов
	int CurrentSlice;					//текущий слой (для вывода результата)
	int alpha, beta, gamma, iter;
	int a,b;							//параметры эллипса
	bool POINT, RECT, ELLIPSE;			// способ задания начального контура

	Parameters()
	{
		CurrentSlice=0;
		brushSize=4;
		//дефолтные параметры для змейки
		alpha=1;
		beta=2;
		gamma=15;
		iter=30;
		winname="Source";
		Xmod=0;
		Ymod=0;
		//дефолтные параметры эллипса
		a=3;
		b=6;
		//для выбора метода выделения
		POINT=true; RECT=false; ELLIPSE=false;
	}
};


void refresh(Parameters &params);

void onMouseEvent(int event, int x, int y, int flags, void* data)
{
	//если кликаем, то рисуем seed
	if ((event == CV_EVENT_LBUTTONDOWN) )
	{
		Parameters* params = (Parameters*)data;
		if (params->POINT)
		{
			if (!params->points.empty())
			{
				params->image_backup.copyTo(params->image);
				params->points.clear();
				refresh(*params);
			}
			params->points.push_back(Point(x+params->Xmod,y+params->Ymod));
			circle(params->image, Point(x+params->Xmod, y+params->Ymod), params->brushSize, Scalar(0, 0, 255));
			circle(params->wind, Point(x, y), params->brushSize, Scalar(0, 0, 255));
			imshow(params->winname, params->wind);
		}
		if (params->RECT)
		{
			params->points.push_back(Point(x+params->Xmod, y+params->Ymod));
			if (params->points.size()>2)
			{
				params->points.clear();
				params->image_backup.copyTo(params->image);
				refresh(*params);
				params->points.push_back(Point(x+params->Xmod, y+params->Ymod));
			}
			if (params->points.size()==2)
			{
				rectangle(params->image, params->points[0], params->points[1], Scalar(0,0,255));
				rectangle(params->wind, params->points[0]-Point(params->Xmod, params->Ymod),
							params->points[1]-Point(params->Xmod, params->Ymod), Scalar(0,0,255));
			}
			circle(params->image, Point(x+params->Xmod, y+params->Ymod), params->brushSize, Scalar(0, 0, 255));
			circle(params->wind, Point(x, y), params->brushSize, Scalar(0, 0, 255));
			imshow(params->winname, params->wind);
		}
		if (params->ELLIPSE)
		{
			if(!params->points.empty())
			{
				params->image_backup.copyTo(params->image);
				params->points.clear();
				refresh(*params);
			}
			params->points.push_back(Point(x+params->Xmod,y+params->Ymod));
			ellipse(params->wind, Point(x, y), Size(params->a, params->b), 0, 0, 360, Scalar(0,0,255));
			ellipse(params->image, Point(x+params->Xmod, y+params->Ymod), Size(params->a, params->b), 0, 0, 360, Scalar(0,0,255));
			imshow(params->winname, params->wind);
		}
	}
}

//init method's callbacks
void buttonPointCallback (int state, void* data)
{
	if (state == 1)
	{
		Parameters *params= (Parameters*) data; 
		params->ELLIPSE=false;
		params->RECT=false;
		params->POINT=true;
		if (!params->points.empty())
		{
			params->points.clear();
			params->image_backup.copyTo(params->image);
			refresh(*params);
			imshow(params->winname, params->wind);
		}
	}
}
void buttonRectCallback (int state, void* data)
{
	if (state == 1)
	{
		Parameters *params= (Parameters*) data; 
		params->ELLIPSE=false;
		params->RECT=true;
		params->POINT=false;
		if (!params->points.empty())
		{
			params->points.clear();
			params->image_backup.copyTo(params->image);
			refresh(*params);
			imshow(params->winname, params->wind);
		}
	}
}
void buttonEllCallback (int state, void* data)
{
	if (state == 1)
	{
		Parameters *params= (Parameters*) data; 
		params->ELLIPSE=true;
		params->RECT=false;
		params->POINT=false;
		if (!params->points.empty())
		{
			params->points.clear();
			params->image_backup.copyTo(params->image);
			refresh(*params);
			imshow(params->winname, params->wind);
		}
	}
}
void attachInitMethods(Parameters &params)
{
	//default
	if (params.POINT)
		createButton("Point", buttonPointCallback, &params, CV_RADIOBOX, 1);
	else
		createButton("Point", buttonPointCallback, &params, CV_RADIOBOX, 0);
	//rectangle
	if (params.RECT)
		createButton("Rect", buttonRectCallback, &params, CV_RADIOBOX, 1);
	else
		createButton("Rect", buttonRectCallback, &params, CV_RADIOBOX, 0);
	//ellipse
	if (params.ELLIPSE)
		createButton("Ell", buttonEllCallback, &params, CV_RADIOBOX, 1);
	else
		createButton("Ell", buttonEllCallback, &params, CV_RADIOBOX, 0);
}

//dummy mouse event
void dummyEvent(int event, int x, int y, int flags, void* data)
{}

//при изменении ползунков X_Offset и  Y_Offset
void XEvent(int position, void* data)
{
	Parameters* params = (Parameters*)data;
	for (int y=params->Ymod; y<params->resY+params->Ymod; y++)
		for(int x=params->Xmod; x<params->resX+params->Xmod; x++)
			params->wind.at<Vec3b>(y-params->Ymod,x-params->Xmod)=params->image.at<Vec3b>(y,x);
	imshow(params->winname, params->wind);
}

void refresh(Parameters &params)
{
	for (int y=params.Ymod; y<params.resY+params.Ymod; y++)
		for(int x=params.Xmod; x<params.resX+params.Xmod; x++)
			params.wind.at<Vec3b>(y-params.Ymod,x-params.Xmod)=params.image.at<Vec3b>(y,x);
}

void attachTB(Parameters &params)
{
	createTrackbar("Alpha", params.winname, &params.alpha, 100);
	createTrackbar("Beta", params.winname, &params.beta, 100);
	createTrackbar("Gamma", params.winname, &params.gamma, 100);
	createTrackbar("Iterations", params.winname, &params.iter, 1000);
}

void attachSliders(Parameters &params)
{
	if (params.image.cols>800)
		createTrackbar("X_Offset", params.winname, &params.Xmod, params.image.cols-params.resX-1, XEvent, &params);
	if (params.image.rows>600)
		createTrackbar("Y_Offset", params.winname, &params.Ymod, params.image.rows-params.resY-1, XEvent, &params);
	createTrackbar("A", params.winname, &params.a, 50);
	createTrackbar("B", params.winname, &params.b, 50);
}
//gthpfuhe;ftv rfhnbyre
void ReloadSlice(int position, void* data)
{
	Parameters* params = (Parameters*)data;

	params->image=imread(params->FNames[position], 1);
	if (!params->ResPoints.empty())
		for (int i=0; i<params->ResPoints[position].size(); i++)
		{
			circle(params->image, params->ResPoints[position][i], 3, Scalar(0, 0, 255), -1);
		}
	refresh(*params);
	imshow(params->winname, params->wind);
}

void attachSliceSlider(Parameters &params)
{
	if (params.numslices>1)
		createTrackbar("Slice", params.winname, &params.CurrentSlice, params.numslices-1, ReloadSlice, &params);
}
//Экспериментально (сглаживаем возможный шум)
void preprocess(Mat& img)
{
	GaussianBlur(img, img, Size(5,5), 0, 0);
	medianBlur(img, img, 5);
}

bool isInputCorrect(Parameters &params)
{
	if (params.POINT || params.ELLIPSE)
		{
			if (params.points.empty())
			{
				cout<<"Error, no initial point"<<endl;
				return false;
			}
			if (params.ELLIPSE && (params.a < 2 || params.b < 2 ) )
			{
				cout<<"Error, wrong ellipse parameters"<<endl;
				return false;
			}
		}
		if (params.RECT)
		{
			if (params.points.empty() || params.points.size() < 2)
			{
				cout<<"Error, no or too few initial points"<<endl;
				params.points.clear();
				return false;
			}
		}
		return true;
}

int main (int argc, char *argv[])
{
	Parameters params;
	Mat src_1ch;
	char Pressed;							//нажатая клавиша
	Texture2D *img;					
	TextureData2D *data; 
	ShaderSnake *Snake;

	//load files
	char fname[256]="../Data/list.lst";
	cout<<"Enter path to list-file: "<<endl;
	cin>>fname;
	ifstream ifs(fname);

	if (!ifs.is_open())
	{
		cout<<"Could not open list file"<<endl;
		_getch();
		return 1;
	}

	while (!ifs.eof()) 
	{
		char * str=new char [300];
		ifs>>str;
		params.FNames.push_back(str);
	}
	params.numslices=params.FNames.size();
		
	//инициализируем  glfw (для шейдеров)
	glfwInit();
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1);
	if(!glfwOpenWindow(1, 1, 0, 0, 0, 0, 16, 0, GLFW_WINDOW))
	{
		glfwTerminate(); 
		MessageBoxA(0, lpszGlfwError, "Fatal", 0);
		return 1;
	}
	glfwSetWindowTitle("Output window");
		
	namedWindow(params.winname,CV_GUI_EXPANDED|CV_WINDOW_NORMAL|CV_WINDOW_KEEPRATIO);
	setWindowProperty(params.winname,CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
	//цепляем сразу же (чтобы избежать дублирования)
	attachInitMethods(params);

	//основной цикл
	while(1)
	{
		params.image=imread(params.FNames[params.CurrentSlice],1);
		//устанавливаем разрешение окна
		if (params.image.cols<800)
			params.resX=params.image.cols;
		else
			params.resX=800;
		if (params.image.rows<600)
			params.resY=params.image.rows;
		else 
			params.resY=600;
		params.wind=Mat::zeros(params.resY, params.resX, CV_8UC3);
		params.image.copyTo(params.image_backup);
		//создаем окно просмотра

		Pressed=-1;

		//предобработка исходного изображения
		//по совету из презентации Nick Govier и David Newman
		//призвана уменьшить зашумленность изображения
		//т.к. алгоритм очень чувствителен к шуму
		//	preprocess(src_1ch);

		refresh(params);
		//показываем исходное изображение
		imshow(params.winname, params.wind);

		//устанавливаем мышиный callback
		cvSetMouseCallback(params.winname, onMouseEvent, &params);
		//цепляем слайдеры
		attachTB(params);
		attachSliders(params);
		attachSliceSlider(params);

		//ждем ввода
		Pressed=-1;
		while ((Pressed!=27)&&(Pressed!=13))
			Pressed=waitKey(0);
		if(Pressed==27)
			break;
			
		//проверяем корректность ввода
		if (!isInputCorrect(params))
			continue;

		//удаляем лишнее
		params.image.~Mat();
		params.image_backup.~Mat();

		for (int l=0; l< params.numslices; l++)
		{
			src_1ch=imread(params.FNames[l], 0);
			preprocess(src_1ch);
			data = new TextureData2D(src_1ch.cols, src_1ch.rows, 3);
			if (!data)
			{
				MessageBoxA(0, lpszInternalError, "Error", 0);
				return 1;
			}

			//копируем изображение в подходящий формат
			img = new Texture2D(data, 0, GL_TEXTURE_RECTANGLE_ARB);
			if (!img)
			{
				MessageBoxA(0, lpszInternalError, "Error", 0);
				return 1;
			}

			for (int y = 0; y <  src_1ch.rows; y++)
			{
				for (int x = 0; x < src_1ch.cols; x++)
				{
					uchar pixel = src_1ch.at<uchar>(y,x);
					data->Pixel<Vector3D> (x,abs(y-src_1ch.rows+1)) = 
						Vector3D (	(float)pixel / 255.0F,
									(float)pixel / 255.0F,
									(float)pixel / 255.0F);
				}
			}

			//производим итерации змейки
			SnakeParams sparam;
			sparam.alpha=(float) params.alpha;
			sparam.beta=(float) params.beta;
			sparam.gamma=(float) params.gamma;
			Snake=new ShaderSnake();
			Snake->Init();
			Snake->GetReady();
			Snake->FixParams(img, sparam);
			if (params.POINT)
				Snake->AddSeed(params.points[0].x, abs(params.points[0].y-src_1ch.rows+1));
			if (params.ELLIPSE)
				Snake->AddSeed_Ell(	params.points[0].x, abs(params.points[0].y-src_1ch.rows+1),
									params.a, params.b);
			if (params.RECT)
				Snake->AddSeed_Rect(params.points[0].x, abs(params.points[0].y-src_1ch.rows+1),
									params.points[1].x, abs(params.points[1].y-src_1ch.rows+1));

			for (int i=0; i<params.iter; i++)
				Snake->Iterate();

			//достаем точки
			Texture2D* ResPoints=Snake->Output();
			int ResSize=Snake->GetSize();
			vector <Point> OCV_ResPoints;

			for (int i=0; i<ResSize; i++)
			{
				Vector3D temp;
				temp=ResPoints->Data->Pixel<Vector3D>(i,0);
				OCV_ResPoints.push_back(Point(temp.X, abs(temp.Y-src_1ch.rows+1)));
			}
			//закидываем все в параметры
			params.ResPoints.push_back(OCV_ResPoints);
			src_1ch.~Mat();
			Snake->~ShaderSnake();
	//		data->~TextureData2D();
			img->~Texture2D();
			//ResPoints=NULL;
		}

		//вывод
		params.image=imread(params.FNames[params.CurrentSlice], 1);
		for (int i=0; i<params.ResPoints[params.CurrentSlice].size(); i++)
		{
			circle(params.image, params.ResPoints[params.CurrentSlice][i], 3, Scalar(0, 0, 255), -1);
		}
		refresh(params);
		params.points.clear();
		imshow(params.winname, params.wind);
		//запрещаем тыкать мышью (пока)
		cvSetMouseCallback(params.winname, dummyEvent, &params);

		//ждем ввода
		Pressed=-1;
		while ((Pressed!=27)&&(Pressed!=13))
			Pressed=waitKey(0);
		if(Pressed==27)
			break;
	//	cvDestroyWindow(params.winname);
		params.ResPoints.clear();
		params.image.~Mat();
	}
	return 0;
}