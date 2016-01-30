#ifndef _Math_Quaternion_H
#define _Math_Quaternion_H

#include <Math/Vector3.h>
#include <Math/Object.h>

namespace Math
{
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /// \class	Quaternion
  ///
  /// \brief	A quaternion.
  ///
  /// \author	F. Lamarche, Université de Rennes 1
  /// \date	03/12/2013
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  class Quaternion : public Object
  {
  protected:
    float   m_s ;
    Vector3 m_v ;

    float m_angle ;
    Vector3 m_axis ;

  public:

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion::Quaternion()
    ///
    /// \brief	Default constructor. 
    /// 		
    /// \warning Initializes nothing.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion()
    {}

    /** \brief Constructor with vector/angle arguments */

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion::Quaternion(Vector3 const & v, float const & angle)
    ///
    /// \brief	Constructor with rotation axis and angle.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	v	 	The rotation axis.
    /// \param	angle	The angle.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion(Vector3 const & v, float const & angle)
      : m_s((float)cos(angle/2.0)), m_v(v*(float)sin(angle/2.0)), m_angle(angle), m_axis(v)
    {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion::Quaternion(Vector3 const & v)
    ///
    /// \brief	Constructor from a point.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	v	The point
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion(Vector3 const & v)
      : m_s(0.0), m_v(v), m_angle(0.0), m_axis(v) 
    {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion::Quaternion(Quaternion const & q)
    ///
    /// \brief	Copy constructor.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	q	The Quaternion const &amp; to process.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion(Quaternion const & q)
      : m_s(q.m_s), m_v(q.m_v), m_angle(q.m_angle), m_axis(q.m_axis)
    {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion::Quaternion(float const & s, Vector3 const & v)
    ///
    /// \brief	Constructor with quaternion representation.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	s	
    /// \param	v	
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion(float const & s, Vector3 const & v)
      : m_s(s), m_v(v)
    {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	float Quaternion::getAngle() const
    ///
    /// \brief	Gets the rotation angle.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \return	The angle.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    float getAngle() const
    { return m_angle ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Vector3 const & Quaternion::getAxis() const
    ///
    /// \brief	Gets the rotation axis.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \return	The axis.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Vector3 const & getAxis() const
    { return m_axis ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	void Quaternion::setAxisAngle(Vector3 const & v, float angle)
    ///
    /// \brief	Sets the quaternion from an axis and an angle.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	v	 	The rotation axis.
    /// \param	angle	The angle.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void setAxisAngle(Vector3 const & v, float angle)
    {
      m_s = (float)cos(angle/2.0f) ;
      m_v = v*sin(angle/2.0f) ;
      m_angle = angle ;
      m_axis  = v ;
    }

    float & s()
    { return m_s ; }

    float s() const
    { return m_s ; }

    Vector3 v() const
    { return m_v ; }

    Vector3 & v()
    { return m_v ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion Quaternion::operator+ (Quaternion const & q) const
    ///
    /// \brief	Addition operator.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	q	The other quaternion 
    ///
    /// \return	The addition of this quaternion and the other.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion operator+ (Quaternion const & q) const
    {	return Quaternion(m_s+q.m_s, m_v+q.m_v) ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion Quaternion::operator- (Quaternion const & q) const
    ///
    /// \brief	Soustraction operator.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	q	The other quaternion.
    ///
    /// \return	The result of the operation.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion operator- (Quaternion const & q) const
    {	return Quaternion(m_s+q.m_s, m_v+q.m_v) ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion Quaternion::operator* (Quaternion const & q) const
    ///
    /// \brief	Multiplication operator.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	q	The other quaternion.
    ///
    /// \return	The result of the operation.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion operator* (Quaternion const & q) const
    {
      return Quaternion(m_s*q.m_s-m_v*q.m_v, q.m_v*m_s+m_v*q.m_s+(m_v^q.m_v)) ; 
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion Quaternion::operator* (float const & v) const
    ///
    /// \brief	Multiplication operator.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	v	The scalar.
    ///
    /// \return	The result of the operation.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion operator* (float const & v) const
    {	return Quaternion(m_s*v, m_v*v) ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion Quaternion::operator/ (float const & v) const
    ///
    /// \brief	Division operator.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	v	The scalar.
    ///
    /// \return	The result of the operation.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion operator/ (float const & v) const
    {	return Quaternion(m_s/v, m_v/v) ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion Quaternion::operator- () const
    ///
    /// \brief	Negation operator.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \return	The result of the operation.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion operator- () const
    {   return Quaternion(-m_s, -m_v) ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion Quaternion::inv() const
    ///
    /// \brief	Gets the inverse of the quaternion.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \return	.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion inv() const
    {   return Quaternion(m_s, -m_v) ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	float Quaternion::norm2() const
    ///
    /// \brief	Gets the square of the quaternion norm.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \return	.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    float norm2() const
    {   return m_s*m_s+m_v.norm2() ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	float Quaternion::norm() const
    ///
    /// \brief	Gets the norm of the quaternion.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \return	.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    float norm() const
    {	return sqrt(this->norm2()) ; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion & Quaternion::operator= (Quaternion const & q)
    ///
    /// \brief	Assignment operator.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	q	The other quaternion.
    ///
    /// \return	A shallow copy of this object.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion & operator= (Quaternion const & q)
    {
      m_s = q.m_s ;
      m_v = q.m_v ;
      return (*this) ;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion & Quaternion::normalize()
    ///
    /// \brief	Normalizes this quaternion.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \return	.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion & normalize() 
    {
      (*this) = (*this)/this->norm() ;
      return *this ;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// \fn	Quaternion Quaternion::rotate(Quaternion const & q) const
    ///
    /// \brief	Rotates the given quaternion.
    ///
    /// \author	F. Lamarche, Université de Rennes 1
    /// \date	03/12/2013
    ///
    /// \param	q	The Quaternion const &amp; to process.
    ///
    /// \return	.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Quaternion rotate(Quaternion const & q) const
    {
      return (*this)*q*this->inv() ;
    }
  };
} 

#endif
