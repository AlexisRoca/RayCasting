#ifndef _Rennes1_Math_sse_Float4_H
#define _Rennes1_Math_sse_Float4_H

#include <assert.h>
#include <smmintrin.h>

namespace Math
{
		namespace sse
		{
			typedef __m128 Float4 ;

			///////////////////////////////////////////////////////////////////////////////////
			/// \brief Mask for absolute value computation of a float4
			/// 
			/// \author F. Lamarche, University of Rennes 1.
			///////////////////////////////////////////////////////////////////////////////////
			_declspec(align(16)) static const union
			{
				__int32 i[4];
				__m128 m;
			} Float4_absMask = {0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff};

			///////////////////////////////////////////////////////////////////////////////////
			/// \brief Mask used to negate a float4 value
			/// 
			/// \author F. Lamarche, University of Rennes 1.
			///////////////////////////////////////////////////////////////////////////////////
			_declspec(align(16)) static const union
			{
				__int32 i[4];
				__m128 m;
			} Float4_negateMask = {~0x7fffffff, ~0x7fffffff, ~0x7fffffff, ~0x7fffffff};

			///////////////////////////////////////////////////////////////////////////////////
			/// \brief 
			/// 
			/// \author F. Lamarche, University of Rennes 1.
			///////////////////////////////////////////////////////////////////////////////////
			_declspec(align(16)) static const union
			{
				__int32 i[4];
				__m128 m;
			} Float4_negateMaskFirst = {~0x7fffffff, 0, 0, 0};

			_declspec(align(16)) static const union
			{
				__int32 i[4];
				__m128 m;
			} Float4_negateMaskSecond = {0, ~0x7fffffff, 0, 0};

			_declspec(align(16)) static const union
			{
				__int32 i[4];
				__m128 m;
			} Float4_negateMaskThird = {0, 0, ~0x7fffffff , 0};

			_declspec(align(16)) static const union
			{
				__int32 i[4];
				__m128 m;
			} Float4_negateMaskFourth = {0, 0 ,0, ~0x7fffffff};
		}
}


inline Math::sse::Float4 makeFloat4(float value)
{
	Math::sse::Float4 result = {value, value, value, value} ;
	return result ;
}

inline Math::sse::Float4 makeFloat4(float v0, float v1, float v2, float v3)
{
	Math::sse::Float4 result = {v0, v1, v2, v3} ;
	return result ;
}

inline Math::sse::Float4 operator +(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_add_ps(v0, v1) ;
}

inline Math::sse::Float4 operator -(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_sub_ps(v0, v1) ;
}

inline Math::sse::Float4 operator *(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_mul_ps(v0, v1) ;
}

inline Math::sse::Float4 operator *(Math::sse::Float4 const & v0, float v1)
{
	return _mm_mul_ps(v0, makeFloat4(v1)) ;
}

inline Math::sse::Float4 operator /(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_div_ps(v0, v1) ;
}

inline Math::sse::Float4 operator /(Math::sse::Float4 const & v0, float v1)
{
	return _mm_div_ps(v0, makeFloat4(v1)) ;
}

inline Math::sse::Float4 operator &(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_and_ps(v0, v1) ;
}

inline Math::sse::Float4 operator ^(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_xor_ps(v0, v1) ;
}

inline Math::sse::Float4 operator |(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_or_ps(v0, v1) ;
}

inline Math::sse::Float4 operator ~(Math::sse::Float4 const & v0)
{
	int cst=-1;
	return makeFloat4(reinterpret_cast<const float &>(cst))^v0 ;
}

inline Math::sse::Float4 simdEquals(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_cmpeq_ps(v0, v1) ;
}

inline Math::sse::Float4 simdLess(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_cmplt_ps(v0,v1) ;
}

inline Math::sse::Float4 simdLessEquals(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_cmple_ps(v0,v1) ;
}

inline Math::sse::Float4 simdGreater(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_cmpgt_ps(v0,v1) ;
}

inline Math::sse::Float4 simdGreaterEquals(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return _mm_cmpge_ps(v0,v1) ;
}

inline float & get(Math::sse::Float4 & v, int index)
{
	assert(index>=0 && index<4) ;
	return v.m128_f32[index] ;
}

inline float const & get(Math::sse::Float4 const & v, int index)
{
	assert(index>=0 && index<4) ;
	return v.m128_f32[index] ;
}

