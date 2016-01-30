#ifndef _Geometry_RGBColor
#define _Geometry_RGBColor

namespace Geometry
{
	/** \brief Représentation d'une couleur */

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	RGBColor
	///
	/// \brief	A Red / Green / Blue color. Each component should be in range [0;1]. If a component 
	/// 		value is greater than 1, rendering should be able to handle HDR.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	04/12/2013
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class RGBColor
	{
	protected:
		/// \brief	The red(0), green(1) and blue (2) components.
		float m_color[3] ;

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RGBColor::RGBColor(float R=0, float G=0, float B=0)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	R	Red component.
		/// \param	G	Green component.
		/// \param	B	Blue component.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RGBColor(float R=0, float G=0, float B=0)
		{
			//if(R>1.0) R = 1.0 ;
			//if(G>1.0) G = 1.0 ;
			//if(B>1.0) B = 1.0 ;
			m_color[0] = R ;
			m_color[1] = G ;
			m_color[2] = B ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RGBColor RGBColor::operator+ (RGBColor const & c) const
		///
		/// \brief	Addition operator.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	c	The other color.
		///
		/// \return	The sum of this color with the provided one.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RGBColor operator+ (RGBColor const & c) const
		{
			return RGBColor(c.m_color[0]+m_color[0], c.m_color[1]+m_color[1], c.m_color[2]+m_color[2]) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RGBColor RGBColor::operator* (RGBColor const & c) const
		///
		/// \brief	Multiplication operator. Multiplication is achieved by multiplying the two red components,
		/// 		the two green components and the two blue components.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	c	The other rgb color.
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RGBColor operator* (RGBColor const & c) const
		{
			return RGBColor(c.m_color[0]*m_color[0], c.m_color[1]*m_color[1], c.m_color[2]*m_color[2]) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RGBColor RGBColor::operator* (float v) const
		///
		/// \brief	Multiplies a color by a scalar value.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	v	The scalar.
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RGBColor operator* (float v) const
		{
			return RGBColor(m_color[0]*v, m_color[1]*v, m_color[2]*v) ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	RGBColor RGBColor::operator/ (float v) const
		///
		/// \brief	Devides a color by a scalar value.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	v	The scalar.
		///
		/// \return	The result of the operation.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		RGBColor operator/ (float v) const
		{
			return RGBColor(m_color[0]/v, m_color[1]/v, m_color[2]/v) ;			
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	float RGBColor::operator[] (int c) const
		///
		/// \brief	Access to each color component. 0: red, 1: green, 2: blue.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	c	The index of the component.
		///
		/// \return	The value of the component.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float operator[] (int c) const
		{
			return m_color[c] ;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	float & RGBColor::operator[] (int c)
		///
		/// \brief	Access to each color component. 0: red, 1: green, 2: blue.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	04/12/2013
		///
		/// \param	c	The index of the component.
		///
		/// \return	The value of the component.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		float & operator[] (int c)
		{
			return m_color[c] ;
		}

		bool operator==(RGBColor const & color) const
		{
			return m_color[0]==color[0] && m_color[1]==color[1] && m_color[2]==color[2] ;
		}

		bool operator!=(RGBColor const & color) const
		{
			return !((*this)==color) ;
		}
	} ;
}

#endif
