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

#ifndef _VECTOR4D_

#define _VECTOR4D_

#include "Util.h"

#include "Vector2D.h"

#include "Vector3D.h"

#include <iostream>

using namespace std;

namespace BMath
{
        class Vector2D;

        class Vector3D;

        class Vector4D
        {
                public:

                        //----------------------------------- Public Fields -----------------------------------

                        float X;

                        float Y;

                        float Z;

                        float W;

                        //---------------------------------- Public Constants ---------------------------------

                        static const Vector4D Zero;

                        static const Vector4D Unit;

                        static const Vector4D AxisX;

                        static const Vector4D AxisY;

                        static const Vector4D AxisZ;

                        static const Vector4D AxisW;

                        //------------------------------------ Constructors -----------------------------------

                        Vector4D ( float = 0, float = 0, float = 0, float = 0 );

                        Vector4D ( const float [SIZE4D] );

                        Vector4D ( const Vector2D&, float = 0, float = 0  );

                        Vector4D ( const Vector3D&, float = 0 );

                        Vector4D ( const Vector4D& );

                        //-------------------------------- Arithmetic Operators -------------------------------

                        friend Vector4D operator - ( const Vector4D& );

                        friend Vector4D operator + ( const Vector4D&, const Vector4D& );
                       
                        friend Vector4D operator - ( const Vector4D&, const Vector4D& );

                        friend Vector4D operator + ( const Vector4D&, float );
                       
                        friend Vector4D operator - ( const Vector4D&, float );

                        friend Vector4D operator + ( float, const Vector4D& );
                       
                        friend Vector4D operator - ( float, const Vector4D& );
                       
                        friend Vector4D operator * ( const Vector4D&, const Vector4D& );
                       
                        friend Vector4D operator / ( const Vector4D&, const Vector4D& );

                        friend Vector4D operator * ( const Vector4D&, float );

                        friend Vector4D operator / ( const Vector4D&, float );  

                        friend Vector4D operator * ( float, const Vector4D& );                          

                        friend Vector4D operator / ( float, const Vector4D& );

                        friend Vector4D operator += ( const Vector4D&, const Vector4D& );
                       
                        friend Vector4D operator -= ( const Vector4D&, const Vector4D& );

                        friend Vector4D operator += ( const Vector4D&, float );

                        friend Vector4D operator -= ( const Vector4D&, float );

                        friend Vector4D operator *= ( const Vector4D&, const Vector4D& );
                       
                        friend Vector4D operator /= ( const Vector4D&, const Vector4D& );

                        friend Vector4D operator *= ( const Vector4D&, float );

                        friend Vector4D operator /= ( const Vector4D&, float );

                        //---------------------------------- Logic Operators ----------------------------------

                        friend bool operator < ( const Vector4D&, const Vector4D& );

                        friend bool operator > ( const Vector4D&, const Vector4D& );

                        friend bool operator < ( const Vector4D&, float );

                        friend bool operator > ( const Vector4D&, float );

                        friend bool operator < ( float, const Vector4D& );                              

                        friend bool operator > ( float, const Vector4D& );

                        friend bool operator <= ( const Vector4D&, const Vector4D& );

                        friend bool operator >= ( const Vector4D&, const Vector4D& );

                        friend bool operator <= ( const Vector4D&, float );

                        friend bool operator >= ( const Vector4D&, float );

                        friend bool operator <= ( float, const Vector4D& );                            

                        friend bool operator >= ( float, const Vector4D& );

                        friend bool operator == ( const Vector4D&, const Vector4D& );

                        friend bool operator != ( const Vector4D&, const Vector4D& );

                        friend bool operator == ( const Vector4D&, float );

                        friend bool operator != ( const Vector4D&, float );

                        friend bool operator == ( float, const Vector4D& );

                        friend bool operator != ( float, const Vector4D& );

                        //----------------------------- Input and Output Operators ----------------------------

                        friend istream& operator >> ( istream&, Vector4D& );

                        friend ostream& operator << ( ostream&, const Vector4D& );

                        //-------------------------------- Auxiliary Operators --------------------------------

                        operator float * ( )
                        {
                                return &X;
                        }

                        operator const float * ( ) const
                        {
                                return &X;
                        }

                        float& operator [] ( int index )
                        {
                                return *( index + &X );
                        }

                        //--------------------------------- Common Functions ----------------------------------

                        friend Vector4D Abs ( const Vector4D& );

                        friend Vector4D Sign ( const Vector4D& );

                        friend Vector4D Floor ( const Vector4D& );

                        friend Vector4D Ceil ( const Vector4D& );

                        friend Vector4D Fract ( const Vector4D& );

                        friend Vector4D Mod ( const Vector4D&, const Vector4D& );

                        friend Vector4D Mod ( const Vector4D&, float );

                        friend Vector4D Mod ( float, const Vector4D& );

                        friend Vector4D Min ( const Vector4D&, const Vector4D& );

                        friend Vector4D Min ( const Vector4D&, float );

                        friend Vector4D Min ( float, const Vector4D& );

                        friend Vector4D Max ( const Vector4D&, const Vector4D& );

                        friend Vector4D Max ( const Vector4D&, float );

                        friend Vector4D Max ( float, const Vector4D& );

                        friend Vector4D Clamp ( const Vector4D&, const Vector4D&, const Vector4D& );

                        friend Vector4D Clamp ( const Vector4D&, float, float );

                        friend Vector4D Mix ( const Vector4D&, const Vector4D&, const Vector4D& );

                        friend Vector4D Mix ( const Vector4D&, const Vector4D&, float );

                        friend Vector4D Step ( const Vector4D&, const Vector4D& );

                        friend Vector4D Step ( const Vector4D&, float );

                        friend Vector4D Smooth ( const Vector4D&, const Vector4D&, const Vector4D& );

                        friend Vector4D Smooth ( const Vector4D&, float, float );

                        //-------------------------------- Geometric Functions --------------------------------

                        friend float Length ( const Vector4D& );

                        friend float Square ( const Vector4D& );

                        friend float Distance ( const Vector4D&, const Vector4D& );
               
                        friend float Dot ( const Vector4D&, const Vector4D& );    
               
                        friend Vector4D Normalize ( const Vector4D& );

                        friend Vector4D Reflect ( const Vector4D&, const Vector4D& );

                        friend Vector4D Refract ( const Vector4D&, const Vector4D&, float );

                        //-------------------------- Angle and Trigonometry Functions -------------------------

                        friend Vector4D Radians ( const Vector4D& );

                        friend Vector4D Degrees ( const Vector4D& );

                        friend Vector4D Sin ( const Vector4D& );

                        friend Vector4D Cos ( const Vector4D& );

                        friend Vector4D Tan ( const Vector4D& );

                        friend Vector4D Asin ( const Vector4D& );

                        friend Vector4D Acos ( const Vector4D& );

                        friend Vector4D Atan ( const Vector4D& );

                        //------------------------------- Exponential Functions -------------------------------

                        friend Vector4D Pow ( const Vector4D&, const Vector4D& );

                        friend Vector4D Pow ( const Vector4D&, float );

                        friend Vector4D Exp ( const Vector4D& );

                        friend Vector4D Log ( const Vector4D& );

                        friend Vector4D Sqrt ( const Vector4D& );
        };
}

#endif

