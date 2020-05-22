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

#ifndef _KEYBOARD_

#define _KEYBOARD_

#include "Camera.h"

namespace Render
{
        struct KeyboardState
        {
                //-------------------------------------- Moving Keys --------------------------------------

                bool KeyW;

                bool KeyS;

                bool KeyA;

                bool KeyD;

                bool KeyX;

                bool KeyZ;

                //------------------------------------- Rotation Keys -------------------------------------

                bool ArrowL;

                bool ArrowR;

                bool ArrowU;

                bool ArrowD;
        };

        class Keyboard
        {
                private:

                        //------------------------------ States of Control Keys -------------------------------
                        
                        KeyboardState State;

                public:

                        //--------------------------------- Minimum Move Step ---------------------------------

                        float Step;

                        //----------------- Space for Camera Transformation ( Local or World ) ----------------

                        bool Local;

                        //------------------------------------ Constructor ------------------------------------
                        
                        Keyboard ( float = 0.005F, bool = true );

                        //----------------------------------- Event Handler -----------------------------------

                        void StateChange ( int, int );

                        //------------------ Applying new Position and Orientation to Camera ------------------

                        void Apply ( Camera * );
        };
}

#endif
