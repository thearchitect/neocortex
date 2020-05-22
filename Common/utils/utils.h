/////////////////////////////////////////////////////
/// @file utils.h
///	    Various utility functions
///
/// @author Dmitry Kolzov
///
#ifndef utils_H
#define utils_H

#include "common_defs.h"
#include <time.h>
#include <stdlib.h>

namespace core
{
	/// Convert 3d vector to homogenous point to apply trasnform to
	inline vector4 vector_to_point( const vector3& v ) { return vector4(v.x(), v.y(), v.z(), REAL(1)); }
	
	/// Convert 3d vector to homogenous vector to apply transform to
	/// Note that normal transforms should be declared explicitly 
	inline vector4 vector_to_vector( const vector3& v ) { return vector4(v.x(), v.y(), v.z(), REAL(0)); }

	/// Initialize RNG
	inline void    rand_init() {srand((unsigned)time(0));}

	/// Generate random float value within [0,1] range
	inline REAL    rand_float() { return (REAL)rand()/RAND_MAX; }

	/// Genarate random uint value
	inline UINT	   rand_uint() { return (UINT)rand(); }

	/// Convert cartesian coordinates to spherical
	inline void    cartesian_to_spherical ( const vector3& cart, REAL& r, REAL& phi, REAL& theta )
	{
		REAL temp = atan2(cart.x(), cart.z());
		r = sqrt(cart.x()*cart.x() + cart.y()*cart.y() + cart.z()*cart.z());
		phi = (temp >= 0)?temp:(temp + 2*M_PI);
		theta = acos(cart.y()/r);
	}

	/// Convert cartesian coordinates to spherical
	inline void    cartesian_to_spherical ( const vector3& cart, vector3& sph ) 
	{
		cartesian_to_spherical(cart, sph.x(), sph.y(), sph.z());
	}

	/// Convert spherical coordinates to cartesian 
	inline void    spherical_to_cartesian ( const REAL& r, const REAL& phi, const REAL& theta, vector3& cart )
	{
		cart.y() = r * cosf(theta);
		cart.z() = r * sinf(theta) * cosf(phi);
		cart.x() = r * sinf(theta) * sinf(phi);
	}

	/// Convert spherical coordinates to cartesian 
	inline void    spherical_to_cartesian ( const vector3& sph, vector3& cart )
	{
		spherical_to_cartesian(sph.x(), sph.y(), sph.z(), cart); 
	}

	/// Solve quadratic equation
	/// Returns false in case of no real roots exist
	/// true otherwise
	bool    SolveQuadratic( const REAL& a, const REAL& b, const REAL&c, REAL& x1, REAL& x2 );
}

#endif