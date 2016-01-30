#include <Math/Vector3.h>
#include <Geometry/Ray.h>
#include <Geometry/Triangle.h>
#include <Geometry/CastedRay.h>
#include <stdlib.h>
#include <iostream>
#include <Geometry/RGBColor.h>
#include <Geometry/Material.h>
#include <Geometry/PointLight.h>
#include <Geometry/Camera.h>
#include <Geometry/Cube.h>
#include <Geometry/Disk.h>
#include <Geometry/Cylinder.h>
#include <Geometry/Cone.h>
#include <Visualizer/Visualizer.h>
#include <Geometry/Scene.h>
#include <Geometry/Cornel.h>
#include <Geometry/BoundingBox.h>
//#include <omp.h>

//Test

using Geometry::RGBColor ;
using Geometry::Cone ;

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void initDiffuse(Geometry::Scene & scene)
///
/// \brief	Adds a Cornell Box with diffuse material on each walls to the scene. This Cornel box
/// 		contains two cubes.
///
/// \author	F. Lamarche, Université de Rennes 1
/// \date	03/12/2013
///
/// \param [in,out]	scene	The scene.
////////////////////////////////////////////////////////////////////////////////////////////////////
void initDiffuse(Geometry::Scene & scene)
{
	Geometry::Material * material = new Geometry::Material(RGBColor(), RGBColor(0,0,0.0), RGBColor(0.95f,0.95f,0.95f), RGBColor(), 1) ;
	Geometry::Material * material2 = new Geometry::Material(RGBColor(), RGBColor(1.0,1.0,1.0), RGBColor(0,0,0), RGBColor(), 1000) ;
	Geometry::Material * cubeMat = new Geometry::Material(RGBColor(), RGBColor(1.0f,0.0,0.0), RGBColor(0.0,0.0,0.0),RGBColor(10.0,0,0), 10.0f) ;
	Geometry::Cornel geo(material2, material2, material2, material2, material2, material2) ; 

	geo.scaleX(10) ;
	geo.scaleY(10) ;
	geo.scaleZ(10) ;
	scene.add(geo) ;

	Geometry::Cube tmp(cubeMat) ;
	tmp.translate(Math::Vector3(1.5,-1.5,0.0)) ;
	scene.add(tmp) ;
	
	Geometry::Cube tmp2(cubeMat) ;
	tmp2.translate(Math::Vector3(2,1,-4)) ;
	scene.add(tmp2) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void initSpecular(Geometry::Scene & scene)
///
/// \brief	Adds a Cornel box in the provided scene. Walls are specular and the box contains two 
/// 		cubes.
///
/// \author	F. Lamarche, Université de Rennes 1
/// \date	03/12/2013
////////////////////////////////////////////////////////////////////////////////////////////////////
void initSpecular(Geometry::Scene & scene)
{
	Geometry::Material * material = new Geometry::Material(RGBColor(), RGBColor(0,0,0.0), RGBColor(0.7f,0.7f,0.7f), RGBColor(), 100) ;
	Geometry::Material * material2 = new Geometry::Material(RGBColor(), RGBColor(0,0,1.0f), RGBColor(0,0,0), RGBColor(), 1000) ;
	Geometry::Material * cubeMat = new Geometry::Material(RGBColor(), RGBColor(1.0f,0.0,0.0), RGBColor(0.0,0.0,0.0), RGBColor(10.0,0,0), 20.0f) ;
	Geometry::Cornel geo(material, material, material, material, material, material) ; //new Geometry::Cube(material2) ;////new Cone(4, material) ; //new Geometry::Cylinder(5, 1, 1, material) ;////////new Geometry::Cube(material) ;////; //new Geometry::Cube(material) ; //new Geometry::Cylinder(100, 2, 1, material) ; //

	geo.scaleX(10) ;
	geo.scaleY(10) ;
	geo.scaleZ(10) ;
	scene.add(geo) ;

	Geometry::Cube tmp(cubeMat) ;
	tmp.translate(Math::Vector3(1.5,-1.5,0.0)) ;
	scene.add(tmp) ;
	//geo->merge(tmp) ;

	Geometry::Cube tmp2(cubeMat) ;
	tmp2.translate(Math::Vector3(2,1,-4)) ;
	scene.add(tmp2) ;
	//geo->merge(tmp2) ;
	//return geo ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void initDiffuseSpecular(Geometry::Scene & scene)
///
/// \brief	Adds a Cornel box in the provided scene. The cornel box as diffuse and specular walls and 
/// 		contains two boxes.
///
/// \author	F. Lamarche, Université de Rennes 1
/// \date	03/12/2013
///
/// \param [in,out]	scene	The scene.
////////////////////////////////////////////////////////////////////////////////////////////////////
void initDiffuseSpecular(Geometry::Scene & scene)
{
	Geometry::Material * material = new Geometry::Material(RGBColor(), RGBColor(0,0,0.0), RGBColor(0.7f,0.7f,0.7f), RGBColor(), 100) ;
	Geometry::Material * material2 = new Geometry::Material(RGBColor(), RGBColor(1,1,1.0f), RGBColor(0,0,0), RGBColor(), 1000) ;

	Geometry::Material * cubeMat = new Geometry::Material(RGBColor(), RGBColor(0.0f,100.0f,0.0f), RGBColor(0.0f,0.0f,0.0f), RGBColor(), 20.0f) ;
	Geometry::Material * cubeMat2 = new Geometry::Material(RGBColor(), RGBColor(10.0f,0.0f,0.0f), RGBColor(0.0f,0.0f,0.0f), RGBColor(), 20.0f) ;
	Geometry::Material * cubeMat3 = new Geometry::Material(RGBColor(), RGBColor(0.2f, 0.8f, 1.0f), RGBColor(0.0f, 0.0f, 0.0f), RGBColor(), 30.0f);
	
	Geometry::Material * transparent = new Geometry::Material(RGBColor(), RGBColor(1.0f,1.0f,1.0f), RGBColor(), RGBColor(), 0, 1.5);
	
	Geometry::Cornel geo(material2, material2, material, material, material, material) ; //new Geometry::Cube(material2) ;////new Cone(4, material) ; //new Geometry::Cylinder(5, 1, 1, material) ;////////new Geometry::Cube(material) ;////; //new Geometry::Cube(material) ; //new Geometry::Cylinder(100, 2, 1, material) ; //

	geo.scaleX(10) ;
	geo.scaleY(10) ;
	geo.scaleZ(10) ;
	scene.add(geo) ;

	Geometry::Cube tmp(cubeMat2) ;
	tmp.translate(Math::Vector3(2,0,-4)) ;
	scene.add(tmp) ;

	Geometry::Cube tmp2(cubeMat) ;
	tmp2.translate(Math::Vector3(2,2,-4)) ;
	scene.add(tmp2) ;

	Geometry::Cube tmp3(cubeMat3);
	tmp3.translate(Math::Vector3(3,-1.5,0.0));
	scene.add(tmp3);

	Geometry::Disk tmp4(20,transparent);
	tmp4.translate(Math::Vector3(0.5, 1, -3));
	scene.add(tmp4);
}

void initGlobal(Geometry::Scene & scene)
{
	Geometry::Material * material = new Geometry::Material(RGBColor(), RGBColor(0,0,0.0), RGBColor(0.7f,0.7f,0.7f), RGBColor(), 100.0f) ;
	Geometry::Material * material2 = new Geometry::Material(RGBColor(), RGBColor(1.0,1.0,1.0f), RGBColor(0,0,0), RGBColor(), 1000.0f) ;
	Geometry::Material * material3 = new Geometry::Material(RGBColor(), RGBColor(1, 0.8f, 0.0f), RGBColor(0.5f, 0.5f, 0.5f), RGBColor(), 100);

	Geometry::Material * cubeMat = new Geometry::Material(RGBColor(), RGBColor(0.0f,100.0f,0.0f), RGBColor(0.0f,0.0f,0.0f), RGBColor(0.0f,100.0f,0.0f), 20.0f) ;
	Geometry::Material * cubeMat2 = new Geometry::Material(RGBColor(), RGBColor(10.0f,0.0f,0.0f), RGBColor(0.0f,0.0f,0.0f), RGBColor(10.0f,0.0f,0.0f), 20.0f) ;
	Geometry::Material * cubeMat3 = new Geometry::Material(RGBColor(), RGBColor(0.2f, 0.8f, 1.0f), RGBColor(0.0f, 0.0f, 0.0f), RGBColor(0.2f, 0.8f, 1.0f), 30.0f);

	Geometry::Material * transparent = new Geometry::Material(RGBColor(), RGBColor(1.0f,1.0f,1.0f), RGBColor(), RGBColor(), 0, 1.5);
	
	Geometry::Cornel geo(material2, material2, material, material, material, material) ; //new Geometry::Cube(material2) ;////new Cone(4, material) ; //new Geometry::Cylinder(5, 1, 1, material) ;////////new Geometry::Cube(material) ;////; //new Geometry::Cube(material) ; //new Geometry::Cylinder(100, 2, 1, material) ; //

	geo.scaleX(10) ;
	geo.scaleY(10) ;
	geo.scaleZ(10) ;
	scene.add(geo) ;


	Geometry::Cube tmp(cubeMat2) ;
	tmp.translate(Math::Vector3(2,0,-4)) ;
	scene.add(tmp) ;

	Geometry::Cube tmp2(cubeMat) ;
	tmp2.translate(Math::Vector3(2,2,-4)) ;
	scene.add(tmp2) ;

	Geometry::Cube tmp3(cubeMat3);
	tmp3.translate(Math::Vector3(0,-1.5,0.0));
	scene.add(tmp3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void waitKeyPressed()
///
/// \brief	Waits until a key is pressed.
/// 		
/// \author	F. Lamarche, Université de Rennes 1
/// \date	03/12/2013
////////////////////////////////////////////////////////////////////////////////////////////////////
void waitKeyPressed()
{
  SDL_Event event;
  bool done = false;
  while( !done ) {
    while ( SDL_PollEvent(&event) ) {
      switch (event.type) {
        case SDL_KEYDOWN:
        /*break;*/
        case SDL_QUIT:
          done = true;
        break;
        default:
        break;
      }
    }/*while*/
  }/*while(!done)*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	int main(int argc, char ** argv)
///
/// \brief	Main entry-point for this application.
///
/// \author	F. Lamarche, Université de Rennes 1
/// \date	03/12/2013
///
/// \param	argc	Number of command-line arguments.
/// \param	argv	Array of command-line argument strings.
///
/// \return	Exit-code for the process - 0 for success, else an error code.
////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
	 //omp_set_num_threads(8);

	// 1 - Initializes a window for rendering
	//Visualizer::Visualizer visu(600,600) ;
	Visualizer::Visualizer visu(300,300) ;
	//Visualizer::Visualizer visu(200,200) ;

	// 2 - Initializes the scene
	Geometry::Scene scene(&visu) ;

	// 2.1 intializes the geometry (choose only one initialization)
	int choix = 0;

	cout << "Choisissez le type de la scene:" << endl;
	cout << "1.Scene avec le diffus" << endl;
	cout << "2.Scene avec le speculaire" << endl;
	cout << "3.Scene avec le diffus,speculaire et réfraction" << endl;
	cout << "4.Scene avec l'illumination globale" << endl;
	cout << "5.Quitter" << endl;
	//cin >> choix;
	choix = 4;

	switch (choix)
	{
		case 1:
			initDiffuse(scene);
			break;

		case 2:
			initSpecular(scene);
			break;

		case 3:
			initDiffuseSpecular(scene);
			break;
		
		case 4:
			initGlobal(scene);
			break;

		default:
			return 0;
	}


	// 2.2 Adds point lights in the scene 
	{
		Geometry::PointLight pointLight(Math::Vector3(0.0,0,2.0f), RGBColor(0.8f,0.8f,0.8f)) ;
		scene.add(pointLight) ;
	}
	{
		Geometry::PointLight pointLight2(Math::Vector3(4,0,0), RGBColor(0.5f,0.5f,0.5f)) ;
		scene.add(pointLight2) ;
	}
	{
		Geometry::Camera camera(Math::Vector3(-4.0f, 0.0, 0.0), Math::Vector3(0.0, 0.0, 0.0), 0.3f, 1.0f, 1.0f) ;  // (Math::Vector3(-4.0f, 0.0, 0.0), Math::Vector3(0.0, 0.0, 0.0), 0.3f, 1.0f, 1.0f)
		scene.setCamera(camera) ;
	}

	// 3 - Computes the scene
	scene.compute(2);

	// 4 - waits until a key is pressed
	waitKeyPressed();

	return 0 ;
}
