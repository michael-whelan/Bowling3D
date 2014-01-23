#include "PinManager.h"
#include <vector>

PinManager::PinManager(){
	pinsHit = 0;
}

void PinManager::PlacePins(Ogre::SceneManager* mSceneMgr){
	Ogre::Vector3 pinPos[10];

	pinPos[0] = Ogre::Vector3(0,3,-280);
	pinPos[1] = Ogre::Vector3(5,3,-285);
	pinPos[2] = Ogre::Vector3(-5,3,-285);
	pinPos[3] = Ogre::Vector3(10,3,-290);
	pinPos[4] = Ogre::Vector3(0,3,-290);
	pinPos[5] = Ogre::Vector3(-10,3,-290);
	pinPos[6] = Ogre::Vector3(15,3,-295);
	pinPos[7] = Ogre::Vector3(5,3,-295);
	pinPos[8] = Ogre::Vector3(-4,3,-295);
	pinPos[9] = Ogre::Vector3(-15,3,-295);

	for(int i = 0;i<10;i++){
		pins.push_back(new Pin(mSceneMgr,pinPos[i],i));
	}

}

void PinManager::RemovePins(){
}

void PinManager::replacePins(){
	it = pins.begin();
	while(it != pins.end()){
		(*it)->addPin();
		it++;
	}
	pinsHit = 0;
}


int PinManager::getHitPins(){
	return pinsHit;
}

bool PinManager::collisions(BowlingBall * ball){
	it = pins.begin();
	while(it != pins.end()){
		if(ball->getNode()->_getWorldAABB().intersects((*it)->getNode()->_getWorldAABB())){
			(*it)->removePin();
			pinsHit++;
			return true;
		}
		it++;
	}
	return false;
}