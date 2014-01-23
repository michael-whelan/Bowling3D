#ifndef __Cannon_h_
#define __Cannon_h_

#include "BaseApplication.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

class Cannon
{
protected:
	Ogre::Vector3 m_position;
	Ogre::Quaternion m_orientation;
	float m_lengthBarrel;
	float m_radiusBarrel;
	float m_heightAboveGround;
	Ogre::SceneNode * m_gunBarrel;
	
	public:
	Cannon(Ogre::SceneNode *, Ogre::Vector3, float, float,float);
				
	void rotate(OIS::Keyboard*);
	void rotate();
	//void translate();
	void setOrientation(Ogre::Quaternion);
	Ogre::Quaternion getOrientation();
	Ogre::Vector3 getPosition();
	float getLengthBarrel();
	float getRadiusBarrel();
	float getHeightAboveGround();
		
	~Cannon();

};

#endif
