/////////////////////////////////////////////////////
/// @file vector.h
///	    Describes the entity representing R^n element
///
/// @author Dmitry Kolzov
///
#ifndef vector_base_H
#define vector_base_H

#include <cmath>

namespace core
{
	////////////////////////////////////
	///
	/// vector_base CLASS: INTERFACE
	///
	template <typename T, size_t size> class vector_base
	{
	public:
		// constructors and factory methods
		vector_base();
		vector_base(const vector_base<T,size>& other);
		vector_base(const T* data);

		// unary operators
		T& operator [](int i);
		T operator [](int i) const;
		vector_base<T,size> operator-() const;
		T			   sq_norm() const;
		vector_base<T,size>& normalize() {return (*this)/=(sqrt(sq_norm()));} 
		//size_t		   size() const;

		// binary operators
		vector_base<T,size>& operator += (const vector_base<T,size>& other);
		vector_base<T,size>& operator -= (const vector_base<T,size>& other);
		vector_base<T,size>& operator *= (const vector_base<T,size>& other);
		vector_base<T,size>& operator *= (const T& c);
		vector_base<T,size>& operator /= (const T& c);
		
	private:
		T _v[size];
	};

	////////////////////////////////////
	///
	/// vector_base CLASS: IMPLEMENTATION
	///
	template <typename T, size_t size> vector_base<T,size>::vector_base() { memset(_v, 0, sizeof(_v)); }
	template <typename T, size_t size> vector_base<T,size>::vector_base(const vector_base<T,size>& other) { memcpy(_v, other._v, sizeof(_v)); }
	template <typename T, size_t size> vector_base<T,size>::vector_base(const T* data) { memcpy(_v, data, sizeof(_v)); }

	template <typename T, size_t size> T& vector_base<T,size>::operator[](int i) {return _v[i];}
	template <typename T, size_t size> T  vector_base<T,size>::operator[](int i) const {return _v[i];}
	template <typename T, size_t size> vector_base<T,size> vector_base<T,size>::operator -() const
	{
		vector_base<T,size> res = *this;
		for(int i=0;i<size;++i)
			res._v[i] = -_v[i];	
		return res;
	}
	template <typename T, size_t size> T vector_base<T,size>::sq_norm() const
	{
		T res = T();
		for(int i=0;i<size;++i)
			res += _v[i]*_v[i];
		return res;
	}

	template <typename T, size_t size> vector_base<T,size>& vector_base<T,size>::operator += (const vector_base<T,size>& other)
	{
		for(int i=0;i<size;++i)
			_v[i]+=other._v[i];
		return *this;
	}
	template <typename T, size_t size> vector_base<T,size>& vector_base<T,size>::operator -= (const vector_base<T,size>& other)
	{
		for(int i=0;i<size;++i)
			_v[i]-=other._v[i];
		return *this;
	}
	template <typename T, size_t size> vector_base<T,size>& vector_base<T,size>::operator *= (const vector_base<T,size>& other)
	{
		for(int i=0;i<size;++i)
			_v[i]*=other._v[i];
		return *this;
	}
	template <typename T, size_t size> vector_base<T,size>& vector_base<T,size>::operator *= (const T& c)
	{
		for(int i=0;i<size;++i)
			_v[i]*=c;
		return *this;
	}
	template <typename T, size_t size> vector_base<T,size>& vector_base<T,size>::operator /= (const T& c)
	{
		return operator *= (1/c);
	}
	template <typename T, size_t size> vector_base<T,size> operator+(const vector_base<T,size>& v1, const vector_base<T,size>& v2)
	{
		vector_base<T,size> res = v1;
		return res+=v2;
	}
	template <typename T, size_t size> vector_base<T,size> operator-(const vector_base<T,size>& v1, const vector_base<T,size>& v2)
	{
		vector_base<T,size> res = v1;
		return res-=v2;
	}
	template <typename T, size_t size> vector_base<T,size> operator*(const vector_base<T,size>& v1, const vector_base<T,size>& v2)
	{
		vector_base<T,size> res = v1;
		return res*=v2;
	}
	template <typename T, size_t size> vector_base<T,size> operator*(const vector_base<T,size>& v, const T& c)
	{
		vector_base<T,size> res = v;
		return res*=c;
	}
	template <typename T, size_t size> vector_base<T,size> operator*(const T& c, const vector_base<T,size>& v)
	{
		vector_base<T,size> res = v;
		return res*=c;
	}
	template <typename T, size_t size> T			  dot(const vector_base<T,size>& v1, const vector_base<T,size>& v2)
	{
		T res = T();
		for (int i=0;i<size;++i)
			res += v1[i]*v2[i];
		return res;
	}
	template <typename T, size_t size> vector_base<T,size> cross(const vector_base<T,size>& v1, const vector_base<T,size>& v2)
	{
		return vector_base<T,size>();
	}

