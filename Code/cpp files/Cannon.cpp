#include "Cannon.h"


Cannon::Cannon(Ogre::SceneNode * myGunBarrel, Ogre::Vector3 myPosition, float myRadius, float myLength, float heightAboveGround)
{ // constructor
	m_position = myPosition;
	// Set initial orientation w = cos (angle/2)  and z = -sin (angle/2) 
	// i.e. rotate "angle" degrees about the z-axis
	float angle = 40;
	m_orientation.w = cos(Ogre::Math::PI*(angle/2)/180), m_orientation.x = 0;
	m_orientation.y = 0; m_orientation.z = -sin(Ogre::Math::PI*(angle/2)/180);
	// or for straight upright at 0 degrees to the y-axis use
	//m_orientation.w = 1;  m_orientation.x = 0; m_orientation.y = 0; m_orientation.z = 0;
	m_lengthBarrel = myLength;  // length of barrel of gun
	m_radiusBarrel = myRadius;   // radius of gun
	m_gunBarrel = myGunBarrel;
	m_gunBarrel->setPosition(m_position);
	m_heightAboveGround = heightAboveGround;
	rotate();
}

//To rotate the cannon at the start to its initial orientation

//Rotate() method used with constructor only
void Cannon:: rotate( )
{  
	// Before rotation about the centre of the cannon, move the centre to the base of the cannon
	m_gunBarrel->translate(-(m_gunBarrel->getOrientation() * (Ogre::Vector3::UNIT_Y))*m_lengthBarrel/2);

	// Then rotate about the centre
	m_gunBarrel->rotate(m_orientation,Ogre::Node::TS_WORLD);

	// Now move cannon back
	m_gunBarrel->translate((-(m_gunBarrel->getOrientation()) * (Ogre::Vector3::UNIT_Y))*m_lengthBarrel/2);
}

//Rotate() method used with keyboard input
void Cannon:: rotate(OIS::Keyboard* mKeyboard)
{
	// Before rotation about the centre of the cannon, move the centre to the base of the cannon
	m_gunBarrel->translate(-(m_gunBarrel->getOrientation() * (Ogre::Vector3::UNIT_Y))*m_lengthBarrel/2);

	// Then rotate about the centre
	if (mKeyboard->isKeyDown(OIS::KC_Y))
		// if hit Y-key for y-axis clockwise rotation about centre of object
		m_gunBarrel->yaw(  (Ogre::Radian)0.2*Ogre::Math::PI/180 ,Ogre::Node::TS_WORLD);

	if (mKeyboard->isKeyDown(OIS::KC_U))
		// if hit U-key for y-axis anti-clockwise rotation about centre of object
		m_gunBarrel->yaw( -(Ogre::Radian)0.2*Ogre::Math::PI/180,Ogre::Node::TS_WORLD);


	// find the direction of rotation for x z -rotations
	// perpendicular to the y-axis and the cannondirection
		Ogre::Vector3 rotationAxis = Ogre::Vector3((m_gunBarrel->getOrientation()*(Ogre::Vector3::UNIT_Y)).crossProduct((Ogre::Vector3::UNIT_Y)));
	// Then rotate about the centre in this direction
		if ((mKeyboard->isKeyDown(OIS::KC_X))&& ((m_gunBarrel->getOrientation()*(Ogre::Vector3::UNIT_Y)).dotProduct((Ogre::Vector3::UNIT_Y)) < 0.95))
		// if hit X-key for x-axis rotation about centre of object, avoiding gimbal lock at y-axis 
	{
		m_gunBarrel->rotate(rotationAxis,(Ogre::Radian)0.2*Ogre::Math::PI/180,Ogre::Node::TS_WORLD);

	}
	if ((mKeyboard->isKeyDown(OIS::KC_C))&&((m_gunBarrel->getOrientation()*(Ogre::Vector3::UNIT_Y)).dotProduct((Ogre::Vector3::UNIT_Y)) > 0))
		// if hit C-key for x-axis rotation about centre of object,keeping the cannon above the horizontal
	{
		m_gunBarrel->rotate(rotationAxis,-(Ogre::Radian)0.2*Ogre::Math::PI/180,Ogre::Node::TS_WORLD);
	}
	// Now move cannon back along the new direction
	m_gunBarrel->translate(((m_gunBarrel->getOrientation()) * (Ogre::Vector3::UNIT_Y))*m_lengthBarrel/2);

	// Reset the orientation of the Cannon class
	m_orientation = m_gunBarrel->getOrientation();

}


void Cannon:: setOrientation(Ogre::Quaternion orientat)
{
	m_orientation = orientat;
}

Ogre::Vector3 Cannon:: getPosition()
{
	return m_position;
}

Ogre::Quaternion Cannon:: getOrientation()
{
	return m_orientation;
}

float Cannon:: getLengthBarrel()
{
	return m_lengthBarrel;
}

float Cannon:: getRadiusBarrel()
{
	return m_radiusBarrel;
}
float Cannon:: getHeightAboveGround()
{
	return m_heightAboveGround;
}

Cannon::~Cannon()
{// destructor
}
