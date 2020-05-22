/////////////////////////////////////////////////////
/// @file quaternion.h
///	    Quaternion operations
///
/// @author Dmitry Kolzov
///
#ifndef quaternion_H
#define quaternion_H
#include <cmath>
#include "vector.h"
#include "matrix.h"

namespace core
{
	////////////////////////////////////
	///
	/// quaternion CLASS: INTERFACE
	///
	template <typename T> class quaternion
	{
	public:
		////////////////////////////////////
		/// constructors and factory methods
		                       quaternion (const T& qx = T(), const T& qy = T(), const T& qz = T(), const T& qw = T());
		/// create quaternion from a vector
		explicit               quaternion( const vector<T,4>& v );
		/// create quaternion from a orthogonal(!) matrix
		/// make sure the matrix is ORTHOGONAL
		explicit               quaternion( const matrix<T,4,4>& m );
		/// create quaternion representing rotation about given axis by angle radians
		static   quaternion<T> create_quaternion_rotation( const vector<T,4>& axis, const T& angle );
		static void            create_quaternion_rotation_i( const vector<T,4>& axis, const T& angle, quaternion<T>* pQ );
		/// apply quaternion rotation to point p
		static vector<T,4>     apply_quaternion_rotation( const vector<T,4>& v, const quaternion<T>& q );
		static void            apply_quaternion_rotation_i( const vector<T,4>& v, const quaternion<T>& q, vector<T,4>* pV );

		/// convert quaternion to matrix
		void                   to_matrix( matrix<T,4,4>* pM ) const;

		///////////////////
		/// unary operators
		quaternion<T>          operator -() const;
		quaternion<T>&         operator +=( const quaternion<T>& other );
		quaternion<T>&         operator -=( const quaternion<T>& other );
		quaternion<T>&         operator *=( const quaternion<T>& other );
		quaternion<T>&         operator *=( const T& a );
		quaternion<T>&         operator /=( const T& a );
		
		////////////////////////
		/// conjugate quaternion
		quaternion<T>          conjugate() const { return quaternion<T>(-qx(),-qy(),-qz(),qw()); }
		//////////////////////
		/// inverse quaternion
		quaternion<T>          inverse() const { return (sq_norm() == 0)?(quaternion<T>()):((1/sq_norm())*conjugate()); }
		///////////////////
		/// quaternion norm
		T			           sq_norm() const { return qx() * qx() + qy() * qy() + qz() * qz() + qw() * qw(); }
		T			           norm() const { return sqrt(sq_norm()); }
		
		/////////////
		/// accessors
		T  qx() const { return _qx; }
		T  qy() const { return _qy; }
		T  qz() const { return _qz; }
		T  qw() const { return _qw; }
		T& qx()       { return _qx; }
		T& qy()       { return _qy; }
		T& qz()       { return _qz; }
		T& qw()       { return _qw; }

	private:
		T _qx;
		T _qy;
		T _qz;
		T _qw;
	};
	
	////////////////////////////////////
	///
	/// quatrnion CLASS: IMPLEMENTATION
	///
	template <typename T> quaternion<T>::quaternion (const T& qx, const T& qy, const T& qz, const T& qw)
		: _qx(qx), _qy(qy),_qz(qz),_qw(qw)
	{}

	template <typename T> quaternion<T>::quaternion (const vector<T,4>& v)
		: _qx(v.x()), _qy(v.y()),_qz(v.z()),_qw(v.w())
	{}

	template <typename T> quaternion<T>::quaternion (const matrix<T,4,4>& m)
	{
		_qw = 0.5f*sqrt(m.trace());
		_qx = (m(2,1) - m(1,2))/(4*_qw);
		_qy = (m(0,2) - m(2,0))/(4*_qw);
		_qz = (m(1,0) - m(0,1))/(4*_qw);
	}

	template <typename T> quaternion<T> quaternion<T>::operator -() const
	{
		return quaternion<T>(-qx(),-qy(),-qz(),-qw());
	}

	template <typename T> quaternion<T>& quaternion<T>::operator +=( const quaternion<T>& other )
	{
		_qx += other._qx;
		_qy += other._qy;
		_qz += other._qz;
		_qw += other._qw;
		return *this;
	}

	template <typename T> quaternion<T>& quaternion<T>::operator -=( const quaternion<T>& other )
	{
		return operator += (-other);
	}

