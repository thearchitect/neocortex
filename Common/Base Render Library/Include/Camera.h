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

#ifndef _CAMERA_

#define _CAMERA_

#include "ShaderManager.h"

using namespace BMath;

namespace Render
{
        class Camera
        {
                private:

                        //------------------------ Position and Orientation of Camera -------------------------

                        Vector3D Position;

                        Vector3D Orientation;

                        //------------------------- Axes of Camera Coordinate System --------------------------

                        Vector3D Side;

                        Vector3D Up;

                        Vector3D View;

                        //------------------------------- View Frustum Settings -------------------------------
                        
                        float FieldOfView;

                        float NearPlane;                        
                        
                        float FarPlane;

                        //--------------------------------- Viewport Settings ---------------------------------
                        
                        unsigned Width;

                        unsigned Height;                        
                        
                        float Aspect;

                        //--------------------- Updating Axes of Camera Coordinate System ---------------------
                        
                        void Update ( void );
               
                public:                 

                        //------------------------------------ Constructor ------------------------------------

                        Camera ( const Vector3D& = Vector3D :: Zero,
                                     const Vector3D& = Vector3D :: Zero );

                        //--------------------- Moving and Rotating Camera in World Space ---------------------

                        void MoveStraight ( float );

                        void MoveHorizontal ( float );

                        void MoveVertical ( float );
                        
                        void Rotate ( const Vector3D& );
                        
                        //---------------------- Applying Settings to OpenGL and Shaders ----------------------

                        void Setup ( void );

                        void SetShaderData ( ShaderManager * );

                        //--------------------------- Setting Viewport and Frustum ----------------------------

                        void SetViewport ( unsigned = 512, unsigned = 512 );

                        void SetFrustum ( float = ONEPI / 3.0F, float = 0.01F, float = 1000000.0F );

                        //--------------------------------- Getting Settings ----------------------------------

                        unsigned GetWidth ( void ) { return Width; }

                        unsigned GetHeight ( void ) { return Height; }

                        //-------------------------------------------------------------------------------------

                        float GetFieldOfView ( void ) { return FieldOfView; }

                        float GetNearPlane ( void ) { return NearPlane; }

                        float GetFarPlane ( void ) { return FarPlane; }

                        //-------------------------------------------------------------------------------------

                        const Vector3D& GetPosition ( void ) { return Position; }

                        const Vector3D& GetOrientation ( void ) { return Orientation; }

                        //-------------------------------------------------------------------------------------

                        const Vector3D& GetSide ( void ) { return Side; }

                        const Vector3D& GetUp ( void ) { return Up; }

                        const Vector3D& GetView ( void ) { return View; }

                        //-------------------------------------------------------------------------------------

                        Vector2D GetScreenScale ( void );

                        Vector2D GetPixelSize ( void );
        };
}

#endif
