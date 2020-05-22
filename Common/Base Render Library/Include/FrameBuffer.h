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

#ifndef _FRAME_BUFFER_

#define _FRAME_BUFFER_

#include "RenderBuffer.h"

#include "Texture2D.h"

#include <vector>

using namespace std;

namespace Render
{
        class FrameBuffer
        {
                private:

                        //----------------------------------- Buffer Handle -----------------------------------

                        unsigned Handle;

                public:

                        //--------------------------------- Buffer Attachments --------------------------------
                       
                        vector <Texture2D *> ColorBuffers;

                        vector <RenderBuffer *> RenderBuffers;

                        //--------------------------------- OpenGL Identifier ---------------------------------
                       
                        static const unsigned Target = GL_FRAMEBUFFER_EXT;

                        //----------------------------- Constructor and Destructor ----------------------------

                        FrameBuffer ( void );

                        ~FrameBuffer ( void );

                        //--------------------------------- Buffer Management ---------------------------------
                       
                        void Setup ( void );
                       
                        void Bind ( void );
                       
                        void Unbind ( void );

                        void FetchOutcome ( void );

                        //------------------------------------ Buffer Info ------------------------------------
                       
                        int GetHandle ( void ) const { return Handle; }
        };
}

#endif

