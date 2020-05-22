/////////////////////////////////////////////////////
/// @file matrix.h
///	    Describes the entity representing R^n^n element
///
/// @author Dmitry Kolzov
///
#ifndef matrix_base_H
#define matrix_base_H

#include <cmath>
#include <string.h>
#include "vector.h"

namespace core
{
	////////////////////////////////////
	///
	/// matrix_base CLASS: INTERFACE
	///
	template <typename T, size_t W, size_t H> class matrix_base
	{
	public:
		// constructors and factory methods
		matrix_base();
		matrix_base(const matrix_base<T,W,H>& other);
		matrix_base(const T* data);

		// unary operators
		T& operator ()(int i, int j);
		T operator ()(int i, int j) const;
		matrix_base<T,W,H> operator-() const;
		matrix_base<T,H,W> transpose() const;
		matrix_base<T,H,W> inverse() const;
		T trace() const;

		// binary operators
		matrix_base<T,W,H>& operator += (const matrix_base<T,W,H>& other);
		matrix_base<T,W,H>& operator -= (const matrix_base<T,W,H>& other);
		matrix_base<T,W,H>& operator *= (const matrix_base<T,W,W>& other);
		matrix_base<T,W,H>& operator *= (const T& c);
		
	private:
		T _m[H][W];
	};

	////////////////////////////////////
	///
	/// vector_base CLASS: IMPLEMENTATION
	///
	template <typename T, size_t W, size_t H> matrix_base<T,W,H>::matrix_base() { memset(_m, T(), sizeof(_m)); }
	template <typename T, size_t W, size_t H> matrix_base<T,W,H>::matrix_base(const matrix_base<T,W,H>& other) { memcpy(_m, other._m, sizeof(_m)); }
	template <typename T, size_t W, size_t H> matrix_base<T,W,H>::matrix_base(const T* data) { memcpy(_m, data, sizeof(_m)); }

	template <typename T, size_t W, size_t H> T& matrix_base<T,W,H>::operator()(int i, int j) {return _m[i][j];}
	template <typename T, size_t W, size_t H> T  matrix_base<T,W,H>::operator()(int i, int j) const {return _m[i][j];}
	template <typename T, size_t W, size_t H> matrix_base<T,W,H> matrix_base<T,W,H>::operator -() const
	{
		matrix_base<T,W,H> res = *this;
		for(int i=0;i<H;++i)
			for (int j=0;j<W;++j)
				res._m[i][j] = -_m[i][j];	
		return res;
	}

	template <typename T, size_t W, size_t H> matrix_base<T,H,W> matrix_base<T,W,H>::transpose() const
	{
		matrix_base<T,H,W> res;

		for (int i=0;i<H;++i)
			for (int j=0;j<W;++j)
				res(j,i) = _m[i][j];

		return res;
	}

	template <typename T, size_t W, size_t H> matrix_base<T,H,W> matrix_base<T,W,H>::inverse() const
	{
		// FIXME: not implemeneted yet
		return matrix_base<T,W,H>();
	}
	template <typename T, size_t W, size_t H> matrix_base<T,W,H>& matrix_base<T,W,H>::operator += (const matrix_base<T,W,H>& other)
	{
		for(int i=0;i<H;++i)
			for (int j=0;j<W;++j)
				_m[i][j] += other._m[i][j];	
		return *this;
	}
	template <typename T, size_t W, size_t H> matrix_base<T,W,H>& matrix_base<T,W,H>::operator -= (const matrix_base<T,W,H>& other)
	{
		for(int i=0;i<H;++i)
			for (int j=0;j<W;++j)
				_m[i][j] -= other._m[i][j];	
		return *this;
	}
	template <typename T, size_t W, size_t H> matrix_base<T,W,H>& matrix_base<T,W,H>::operator *= (const matrix_base<T,W,W>& other)
	{
		matrix_base<T,W,H> temp;
		for (int i=0;i<H;++i)
		{
			for (int j=0;j<W;++j)
			{
				temp(i,j) = T();
				for (int k=0;k<W;++k)
					temp(i,j) += _m[i][k] * other._m[k][j];
			}
		}
		*this = temp;
		return *this;
	}
	template <typename T, size_t W, size_t H> matrix_base<T,W,H>& matrix_base<T,W,H>::operator *= (const T& c)
	{
		for(int i=0;i<H;++i)
			for (int j=0;j<W;++j)
				_m[i][j] *= c;	
		return *this;
	}

