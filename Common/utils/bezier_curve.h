/////////////////////////////////////////////////////
/// @file bezier_curve.h
///	    Bezier curve representation
///
/// @author Dmitry Kolzov
///
#ifndef BEZIER_CURVE_H
#define BEZIER_CURVE_H
#include <vector>
#include "vector.h"

typedef unsigned int UINT;

namespace core
{
	////////////////////////////////////
	///
	///  BEZIER CURVE CLASS: INTERFACE
	///
	template <typename T, size_t size> class bezier_curve
	{
		typedef vector<T, size> point;
	public:
		bezier_curve( const T* pdata, UINT npts );
		bezier_curve( const point* ppts, UINT npts );
		bezier_curve( const std::vector<point>& vpts );

		/// Evaluate curve at the specified parameter value
		point operator()(const T& v) const;
		/// Calculate tangent and normal
		void  tnb     ( const T& v, vector<T,size>& t, vector<T,size>& n, vector<T,size>& b ) const; 
		/// Split the curve at the parameter value
		void split(const T& v, bezier_curve& c1, bezier_curve& c2);

	private:
		/// Control points
		std::vector<point> _cp;
		/// Number of control points (curve degree = _ncp - 1)
		UINT			   _ncp;
	};

	/// Calculate all n-degree Bernstein polynomials (n+1 items)
	/// using recurrent formula B(i,n,u) = (1-u)*B(i,n-1,u) + u*B(i-1,n-1,u)
	template <typename T, size_t size> void _bernstein_array( const T& v, T* pcoefs, UINT n );

	///////////////////////////////////////
	///
	///  BEZIER CURVE CLASS: IMPLEMENTATION
	///
	template <typename T, size_t size> bezier_curve<T,size>::bezier_curve( const T* pdata, UINT npts )
	{
		_cp.resize(_ncp = npts);
		for (UINT i=0;i<npts;++i)
		{
			for (UINT j=0;j<size;++j)
				_cp[i][j] = pdata[i*size + j];
		}
	}

	template <typename T, size_t size> bezier_curve<T,size>::bezier_curve( const point* ppts, UINT npts )
	{
		_cp.resize(_ncp = npts);
		for (UINT i=0;i<_ncp;++i)
			_cp[i] = ppts[i];
	}

	template <typename T, size_t size> bezier_curve<T,size>::bezier_curve( const std::vector<point>& vpts )
	{
		_cp = vpts;
		_npts = _cp.size();
	}

	template <typename T, size_t size> vector<T,size> bezier_curve<T,size>::operator()(const T& v) const
	{
		std::vector<T> coefs(_ncp);
		_bernstein_array<T,size>(v, &coefs[0], _ncp - 1);

		point res = point();
		for (UINT i=0;i<_ncp;++i)
			res += coefs[i]*_cp[i];

		return res;
	}

	template <typename T, size_t size> void _bernstein_array( const T& v, T* pcoefs, UINT n )
	{
		memset(pcoefs, 0, sizeof(T)*n);
		
		T v1 = 1 - v;
		pcoefs[0] = v1;
		pcoefs[1] = v;

		T temp = T();

		for(UINT i=2; i<=n; ++i)
		{
			temp = pcoefs[0];
			pcoefs[0] *= v1;

			for(UINT j=1;j<=i;++j)
			{
				T temp1 = pcoefs[j];
				pcoefs[j] = v*temp + v1*pcoefs[j];
				temp = temp1;
			}
		}
	}

	/// Calculate tangent and normal
	template <typename T, size_t size> void  bezier_curve<T,size>::tnb( const T& v, vector<T,size>& t, vector<T,size>& n, vector<T,size>& b ) const
	{
		// TODO: add TNB generation instead of just tangent
		std::vector<T> coeffs(_ncp-1);
		_bernstein_array<T,size>(v, &coeffs[0], _ncp-2);

		t = vector<T,size>();
		for (UINT i=0;i<_ncp-1;++i)
			t += coeffs[i] * (_cp[i+1] - _cp[i]);

		t*=_ncp;
	}

};

#endif