inline float dot(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{ return  get(_mm_dp_ps(v0, v1, 0xFF),0) ; }

inline Math::sse::Float4 min(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{ return _mm_min_ps(v0,v1) ; }

inline Math::sse::Float4 max(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{ return _mm_max_ps(v0, v1) ; }

inline Math::sse::Float4 abs(Math::sse::Float4 const & v)
{ 
	return v & Math::sse::Float4_absMask.m ;
}

inline Math::sse::Float4 floor(Math::sse::Float4 const & v0)
{ return _mm_floor_ps(v0) ; }

inline Math::sse::Float4 ceil(Math::sse::Float4 const & v0)
{ return _mm_ceil_ps(v0) ; }

inline Math::sse::Float4 round(Math::sse::Float4 const & v0)
{ return _mm_round_ps(v0, _MM_FROUND_TO_NEAREST_INT) ; }

inline Math::sse::Float4 sqrt(Math::sse::Float4 const & v0)
{ 
	return _mm_sqrt_ps(v0) ; 
}

inline Math::sse::Float4 reciprocalSqrt(Math::sse::Float4 const & v0)
{
	return _mm_rsqrt_ps(v0) ;
}

///////////////////////////////////////////////////////////////////////////////////
/// \brief Shuffles two 
/// 
/// \param v0
/// \param v1
/// \param i0
/// \param i1
/// \param i2
/// \param i3
/// \return (v0[i0], v0[i1], v1[i2], v1[i3])
/// 
/// \author F. Lamarche, University of Rennes 1.
///////////////////////////////////////////////////////////////////////////////////
template <int i0, int i1, int i2, int i3>
Math::sse::Float4 shuffle(Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	assert(i0>=0 && i0<4) ;
	assert(i1>=0 && i1<4) ;
	assert(i2>=0 && i2<4) ;
	assert(i3>=0 && i3<4) ;
	return _mm_shuffle_ps(v0, v1, _MM_SHUFFLE(i3,i2,i1,i0)) ; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	template <int i0, int i1, int i2, int i3> Math::sse::Float4 shuffle(Math::sse::Float4 const & v)
///
/// \brief	Shuffles the given v.
///
/// \author	F. Lamarche, Université de Rennes 1
/// \date	11/12/2013
///
/// \tparam	int i0	Type of the int i 0.
/// \tparam	int i1	Type of the int i 1.
/// \tparam	int i2	Type of the int i 2.
/// \tparam	int i3	Type of the int i 3.
/// \param	v	The Math::sse::Float4 const &amp; to process.
///
/// \return	(v[i0], v[i1], v[i2], v[i3]).
////////////////////////////////////////////////////////////////////////////////////////////////////
template <int i0, int i1, int i2, int i3>
Math::sse::Float4 shuffle(Math::sse::Float4 const & v)
{
	return shuffle<i0,i1,i2,i3>(v,v) ;
}

Math::sse::Float4 rotateLeft(Math::sse::Float4 const & value)
{
	return shuffle<1,2,3,0>(value, value) ;
}

Math::sse::Float4 rotateRight(Math::sse::Float4 const & value)
{
	return shuffle<3,0,1,2>(value, value) ;
}

///////////////////////////////////////////////////////////////////////////////////
/// \brief Lexicographical == comparison
/// 
/// \param v0
/// \param v1
/// \return 
/// 
/// \author F. Lamarche, University of Rennes 1.
///////////////////////////////////////////////////////////////////////////////////
inline bool operator== (Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return (get(v0,0)==get(v1,0)) & (get(v0,1)==get(v1,1)) & (get(v0,2)==get(v1,2)) & (get(v0,3)==get(v1,3)) ;
	//Math::sse::Float4 result = _mm_cmpeq_ps(v0,v1) ;
	//Math::sse::Float4 resultShift2 = shuffle<2,3,0,1>(result, result);
	//Math::sse::Float4 tmp = result & resultShift2 ;
	//return get(tmp & shuffle<2,3,0,1>(tmp,tmp), 0) ;
	//return result & suffle<2,3,>(result, result) & 
	//(get(result,0) & get(result,1) & get(result,2) & get(result,3))==0.0 ;
}

///////////////////////////////////////////////////////////////////////////////////
/// \brief Lexicographical < comparison
/// 
/// \param v0
/// \param v1
/// \return 
/// 
/// \author F. Lamarche, University of Rennes 1.
///////////////////////////////////////////////////////////////////////////////////
inline bool operator< (Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	for(int cpt=0 ; cpt<3 ; ++cpt)
	{
		if(get(v0, cpt)>get(v1, cpt)) { return false ; }
		if(get(v0, cpt)<get(v1, cpt)) { return true ; }
	}
	return false ; 
}

///////////////////////////////////////////////////////////////////////////////////
/// \brief Lexicographical <= comparison
/// 
/// \param v0
/// \param v1
/// \return 
/// 
/// \author F. Lamarche, University of Rennes 1.
///////////////////////////////////////////////////////////////////////////////////
inline bool operator<= (Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	for(int cpt=0 ; cpt<3 ; ++cpt)
	{
		if(get(v0, cpt)>get(v1, cpt)) { return false ; }
		if(get(v0, cpt)<get(v1, cpt)) { return true ; }
	}
	return true ; 
	//return get(v0,0)<get(v1,0) || (get(v0,0)==get(v1,0) && get(v0,1)<=get(v1,1)) ;
}

///////////////////////////////////////////////////////////////////////////////////
/// \brief Lexicographical > comparison
/// 
/// \param v0
/// \param v1
/// \return 
/// 
/// \author F. Lamarche, University of Rennes 1.
///////////////////////////////////////////////////////////////////////////////////
inline bool operator> (Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return !(v0<=v1) ;
}

///////////////////////////////////////////////////////////////////////////////////
/// \brief Lexicographical >= comparison
/// 
/// \param v0
/// \param v1
/// \return 
/// 
/// \author F. Lamarche, University of Rennes 1.
///////////////////////////////////////////////////////////////////////////////////
inline bool operator>= (Math::sse::Float4 const & v0, Math::sse::Float4 const & v1)
{
	return !(v0<v1) ;
}


#endif