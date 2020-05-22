/*
   Base Render Library   
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

#ifndef _SHADER_MANAGER_

#define _SHADER_MANAGER_

#include "Matrix2D.h"

#include "Matrix3D.h"

#include "Matrix4D.h"

#include "Texture1D.h"

#include "Texture2D.h"

#include "Texture3D.h"

using namespace BMath;

namespace Render
{
        class ShaderManager
        {
                private:

                        //---------------------------------- Private Fields -----------------------------------

                        int Vertex;

                        int Fragment;

                        int Program;

                        //---------------------------------- Private Methods ----------------------------------

                        bool Load ( int, const char **, int, const char * = "" );

                        bool Compile ( int );

                        bool Attach ( int );

                public:

                        //----------------------------- Constructor and Destructor ----------------------------

                        ShaderManager( void );
                        
                        ~ShaderManager( void );

                        //--------------------------------- Shaders Management --------------------------------

                        bool LoadVertexShader ( const char *, const char * = "" );

                        bool LoadFragmentShader ( const char *, const char * = "" );

                        bool LoadVertexShader ( const char **, int, const char * = "" );

                        bool LoadFragmentShader ( const char **, int, const char * = "" );

                        bool BuildProgram ( void );

                        void Bind ( void );
                        
                        void Unbind ( void );

                        //------------------------------- Input and Output Data -------------------------------

						int GetVertexHandle();

						int GetFragmentHandle();

						int GetProgramHandle();

                        int GetUniformLocation ( char * );
                        
                        int GetAttributeLocation ( char * );
                        
                        Vector4D GetUniformVector ( char * );
                        
                        Vector4D GetUniformVector ( int );
                        
                        Vector4D GetAttributeVector ( char * );
                        
                        Vector4D GetAttributeVector ( int );
        
                        bool SetUniformInteger ( const char *, int );

                        bool SetUniformInteger ( int, int );

                        bool SetUniformFloat ( const char *, float );

                        bool SetUniformFloat ( int, float );

                        bool SetUniformVector ( const char *, const Vector2D& );

                        bool SetUniformVector ( int, const Vector2D& );

                        bool SetUniformVector ( const char *, const Vector3D& );

                        bool SetUniformVector ( int, const Vector3D& );

                        bool SetUniformVector ( const char *, const Vector4D& );

                        bool SetUniformVector ( int, const Vector4D& );

                        bool SetUniformMatrix ( const char *, const Matrix2D& );

                        bool SetUniformMatrix ( int, const Matrix2D& );

                        bool SetUniformMatrix ( const char *, const Matrix3D& );

                        bool SetUniformMatrix ( int, const Matrix3D& );

                        bool SetUniformMatrix ( const char *, const Matrix4D& );

                        bool SetUniformMatrix ( int, const Matrix4D& );
                        
                        bool SetTexture ( int, const Texture1D * );

                        bool SetTexture ( const char *, const Texture1D * );

                        bool SetTexture ( int, const Texture2D * );

                        bool SetTexture ( const char *, const Texture2D * );

                        bool SetTexture ( int, const Texture3D * );

                        bool SetTexture ( const char *, const Texture3D * );

                        bool SetAttributeName ( int, const char * );

                        bool SetAttributeFloat ( const char *, float );

                        bool SetAttributeFloat ( int, float );

                        bool SetAttributeVector ( const char *, const Vector2D& );

                        bool SetAttributeVector ( int, const Vector2D& );

                        bool SetAttributeVector ( const char *, const Vector3D& );

                        bool SetAttributeVector ( int, const Vector3D& );

                        bool SetAttributeVector ( const char *, const Vector4D& );

                        bool SetAttributeVector ( int, const Vector4D& );
        };
}

#endif
