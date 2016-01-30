#ifndef _Geometry_BoundingBox_H
#define _Geometry_BoundingBox_H

#include <Geometry/Geometry.h>

namespace Geometry
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	BoundingBox
	///
	/// \brief	A bounding box.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	04/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class BoundingBox
	{
	protected:
		/// \brief	The bounds (min / max vectors).
		Math::Vector3 m_bounds[2] ;
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox::BoundingBox(Geometry const & geometry)
		///
		/// \brief	Initializes the bounding box from the provided geometry.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	geometry	The geometry.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox(Geometry const & geometry)
		{
			set(geometry);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	BoundingBox::BoundingBox(Math::Vector3 const & minVertex, Math::Vector3 const & maxVertex)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	minVertex	The smallest coordinates on X, Y, Z axes.
		/// \param	maxVertex	The highest coordinates on X, Y, Z axes.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		BoundingBox(Math::Vector3 const & minVertex, Math::Vector3 const & maxVertex)
		{
			m_bounds[0] = minVertex ;
			m_bounds[1] = maxVertex ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void BoundingBox::set( Geometry const &geometry )
		///
		/// \brief	Sets the bouding box with the given geometry.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	10/12/2013
		///
		/// \param	geometry	The geometry.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void set( Geometry const &geometry ) 
		{
			const std::deque<Math::Vector3, aligned_allocator<Math::Vector3, 16> > & vertices(geometry.getVertices()) ;
			m_bounds[0] = vertices[0] ;
			m_bounds[1] = vertices[0] ;
			update(geometry) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void BoundingBox::update(Geometry const & geometry)
		///
		/// \brief	Updates the bounding box with the given geometry.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	10/12/2013
		///
		/// \param	geometry	The geometry.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void update(Geometry const & geometry)
		{
			const std::deque<Math::Vector3, aligned_allocator<Math::Vector3, 16> > & vertices(geometry.getVertices()) ;
			for(auto it=vertices.begin(), end=vertices.end() ; it!=end ; ++it)
			{
				m_bounds[0] = m_bounds[0].simdMin(*it) ;
				m_bounds[1] = m_bounds[1].simdMax(*it) ;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void BoundingBox::update(BoundingBox const & boundingBox)
		///
		/// \brief	Updates this bounding box to bound the given boundingBox.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	10/12/2013
		///
		/// \param	boundingBox	The bounding box.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void update(BoundingBox const & boundingBox)
		{
			m_bounds[0] = m_bounds[0].simdMin(boundingBox.m_bounds[0]) ;
			m_bounds[1] = m_bounds[1].simdMax(boundingBox.m_bounds[1]) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool BoundingBox::intersect(const Ray & ray) const
		///
		/// \brief	Tests if the provided ray intersects this box.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	09/12/2013
		///
		/// \param	ray	The ray.
		///
		/// \return	true if an intersection is found, false otherwise.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool intersect(const Ray & ray, float t0, float t1) const
		{
			//int sign[3] = { ray.direction()[0]<0.0, ray.direction()[1]<0.0, ray.direction()[2]<0.0 } ;
			const int * sign = ray.getSign() ;
			Math::Vector3 tmin(m_bounds[sign[0]][0], m_bounds[sign[1]][1], m_bounds[sign[2]][2]) ;
			tmin = (tmin - ray.source()).simdMul(ray.invDirection()) ;
			Math::Vector3 tmax(m_bounds[1-sign[0]][0], m_bounds[1-sign[1]][1], m_bounds[1-sign[2]][2]) ;
			tmax = (tmax - ray.source()).simdMul(ray.invDirection()) ;
			
			if((tmin[0]>tmax[1]) || (tmin[1]>tmax[0]))
			{
				return false ;
			}
			if(tmin[1] > tmin[0])
			{
				tmin[0] = tmin[1] ;
			}
			if(tmax[1] < tmax[0])
			{
				tmax[0] = tmax[1] ;
			}
			
			if((tmin[0]>tmax[2]) || (tmin[2] > tmax[0]))
			{
				return false ;
			}
			if(tmin[2] > tmin[0])
			{
				tmin[0] = tmin[2] ;
			}
			if(tmax[2] < tmax[0])
			{
				tmax[0] = tmax[2] ; 
			}
			return (tmin[0]<t1) && (tmax[0]>t0) ;
		}
	} ;
}

#endif