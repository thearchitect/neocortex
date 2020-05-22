#ifndef common_defs_H
#define common_defs_H

// Util classes
#define _USE_MATH_DEFINES
#include <math.h>
#include "matrix.h"
#include "vector.h"
#include "quaternion.h"
#include "bbox.h"

namespace core
{
	// Floating point type to use within core library
	typedef double        REAL;
	typedef unsigned int  UINT;
	typedef unsigned char BYTE;

	// Vector types
	typedef vector<REAL, 1> vector1;
	typedef vector<REAL, 2> vector2;
	typedef vector<REAL, 3> vector3;
	typedef vector<REAL, 4> vector4;
	
	// Color types
	typedef vector3 color_rgb;
	typedef vector4 color_rgba;

	// Matrix types
	typedef matrix<REAL, 2, 2> matrix2x2;
	typedef matrix<REAL, 3, 3> matrix3x3;
	typedef matrix<REAL, 4, 4> matrix4x4;

	// Quaternion type
	typedef quaternion<REAL> quat;
}

#endif