	// back-end class for vector-base
	template<typename T, size_t size> class vector : public vector_base<T,size>
	{
	public:
		// constructors and factory methods
		vector();
		vector(const vector_base<T,size>& other);
		vector(const T* data);
	};

	// specializations 
	template<typename T> class vector<T,1> : public vector_base<T,1>
	{
        typedef vector_base<T,1> vector_base;
	public:
		// constructors and factory methods
		// vector():vector_base(){}
		vector(const vector_base& other):vector_base(other){}
		vector(const T* data):vector_base(data){}
		vector(const T& xx = T()){x() = xx;}

		// accessors
		T  x() const {return (*this)[X];}
		T& x()		 {return (*this)[X];}
	private:
		enum {X};
	};

	template<typename T> class vector<T,2> : public vector_base<T,2>
	{
        typedef vector_base<T,2> vector_base;
	public:
		// constructors and factory methods
		// vector():vector_base(){}
		vector(const vector_base& other):vector_base(other){}
		vector(const T* data):vector_base(data){}
		vector(const T& xx = T(), const T& yy = T()){x() = xx; y() = yy;}

		// accessors
		T  x() const {return (*this)[X];}
		T  y() const {return (*this)[Y];}
		T& x()		 {return (*this)[X];}
		T& y()	     {return (*this)[Y];}
	private:
		enum {X, Y};
	};

	template<typename T> class vector<T,3> : public vector_base<T,3>
	{
        typedef vector_base<T,3> vector_base;
	public:
		// constructors and factory methods
		// vector():vector_base(){}
		vector(const vector_base& other):vector_base(other){}
		vector(const T* data):vector_base(data){}
		vector(const T& xx = T(), const T& yy = T(), const T& zz = T()){x() = xx; y() = yy; z() = zz;}

		// accessors
		T  x() const {return (*this)[X];}
		T  y() const {return (*this)[Y];}
		T  z() const {return (*this)[Z];}
		T& x()		 {return (*this)[X];}
		T& y()	     {return (*this)[Y];}
		T& z()		 {return (*this)[Z];}
	private:
		enum {X, Y, Z};
	};

	template<typename T> class vector<T,4> : public vector_base<T,4>
	{
        typedef vector_base<T,4> vector_base;
	public:
		// constructors and factory methods
		// vector():vector_base(){}
		vector(const vector_base& other):vector_base(other){}
		vector(const T* data):vector_base(data){}
		vector(const T& xx = T(), const T& yy = T(), const T& zz = T(), const T& ww = T()){x() = xx; y() = yy; z() = zz; w() = ww;}

		// accessors
		T  x() const {return (*this)[X];}
		T  y() const {return (*this)[Y];}
		T  z() const {return (*this)[Z];}
		T  w() const {return (*this)[W];}
		T& x()		 {return (*this)[X];}
		T& y()	     {return (*this)[Y];}
		T& z()		 {return (*this)[Z];}
		T& w()		 {return (*this)[W];}
	private:
		enum {X, Y, Z, W};
	};
}

#endif