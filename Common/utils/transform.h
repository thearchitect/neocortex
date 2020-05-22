/////////////////////////////////////////////////////
/// @file transform.h
///	    Transformation routines
///
/// @author Dmitry Kolzov
/// 
#ifndef geometry_H
#define geometry_H

#include "common_defs.h"

namespace core
{
	// Transform class 
	class transform
	{
	public:
		// rotation axis type
		enum axis { X, Y, Z };
		
		// factory methods: transform construction
		// this method assumes the matrix is in column major order
		// be careful while specifying matrix components
		static transform create_transform( const REAL& m00 = 1.0, const REAL& m10 = 0.0, const REAL& m20 = 0.0, const REAL& m30 = 0.0, 
			   const REAL& m01 = 0.0, const REAL& m11 = 1.0, const REAL& m21 = 0.0, const REAL& m31 = 0.0,
			   const REAL& m02 = 0.0, const REAL& m12 = 0.0, const REAL& m22 = 1.0, const REAL& m32 = 0.0,
			   const REAL& m03 = 0.0, const REAL& m13 = 0.0, const REAL& m23 = 0.0, const REAL& m33 = 1.0 );
		
		// this method allows performance optimizations
		// in the cases where matrix invesre may
		// be computed in some simple way
		static transform create_transform ( const matrix4x4& m, const matrix4x4 inv );
		
		// create translation transform
		static transform create_translation( const REAL& dx, const REAL& dy, const REAL& dz );
		
		// create rotation around coordinate axis
		static transform create_rotation ( axis ax, const REAL& ang );
		
		// create rotation around arbitrary axis
		/*static transform create_rotation ( const vector4& axis, const REAL& ang );*/
		
		// create scaling transform
		static transform create_scaling ( const REAL& sx, const REAL& sy, const REAL& sz );

		// apply transform to four component vector
		vector4 operator ()( const vector4& v ) const { return _m*v; }

		// create inverse transform
		transform inverse() const { return transform (_inv, _m);}
		
	private:
		// direct constructor
		// calls matrix4x4::inverse() method, performance penalty could be introduced
		transform (const REAL& m00 = 1.0, const REAL& m10 = 0.0, const REAL& m20 = 0.0, const REAL& m30 = 0.0, 
			   const REAL& m01 = 0.0, const REAL& m11 = 1.0, const REAL& m21 = 0.0, const REAL& m31 = 0.0,
			   const REAL& m02 = 0.0, const REAL& m12 = 0.0, const REAL& m22 = 1.0, const REAL& m32 = 0.0,
			   const REAL& m03 = 0.0, const REAL& m13 = 0.0, const REAL& m23 = 0.0, const REAL& m33 = 1.0) : 
		_m(m00,m10,m20,m30,m01,m11,m21,m31,m02,m12,m22,m32,m03,m13,m23,m33) {_inv = _m.inverse();}
		
		// constructor from two matrices
		transform ( const matrix4x4& m, const matrix4x4& inv ) : _m(m), _inv(inv){}
		
		// direct transform
		matrix4x4 _m;
		// invesrse transform
		matrix4x4 _inv;
	};
}

#endif