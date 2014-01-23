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
	Arrow(Ogre::SceneNode *, Ogre::Vector3, float, float,float);
	Ogre::Vector3 ArrowTop;		
	void rotate(OIS::Keyboard*);
	void rotate();
	void initialize();
	//void translate();
	void setOrientation(Ogre::Quaternion);
	Ogre::Quaternion getOrientation();
	Ogre::Vector3 getPosition();
	void setPosition(Ogre::Vector3);
	float getLengthBarrel();
	float getRadiusBarrel();
	void Reset();
};


#endif
