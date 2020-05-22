#pragma once

// Contains common stuff for all project units

#include <math.h>
#include <float.h>
#include <typeinfo>
#include "GLee/Glee.h"
#include <GL/gl.h>
#include <Base Render Library/Keyboard.h>
#include <Base Render Library/Mouse.h>
#include <Base Render Library/FrameBuffer.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib") 
#pragma comment(lib,"glfw.lib") 


using namespace BMath;
using namespace Render;


#define SP_ALPHA	1.0
#define SP_BETA		2.0
#define SP_GAMMA	15.0
#define SP_KAPPA	4.0
#define SP_ITERATIONS 100

// Methods
void RunShader(int width, int height);

// Definitions
const double M_PI = 3.14159265358979323846;

const int MAX_ITEM_COUNT = 20;
const int MAX_FILTER_STAGE_COUNT = 8;
enum {MATRIX_FILTER_FBO = MAX_FILTER_STAGE_COUNT, 
	  AUX_TEX_0, 
	  AUX_TEX_1,
	  AUX_TEX_2,
	  AUX_TEX_3,
	  SNAKE_IMAGE_FBO,
	  SNAKE_POINTS_FBO_1,
	  SNAKE_CONN_FBO_1,
	  SNAKE_POINTS_FBO_2,
	  SNAKE_CONN_FBO_2,
};

const int MAX_FILE_NAME_LENGTH = 40;
const int MAX_FILTER_NAME_LENGTH = 30;
const int TMP_BUFFER_SIZE = 30;
const int MAX_IMAGE_SIZE = 2048;


const char lpszBadFileFormat[] = "Bad image format.";
const char lpszReachedMaxCount[] = "Max image count reached. Please, restart application to clear the list.";
const char lpszInternalError[] = "Internal error occured. Please, restart application if it happens once again.";
const char lpszGlfwError[] = "Glfw error occured. Please, restart application.";
const char lpszErrorProcessing[] = "An error occured during image processing.";
const char lpszReachedMaxFilterStage[] = "Limit of filter chain exceed. You cannot filter this image.";
const char lpszSnakeHelp[] = "Snake is run in stepped mode\nPress SPACE key to iterate snake step by step\nUse ENTER key to toggle stepped/full-run mode\nUse ESC key to stop snake";
const char lpszIsRun[] = "No actions are allowed while snake is running. Use ESC to stop snake.";
const char lpszFinishSnake[] = "Snake stopped.";
const char lpszSnakeInitFailed[] = "Snake initialization failed.";
const char lpszSnakeError[] = "Cannot get snake ready. Please, restart application.";

struct Picture{
	int stage;
	char lpszTitle[MAX_FILE_NAME_LENGTH + MAX_FILTER_NAME_LENGTH];
	Texture2D *image;
	TextureData2D *image_data;
};