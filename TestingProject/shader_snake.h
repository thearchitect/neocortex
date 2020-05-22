#include <stddef.h>
#include "common_defs.h"

#pragma once

//параметры змейки
 struct SnakeParams{

	float alpha;
	float beta;
	float gamma;
	float kappa;
	int window;

	SnakeParams()
	{
		alpha=SP_ALPHA;
		beta=SP_BETA;
		gamma=SP_GAMMA;
		kappa=SP_KAPPA;

		window = 2;
	}
};



class ShaderSnake
{
public:
	
	// Performs initialization
	bool Init();

	// Prepares snake to work
	bool GetReady();

	// Sets initial snake position(replaces old with a new if called multiple times)
	void AddSeed(int x, int y);

	void AddSeed_Rect(int x1, int y1, int x2, int y2);

	void AddSeed_Ell(int x, int y, int a, int b);

	// Sets snake params and image to work with
	bool FixParams(Texture2D* &image, SnakeParams& params);

	// Returns pointer to algorithm output
	Texture2D* Output() const;

	// Performs an iteration
	int Iterate();

	// Checks if all initializations has been done successfully
	bool IsReady() const;

	int GetSize();

	ShaderSnake();
	~ShaderSnake();

private:
	int inum;

	// Snake points
	Texture2D* m_points_1;
	Texture2D* m_points_2;
	int m_size;
	bool m_odd_iter;

	// Shader stuff
	ShaderManager* m_shader;
	FrameBuffer *m_FBO_1;
	FrameBuffer *m_FBO_2;

	// Params
	SnakeParams m_params;

	// Image
	Texture2D* m_image;

	void Cleanup();
	void Resample();

	void Reset();
};