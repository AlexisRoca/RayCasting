#ifndef _Math_RandomDirection_H
#define _Math_RandomDirection_H

#include <math.h>
#include <stdlib.h>

namespace Math
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	RandomDirection
	///
	/// \brief	Random direction sampling. the sampling is biased by a cosine distribution, useful for
	/// 		respecting a BRDF distribution (diffuse or specular).
	/// 		
	/// \author	F. Lamarche, University of Rennes 1.
	/// \date	04/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class RandomDirection
	{
	protected:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static ::std::pair<float,float> RandomDirection::randomPolar(float n=1.0)
		///
		/// \brief	Random sampling of spherical coordinates.
		///
		/// \author	F. Lamarche, University of Rennes 1.
		/// \date	04/12/2013
		///
		/// \param	n	(optional) The specular index (1.0 if diffuse).
		///
		/// \return	Random spherical coordinates repecting a cos^n distribution.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static ::std::pair<float,float> randomPolar(float n=1.0)
		{
			float rand1 = random() ;
			float p = pow(rand1, 1/(n+1)) ;
			float theta = acos(p) ;
			float rand2 = random() ;
			float phy = 2*M_PI*rand2 ;
			return ::std::make_pair(theta, phy) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static Math::Vector3 RandomDirection::getVector(float theta, float phy)
		///
		/// \brief	Computes the normalized vector corresponding to provided spherical coordinates.
		/// 		
		/// \author	F. Lamarche, University of Rennes 1.
		/// \date	04/12/2013
		///
		/// \param	theta	
		/// \param	phy  	
		///
		/// \return	The vector.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Math::Vector3 getVector(float theta, float phy)
		{
			return Math::Vector3(sin(theta)*cos(phy), sin(theta)*sin(phy), cos(theta)) ;
		}

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	static float RandomDirection::random()
		///
		/// \brief	A random value in interval [0;1]
		///
		/// \author	F. Lamarche, University of Rennes 1.
		/// \date	04/12/2013
		///
		/// \return	A random number in [0;1].
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static float random()
		{
			return (float)rand()/RAND_MAX ;
		}

	protected:

		/// \brief	The main direction for sampling.
		Math::Vector3 m_direction ;

		/// \brief	A direction normal to the direction vector.
		Math::Vector3 m_directionNormal ;

		/// \brief	The specular coefficient.
		float m_n ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RandomDirection::RandomDirection(Math::Vector3 const & direction, float n=1.0)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, University of Rennes 1.
		/// \date	04/12/2013
		///
		/// \param	direction	The main direction of the random sampling.
		/// \param	n		 	n The specular coefficient of the surface (1.0 is diffuse component, the 
		/// 					specular coefficient otherwise)
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RandomDirection(Math::Vector3 const & direction, float n=1.0)
			: m_direction(direction.normalized()), m_n(n)
		{
			// We compute a vector normal to the main direction
			m_directionNormal = Math::Vector3(1.0,0.0,0.0) ;
			m_directionNormal = m_directionNormal - m_direction*(m_direction*m_directionNormal) ;
			if(m_directionNormal.norm()<std::numeric_limits<float>::epsilon()*10.0)
			{
				m_directionNormal = Math::Vector3(0.0,1.0,0.0) ;
				m_directionNormal =  m_directionNormal - m_direction*(m_direction*m_directionNormal) ;
				if(m_directionNormal.norm()<std::numeric_limits<float>::epsilon()*10.0)
				{
					m_directionNormal = Math::Vector3(0.0,0.0,1.0) ;
					m_directionNormal =  m_directionNormal - m_direction*(m_direction*m_directionNormal) ;

				}	
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 RandomDirection::generate() const
		///
		/// \brief	Generate a random direction respecting a cosine^n distribution.
		///
		/// \author	F. Lamarche, University of Rennes 1.
		/// \date	04/12/2013
		///
		/// \return	The random direction.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 generate() const
		{
			::std::pair<float,float> perturbation = randomPolar(m_n) ;
			Quaternion q1(m_directionNormal, perturbation.first) ;
			Quaternion q2(m_direction, perturbation.second) ;
			Math::Quaternion result = q2.rotate(q1.rotate(m_direction)) ;
			return result.v() ;
		}
	};
}

#endif