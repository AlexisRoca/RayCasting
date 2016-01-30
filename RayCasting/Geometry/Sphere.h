#ifndef _Geometry_Sphere_H
#define _Geometry_Sphere_H

#include <Geometry/Geometry.h>
#include <Geometry/Material.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

namespace Geometry
{
	/** \brief Représentation d'une sphere */

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Sphere
	///
	/// \brief	A sphere, centered in (0,0,0), 1.0 radius.
	///
	/// \author	Ific Goudé, ESIR 2
	/// \date	16/12/2015
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Sphere : public Geometry
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Cone::Cone(int nbDiv, Material * material)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	nbDiv   	Number of base circle subdivisions.
		/// \param	material	The material.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sphere(int nbDiv, Material * material)
		{
			int center = addVertex(Math::Vector3()) ;
			::std::vector<unsigned int> vertices;
			for (int cpt1 = 0; cpt1<nbDiv; cpt1++)
			{
				float theta = float(cpt1 * M_PI / nbDiv);
				
				for (int cpt2 = 0; cpt2 < nbDiv; cpt2++)
				{
					float phi = float(cpt2 * 2 * M_PI / nbDiv);

					float x = cos(phi) * sin(theta);
					float y = cos(theta);
					float z = sin(phi) * sin(theta);

					int i = addVertex(Math::Vector3(x/2, y/2, z/2 ));
					
					vertices.push_back(i);
				}
			}
			for (int cpt1 = 0; cpt1<nbDiv; cpt1++)
			{
				for (int cpt2 = 0; cpt2 < nbDiv; cpt2++)
				{
					int first = (cpt1 * (nbDiv + 1)) + cpt2;
					int second = first + nbDiv + 1;

					addTriangle(vertices[first], vertices[first+1], vertices[second], material);
					addTriangle(vertices[first+1], vertices[second], vertices[second+1], material);

				}
			}
		}
	} ;
}

#endif