	template <typename T, size_t W, size_t H> matrix_base<T,W,H> operator+(const matrix_base<T,W,H>& m1, const matrix_base<T,W,H>& m2)
	{
		matrix_base<T,W,H> res = m1;
		return res+=m2;
	}
	template <typename T, size_t W, size_t H> matrix_base<T,W,H> operator-(const matrix_base<T,W,H>& m1, const matrix_base<T,W,H>& m2)
	{
		matrix_base<T,W,H> res = m1;
		return res-=m2;
	}
	template <typename T, size_t W, size_t H, size_t K> matrix_base<T,W,H> operator*(const matrix_base<T,K,H>& m1, const matrix_base<T,W,K>& m2)
	{
		matrix_base<T,W,H> res;

		for (int i=0;i<H;++i)
		{
			for (int j=0;j<W;++j)
			{
				res(i,j) = T();
				for (int k=0;k<K;++k)
					res(i,j)+= m1(i,k)*m2(k,j);
			}
		}

		return res;
	}
	template <typename T, size_t W, size_t H> matrix_base<T,W,H> operator*(const matrix_base<T,W,H>& m, const T& c)
	{
		matrix_base<T,W,H> res = m;
		return res*=c;
	}
	template <typename T, size_t W, size_t H> matrix_base<T,W,H> operator*(const T& c, const matrix_base<T,W,H>& m)
	{
		matrix_base<T,W,H> res = m;
		return res*=c;
	}

	template <typename T, size_t W, size_t H> vector_base<T,H> operator* (const matrix_base<T,W,H>& m, const vector_base<T,W>& v )
	{
		vector_base<T,W> res;

		for (int i=0;i<H;++i)
		{
			res[i] = T();
			for (int j=0;j<W;++j)
				res[i] += m(i,j) * v[j]; 
		}

		return res;
	}

	// back-end class for vector-base
	template <typename T, size_t W, size_t H> class matrix : public matrix_base<T,W,H>
	{
	public:
		// constructors and factory methods
		matrix();
		matrix(const matrix_base<T,W,H>& other);
		matrix(const T* data);
	};

	// specializations 
	template<typename T> class matrix<T,2,2> : public matrix_base<T,2,2>
	{
        typedef matrix_base<T,2,2> matrix_base;
	public:
		// constructors and factory methods
		// vector():vector_base(){}
		matrix(const matrix_base& other):matrix_base(other){}
		matrix(const T* data):matrix_base(data){}
		matrix(const T& m00 = T(), const T& m10 = T(), const T& m01 = T(), const T& m11 = T())
		{
			((*this))(0,0) = m00; ((*this))(1,0) = m10; (*this)(0,1) = m01; (*this)(1,1) = m11;
		}

		T trace() const
		{
			return (*this)(0,0) + (*this)(1,1);  
		}
	};

	// specializations 
	template<typename T> class matrix<T,3,3> : public matrix_base<T,3,3>
	{
        typedef matrix_base<T,3,3> matrix_base;
	public:
		// constructors and factory methods
		// vector():vector_base(){}
		matrix(const matrix_base& other):matrix_base(other){}
		matrix(const T* data):matrix_base(data){}
		matrix(const T& m00 = T(), const T& m10 = T(), const T& m20 = T(), const T& m01 = T(), const T& m11 = T(), const T& m21 = T(),
			   const T& m02 = T(), const T& m12 = T(), const T& m22 = T())
		{
			(*this)(0,0) = m00; (*this)(1,0) = m10; (*this)(2,0) = m20;
			(*this)(0,1) = m01; (*this)(1,1) = m11; (*this)(2,1) = m21;
			(*this)(0,2) = m02; (*this)(1,2) = m12; (*this)(2,2) = m22;
	
		}

		T trace() const
		{
			return (*this)(0,0) + (*this)(1,1) + (*this)(2,2);  
		}
	};

		// specializations 
	template<typename T> class matrix<T,4,4> : public matrix_base<T,4,4>
	{
        typedef matrix_base<T,4,4> matrix_base;
	public:
		// constructors and factory methods
		// vector():vector_base(){}
		matrix(const matrix_base& other):matrix_base(other){}
		matrix(const T* data):matrix_base(data){}
		matrix(const T& m00 = T(), const T& m10 = T(), const T& m20 = T(), const T& m30 = T(), 
			   const T& m01 = T(), const T& m11 = T(), const T& m21 = T(), const T& m31 = T(),
			   const T& m02 = T(), const T& m12 = T(), const T& m22 = T(), const T& m32 = T(),
			   const T& m03 = T(), const T& m13 = T(), const T& m23 = T(), const T& m33 = T())
		{
			(*this)(0,0) = m00; (*this)(1,0) = m10; (*this)(2,0) = m20; (*this)(3,0) = m30;
			(*this)(0,1) = m01; (*this)(1,1) = m11; (*this)(2,1) = m21; (*this)(3,1) = m31;
			(*this)(0,2) = m02; (*this)(1,2) = m12; (*this)(2,2) = m22; (*this)(3,2) = m32;
			(*this)(0,3) = m03; (*this)(1,3) = m13; (*this)(2,3) = m23; (*this)(3,3) = m33;
		}

		T trace() const
		{
			return (*this)(0,0) + (*this)(1,1) + (*this)(2,2) + (*this)(3,3);  
		}
	};
}

#endif