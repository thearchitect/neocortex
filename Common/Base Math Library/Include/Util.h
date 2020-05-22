/*
   Base Math Library   
   Copyright (C) 2009  Denis Bogolepov ( bogdencmc@inbox.ru )

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see http://www.gnu.org/licenses.
 */

#pragma once

#ifndef _MATH_UTIL_

#define _MATH_UTIL_

#include <math.h>

//--------------------------------------- Useful Constants ----------------------------------------

static const float ONEPI = 3.141592653589F;
                
static const float TWOPI = 6.283185307179F;
        
static const float EXPONENT = 2.718281828459F;
        
static const float EPSILON = 0.0001F;

//-------------------------------------------------------------------------------------------------

static const int SIZE2D = 2;

static const int SIZE3D = 3;

static const int SIZE4D = 4;

//-------------------------------------------------------------------------------------------------

static const int A = 0;

static const int B = 1;

static const int C = 2;

static const int D = 3;

//--------------------------------------- Useful Functions ----------------------------------------

namespace BMath
{
    float Degrees ( float );
        
        float Radians ( float );

        float Sign ( float );

        float Fract ( float );
         
        float Mod ( float, float );

        float Clamp ( float, float, float );
                
        float Mix ( float, float, float );
                
        float Step ( float, float );

        float Smooth ( float, float, float );
}

#endif
