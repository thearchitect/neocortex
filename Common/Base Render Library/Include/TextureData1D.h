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

#ifndef _TEXTURE_DATA_1D_

#define _TEXTURE_DATA_1D_

#include <GLee.h>

namespace Render
{
        class TextureData1D
        {
                private:

                        //----------------------------------- Pixels Array ------------------------------------

                        float * Pixels;

                        //----------------------------------- Texture Size ------------------------------------
                        
                        int Width;

                        //--------------------------------- Pixel Components ----------------------------------

                        int Components;
                
                public:

                        //----------------------------- Constructor and Destructor ----------------------------
                
                        TextureData1D ( int, int = 3 );
                        
                        ~TextureData1D ( void );

                        //---------------------------------- Type Conversion ----------------------------------

                        operator float * ( void ) { return Pixels; }
                        
                        operator const float * ( void ) const { return Pixels; }

                        //------------------------------------ Data Access ------------------------------------

                        template <class Type> Type& Pixel ( int );

                        //------------------------------------ Data Format ------------------------------------
                        
                        int GetPixelFormat ( void );

                        int GetInternalFormat ( void );

                        int GetType ( void ) { return GL_FLOAT; }
                        
                        int GetWidth ( void ) { return Width; }

                        int GetComponents ( void ) { return Components; }

                        //------------------------------------ Data Upload ------------------------------------

                        void Upload ( int target = GL_TEXTURE_1D );
        };

        //------------------------------------- Template Functions ------------------------------------
        
        template <class Type> Type& TextureData1D :: Pixel ( int x )
        {
                return ( Type& ) Pixels [x * Components];
        }
}

#endif
