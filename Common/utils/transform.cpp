#include "transform.h"

namespace core
{
	/// create transform from a matrix
	transform transform::create_transform( const REAL& m00, const REAL& m10, const REAL& m20, const REAL& m30 , 
		const REAL& m01 , const REAL& m11 , const REAL& m21 , const REAL& m31 ,
		const REAL& m02 , const REAL& m12 , const REAL& m22 , const REAL& m32 ,
		const REAL& m03 , const REAL& m13 , const REAL& m23 , const REAL& m33  )
	{
		return transform(m00, m10, m20, m30, m01, m11, m21, m31, m02, m12, m22, m32, m03, m13, m23, m33);
	}

	/// create transform using matrix and direct inverse
	transform transform::create_transform ( const matrix4x4& m, const matrix4x4 inv )
	{
		return transform(m,inv);
	}

	/// create translation
	transform transform::create_translation( const REAL& dx, const REAL& dy, const REAL& dz )
	{
		matrix4x4 m( 1, 0, 0, 0, 
			0, 1, 0, 0, 
			0, 0, 1, 0, 
			dx, dy, dz, 1);
		matrix4x4 inv ( 1, 0, 0, 0, 
			0, 1, 0, 0, 
			0, 0, 1, 0, 
			-dx, -dy, -dz, 1);
		return transform(m, inv);
	}

	/// create rotation
	transform transform::create_rotation ( axis ax, const REAL& ang )
	{
		switch (ax)
		{
		case X:
			{
				matrix4x4 m(1, 0, 0, 0, 
					0, cos(ang), sin(ang), 0,
					0, -sin(ang), cos(ang), 0,
					0, 0, 0, 1);
				matrix4x4 inv = m.transpose();
				return transform (m, inv);
			}			 
		case Y:
			{
				matrix4x4 m(cos(ang), 0, -sin(ang), 0,
					0, 1, 0, 0,
					sin(ang), 0, cos(ang), 0,
					0, 0, 0, 1);
				matrix4x4 inv = m.transpose();
				return transform (m, inv);
			}
		case Z:
			{
				matrix4x4 m(cos(ang), sin(ang), 0, 0,
					-sin(ang), cos(ang), 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
				matrix4x4 inv = m.transpose();
				return transform (m,inv);
			}
		}

		return transform();
	}

	//transform transform::create_rotation ( const vector4& axis, const REAL& ang )
	//{

	//}

	/// create custom scaling
	transform transform::create_scaling ( const REAL& sx, const REAL& sy, const REAL& sz )
	{
		return transform ( sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1 );
	}

}