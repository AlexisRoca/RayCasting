#ifndef _Rennes1_Math_VectorFloat_H
#define _Rennes1_Math_VectorFloat_H

#include <iostream>
#include <Math/sse/Float4_functions.h>

#include <emmintrin.h>


namespace Math
{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Vector
	///
	/// \brief	Class representing m_vector N-dimensional vector. 
	///
	/// \param Float The scalar type.
	/// \param dimensions The dimension of the vector
	/// 
	/// \author	Fabrice Lamarche, University Of Rennes 1
	/// \date	23/01/2010
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Vector3
	{
	protected:
		sse::Float4 m_vector ;

		Vector3(sse::Float4 const & value)
			: m_vector(value)
		{}
	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector()
		///
		/// \brief	Default constructor. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3() 
		{
			m_vector = makeFloat4(0.0, 0.0, 0.0, 0.0) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector(Float const & value)
		///
		/// \brief	Constructor that initializes each coordinate with the given value. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \param value	the value of each coordinate. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3(float const & value)
		{
			m_vector = makeFloat4(value, value, value, 0.0) ; //makeDouble2(value, value) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector3::Vector3(float x, float y, float z)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	08/12/2013
		///
		/// \param	x	The x coordinate.
		/// \param	y	The y coordinate.
		/// \param	z	The z coordinate.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3(float x, float y, float z)
		{
			m_vector = makeFloat4(x,y,z,0.0) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float norm() const
		///
		/// \brief	Return the norm of the vector. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \return	the norm of the vector.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float norm() const
		{
			return sqrt(norm2()) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float norm2() const
		///
		/// \brief	Returns the squared norm of the vector. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \return	the squared norm of the vector. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float norm2() const
		{
			return (*this)*(*this) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Float & operator[] (int index) const
		///
		/// \brief	 Access to the value of each coordinate. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \param	index	Zero-based index of the coordinate. 
		///
		/// \return	the value of the 'index' nth coordinate. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const float & operator[] (int index) const
		{
			return m_vector.m128_f32[index] ;
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float & operator[] (int index)
		///
		/// \brief	 Access to the value of each coordinate. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \param	index	Zero-based index of the coordinate. 
		///
		/// \return	the value of the 'index' nth coordinate. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float & operator[] (int index) 
		{ 
			return m_vector.m128_f32[index] ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector<Float, dimensions> operator+ (Vector<Float, dimensions> const & v) const
		///
		/// \brief	Addition operator. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \param [in,out]	v	the v. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator+ (Vector3 const & v) const
		{
			Vector3 result ;
			result.m_vector = m_vector+v.m_vector ;
			return result; 
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector<Float, dimensions> operator- (Vector<Float, dimensions> const & v) const
		///
		/// \brief	Substraction operator. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \param [in,out]	v	the v. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator- (Vector3 const & v) const
		{
			Vector3 result ;
			result.m_vector = m_vector-v.m_vector ;
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector<Float, dimensions> operator- () const
		///
		/// \brief	Negation operator. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator- () const
		{
			Vector3 result ;
			result.m_vector = m_vector*-1.0 ;
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Float operator * (Vector<Float, dimensions> const & v) const
		///
		/// \brief	Scalar product. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \param [in,out]	v	the v. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float operator * (Vector3 const & v) const
		{
			return dot(m_vector,v.m_vector) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector<Float, dimensions> operator* (Float const & v) const
		///
		/// \brief	Muliplication operator. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \param [in,out]	v	the v. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator* (float const & v) const
		{
			Vector3 result ;
			result.m_vector = m_vector*v ;
			return result ;
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector<Float, dimensions> operator/ (Float const & v) const
		///
		/// \brief	Division operator. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \param [in,out]	v	the v. 
		///
		/// \return	The result of the operation. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 operator/ (float const & v) const
		{
			Vector3 result ;
			result.m_vector = m_vector/v ;
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector<Float, dimensions> inv() const
		///
		/// \brief	Pseudo inverse of the vector. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 inv() const
		{ return (*this)/norm2() ; }

		int size() const
		{
			return 3 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Vector<Float, dimensions> normalized() const
		///
		/// \brief	Return the associated normalized vector. 
		///
		/// \author	Fabrice Lamarche, University Of Rennes 1
		/// \date	23/01/2010
		///
		/// \return	. 
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 normalized() const
		{
			return (*this)/norm() ;
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
		Vector3 operator^(Vector3 const & v) const
		{
			Vector3 result ;
			result.m_vector = _mm_sub_ps(
				_mm_mul_ps(_mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(v.m_vector, v.m_vector, _MM_SHUFFLE(3, 1, 0, 2))), 
				_mm_mul_ps(_mm_shuffle_ps(m_vector, m_vector, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(v.m_vector, v.m_vector, _MM_SHUFFLE(3, 0, 2, 1)))
				);
			return result ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Vector3::simdMax(Math::Vector3 const & v) const
		///
		/// \brief	SIMD maximum. Returns vector for each each component is the minimum of the corresponding
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
		Math::Vector3 simdMin(Math::Vector3 const & v) const
		{
			return min(m_vector, v.m_vector) ;
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
			return max(m_vector, v.m_vector) ;
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
			return m_vector*v.m_vector ;
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
			return m_vector/v.m_vector ;
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
			sse::Float4 result = makeFloat4(1.0,1.0,1.0,0.0)/m_vector ;
			result.m128_f32[3] = 0.0 ;
			return result ;
		}
	} ;
}


#endif
