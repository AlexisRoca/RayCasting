#ifndef _Geometry_Geometry_H
#define _Geometry_Geometry_H

#include <Geometry/Triangle.h>
#include <Geometry/Material.h>
#include <Math/Vector3.h>
#include <vector>
#include <deque>
#include <map>
#include <System/aligned_allocator.h>

namespace Geometry
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Geometry
	///
	/// \brief	A 3D geometry.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	04/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Geometry
	{
	protected:
	    /// \brief	The vertices.
	    std::deque<Math::Vector3, aligned_allocator<Math::Vector3, 16> > m_vertices ;
		/// \brief	The triangles.
		std::deque<Triangle, aligned_allocator<Triangle, 16> >      m_triangles ;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::updateTriangles()
		///
		/// \brief	Updates all the triangles of the geometry (normals, u and v vectors). This method should
		/// 		be called if some transformations arer applied on the vertices of the geometry.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void updateTriangles()
		{
			for(int cpt=0 ; cpt<(int)m_triangles.size() ; cpt++)
			{
				m_triangles[cpt].update() ;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::addTriangle(int i1, int i2, int i3, Material * material)
		///
		/// \brief	Adds a triangle.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	i1					Zero-based index of the first vertex.
		/// \param	i2					Zero-based index of the second vertex.
		/// \param	i3					Zero-based index of the third vertex.
		/// \param [in,out]	material	If non-null, the material.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void addTriangle(int i1, int i2, int i3, Material * material)
		{
			m_triangles.push_back(Triangle(&m_vertices[i1], &m_vertices[i2], &m_vertices[i3], material)) ; 
		}

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const std::deque<Math::Vector3> & Geometry::getVertices() const
		///
		/// \brief	Gets the vertices.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	The vertices.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::deque<Math::Vector3, aligned_allocator<Math::Vector3, 16> > & getVertices() const
		{ return m_vertices ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	const std::vector<Triangle> & Geometry::getTriangles() const
		///
		/// \brief	Gets the triangles.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \return	The triangles.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const std::deque<Triangle, aligned_allocator<Triangle, 16> > & getTriangles() const
		{ return m_triangles ; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Geometry::Geometry()
		///
		/// \brief	Default constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Geometry()
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Geometry::Geometry(const Geometry & geom)
		///
		/// \brief	Copy constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	10/12/2013
		///
		/// \param	geom	The geometry.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Geometry(const Geometry & geom)
		{
			merge(geom) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	unsigned int Geometry::addVertex(const Math::Vector3 & vertex)
		///
		/// \brief	Adds a vertex.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	vertex	The vertex.
		///
		/// \return	The index of the added vertex.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		unsigned int addVertex(const Math::Vector3 & vertex)
		{ 
			m_vertices.push_back(vertex) ; 
			return m_vertices.size()-1 ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::addTriangle(const Triangle & triangle)
		///
		/// \brief	Adds a triangle.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	triangle	The triangle.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void addTriangle(const Triangle & triangle)
		{
			int i1 = addVertex(triangle.vertex(0)) ;
			int i2 = addVertex(triangle.vertex(1)) ;
			int i3 = addVertex(triangle.vertex(2)) ;
			addTriangle(i1,i2,i3,triangle.material()) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::addTriangle(const Math::Vector3 & p0, const Math::Vector3 & p1,
		/// 	const Math::Vector3 & p2, Material * material)
		///
		/// \brief	Adds a triangle.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	p0					The first vertex.
		/// \param	p1					The second vertex.
		/// \param	p2					The third vertex.
		/// \param [in,out]	material	If non-null, the material.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void addTriangle(const Math::Vector3 & p0, const Math::Vector3 & p1, const Math::Vector3 & p2, Material * material)
		{
			int i1 = addVertex(p0) ;
			int i2 = addVertex(p1) ;
			int i3 = addVertex(p2) ;
			addTriangle(i1,i2,i3,material) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::merge(const Geometry & geometry)
		///
		/// \brief	Merges the provided geometry with this one.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	geometry The geometry that should be merged
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void merge(const Geometry & geometry)
		{
			::std::map<const Math::Vector3*, int> vectorToIndex ;
			for(int cpt=0 ; cpt<(int)geometry.getVertices().size() ; cpt++)
			{
				const Math::Vector3 * vertex = &geometry.getVertices()[cpt];
				auto it = vectorToIndex.find(vertex) ;
				if(it==vectorToIndex.end())
				{
					int index = addVertex(geometry.getVertices()[cpt]) ;
					vectorToIndex.insert(::std::make_pair(vertex, addVertex(*vertex))) ;
				}
			}
			for(int cpt=0 ; cpt<(int)geometry.getTriangles().size() ; cpt++)
			{
				const Triangle & current = geometry.getTriangles()[cpt] ;
				auto it1 = vectorToIndex.find(&current.vertex(0)) ;
				auto it2 = vectorToIndex.find(&current.vertex(1)) ;
				auto it3 = vectorToIndex.find(&current.vertex(2)) ;
				addTriangle(it1->second, it2->second, it3->second, current.material()) ;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	bool Geometry::intersection(CastedRay & ray)
		///
		/// \brief	Computes the intersection between this geometry and the provided Ray.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param [in,out]	ray	The ray.
		///
		/// \return	true if it succeeds, false if it fails.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		bool intersection(CastedRay & ray)
		{
			for(auto it=m_triangles.begin(), end=m_triangles.end() ; it!=end ; ++it)
			{
				ray.intersect(&(*it)) ;
			}
			//for(int cpt=0 ; cpt<(int)m_triangles.size() ; cpt++)
			//{
			//	ray.intersect(&m_triangles[cpt]) ;
			//}
			return ray.validIntersectionFound() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::translate(Math::Vector3 const & t)
		///
		/// \brief	Translate this geometry.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	t	The translation vector.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void translate(Math::Vector3 const & t)
		{
			for(auto it=m_vertices.begin(), end=m_vertices.end() ; it!=end ; ++it)
			{
				(*it) = (*it)+t ; 
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::scale(float v)
		///
		/// \brief	Applies a scale factor on this geometry.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	v	The scale factor.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void scale(float v)
		{
			for(auto it=m_vertices.begin(), end=m_vertices.end() ; it!=end ; ++it)
			{
				(*it) = (*it)*v ;
			}
			updateTriangles() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::scaleX(float v)
		///
		/// \brief	Scales geometry on X axis.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	v	The scale factor on X axis.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void scaleX(float v)
		{
			for(auto it=m_vertices.begin(), end=m_vertices.end() ; it!=end ; ++it)
			{
				(*it)[0] = (*it)[0]*v ;
			}
			updateTriangles() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::scaleY(float v)
		///
		/// \brief	Scales geometry on Y axis.
		/// 		
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	v	The scale factor.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void scaleY(float v)
		{
			for(auto it=m_vertices.begin(), end=m_vertices.end() ; it!=end ; ++it)
			{
				(*it)[1] = (*it)[1]*v ;
			}
			updateTriangles() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::scaleZ(float v)
		///
		/// \brief	Scales the geometry on Z axis.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	v	The scale factor.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void scaleZ(float v)
		{
			for(auto it=m_vertices.begin(), end=m_vertices.end() ; it!=end ; ++it)
			{
				(*it)[2] = (*it)[2]*v ;
			}
			updateTriangles() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Geometry::rotate(Math::Quaternion const & q)
		///
		/// \brief	Rotates this geometry.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	q	Quaternion describing the rotation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void rotate(Math::Quaternion const & q)
		{
			for(auto it=m_vertices.begin(), end=m_vertices.end() ; it!=end ; ++it)
			{
				(*it) = q.rotate(*it).v() ;
			}
			updateTriangles() ;
		}
	} ;

}


#endif
