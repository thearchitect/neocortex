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

#ifndef _MATRIX4D_

#define _MATRIX4D_

#include "Vector4D.h"

namespace BMath
{
        class Matrix4D
        {
                private:

                        //---------------------------------- Private Fields -----------------------------------

                        float values [SIZE4D][SIZE4D];

                public:

                        //--------------------------------- Public Constants ----------------------------------

                        static const Matrix4D Zero;

                        static const Matrix4D Unit;

                        //----------------------------------- Constructors ------------------------------------

                        Matrix4D ( float = 0 );

                        Matrix4D ( const float [SIZE4D] );

                        Matrix4D ( const Vector4D& );

                        Matrix4D ( const float [SIZE4D][SIZE4D] );

                        Matrix4D ( const Matrix4D& );

                        //-------------------------------- Arithmetic Operators -------------------------------
               
                        friend Matrix4D operator - ( const Matrix4D& );

                        friend Matrix4D operator + ( const Matrix4D&, const Matrix4D& );
                       
                        friend Matrix4D operator - ( const Matrix4D&, const Matrix4D& );

                        friend Matrix4D operator * ( const Matrix4D&, const Matrix4D& );
                       
                        friend Vector4D operator * ( const Matrix4D&, const Vector4D& );

                        friend Matrix4D operator * ( const Matrix4D&, float );

                        friend Matrix4D operator / ( const Matrix4D&, float );
                       
                        friend Matrix4D operator * ( float, const Matrix4D& );

                        friend Matrix4D operator / ( float, const Matrix4D& );

                        //----------------------------- Input and Output Operators ----------------------------

                        friend istream& operator >> ( istream&, Matrix4D& );

                        friend ostream& operator << ( ostream&, const Matrix4D& );

                        //-------------------------------- Auxiliary Operators --------------------------------

                        float * operator [] ( int index )
                        {
                                return &values [index][0];
                        }

                        const float * operator [] ( int index ) const
                        {
                                return &values [index][0];
                        }

                        //--------------------------------- Common Functions ----------------------------------
                       
                        friend float Determinant ( const Matrix4D& );

                        friend Matrix4D Transpose ( const Matrix4D& );

                        friend Matrix4D Adjugate ( const Matrix4D& );

                        friend Matrix4D Inverse ( const Matrix4D& );
        };
}

#endif

