#include "CollisionManager.h"


CollisionManager::CollisionManager(){	
	}

bool CollisionManager::checkCollisions(BowlingBall* ball, Pin* pin){
	Ogre::Vector3 ballPos = ball->getPosition();
	Ogre::Vector3 pinPos = pin->getPosition();
	
	float distance = Ogre::Math::Sqrt(((ballPos.x-pinPos.x)*(ballPos.x-pinPos.x))+((ballPos.y-pinPos.y)*(ballPos.y-pinPos.y))+((ballPos.z-pinPos.z)*(ballPos.z-pinPos.z)));
	
	float combinedRad = ball->getRadius()+ pin->getRadius();

	if(distance <= combinedRad){
		return true;
	}
	return false;
}