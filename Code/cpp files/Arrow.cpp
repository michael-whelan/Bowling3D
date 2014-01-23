#include "Arrow.h"


Arrow::Arrow(Ogre::SceneNode * myGunBarrel, Ogre::Vector3 myPosition, float myRadius, float myLength, float heightAboveGround)
{ // constructor
			m_position = myPosition;
	float angle = -90;
	m_orientation.w = cos(Ogre::Math::PI*(angle/2)/180), m_orientation.x = 0;
	m_orientation.y = 0; m_orientation.z = -sin(Ogre::Math::PI*(angle/2)/180);
	m_arrow = myGunBarrel;
	m_arrow->setPosition(m_position);
	//rotate();
}

void Arrow::initialize(){


}

//Rotate() method used with constructor only
void Arrow:: rotate( )
{  
	// Before rotation about the centre of the Arrow, move the centre to the base of the Arrow
	m_arrow->translate(-(m_arrow->getOrientation() * (Ogre::Vector3::UNIT_Y))*m_lengthArrow/2);

	// Then rotate about the centre
	m_arrow->rotate(m_orientation,Ogre::Node::TS_WORLD);

	// Now move Arrow back
	m_arrow->translate((-(m_arrow->getOrientation()) * (Ogre::Vector3::UNIT_Y))*m_lengthArrow/2);
}

//Rotate() method used with keyboard input
void Arrow:: rotate(OIS::Keyboard* mKeyboard)
{	
	// Before rotation about the centre of the Arrow, move the centre to the base of the Arrow
	m_arrow->translate(-(m_arrow->getOrientation() * (Ogre::Vector3::UNIT_Y))*m_lengthArrow/2);

	// Then rotate about the centre
	if (mKeyboard->isKeyDown(OIS::KC_N))
		// if hit Y-key for y-axis clockwise rotation about centre of object
		m_arrow->yaw(  (Ogre::Radian)0.09*Ogre::Math::PI/180 ,Ogre::Node::TS_WORLD);

	if (mKeyboard->isKeyDown(OIS::KC_M))
		// if hit U-key for y-axis anti-clockwise rotation about centre of object
		m_arrow->yaw( -(Ogre::Radian)0.09*Ogre::Math::PI/180,Ogre::Node::TS_WORLD);

		Ogre::Vector3 rotationAxis = Ogre::Vector3((m_arrow->getOrientation()*(Ogre::Vector3::UNIT_Y)).crossProduct((Ogre::Vector3::UNIT_Y)));

	
	// Now move Arrow back along the new direction
	m_arrow->translate(((m_arrow->getOrientation()) * (Ogre::Vector3::UNIT_Y))*m_lengthArrow/2);

	// Reset the orientation of the Arrow class
	m_orientation = m_arrow->getOrientation();



	//update node position
	m_arrow->setPosition(m_position);
	m_arrow->setOrientation(m_orientation);
}

void Arrow:: setOrientation(Ogre::Quaternion orientat)
{
	m_orientation = orientat;
}

Ogre::Vector3 Arrow:: getPosition()
{
	return m_position;
}

void Arrow::setPosition(Ogre::Vector3 v){
	m_position = v;	
}

Ogre::Quaternion Arrow:: getOrientation()
{
	return m_orientation;
}

float Arrow:: getLengthBarrel()
{
	return m_lengthArrow;
}

float Arrow:: getRadiusBarrel()
{
	return m_radiusBarrel;
}

void Arrow::Reset(){
		float angle = 90;
	m_position = Ogre::Vector3(0,10.0f,0);
	m_orientation.w = cos(Ogre::Math::PI*(angle/2)/180), m_orientation.x = 0;
	m_orientation.y = 0; m_orientation.z = -sin(Ogre::Math::PI*(angle/2)/180);
}