#ifndef _Geometry_camera_H
#define _Geometry_camera_H

#include <Math/Vector3.h>
#include <Math/Quaternion.h>
#include <Geometry/Ray.h>
#include <math.h>

namespace Geometry
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Camera
	///
	/// \brief	A camera.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	04/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Camera
	{
	protected:
		/// \brief	The camera position.
		Math::Vector3 m_position ;
		/// \brief	The aim of the camera.
		Math::Vector3 m_target ;
		/// \brief	Distance of the focal plane.
		float		  m_planeDistance ;
		/// \brief	Width of the projection rectangle.
		float	      m_planeWidth ;
		/// \brief	Height of the projection rectangle.
		float		  m_planeHeight ;
		/// \brief	The front vector of the camera.
		Math::Vector3 m_front ;
		/// \brief	The right vector.
		Math::Vector3 m_right ;
		/// \brief	The down vector.
		Math::Vector3 m_down ;
		/// \brief	The width vector of the projection rectangle.
		Math::Vector3 m_widthVector ;
		/// \brief	The height vector of the projection rectangle.
		Math::Vector3 m_heightVector ;
		/// \brief	The upper left point oft he projection rectangle.
		Math::Vector3 m_upLeftPoint ;
	
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Camera::computeParameters()
		///
		/// \brief	Calculates the camera parameters.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void computeParameters()
		{
			m_front = m_target-m_position ;
			m_front = m_front/m_front.norm() ;
			m_right = Math::Quaternion(Math::Vector3(0.0f, 0.0f, 1.0f), -3.14159265f/2.0f).rotate(m_front).v() ;
			m_right = m_right/m_right.norm() ;
			m_down  = m_front^m_right ;
			m_down  = m_down/m_down.norm() ;
			m_widthVector  = m_right*m_planeWidth ;
			m_heightVector = m_down*m_planeHeight ;
			m_upLeftPoint  = m_position+m_front*m_planeDistance-m_widthVector*0.5-m_heightVector*0.5 ;
		}

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Camera::Camera(Math::Vector3 const & position = Math::Vector3(0.0, 0.0, 0.0),
		/// 	Math::Vector3 const & target = Math::Vector3(0.0, 1.0, 0.0), float planeDistance=1.0,
		/// 	float planeWidth=1.0, float planeHeight=1.0)
		///
		/// \brief	Constructeur de la caméra.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	position	 	The camera position
		/// \param	target		 	The target of the camera
		/// \param	planeDistance	La distance of the focal plane.
		/// \param	planeWidth   	Width of the projection rectangle.
		/// \param	planeHeight  	Height of the projection rectangle.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Camera(Math::Vector3 const & position = Math::Vector3(0.0, 0.0, 0.0), 
			   Math::Vector3 const & target = Math::Vector3(0.0, 1.0, 0.0), 
			   float planeDistance=1.0, float planeWidth=1.0, float planeHeight=1.0)
		   : m_position(position), m_target(target), m_planeDistance(planeDistance), 
		     m_planeWidth(planeWidth), m_planeHeight(planeHeight)
		{
			computeParameters() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Camera::setPosition(Math::Vector3 const & position)
		///
		/// \brief	Sets the camera position position.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	position	The new camera position.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setPosition(Math::Vector3 const & position)
		{
			m_position = position ;
			computeParameters() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	void Camera::setTarget(Math::Vector3 const & target)
		///
		/// \brief	Sets the target.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	target	The new target.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void setTarget(Math::Vector3 const & target)
		{
			m_target = target ;
			computeParameters() ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Ray Camera::getRay(float coordX, float coordY) const
		///
		/// \brief	Get a primary ray from screen coordinates (coordX, coordY)
		/// 		
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	coordX	X coordinate in the projection rectangle.
		/// \param	coordY	Y coordinate in the projection rectangle.
		///
		/// \return	The ray.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Ray getRay(float coordX, float coordY) const
		{
			return Ray(m_position, m_upLeftPoint+m_widthVector*coordX+m_heightVector*coordY-m_position) ;
		}
	} ;
}

#endif
