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

#ifndef _MOUSE_

#define _MOUSE_

#include "Camera.h"

namespace Render
{
        class Mouse
        {
                private:

                        //---------------------------------- Mouse Location -----------------------------------
                        
                        int LocationX;
                        
                        int LocationY;

                        //-------------------------------- Location Difference --------------------------------

                        int DeltaX;
                        
                        int DeltaY;

                        //--------------------------------- Mouse Active Flag ---------------------------------

                        bool Active;

                public:

                        //------------------------------- Minimum Rotation Step -------------------------------

                        float Step;

                        //----------------- Space for Camera Transformation ( Local or World ) ----------------

                        bool Local;

                        //------------------------------------ Constructor ------------------------------------
                        
                        Mouse ( float = 0.005F, bool = true );

                        //---------------------------------- Event Handlers -----------------------------------
                        
                        void StateChange ( int, int );
                        
                        void MouseMove ( int, int );

                        //------------------ Applying new Position and Orientation to Camera ------------------

                        void Apply ( Camera * );
        };
}

#endif
