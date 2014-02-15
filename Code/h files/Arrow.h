#ifndef ARROW_H
#define ARROW_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include "BowlingBall.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

using namespace Ogre;

class Arrow {


protected:
	Ogre::Vector3 m_position;
	Ogre::Quaternion m_orientation;
	Ogre::SceneNode * m_arrow;
	float m_lengthArrow;
	float m_radiusBarrel;

	public:
	Arrow(Ogre::SceneNode *, Ogre::Vector3, float, float,float);//radius, length, height above ground
	Ogre::Vector3 ArrowTop;		
	void rotate(OIS::Keyboard*);//controls the rotation of the arrow object
	void rotate();
	void initialize();
	void setOrientation(Ogre::Quaternion);
	Ogre::Quaternion getOrientation();
	Ogre::Vector3 getPosition();
	void setPosition(Ogre::Vector3);
	float getLengthBarrel();
	float getRadiusBarrel();
	void Reset();//sets the arrow back to initial orientation
};


#endif
