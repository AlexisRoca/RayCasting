#ifndef _Geometry_Scene_H
#define _Geometry_Scene_H

#include <limits>
#include <windows.h>
#include <Geometry/Geometry.h>
#include <Geometry/PointLight.h>
#include <Visualizer/Visualizer.h>
#include <Geometry/Camera.h>
#include <Geometry/BoundingBox.h>
#include <Math/RandomDirection.h>
#include <windows.h>
#include <System/aligned_allocator.h>

using namespace std;

namespace Geometry
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Scene
	///
	/// \brief	An instance of a geometric scene that can be rendered using ray casting. A set of methods
	/// 		allowing to add geometry, lights and a camera are provided. Scene rendering is achieved by
	/// 		calling the Scene::compute method.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	03/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Scene
	{
	public:
		int count;		

	protected:
		/// \brief	The visualizer (rendering target).
		Visualizer::Visualizer * m_visu ;
		/// \brief	The scene geometry (basic representation without any optimization).
		::std::deque<::std::pair<BoundingBox, Geometry> > m_geometries ;
		//Geometry m_geometry ;
		/// \brief	The lights.
		std::deque<PointLight, aligned_allocator<PointLight, 16> > m_lights ;
		/// \brief	The camera.
		Camera m_camera ;


	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Scene::Scene(Visualizer::Visualizer * visu)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param [in,out]	visu	ifnon-null, the visu.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Scene(Visualizer::Visualizer * visu)
			: m_visu(visu),count(0)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Scene::add(const Geometry & geometry)
		///
		/// \brief	Adds a geometry to the scene.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	03/12/2013
		///
		/// \param	geometry The geometry to add.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void add(const Geometry & geometry)
		{
			//m_geometry.merge(geometry) 
			BoundingBox box(geometry) ;
			m_geometries.push_back(::std::make_pair(box, geometry)) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Scene::add(PointLight * light)
		///
		/// \brief	Adds a poitn light in the scene.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param [in,out]	light	ifnon-null, the light to add.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void add(const PointLight & light)
		{
			m_lights.push_back(light) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Scene::setCamera(Camera const & cam)
		///
		/// \brief	Sets the camera.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	cam	The camera.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setCamera(Camera const & cam)
		{
			m_camera = cam ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RGBColor Scene::sendRay(Ray const & ray, float limit, int depth, int maxDepth)
		///
		/// \brief	Sends a ray in the scene and returns the computed color
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	ray			The ray.
		/// \param	depth   	The current depth.
		/// \param	maxDepth	The maximum depth.
		///
		/// \return	The computed color.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RGBColor sendRay(Ray const & ray, int depth, int maxDepth)
		{
			const int maxRays = 300;

			//
			if (depth == maxDepth)
				return emissiveColor(rayIntersection(ray));
			
			else
				// si le triangle intersecté est "transparent"/"translucide" (indice de réfraction != 0)
				if(rayIntersection(ray).triangle()->material()->refractionIndex() != 0)
					//on relance un rayon suivant la direction refracté de profondeur 2
					return refraction(rayIntersection(ray));
				
			
				else
					//On calcule les composantes diffuse et spéculaire
					//return diffuseColor(rayIntersection(ray)) + specular_indirectColor(rayIntersection(ray), depth, maxDepth);		
					return global_diffuseColor(rayIntersection(ray),maxRays, depth, maxDepth) + global_specular_indirectColor(rayIntersection(ray),maxRays, depth, maxDepth);
		}

		RayTriangleIntersection rayIntersection (Ray const & ray)
		{
			int index_g = 0, index_t = 0;	
			float profondeur_min = std::numeric_limits<float>::max();

			CastedRay castedRay (ray.source(),ray.direction());

			for(int i=0;i<(this->m_geometries).size();i++)
			{
				for(int j=0;j<((this->m_geometries[i].second).getTriangles()).size();j++)
				{
					float profondeur, bidon2, bidon3;

					if(((this->m_geometries[i].second).getTriangles()[j]).intersection(ray,profondeur,bidon2,bidon3))
					{
						if(profondeur < profondeur_min)
						{
							profondeur_min = profondeur;
							index_g = i;
							index_t = j;
						}
					}
				}
			}

			return RayTriangleIntersection(&((this->m_geometries[index_g].second).getTriangles()[index_t]), &ray);
		}

		RGBColor diffuseColor(RayTriangleIntersection const & triangle_intersecte)
		{
			RGBColor diffuseReflection(0, 0, 0);
			RGBColor Kd = triangle_intersecte.triangle()->material()->diffuseColor();
			Math::Vector3 N = triangle_intersecte.triangle()->normal();

			for(int i = 0; i<m_lights.size(); i++)
			{
				Math::Vector3 L = (m_lights[i].position() - (triangle_intersecte.intersection())) / ((m_lights[i].position() - (triangle_intersecte.intersection())).norm());

				Ray light(m_lights[i].position(), -L);
	
				//Test des ombres
				if(!shadow(light, triangle_intersecte.triangle()))
				{
					//On vérifie que la normale de l'objet est dans le bon sens
					if(L * N < 0)
						N = N * -1;

					RGBColor Isource;
					//On vérifie si le triangle intersecté est éclairé
					if((triangle_intersecte.ray()->direction()*(-1)) * N < 0)
						Isource = (0, 0, 0);
					else
						Isource = m_lights[i].color();

					//calcul du diffus
					float cos = N * L;
					float d = (m_lights[i].position() - (triangle_intersecte.intersection())).norm();

					diffuseReflection = diffuseReflection + Kd * Isource * cos / d;
				}
			}

			count++;
			return diffuseReflection;
		}


		RGBColor emissiveColor(RayTriangleIntersection const & triangle_intersecte)
		{
			return triangle_intersecte.triangle()->material()->emissiveColor();
		}

		RGBColor specular_directColor(RayTriangleIntersection const & triangle_intersecte)
		{
			RGBColor specular_directColor(0, 0, 0);

			RGBColor Ks = (triangle_intersecte.triangle()->material())->specularColor();
			Math::Vector3 N = triangle_intersecte.triangle()->normal();
			int n = (triangle_intersecte.triangle()->material())->specularExponent();
		

			for(int i = 0; i < m_lights.size(); i++)
			{
				Math::Vector3 L = (m_lights[i].position() - (triangle_intersecte.intersection())) / ((m_lights[i].position() - (triangle_intersecte.intersection())).norm());
				Ray light(m_lights[i].position(), -L);

				if(!shadow(light, triangle_intersecte.triangle()))
				{
					if(L * N < 0)
						N = N * -1;


					RGBColor Isource;
					if((triangle_intersecte.ray()->direction()*(-1)) * N < 0)
						Isource = (0, 0, 0);
					else
						Isource = m_lights[i].color();

					//calcul du spéculaire
					float d = (m_lights[i].position() - (triangle_intersecte.intersection())).norm();

					Math::Vector3 R = (triangle_intersecte.triangle()->reflectionDirection(light));
					Math::Vector3 V = (triangle_intersecte.ray()->source() - (triangle_intersecte.intersection())) / ((triangle_intersecte.ray()->source() - (triangle_intersecte.intersection())).norm());

					float cosn = pow(R*V , n);

					specular_directColor = specular_directColor + Ks * Isource * cosn / d;
				}
			}

			return specular_directColor;
		}


		RGBColor specular_indirectColor(RayTriangleIntersection const & triangle_intersecte, int depth, int maxDepth)
		{
			RGBColor specular_indirectColor(0, 0, 0);

			RGBColor Ks = (triangle_intersecte.triangle()->material())->specularColor();
			Math::Vector3 N = triangle_intersecte.triangle()->normal();
			int n = (triangle_intersecte.triangle()->material())->specularExponent();
		
			if(Ks != 0)
			{
				for(int i = 0; i < m_lights.size(); i++)
				{
					Math::Vector3 L = (m_lights[i].position() - (triangle_intersecte.intersection())) / ((m_lights[i].position() - (triangle_intersecte.intersection())).norm());
					Ray light(m_lights[i].position(), -L);

					if(!shadow(light, triangle_intersecte.triangle()))
					{
						if(L * N < 0)
							N = N * -1;


						RGBColor Isource;
						if((triangle_intersecte.ray()->direction()*(-1)) * N < 0)
							Isource = (0, 0, 0);
						else
							Isource = m_lights[i].color();


						float d = (m_lights[i].position() - (triangle_intersecte.intersection())).norm();

						Math::Vector3 R = (triangle_intersecte.triangle()->reflectionDirection(light));
						Math::Vector3 V = (triangle_intersecte.ray()->source() - (triangle_intersecte.intersection())) / ((triangle_intersecte.ray()->source() - (triangle_intersecte.intersection())).norm());

						float cosn = pow(R*V , n);

						//On ajoute la contributions d'autres objets pour le calcul du spéculaire
						Ray perfect_reflection((triangle_intersecte.intersection()), (triangle_intersecte.triangle()->reflectionDirection(triangle_intersecte.ray()->direction())));
						specular_indirectColor = specular_indirectColor + (Ks * Isource * cosn / d) + sendRay(perfect_reflection,depth+1,maxDepth);
					}
				}
			}

			return specular_indirectColor;
		}

		RGBColor global_diffuseColor(RayTriangleIntersection const & triangle_intersecte, int const maxRays, int depth, int maxDepth)
		{
			RGBColor diffuseReflection = (0, 0, 0);// diffuseColor(ray, geo_tri);

			RGBColor global_diffus = (0, 0, 0);
			RGBColor Kd = triangle_intersecte.triangle()->material()->diffuseColor();
			float d = triangle_intersecte.tRayValue();
			
			//On ne travaille plus avec des sources ponctuelles mais avec des surfaces emissives
			RGBColor surfaceLight = emissiveColor(triangle_intersecte);

			Math::Vector3 N = triangle_intersecte.triangle()->normal();
			if ((-triangle_intersecte.ray()->direction()) * N < 0)
				N = N * -1;

			//Création d'un générateur de direction suivant la loi cosinus
			Math::RandomDirection random_generator(N);

			if (Kd != 0)
			{
				//On récupère la contributions des autres objets
				for (int i = 0; i < maxRays; i++)
				{
					Math::Vector3 dir = random_generator.generate();
					Ray diffuseRay((triangle_intersecte.intersection())/*+dir*0.1*/, dir);
					global_diffus = global_diffus + (Kd * 1 * sendRay(diffuseRay, depth + 1, maxDepth) / d) + surfaceLight;
				}

				count++;
			}

			//On divise par le nombre de rayons générés pour moyenner le résultat
			return  global_diffus*(1.0f / maxRays);
		}

		RGBColor global_specular_indirectColor(RayTriangleIntersection const & triangle_intersecte, int const maxRays, int depth, int maxDepth)
		{
			RGBColor specular_indirectColor(0, 0, 0);

			RGBColor Ks = (triangle_intersecte.triangle()->material())->specularColor();
			int sh = (triangle_intersecte.triangle()->material())->specularExponent();
			float d = triangle_intersecte.tRayValue();
			RGBColor surfaceLight = emissiveColor(triangle_intersecte);

			if (Ks != 0)
			{
				Math::Vector3 N = triangle_intersecte.triangle()->normal();
				if ((-triangle_intersecte.ray()->direction()) * N < 0)
					N = N * -1;

				Math::Vector3 R = (triangle_intersecte.triangle()->reflectionDirection(*triangle_intersecte.ray()));
				Math::RandomDirection random_generator(R, sh);

				for (int i = 0; i < maxRays; i++)
				{
					Math::Vector3 dir = random_generator.generate();
					Ray specularRay(triangle_intersecte.intersection(), dir);
					specular_indirectColor = specular_indirectColor + (Ks  * sendRay(specularRay, depth + 1, maxDepth) / d) + surfaceLight;

				}
			}

			return specular_indirectColor*(1.0f / maxRays);
		}


		RGBColor refraction(RayTriangleIntersection const & triangle_intersecte)
		{
			//On crée un rayon dans la direction de la refraction et on récupère la couleur de l'objet derrière
			Ray refractionRay((triangle_intersecte.intersection()), (triangle_intersecte.triangle()->refractionDirection(*triangle_intersecte.ray())));
			return sendRay(refractionRay, 0, 2);
		}


		// Calcul des ombres 
		// Renvoie True si le triangle intersecté est dans l'ombre, False sinon
		bool shadow(Ray const & light, const Triangle * intersectionCamera)
		{
			//On compare le point intersecté par la lumière et par la camera
			return !(rayIntersection(light).triangle() ==  intersectionCamera);
		}



		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Scene::compute(int maxDepth)
		///
		/// \brief	Computes a rendering of the current scene, viewed by the camera.
		/// 		
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	maxDepth	The maximum recursive depth.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void compute(int maxDepth)
		{
			// Number of samples per axis forone pixel. Number of samples per pixels = subPixelSubdivision^2
			int subPixelDivision =  1 ; //50 ;//100 ;
			// Step on x and y forsubpixel sampling
			float step = 1.0/subPixelDivision ;
			// Table accumulating values computed per pixel (enable rendering of each pass)
			::std::vector<::std::vector<::std::pair<int, RGBColor> > > pixelTable(m_visu->width(), ::std::vector<::std::pair<int, RGBColor> >(m_visu->width(), ::std::make_pair(0, RGBColor()))) ;

			// 1 - Rendering time
			LARGE_INTEGER frequency;        // ticks per second
			LARGE_INTEGER t1, t2;           // ticks
			double elapsedTime;
			// get ticks per second
			QueryPerformanceFrequency(&frequency);
			// start timer
			QueryPerformanceCounter(&t1);
			// Rendering pass number
			int pass = 0 ;
			// Rendering
			for(float xp=-0.5 ; xp<0.5 ; xp+=step)
			{
				for(float yp=-0.5 ; yp<0.5 ; yp+=step)
				{
					::std::cout<<"Pass: "<<pass<<::std::endl ;
					++pass ;
					// Sends primary rays foreach pixel (uncomment the pragma to parallelize rendering)
#pragma omp parallel for//schedule(dynamic)
					for(int y=0 ; y<m_visu->height() ; y++)
					{
						for(int x=0 ; x<m_visu->width() ; x++)
						{
							//m_visu->plot(x,y,RGBColor(0.0,1.0,0.0)) ;
							//m_visu->update() ;
							// Ray casting
							RGBColor result = sendRay(m_camera.getRay(((float)x+xp)/m_visu->width(), ((float)y+yp)/m_visu->height()), 0, maxDepth)*5 ;
							// Accumulation of ray casting result in the associated pixel
							::std::pair<int, RGBColor> & currentPixel = pixelTable[x][y] ;
							currentPixel.first++ ;
							currentPixel.second = currentPixel.second + result ;
							// Pixel rendering (simple tone mapping)
							m_visu->plot(x,y,pixelTable[x][y].second/pixelTable[x][y].first) ;
							// Updates the rendering context (per pixel)
							//m_visu->update();
						}
						// Updates the rendering context (per line)
						m_visu->update();
					}
					// Updates the rendering context (per pass)
					m_visu->update();
				}
			}
			// stop timer
			QueryPerformanceCounter(&t2);
			elapsedTime = (t2.QuadPart - t1.QuadPart) / frequency.QuadPart;
			::std::cout<<"time: "<<elapsedTime<<"s. "<<::std::endl ;

			cout << "Nombre de lances de rayons:" << count << endl;

		}
	} ;
}

#endif
