#ifndef _Geometry_Cylinder_H
#define _Geometry_Cylinder_H

#include <Geometry/Geometry.h>
#include <Geometry/Material.h>

namespace Geometry
{
	/** \brief Classe décrivant la géométrie d'un cylindre */

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Cylinder
	///
	/// \brief	A cylinder centered in (0,0,0), 1.0 height, 1.0 diameter.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	04/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Cylinder : public Geometry
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Cylinder::Cylinder(int nbDiv, float scaleDown, float scaleUp, Material * material)
		///
		/// \brief	Constructor
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	nbDiv	 	Number of base circle subdivisions.
		/// \param	scaleDown	Radius of the bottom circle.
		/// \param	scaleUp  	Radius of the top circle.
		/// \param	material 	The material.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Cylinder(int nbDiv, float scaleDown, float scaleUp, Material * material)
		{
			Disk disk1(nbDiv, material) ;
			disk1.scale(scaleUp) ;
			disk1.translate(Math::Vector3(0.0, 0.0, 0.5)) ;

			Disk disk2(nbDiv, material) ;
			disk2.scale(scaleDown) ;
			disk2.translate(Math::Vector3(0.0, 0.0, -0.5)) ;

			merge(disk1) ;
			merge(disk2) ;

			for(int cpt=0 ; cpt<nbDiv ; cpt++)
			{
				addTriangle(disk1.getVertices()[cpt], disk1.getVertices()[(cpt+1)%nbDiv], disk2.getVertices()[cpt], material) ;
				addTriangle(disk1.getVertices()[(cpt+1)%nbDiv], disk2.getVertices()[cpt], disk2.getVertices()[(cpt+1)%nbDiv], material) ;
				//addTriangle(new Triangle(disk1.getVertices()[cpt], disk1.getVertices()[(cpt+1)%nbDiv], 
				//			disk2.getVertices()[cpt], material)) ;
				//addTriangle(new Triangle(disk1.getVertices()[(cpt+1)%nbDiv], disk2.getVertices()[cpt], 
				//			disk2.getVertices()[(cpt+1)%nbDiv], material)) ;
			}
		}
	};
}

#endif
