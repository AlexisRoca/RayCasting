#ifndef _Geometry_Triangle
#define _Geometry_Triangle

#include <Math/Vector3.h>
#include <Geometry/Ray.h>
#include <Geometry/Material.h>

namespace Geometry
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Triangle
	///
	/// \brief	A triangle.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	04/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Triangle
	{
	protected:
		/// \brief	Pointers to the three vertices
		const Math::Vector3 * m_vertex[3] ; 
		/// \brief	The vertex 0 (added to enhance cache consistency)
		Math::Vector3 m_vertex0 ;
		/// \brief	The u axis.
		Math::Vector3 m_uAxis ; 
		/// \brief	The v axis.
		Math::Vector3 m_vAxis ;
		/// \brief	The normal.
		Math::Vector3 m_normal ;
		/// \brief	The associated material.
		Material * m_material ;

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Triangle::update()
		///
		/// \brief	Updates precomputed data. This method should be called if vertices are externally 
		/// 		modified.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void update()
		{
			m_vertex0 = *m_vertex[0] ;
			m_uAxis = (*m_vertex[1])-(*m_vertex[0]) ;
			m_vAxis = (*m_vertex[2])-(*m_vertex[0]) ;
			m_normal = m_uAxis^m_vAxis ;
			m_normal = m_normal*(1.0f/m_normal.norm()) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Triangle::Triangle(Math::Vector3 * a, Math::Vector3 * b, Math::Vector3 * c,
		/// 	Material * material)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	a					A pointer to the first vertex.
		/// \param	b					A pointer to the second vertex.
		/// \param	c					A pointer to the third vertex.
		/// \param [in,out]	material	If non-null, the material.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Triangle(Math::Vector3 * a, Math::Vector3 * b, Math::Vector3 * c, Material * material)
			: m_material(material)
		{
			m_vertex[0] = a ;
			m_vertex[1] = b ;
			m_vertex[2] = c ;
			update() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Triangle::Triangle()
		///
		/// \brief	Default constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Triangle()
		{
			m_vertex[0] = NULL ;
			m_vertex[1] = NULL ;
			m_vertex[2] = NULL ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Material * Triangle::material() const
		///
		/// \brief	Gets the material.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	null if it fails, else.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Material * material() const
		{ return m_material ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 const & Triangle::vertex(int i) const
		///
		/// \brief	Gets the ith vertex
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	i	Vertex index in [0;2].
		///
		/// \return	the vertex.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 const & vertex(int i) const
		{ 
			return *(m_vertex[i]) ; 
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector3 & Triangle::uAxis() const
		///
		/// \brief	Gets the u axis.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector3 & uAxis() const		
		{ 
			return m_uAxis ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector3 & Triangle::vAxis() const
		///
		/// \brief	Gets the v axis.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector3 & vAxis() const
		{ 
			return m_vAxis ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const Math::Vector3 & Triangle::normal() const
		///
		/// \brief	Gets the normal.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Math::Vector3 & normal() const
		{ return m_normal ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Triangle::normal(Math::Vector3 const & point) const
		///
		/// \brief	Gets the normal directed toward the half space containing the provided point.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	point	The point.
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 normal(Math::Vector3 const & point) const
		{
			//if((point-vertex(0))*m_normal<0.0)
			if((point-m_vertex0)*m_normal<0.0)
			{ return m_normal*(-1.0) ; }
			return m_normal ; 
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Triangle::reflectionDirection(Math::Vector3 const & dir) const
		///
		/// \brief Returns the direction of a reflected ray, from the direction of the incident ray.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	dir	The direction of the incident ray.
		///
		/// \return	The direction of the reflected ray.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 reflectionDirection(Math::Vector3 const & dir) const
		{
			Math::Vector3 reflected(dir-normal()*(2.0f*(dir*normal()))) ; 
			return reflected ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Triangle::reflectionDirection(Ray const & ray) const
		///
		/// \brief	Returns the direction of the reflected ray from a ray description.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	ray	The incident ray.
		///
		/// \return	.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 reflectionDirection(Ray const & ray) const
		{
			Math::Vector3 n = normal() ;
			//if(n*(ray.source()-vertex(0))<=0.0)
			if(n*(ray.source()-m_vertex0)<=0.0)
			{ n = n*(-1.0) ; }
			Math::Vector3 reflected(ray.direction()-n*(2.0f*(ray.direction()*n))) ; 
			return reflected ;
		}

				
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Math::Vector3 Triangle::refractionDirection(Math::Vector3 const & dir) const
		///
		/// \brief Returns the direction of a refracted ray
		///
		/// \author	A. Roca & M. Toutirais, Université de Rennes 1
		/// \date	27/12/2015
		///
		/// \param	index index of refraction.
		///
		/// \return	The direction of the refracted ray.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Math::Vector3 refractionDirection(Ray const & ray) const
		{
			Math::Vector3 n = normal();

			if (n*(ray.source() - m_vertex0) <= 0.0)
				n = n*(-1.0);
		
			float refractionIndex = 1 / this->material()->refractionIndex();

			float alpha = n * (-ray.direction());
			float beta = sqrt(1 - pow(refractionIndex, 2) * (1 - pow(alpha, 2)));
	
			return (ray.direction()*refractionIndex + n*(refractionIndex*alpha - beta));

		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Triangle::intersection(Ray const & r, float & t, float & u, float & v) const
		///
		/// \brief	Computes the intersection between a ray and this triangle.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	r		 	The tested ray.
		/// \param [t>=0]	t	The distance between the ray source and the intersection point.
		/// \param	u		 	The u coordinate of the intersection (useful for texture mapping).
		/// \param	v		 	The v coordinate of the intersection (useful for texture mapping).
		///
		/// \return	True if an intersection has been found, false otherwise.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool intersection(Ray const & r, float & t, float & u, float & v) const
		{
			/* find vectors for two edges sharing vert0 */
			const Math::Vector3 & edge1(uAxis()) ;
			const Math::Vector3 & edge2(vAxis()) ;

			/* begin calculating determinant - also used to calculate U parameter */
			Math::Vector3 pvec(r.direction() ^ edge2);

			/* if determinant is near zero, ray lies in plane of triangle */
			float det = edge1 * pvec ;
		
			if (fabs(det)<0.000000001) // if(det > -0.000001 && det < 0.000001) 
			{
				return false ; 
			}

			float inv_det = 1.0f / det;

			/* calculate distance from vert0 to ray origin */
			//Math::Vector3 tvec(r.source() - vertex(0));
			Math::Vector3 tvec(r.source() - m_vertex0);

			/* calculate U parameter and test bounds */
			u = (tvec * pvec) * inv_det;

			//std::cout<<"u = "<<u<<std::endl ;

			if (fabs(u-0.5)>0.5) //u < 0.0 || u > 1.0) //
			{
				return  false ;
			}

			/* prepare to test V parameter */
			Math::Vector3 qvec(tvec ^ edge1) ;

			/* calculate V parameter and test bounds */
			v = (r.direction() * qvec) * inv_det;
			if (v < 0.0 || u + v > 1.0)
			{
				return false ;
			}

			/* calculate t, ray intersects triangle */
			t = (edge2 * qvec) * inv_det;

			return t>=0.0001 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Triangle::generalIntersection(Ray const & r, float & t, float & u, float & v) const
		///
		/// \brief	Computes the intersection between the ray and the plane supporting the triangle.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	r	The ray.
		/// \param	t	The distance between the ray source and the intersection.
		/// \param	u	The u coordinate of the intersection.
		/// \param	v	The v coordinate of the intersection.
		///
		/// \return	True if the ray is not parallel to the plane.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool generalIntersection(Ray const & r, float & t, float & u, float & v) const
		{
			/* find vectors for two edges sharing vert0 */
			const Math::Vector3 & edge1(uAxis()) ;
			const Math::Vector3 & edge2(vAxis()) ;
			float det,inv_det;

			/* begin calculating determinant - also used to calculate U parameter */
			Math::Vector3 pvec(r.direction() ^ edge2);

			/* if determinant is near zero, ray lies in plane of triangle */
			det = edge1 * pvec ;
		
			if (det > -0.000001 && det < 0.000001) 
			{
				return false ; 
			}

			inv_det = 1.0f / det;

			/* calculate distance from vert0 to ray origin */
			//Math::Vector3 tvec(r.source() - vertex(0));
			Math::Vector3 tvec(r.source() - m_vertex0);

			/* calculate U parameter and test bounds */
			u = (tvec * pvec) * inv_det;

			/* prepare to test V parameter */
			Math::Vector3 qvec(tvec ^ edge1) ;

			/* calculate V parameter and test bounds */
			v = (r.direction() * qvec) * inv_det;

			/* calculate t, ray intersects triangle */
			t = (edge2 * qvec) * inv_det;

			return true ;
		}

	} ;
}

#endif
 
