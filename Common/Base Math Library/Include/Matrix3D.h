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

#ifndef _MATRIX3D_

#define _MATRIX3D_

#include "Vector3D.h"

namespace BMath
{
        class Matrix3D
        {
                private:

                        //---------------------------------- Private Fields -----------------------------------

                        float values [SIZE3D][SIZE3D];

                public:

                        //--------------------------------- Public Constants ----------------------------------

                        static const Matrix3D Zero;

                        static const Matrix3D Unit;

                        //----------------------------------- Constructors ------------------------------------

                        Matrix3D ( float = 0 );

                        Matrix3D ( const float [SIZE3D] );

                        Matrix3D ( const Vector3D& );

                        Matrix3D ( const float [SIZE3D][SIZE3D] );

                        Matrix3D ( const Matrix3D& );

                        //------------------------------- Arithmetic Operators --------------------------------
                        
                        friend Matrix3D operator - ( const Matrix3D& );

                        friend Matrix3D operator + ( const Matrix3D&, const Matrix3D& );
                        
                        friend Matrix3D operator - ( const Matrix3D&, const Matrix3D& );

                        friend Matrix3D operator * ( const Matrix3D&, const Matrix3D& );
                        
                        friend Vector3D operator * ( const Matrix3D&, const Vector3D& );

                        friend Matrix3D operator * ( const Matrix3D&, float );

                        friend Matrix3D operator / ( const Matrix3D&, float );
                        
                        friend Matrix3D operator * ( float, const Matrix3D& );

                        friend Matrix3D operator / ( float, const Matrix3D& );

                        //----------------------------- Input and Output Operators ----------------------------

                        friend istream& operator >> ( istream&, Matrix3D& );

                        friend ostream& operator << ( ostream&, const Matrix3D& );

                        //-------------------------------- Auxiliary Operators --------------------------------

                        float * operator [] ( int index )
                        {
                                return &values [index][0];
                        }

                        const float * operator [] ( int index ) const
                        {
                                return &values [index][0];
                        }

                        //---------------------------------- Common Functions ---------------------------------
                        
                        friend float Determinant ( const Matrix3D& );

                        friend Matrix3D Transpose ( const Matrix3D& );

                        friend Matrix3D Adjugate ( const Matrix3D& );

                        friend Matrix3D Inverse ( const Matrix3D& );

                        //--------------------------------- Specific Functions --------------------------------

                        static Matrix3D MirrorX ( void );
                        
                        static Matrix3D MirrorY ( void );
                        
                        static Matrix3D MirrorZ ( void );

                        static Matrix3D RotateX ( float );
                        
                        static Matrix3D RotateY ( float );
                        
                        static Matrix3D RotateZ ( float );

                        static Matrix3D Rotate ( float, const Vector3D& );
                        
                        static Matrix3D Rotate ( const Vector3D& );

                        static Matrix3D ScaleX ( float );
                        
                        static Matrix3D ScaleY ( float );
                        
                        static Matrix3D ScaleZ ( float );
                        
                        static Matrix3D Scale ( const Vector3D& );
        };
}

#endif
