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

#ifndef _VECTOR2D_

#define _VECTOR2D_

#include "Util.h"

#include "Vector3D.h"

#include "Vector4D.h"

#include <iostream>

using namespace std;

namespace BMath
{
        class Vector3D;

        class Vector4D;

        class Vector2D
        {
                public:

                        //----------------------------------- Public Fields -----------------------------------

                        float X;

                        float Y;

                        //---------------------------------- Public Constants ---------------------------------

                        static const Vector2D Zero;

                        static const Vector2D Unit;

                        static const Vector2D AxisX;

                        static const Vector2D AxisY;

                        //------------------------------------ Constructors -----------------------------------

                        Vector2D ( float = 0, float = 0 );

                        Vector2D ( const float [SIZE2D] );

                        Vector2D ( const Vector2D& );

                        Vector2D ( const Vector3D& );

                        Vector2D ( const Vector4D& );

                        //-------------------------------- Arithmetic Operators -------------------------------
                       
                        friend Vector2D operator - ( const Vector2D& );

                        friend Vector2D operator + ( const Vector2D&, const Vector2D& );
                       
                        friend Vector2D operator - ( const Vector2D&, const Vector2D& );

                        friend Vector2D operator + ( const Vector2D&, float );
                       
                        friend Vector2D operator - ( const Vector2D&, float );

                        friend Vector2D operator + ( float, const Vector2D& );
                       
                        friend Vector2D operator - ( float, const Vector2D& );
                       
                        friend Vector2D operator * ( const Vector2D&, const Vector2D& );
                       
                        friend Vector2D operator / ( const Vector2D&, const Vector2D& );

                        friend Vector2D operator * ( const Vector2D&, float );

                        friend Vector2D operator / ( const Vector2D&, float );  

                        friend Vector2D operator * ( float, const Vector2D& );                          

                        friend Vector2D operator / ( float, const Vector2D& );

                        friend Vector2D operator += ( Vector2D&, const Vector2D& );
                       
                        friend Vector2D operator -= ( Vector2D&, const Vector2D& );

                        friend Vector2D operator += ( Vector2D&, float );

                        friend Vector2D operator -= ( Vector2D&, float );      

                        friend Vector2D operator *= ( Vector2D&, const Vector2D& );
                       
                        friend Vector2D operator /= ( Vector2D&, const Vector2D& );

                        friend Vector2D operator *= ( Vector2D&, float );

                        friend Vector2D operator /= ( Vector2D&, float );

                        //---------------------------------- Logic Operators ----------------------------------

                        friend bool operator < ( const Vector2D&, const Vector2D& );

                        friend bool operator > ( const Vector2D&, const Vector2D& );

                        friend bool operator < ( const Vector2D&, float );

                        friend bool operator > ( const Vector2D&, float );

                        friend bool operator < ( float, const Vector2D& );                              

                        friend bool operator > ( float, const Vector2D& );

                        friend bool operator <= ( const Vector2D&, const Vector2D& );

                        friend bool operator >= ( const Vector2D&, const Vector2D& );

                        friend bool operator <= ( const Vector2D&, float );

                        friend bool operator >= ( const Vector2D&, float );

                        friend bool operator <= ( float, const Vector2D& );                            

                        friend bool operator >= ( float, const Vector2D& );

                        friend bool operator == ( const Vector2D&, const Vector2D& );

                        friend bool operator != ( const Vector2D&, const Vector2D& );

                        friend bool operator == ( const Vector2D&, float );

                        friend bool operator != ( const Vector2D&, float );

                        friend bool operator == ( float, const Vector2D& );

                        friend bool operator != ( float, const Vector2D& );

                        //----------------------------- Input and Output Operators ----------------------------

                        friend istream& operator >> ( istream&, Vector2D& );

                        friend ostream& operator << ( ostream&, const Vector2D& );

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

                        friend Vector2D Abs ( const Vector2D& );

                        friend Vector2D Sign ( const Vector2D& );

                        friend Vector2D Floor ( const Vector2D& );

                        friend Vector2D Ceil ( const Vector2D& );

                        friend Vector2D Fract ( const Vector2D& );

                        friend Vector2D Mod ( const Vector2D&, const Vector2D& );

                        friend Vector2D Mod ( const Vector2D&, float );

                        friend Vector2D Mod ( float, const Vector2D& );

                        friend Vector2D Min ( const Vector2D&, const Vector2D& );

                        friend Vector2D Min ( const Vector2D&, float );

                        friend Vector2D Min ( float, const Vector2D& );

                        friend Vector2D Max ( const Vector2D&, const Vector2D& );

                        friend Vector2D Max ( const Vector2D&, float );

                        friend Vector2D Max ( float, const Vector2D& );

                        friend Vector2D Clamp ( const Vector2D&, const Vector2D&, const Vector2D& );

                        friend Vector2D Clamp ( const Vector2D&, float, float );

                        friend Vector2D Mix ( const Vector2D&, const Vector2D&, const Vector2D& );

                        friend Vector2D Mix ( const Vector2D&, const Vector2D&, float );

                        friend Vector2D Step ( const Vector2D&, const Vector2D& );

                        friend Vector2D Step ( const Vector2D&, float );

                        friend Vector2D Smooth ( const Vector2D&, const Vector2D&, const Vector2D& );

                        friend Vector2D Smooth ( const Vector2D&, float, float );

                        //-------------------------------- Geometric Functions --------------------------------

                        friend float Length ( const Vector2D& );

                        friend float Square ( const Vector2D& );

                        friend float Distance ( const Vector2D&, const Vector2D& );
               
                        friend float Dot ( const Vector2D&, const Vector2D& );    
               
                        friend Vector2D Normalize ( const Vector2D& );

                        friend Vector2D Reflect ( const Vector2D&, const Vector2D& );

                        friend Vector2D Refract ( const Vector2D&, const Vector2D&, float );

                        //-------------------------- Angle and Trigonometry Functions -------------------------

                        friend Vector2D Radians ( const Vector2D& );

                        friend Vector2D Degrees ( const Vector2D& );

                        friend Vector2D Sin ( const Vector2D& );

                        friend Vector2D Cos ( const Vector2D& );

                        friend Vector2D Tan ( const Vector2D& );

                        friend Vector2D Asin ( const Vector2D& );

                        friend Vector2D Acos ( const Vector2D& );

                        friend Vector2D Atan ( const Vector2D& );

                        //------------------------------- Exponential Functions -------------------------------

                        friend Vector2D Pow ( const Vector2D&, const Vector2D& );

                        friend Vector2D Pow ( const Vector2D&, float );

                        friend Vector2D Exp ( const Vector2D& );

                        friend Vector2D Log ( const Vector2D& );

                        friend Vector2D Sqrt ( const Vector2D& );
        };
}

#endif

