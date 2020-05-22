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

#ifndef _RENDER_BUFFER_

#define _RENDER_BUFFER_

#include <GLee.h>

namespace Render
{
        class RenderBuffer
        {
                private:

                        //----------------------------------- Buffer Handle -----------------------------------

                        unsigned Handle;

                public:

                        //------------------------------------ Buffer Size ------------------------------------
                        
                        unsigned Width;
                        
                        unsigned Height;

                        //------------------------------- Buffer Type and Format ------------------------------

                        unsigned Attachment;
                        
                        unsigned InternalFormat;

                        //--------------------------------- OpenGL Identifier ---------------------------------
                        
                        static const unsigned Target = GL_RENDERBUFFER;

                        //----------------------------- Constructor and Destructor ----------------------------

                        RenderBuffer ( unsigned = 512,
                                           unsigned = 512,
                                                   unsigned = GL_DEPTH_ATTACHMENT,
                                                   unsigned = GL_DEPTH_COMPONENT16 );

                        ~RenderBuffer ( void );

                        //--------------------------------- Buffer Management ---------------------------------
                        
                        void Setup ( void );

                        void Bind ( void );
                        
                        void Unbind ( void );

                        //------------------------------------ Buffer Info ------------------------------------
                        
                        int GetHandle ( void ) const { return Handle; }
        };
}

#endif
