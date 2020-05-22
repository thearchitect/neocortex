/////////////////////////////////////////////////////
/// @file bezier_surface.h
///	    Bezier surface representation
///
/// @author Dmitry Kolzov
///
#ifndef BEZIER_SURFACE_H
#define BEZIER_SURFACE_H
#include <vector>
#include "vector.h"
#include "bezier_curve.h"

typedef unsigned int UINT;

namespace core
{
	////////////////////////////////////
	///
	///  BEZIER SURFACE CLASS: INTERFACE
	///
	template <typename T, size_t size> class bezier_surface
	{
		typedef vector<T, size> point;
	public:
		bezier_surface  ( const T* pdata, UINT upts, UINT vpts );
		bezier_surface  ( const point* ppts, UINT upts, UINT vpts );
		bezier_surface  ( const std::vector<point>& pts, UINT upts, UINT vpts );

		point operator()(const T& u, const T& v) const;
		/// Calculate tangent, normal and binormal
		void  tnb     ( const T& u, const T& v, vector<T,size>& t, vector<T,size>& n, vector<T,size>& b ) const; 
		void  split     (const T& u, const T& v, bezier_surface& p00, bezier_surface& p01, 
										         bezier_surface& p10, bezier_surface& p11);
	private:
		std::vector<point> _cp;
		UINT			   _nucp;
		UINT			   _nvcp;
	};

	/////////////////////////////////////////
	///
	///  BEZIER SURFACE CLASS: IMPLEMENTATION
	///
	template <typename T, size_t size> bezier_surface<T,size>::bezier_surface( const T* pdata, UINT upts, UINT vpts )
	{
		_nucp = upts;
		_nvcp = vpts;
		_cp.resize(_nucp * _nvcp);
		for (UINT i=0;i<_nucp*_nvcp;++i)
		{
			for (UINT j=0;j<size;++j)
				_cp[i][j] = pdata[i*size + j];
		}
	}

	template <typename T, size_t size> bezier_surface<T,size>::bezier_surface( const point* ppts, UINT upts, UINT vpts )
	{
		_nucp = upts;
		_nvcp = vpts;
		_cp.resize(_nucp * _nvcp);
		for (UINT i=0;i<_nucp*_nvcp;++i)
			_cp[i] = ppts[i];
	}

	template <typename T, size_t size> bezier_surface<T,size>::bezier_surface( const std::vector<point>& pts, UINT upts, UINT vpts )
	{
		_cp = pts;
		_nucp = upts;
		_nvcp = vpts;
	}

	template <typename T, size_t size> vector<T,size> bezier_surface<T,size>::operator()(const T& u, const T& v) const
	{
		std::vector<T> ucoefs(_nucp);
		std::vector<T> vcoefs(_nvcp);
		_bernstein_array<T,size>(u, &ucoefs[0], _nucp-1);
		_bernstein_array<T,size>(v, &vcoefs[0], _nvcp-1);

		point res = point();
		for (UINT i=0;i<_nucp;++i)
			for (UINT j=0;j<_nvcp;++j)
				res += ucoefs[i]*vcoefs[j]*_cp[i*_nvcp + j];

		return res;
	}

	template <typename T, size_t size> void bezier_surface<T,size>::tnb ( const T& u, const T& v, vector<T,size>& t, vector<T,size>& n, vector<T,size>& b ) const
	{
		std::vector<T> ucoefs(_nucp);
		std::vector<T> vcoefs(_nvcp);
		
		// dS/du
		_bernstein_array<T,size>(u, &ucoefs[0], _nucp-2);
		_bernstein_array<T,size>(v, &vcoefs[0], _nvcp-1);

		t = vector<T,size>();
		for (UINT j=0;j<_nvcp;++j)
			for (UINT i=0;i<_nucp-1;++i)
				t += vcoefs[j]*ucoefs[i]*(_cp[(i + 1)*_nvcp + j]-_cp[i*_nvcp + j]);
		t *= _nucp;
		t.normalize();

		// dS/dv
		_bernstein_array<T,size>(u, &ucoefs[0], _nucp-1);
		_bernstein_array<T,size>(v, &vcoefs[0], _nvcp-2);

		b = vector<T,size>();
		for (UINT i=0;i<_nucp;++i)
			for (UINT j=0;j<_nvcp-1;++j)
				b += ucoefs[i]*vcoefs[j]*(_cp[i*_nvcp + j + 1]-_cp[i*_nvcp + j]);
		b *= _nvcp;
		b.normalize();

		// n
		n = cross(t,b);
		n.normalize();
	}
};

#endif