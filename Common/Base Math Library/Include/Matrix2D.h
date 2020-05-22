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

#ifndef _MATRIX2D_

#define _MATRIX2D_

#include "Vector2D.h"

namespace BMath
{
        class Matrix2D
        {
                private:

                        //---------------------------------- Private Fields -----------------------------------

                        float values [SIZE2D][SIZE2D];

                public:

                        //--------------------------------- Public Constants ----------------------------------

                        static const Matrix2D Zero;

                        static const Matrix2D Unit;

                        //----------------------------------- Constructors ------------------------------------

                        Matrix2D ( float = 0 );

                        Matrix2D ( const float [SIZE2D] );

                        Matrix2D ( const Vector2D& );

                        Matrix2D ( const float [SIZE2D][SIZE2D] );

                        Matrix2D ( const Matrix2D& );

                        //------------------------------- Arithmetic Operators --------------------------------
                        
                        friend Matrix2D operator - ( const Matrix2D& );

                        friend Matrix2D operator + ( const Matrix2D&, const Matrix2D& );
                        
                        friend Matrix2D operator - ( const Matrix2D&, const Matrix2D& );

                        friend Matrix2D operator * ( const Matrix2D&, const Matrix2D& );
                        
                        friend Vector2D operator * ( const Matrix2D&, const Vector2D& );

                        friend Matrix2D operator * ( const Matrix2D&, float );

                        friend Matrix2D operator / ( const Matrix2D&, float );
                        
                        friend Matrix2D operator * ( float, const Matrix2D& );

                        friend Matrix2D operator / ( float, const Matrix2D& );

                        //----------------------------- Input and Output Operators ----------------------------

                        friend istream& operator >> ( istream&, Matrix2D& );

                        friend ostream& operator << ( ostream&, const Matrix2D& );

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
                        
                        friend float Determinant ( const Matrix2D& );

                        friend Matrix2D Transpose ( const Matrix2D& );

                        friend Matrix2D Adjugate ( const Matrix2D& );

                        friend Matrix2D Inverse ( const Matrix2D& );
        };
}

#endif