	template <typename T> quaternion<T>& quaternion<T>::operator *=( const quaternion<T>& q2 )
	{
		quaternion<T> temp;
		temp.qx() = qy()*q2.qz() - qz()*q2.qy() + q2.qw()*qx() + qw()*q2.qx();
		temp.qy() = qz()*q2.qx() - qx()*q2.qz() + q2.qw()*qy() + qw()*q2.qy();
		temp.qz() = qx()*q2.qy() - q2.qx()*qy() + q2.qw()*qz() + qw()*q2.qz();
		temp.qw() = qw()*q2.qw() - qx()*q2.qx() - qy()*q2.qy() - qz()*q2.qz();

		*this = temp;
		return *this;
	}

	template <typename T> quaternion<T>& quaternion<T>::operator *=( const T& a )
	{
		_qx *= a;
		_qy *= a;
		_qz *= a;
		_qw *= a;
		return *this;
	}

	template <typename T> quaternion<T>& quaternion<T>::operator /=( const T& a )
	{
		return operator*=(1.f/a);
	}

	///////////////////////////////////////
	///
	/// quatrnion CLASS: NON-MEMBER METHODS
	template <typename T> void quaternion<T>::to_matrix( matrix<T,4,4>* pM ) const
	{
		T s = 2/norm();
		(*pM)(0,0) = 1 - s*(qy()*qy() + qz()*qz()); (*pM)(0,1) = s * (qx()*qy() - qw()*qz());      (*pM)(0,2) = s * (qx()*qz() + qw()*qy());     (*pM)(0,3) = 0;
		(*pM)(1,0) = s * (qx()*qy() + qw()*qz());   (*pM)(1,1) = 1 - s * (qx()*qx() + qz()*qz());  (*pM)(1,2) = s * (qy()*qz() - qw()*qx());     (*pM)(1,3) = 0;
		(*pM)(2,0) = s * (qx()*qz() - qw()*qy());   (*pM)(2,1) = s * (qy()*qz() + qw()*qx());      (*pM)(2,2) = 1 - s * (qx()*qx() + qy()*qy()); (*pM)(2,3) = 0;
		(*pM)(3,0) = 0;                             (*pM)(3,1) = 0;                                (*pM)(3,2) = 0;                               (*pM)(3,3) = 1;
	}

	template <typename T> quaternion<T> quaternion<T>::create_quaternion_rotation( const vector<T,4>& axis, const T& angle )
	{
		// create (sin(a/2)*axis, cos(a/2)) quaternion
		// which rotates the point a radians around "axis"
		quaternion<T> res;
		vector<T,4> u = axis; u.normalize();
		float sina2 = sinf(angle/2);
		float cosa2 = cosf(angle/2);

		res.qx() = sina2 * u.x();
		res.qy() = sina2 * u.y();
		res.qz() = sina2 * u.z();
		res.qw() = cosa2;

		return res;
	}

	template <typename T> vector<T,4> quaternion<T>::apply_quaternion_rotation( const vector<T,4>& v, const quaternion<T>& q )
	{
		quaternion<T> p = quaternion<T>(v);
		quaternion<T> tp = q * p * q.inverse();
		return vector<T,4>(tp.qx(), tp.qy(), tp.qz(), tp.qw());
	}

	template <typename T> quaternion<T> operator * ( const quaternion<T>& q1,  const quaternion<T>& q2 )
	{
		quaternion<T> res;
		res.qx() = q1.qy()*q2.qz() - q1.qz()*q2.qy() + q2.qw()*q1.qx() + q1.qw()*q2.qx();
		res.qy() = q1.qz()*q2.qx() - q1.qx()*q2.qz() + q2.qw()*q1.qy() + q1.qw()*q2.qy();
		res.qz() = q1.qx()*q2.qy() - q2.qx()*q1.qy() + q2.qw()*q1.qz() + q1.qw()*q2.qz();
		res.qw() = q1.qw()*q2.qw() - q1.qx()*q2.qx() - q1.qy()*q2.qy() - q1.qz()*q2.qz();
		return res;
	}

	template <typename T> quaternion<T> operator + ( const quaternion<T>& q1,  const quaternion<T>& q2 )
	{
		quaternion<T> res = q1;
		return res += q2;
	}
	
	template <typename T> quaternion<T> operator - ( const quaternion<T>& q1,  const quaternion<T>& q2 )
	{
		quaternion<T> res = q1;
		return res -= q2;
	}

	template <typename T> quaternion<T> operator * ( const quaternion<T>& q,  const T& a )
	{
		quaternion<T> res = q;
		return res *= a;
	}
	
	template <typename T> quaternion<T> operator * ( const T& a,  const quaternion<T>& q )
	{
		quaternion<T> res = q;
		return res *= a;
	}
}

#endif