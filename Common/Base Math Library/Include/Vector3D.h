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

#ifndef _VECTOR3D_

#define _VECTOR3D_

#include "Util.h"

#include "Vector2D.h"

#include "Vector4D.h"

#include <iostream>

using namespace std;

namespace BMath
{
        class Vector2D;

        class Vector4D;

        class Vector3D
        {
                public:

                        //----------------------------------- Public Fields -----------------------------------

                        float X;

                        float Y;

                        float Z;

                        //---------------------------------- Public Constants ---------------------------------

                        static const Vector3D Zero;

                        static const Vector3D Unit;

                        static const Vector3D AxisX;

                        static const Vector3D AxisY;

                        static const Vector3D AxisZ;

                        //------------------------------------ Constructors -----------------------------------

                        Vector3D ( float = 0, float = 0, float = 0 );

                        Vector3D ( const float [SIZE3D] );

                        Vector3D ( const Vector2D&, float = 0 );

                        Vector3D ( const Vector3D& );

                        Vector3D ( const Vector4D& );

                        //-------------------------------- Arithmetic Operators -------------------------------
                        
                        friend Vector3D operator - ( const Vector3D& );

                        friend Vector3D operator + ( const Vector3D&, const Vector3D& );
                        
                        friend Vector3D operator - ( const Vector3D&, const Vector3D& );

                        friend Vector3D operator + ( const Vector3D&, float );
                        
                        friend Vector3D operator - ( const Vector3D&, float );

                        friend Vector3D operator + ( float, const Vector3D& );
                        
                        friend Vector3D operator - ( float, const Vector3D& );
                        
                        friend Vector3D operator * ( const Vector3D&, const Vector3D& );
                        
                        friend Vector3D operator / ( const Vector3D&, const Vector3D& );

                        friend Vector3D operator * ( const Vector3D&, float );

                        friend Vector3D operator / ( const Vector3D&, float );  

                        friend Vector3D operator * ( float, const Vector3D& );                          

                        friend Vector3D operator / ( float, const Vector3D& );

                        friend Vector3D operator += ( Vector3D&, const Vector3D& );
                        
                        friend Vector3D operator -= ( Vector3D&, const Vector3D& );

                        friend Vector3D operator += ( Vector3D&, float );

                        friend Vector3D operator -= ( Vector3D&, float );       

                        friend Vector3D operator *= ( Vector3D&, const Vector3D& );
                        
                        friend Vector3D operator /= ( Vector3D&, const Vector3D& );

                        friend Vector3D operator *= ( Vector3D&, float );

                        friend Vector3D operator /= ( Vector3D&, float );

                        //---------------------------------- Logic Operators ----------------------------------

                        friend bool operator < ( const Vector3D&, const Vector3D& );

                        friend bool operator > ( const Vector3D&, const Vector3D& );

                        friend bool operator < ( const Vector3D&, float );

                        friend bool operator > ( const Vector3D&, float );

                        friend bool operator < ( float, const Vector3D& );                              

                        friend bool operator > ( float, const Vector3D& );

                        friend bool operator <= ( const Vector3D&, const Vector3D& );

                        friend bool operator >= ( const Vector3D&, const Vector3D& );

                        friend bool operator <= ( const Vector3D&, float );

                        friend bool operator >= ( const Vector3D&, float );

                        friend bool operator <= ( float, const Vector3D& );                             

                        friend bool operator >= ( float, const Vector3D& );

                        friend bool operator == ( const Vector3D&, const Vector3D& );

                        friend bool operator != ( const Vector3D&, const Vector3D& );

                        friend bool operator == ( const Vector3D&, float );

                        friend bool operator != ( const Vector3D&, float );

                        friend bool operator == ( float, const Vector3D& );

                        friend bool operator != ( float, const Vector3D& );

                        //----------------------------- Input and Output Operators ----------------------------

                        friend istream& operator >> ( istream&, Vector3D& );

                        friend ostream& operator << ( ostream&, const Vector3D& );

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

                        friend Vector3D Abs ( const Vector3D& );

                        friend Vector3D Sign ( const Vector3D& );

                        friend Vector3D Floor ( const Vector3D& );

                        friend Vector3D Ceil ( const Vector3D& );

                        friend Vector3D Fract ( const Vector3D& );

                        friend Vector3D Mod ( const Vector3D&, const Vector3D& );

                        friend Vector3D Mod ( const Vector3D&, float );

                        friend Vector3D Mod ( float, const Vector3D& );

                        friend Vector3D Min ( const Vector3D&, const Vector3D& );

                        friend Vector3D Min ( const Vector3D&, float );

                        friend Vector3D Min ( float, const Vector3D& );

                        friend Vector3D Max ( const Vector3D&, const Vector3D& );

                        friend Vector3D Max ( const Vector3D&, float );

                        friend Vector3D Max ( float, const Vector3D& );

                        friend Vector3D Clamp ( const Vector3D&, const Vector3D&, const Vector3D& );

                        friend Vector3D Clamp ( const Vector3D&, float, float );

                        friend Vector3D Mix ( const Vector3D&, const Vector3D&, const Vector3D& );

                        friend Vector3D Mix ( const Vector3D&, const Vector3D&, float );

                        friend Vector3D Step ( const Vector3D&, const Vector3D& );

                        friend Vector3D Step ( const Vector3D&, float );

                        friend Vector3D Smooth ( const Vector3D&, const Vector3D&, const Vector3D& );

                        friend Vector3D Smooth ( const Vector3D&, float, float );

                        //-------------------------------- Geometric Functions --------------------------------

                        friend float Length ( const Vector3D& );

                        friend float Square ( const Vector3D& );

                        friend float Distance ( const Vector3D&, const Vector3D& );
                
                        friend float Dot ( const Vector3D&, const Vector3D& );

                        friend Vector3D Cross ( const Vector3D&, const Vector3D& );
                
                        friend Vector3D Normalize ( const Vector3D& );

                        friend Vector3D Reflect ( const Vector3D&, const Vector3D& );

                        friend Vector3D Refract ( const Vector3D&, const Vector3D&, float );

                        //-------------------------- Angle and Trigonometry Functions -------------------------

                        friend Vector3D Radians ( const Vector3D& );

                        friend Vector3D Degrees ( const Vector3D& );

                        friend Vector3D Sin ( const Vector3D& );

                        friend Vector3D Cos ( const Vector3D& );

                        friend Vector3D Tan ( const Vector3D& );

                        friend Vector3D Asin ( const Vector3D& );

                        friend Vector3D Acos ( const Vector3D& );

                        friend Vector3D Atan ( const Vector3D& );

                        //------------------------------- Exponential Functions -------------------------------

                        friend Vector3D Pow ( const Vector3D&, const Vector3D& );

                        friend Vector3D Pow ( const Vector3D&, float );

                        friend Vector3D Exp ( const Vector3D& );

                        friend Vector3D Log ( const Vector3D& );

                        friend Vector3D Sqrt ( const Vector3D& );
        };
}

#endif
