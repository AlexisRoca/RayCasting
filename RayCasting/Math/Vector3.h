#ifndef _Math_Vector_H
#define _Math_Vector_H

#include <math.h>
#include <iostream>
#include <Math/Object.h>

#ifdef SSE_OPT

#include <Math/sse/VectorFloat.h>

#else

namespace Math
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Vector3
	///
	/// \brief	A 3D vector.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	03/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Vector3 : public Object
	{
	protected:
		/// The coordinates of the vector
		float m_vector[3] ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3::Vector3(float x, float y, float z)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	x	The x coordinate.
		/// \param	y	The y coordinate.
		/// \param	z	The z coordinate.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3(float x=0, float y=0, float z=0)
		{
			m_vector[0] = x ;
			m_vector[1] = y ;
			m_vector[2] = z ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const float & Vector3::operator[] (int index) const
		///
		/// \brief	Array indexer operator.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	index	Zero-based index of the corrdinate to retreive.
		///
		/// \return	The indexed value.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const float & operator[] (int index) const
		{ return m_vector[index] ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	float & Vector3::operator[] (int index)
		///
		/// \brief	Array indexer operator.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	index	Zero-based index of the coordinate to retreive.
		///
		/// \return	The indexed value.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float & operator[] (int index) 
		{ return m_vector[index] ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3 Vector3::operator+ (Vector3 const & v) const
		///
		/// \brief	Addition operator.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	v	The other vector
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator+ (Vector3 const & v) const
		{
			Vector3 result ;
			for(int cpt=0 ; cpt<3 ; cpt++)
			{ result[cpt] = m_vector[cpt]+v.m_vector[cpt] ;	}
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3 Vector3::operator- (Vector3 const & v) const
		///
		/// \brief	Soustraction operator.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	v	The other vector.
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator- (Vector3 const & v) const
		{
			Vector3 result ;
			for(int cpt=0 ; cpt<3 ; cpt++)
			{ result[cpt] = m_vector[cpt]-v.m_vector[cpt] ;	}
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3 Vector3::operator- () const
		///
		/// \brief	Negation operator.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator- () const
		{
			Vector3 result ;
			for(int cpt=0 ; cpt<3 ; cpt++)
			{ result[cpt] = -m_vector[cpt] ;	}
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	float Vector3::operator* (Vector3 const & v) const
		///
		/// \brief	Dot product operator.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	v	The other vector
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float operator * (Vector3 const & v) const
		{
			float result ;
			result = m_vector[0]*v.m_vector[0] ;
			for(int cpt=1 ; cpt<3 ; cpt++)
			{ result = result + m_vector[cpt]*v.m_vector[cpt] ; }
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3 Vector3::operator* (float v) const
		///
		/// \brief	Multiplication by a scalar.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	v	The scalar
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator* (float v) const
		{
			Vector3 result ;
			for(int cpt=0 ; cpt<3 ; cpt++)
			{ result[cpt] = m_vector[cpt]*v ;	}
			return result ;			
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3 Vector3::operator/ (float v) const
		///
		/// \brief	Division by a scalar.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	v	The scalar.
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator/ (float v) const
		{
			Vector3 result ;
			for(int cpt=0 ; cpt<3 ; cpt++)
			{ result[cpt] = m_vector[cpt]/v ;	}
			return result ;			
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3 Vector3::operator^(Vector3 const & v) const
		///
		/// \brief	Cross product.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	v	The other vector.
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		__forceinline Vector3 operator^(Vector3 const & v) const
		{
			Vector3 result ;
			result[0] = m_vector[1]*v[2]-m_vector[2]*v[1] ;
			result[1] = m_vector[2]*v[0]-m_vector[0]*v[2] ;
			result[2] = m_vector[0]*v[1]-m_vector[1]*v[0] ;
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	float Vector3::norm2() const
		///
		/// \brief	Gets the squared norm of the vector.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float norm2() const
		{
			return (*this)*(*this) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	float Vector3::norm() const
		///
		/// \brief	Gets the norm of the vector.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float norm() const
		{ return sqrt(this->norm2()) ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3 Vector3::normalized() const
		///
		/// \brief	Gets the normalized vector corresponding to this instance.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 normalized() const
		{
			return (*this)/norm() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3 & Vector3::operator= (float const & s)
		///
		/// \brief	Fills the vector with a given scalar
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	s	The value of all coordinates.
		///
		/// \return	*this.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 & operator= (float const & s)
		{
			for(int cpt=0 ; cpt<3 ; cpt++)
			{ m_vector[cpt] = s ; }
			return *this ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3 Vector3::inv() const
		///
		/// \brief	Gets the peudo inverse of the vector.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 inv() const
		{ return (*this)/norm2() ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	int Vector3::size() const
		///
		/// \brief	Gets the size of the vector.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		int size() const
		{ return 3 ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Vector3::simdMin(Math::Vector3 const & v) const
		///
		/// \brief	SIMD minimum. Returns vector for each each component is the minimum of the corresponding 
		/// 		component in this and v.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	09/12/2013
		///
		/// \param	v	The other vector.
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 simdMin(Math::Vector3 const & v) const
		{
			return Math::Vector3(::std::min(m_vector[0], v.m_vector[0]), ::std::min(m_vector[1], v.m_vector[1]), ::std::min(m_vector[2], v.m_vector[2])) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Vector3::simdMax(Math::Vector3 const & v) const
		///
		/// \brief	SIMD maximum. Returns vector for each each component is the maximum of the corresponding
		/// 		component in this and v.
		///
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	09/12/2013
		///
		/// \param	v	The other vector.
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 simdMax(Math::Vector3 const & v) const
		{
			return Math::Vector3(::std::max(m_vector[0], v.m_vector[0]), ::std::max(m_vector[1], v.m_vector[1]), ::std::max(m_vector[2], v.m_vector[2])) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Vector3::simdMul(Math::Vector3 const & v) const
		///
		/// \brief	SIMD mul. Multiplication of v and this, component by component.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	09/12/2013
		///
		/// \param	v	The Math::Vector3 const &amp; to process.
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 simdMul(Math::Vector3 const & v) const
		{
			return Math::Vector3(m_vector[0]*v.m_vector[0], m_vector[1]*v.m_vector[1], m_vector[2]*v.m_vector[2]) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Vector3::simdDiv(Math::Vector3 const & v) const
		///
		/// \brief	SIMD div. Division of each coordinate of this by each corresponding coordinate in v.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	09/12/2013
		///
		/// \param	v	The Math::Vector3 const &amp; to process.
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 simdDiv(Math::Vector3 const & v) const
		{
			return Math::Vector3(m_vector[0]/v.m_vector[0], m_vector[1]/v.m_vector[1], m_vector[2]/v.m_vector[2]) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Vector3::simdInv() const
		///
		/// \brief	Gets the SIMD inverse. Returns (1.0/x, 1.0/y,1.0/z).
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	09/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 simdInv() const
		{
			return Math::Vector3(1.0/m_vector[0], 1.0/m_vector[1], 1.0/m_vector[2]) ;
		}
	} ;


}

#endif

namespace Math
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	inline std::ostream & operator<< (std::ostream & out, Vector3 const & v)
	///
	/// \brief	Stream insertion operator of a vector.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	03/12/2013
	///
	/// \param [in,out]	out	The output stream.
	/// \param	v		   	The vector.
	///
	/// \return	.
	////////////////////////////////////////////////////////////////////////////////////////////////////
	inline std::ostream & operator<< (std::ostream & out, Vector3 const & v)
	{
		out<<"(" ;
		for(int cpt=0 ; cpt<3 ; cpt++)
		{
			out<<v[cpt] ;
			if(cpt!=2)
			{
				out<<", " ;
			}
		}
		out<<")" ;
		return out ;
	}
}

#endif
