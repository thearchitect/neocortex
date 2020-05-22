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

#ifndef _TEXTURE_2D_

#define _TEXTURE_2D_

#include "TextureData2D.h"

#include "FilterMode.h"

#include "WrapMode.h"

namespace Render
{
        class Texture2D
        {
                private:

                        //---------------------------------- Texture Handle -----------------------------------

                        unsigned Handle;

                        //--------------------------------- OpenGL Identifier ---------------------------------
                        
                        unsigned Target;

                        //----------------------------------- Texture Init ------------------------------------

                        void Init ( unsigned, TextureData2D *, unsigned );
                
                public:

                        //----------------------------------- Texture Unit ------------------------------------

                        unsigned Unit;

                        //----------------------------------- Texture Data ------------------------------------

                        TextureData2D * Data;

                        //---------------------------------- Texture Params -----------------------------------

                        FilterMode FilterMode;

                        WrapMode WrapMode;

                        //----------------------------- Constructor and Destructor ----------------------------

                        Texture2D ( unsigned = 0, unsigned = GL_TEXTURE_2D );

                        Texture2D ( TextureData2D *, unsigned = 0, unsigned = GL_TEXTURE_2D );
						
						Texture2D (	unsigned _Handle, unsigned _Height, unsigned _Width, unsigned _Components,
									unsigned _Target = GL_TEXTURE_2D, unsigned _Unit = 0);
						
						void SafeDestruction();

                        ~Texture2D ( void );

                        //--------------------------------- Texture Management --------------------------------
                        
                        void Setup ( void );

                        void Update ( void );

                        void Bind ( void );

                        void Unbind ( void );

                        //------------------------------------ Texture Info -----------------------------------
                        
                        unsigned GetHandle ( void ) const { return Handle; }

                        unsigned GetTarget ( void ) const { return Target; }

                        unsigned GetUnit ( void ) const { return Unit; }
        };
}

#endif
