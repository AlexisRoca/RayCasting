#ifndef _Geometry_RayTriangleIntersection_H
#define _Geometry_RayTriangleIntersection_H

#include <Geometry/Ray.h>
#include <Geometry/Triangle.h>
#include <Spy/Spy.h>
#include <assert.h>

namespace Geometry
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	RayTriangleIntersection
	///
	/// \brief	An intersection between a ray and a triangle.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	04/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class RayTriangleIntersection
	{
	protected:
		/// \brief	The distance between ray source and the intersection.
		float m_t ;
		/// \brief	The u coordinate of the intersection.
		float m_u ;
		/// \brief	The v coordinate of the intersection.
		float m_v ;
		/// \brief	Is the intersection valid?
		bool m_valid ;
		/// \brief	The triangle associated to the intersection.
		const Triangle * m_triangle ;
		/// \brief	The ray associated to the intersection.
		const Ray * m_ray ;

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RayTriangleIntersection::RayTriangleIntersection(const Triangle * triangle,
		/// 	const Ray * ray)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	triangle	The triangle.
		/// \param	ray			The ray.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RayTriangleIntersection(const Triangle * triangle, const Ray * ray)
			: m_triangle(triangle), m_ray(ray)
		{
			m_valid=triangle->intersection(*ray, m_t, m_u, m_v) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RayTriangleIntersection::RayTriangleIntersection(const Ray * ray)
		///
		/// \brief	Constructor that constructs an invalid intersection.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	ray	The ray.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RayTriangleIntersection(const Ray * ray)
			: m_valid(false), m_triangle(NULL), m_ray(ray)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool RayTriangleIntersection::valid() const
		///
		/// \brief	Is the intersection valid?
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	true if valid, false otherwise.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool valid() const
		{ return m_valid ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	float RayTriangleIntersection::tRayValue() const
		///
		/// \brief	Distance between the ray source and the intersection point
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float tRayValue() const
		{ return m_t ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	float RayTriangleIntersection::uTriangleValue() const
		///
		/// \brief	The u value of the intersection.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float uTriangleValue() const
		{ return m_u ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	float RayTriangleIntersection::vTriangleValue() const
		///
		/// \brief	The v value of the intersection
		/// 		
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float vTriangleValue() const
		{ return m_v ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Triangle * RayTriangleIntersection::triangle() const
		///
		/// \brief	Returns the triangle associated to the intersection.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	The triangle.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Triangle * triangle() const
		{ return m_triangle ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Ray * RayTriangleIntersection::ray() const
		///
		/// \brief	Return the ray associated to the intersection.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	The ray.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Ray * ray() const
		{ return m_ray ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 RayTriangleIntersection::intersection() const
		///
		/// \brief	Returns the intersection point.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 intersection() const
		{ return m_ray->source()+m_ray->direction()*tRayValue() ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool RayTriangleIntersection::operator< (RayTriangleIntersection const & i) const
		///
		/// \brief	Compares two intersections associated with the same ray (otherwise, it is a non-sense)
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	i	Zero-based index of the.
		///
		/// \return	true if the first parameter is less than the second.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool operator < (RayTriangleIntersection const & i) const
		{ 
			return (m_valid & i.m_valid & (m_t<i.m_t)) | (!i.m_valid) ; 
		}
	} ;
}

#endif
