/////////////////////////////////////////////////////
/// @file complex.h
///	    Complex number representation
///
/// @author Dmitry Kolzov
///
#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <complex>
#define M_PI        3.14159265358979323846
#define M_PI_2      1.57079632679489661923

namespace core
{
	////////////////////////////////////
	///
	/// COMPLEX NUMBERS CLASS: INTERFACE
	///
	template <typename T> class complex
	{
	public:
		// constructors and factory methods
		complex( const T& re = T(), const T& im = T() );
		complex( const complex<T>& other );
		complex( const std::complex<T>& other );
		static complex<T> create_complex_radial( const T& rad = T(), const T& arg = T());

		// destructor
		~complex();

		// get accessors
		T re() const;
		T im() const;
		T rad() const;
		T arg() const;

		// set accessors
		void set_re(const T& re);
		void set_im(const T& im);
		void set_rad(const T& rad);
		void set_arg(const T& arg);

		// unary operators 
		complex<T> conjugate() const;
		complex<T> operator -() const;

		// binary operators
		complex<T>& operator += (const complex<T>& other);
		complex<T>& operator -= (const complex<T>& other);
		complex<T>& operator *= (const complex<T>& other);

		// conversion operators
		operator std::complex<T>() const;
	private:
		// Real and imaginary part
		T _re;
		T _im;
	};

	// binary operators
	template <typename T> complex<T> operator + ( const complex<T>& c1, const complex<T>& c2 );
	template <typename T> complex<T> operator - ( const complex<T>& c1, const complex<T>& c2 );
	template <typename T> complex<T> operator * ( const complex<T>& c1, const complex<T>& c2 );


	/////////////////////////////////////////
	///
	/// COMPLEX NUMBERS CLASS: IMPLEMENTATION
	///
	template <typename T> complex<T>::complex( const T& re = T(), const T& im = T() )
		:_re(re), _im(im) {}
	template <typename T> complex<T>::complex( const complex<T>& other )
		:_re(other._re), _im(other._im) {}
	template <typename T> complex<T>::complex( const std::complex<T>& other )
		:_re(other.real()), _im(other.imag()) {}
	template <typename T> complex<T> complex<T>::create_complex_radial(const T& rad = T(), const T& arg = T())
	{
		complex<T> c;
		c.set_rad(rad);
		c.set_arg(arg);
		return c;
	}
	template <typename T> complex<T>::~complex() {}

	template <typename T> T complex<T>::re() const {return _re;}
	template <typename T> T complex<T>::im() const {return _im;}
	template <typename T> T complex<T>::rad() const {return std::sqrt(_re*_re + _im*_im);}
	template <typename T> T complex<T>::arg() const 
	{
		return (_re == 0)?
			((_im > 0) ? (M_PI_2):(-M_PI_2))
			:
			(std::atan2(_im, _re));

	}
	
	template <typename T> void complex<T>::set_re(const T& re) { _re = re; }
	template <typename T> void complex<T>::set_im(const T& im) { _im = im; }
	template <typename T> void complex<T>::set_rad(const T& rad)
	{
		 T old_rad = this->rad();
		 if ( 0 == old_rad )
		 {
			 _re = rad;
			 _im = 0;
		 }
		 else
		 {
			_re = (_re / old_rad) * rad;
			_im = (_im / old_rad) * rad;
		 }
	}
	template <typename T> void complex<T>::set_arg(const T& arg)
	{
		 _re = rad() * std::sin(arg);
         _im = rad() * std::sin(arg);
	}

	template <typename T> complex<T> complex<T>::conjugate() const { return complex<T>(_re, -_im); }
	template <typename T> complex<T> complex<T>::operator -() const { return complex<T>(-_re,-_im); }
	template <typename T> complex<T>& complex<T>::operator += (const complex<T>& other)
	{
		_re += other._re;
		_im += other._im;
		return *this;
	}
	template <typename T> complex<T>& complex<T>::operator -= (const complex<T>& other)
	{
		_re -= other._re;
		_im -= other._im;
		return *this;
	}
	template <typename T> complex<T>& complex<T>::operator *= (const complex<T>& other)
	{
		T old_re = _re;
		T old_im = _im;

		_re = old_re*other._re - old_im*other._im;
		_im = old_re*other._im + old_im*other._re;
		return *this;
	}
	template <typename T> complex<T>::operator std::complex<T>() const
	{
		return std::complex<T>(_re, _im);
	}
	template <typename T> complex<T> operator + ( const complex<T>& c1, const complex<T>& c2 )
	{
		complex<T> res = c1;
		return res += c2;
	}
	template <typename T> complex<T> operator - ( const complex<T>& c1, const complex<T>& c2 )
	{
		complex<T> res = c1;
		return res -= c2;

	}
	template <typename T> complex<T> operator * ( const complex<T>& c1, const complex<T>& c2 )
	{
		complex<T> res = c1;
		return res *= c2;
	}
}





#endif // COMPLEX_H