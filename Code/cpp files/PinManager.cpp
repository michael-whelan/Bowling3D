#include "PinManager.h"
#include <vector>

PinManager::PinManager():pinsHit(0){
	//setup FMOD
	FMOD_RESULT result;
	result = FMOD::System_Create(&FMODsys);     // Create the main system object.
	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.

	result = FMODsys->createSound("C:/CollegeWork/Project/pinHit.wav", FMOD_LOOP_OFF|FMOD_2D, 0, &pinHit);
}

void PinManager::PlacePins(Ogre::SceneManager* mSceneMgr){
	Ogre::Vector3 pinPos[10];

	pinPos[0] = Ogre::Vector3(0,6,-280);
	pinPos[1] = Ogre::Vector3(5,6,-285);
	pinPos[2] = Ogre::Vector3(-5,6,-285);
	pinPos[3] = Ogre::Vector3(10,6,-290);
	pinPos[4] = Ogre::Vector3(0,6,-290);
	pinPos[5] = Ogre::Vector3(-10,6,-290);
	pinPos[6] = Ogre::Vector3(15,6,-295);
	pinPos[7] = Ogre::Vector3(5,6,-295);
	pinPos[8] = Ogre::Vector3(-4,6,-295);
	pinPos[9] = Ogre::Vector3(-15,6,-295);

	for(int i = 0;i<10;i++){
		pins.push_back(new Pin(mSceneMgr,pinPos[i],i));
	}
}

void PinManager::RemovePins(Pin* pin){
	it = pins.begin();
	while(it != pins.end()){
		if(pin->getSpeed()==0){
			pin->removePin();
			//pinsHit++;
			chanPin->stop();
		}
		
		++it;
	}
}

void PinManager::replacePins(){
	chanPin->stop();
	it = pins.begin();
	while(it != pins.end()){
		(*it)->addPin();
		++it;
	}
	pinsHit = 0;
}

int PinManager::getHitPins(){
	return pinsHit;
}

void PinManager::ballCollisions(BowlingBall* ball){
	it = pins.begin();

	while(it != pins.end()){
		
		if(ball->getNode()->_getWorldAABB().intersects((*it)->getNode()->_getWorldAABB())){
			if(!(*it)->getMove() && !(*it)->getBallAttempt()){
				(*it)->pinFallCheck(ball->getPosition(),ball->getVelocity(),ball->getMass());
				if((*it)->getMove() && !(*it)->getPinAttempt()){
					pinsHit++;
					FMODsys->playSound(FMOD_CHANNEL_FREE, pinHit,false, &chanPin);
		chanPin->setVolume(0.8f);       // Set the volume while it is paused.
		chanPin->setPaused(false);      // This is where the sound really starts.
		chanPin->set3DMinMaxDistance(100,10000);
				}
			}
		}
		++it;
	}
}

void PinManager::pinCollisions(Pin* pin){
	it = pins.begin();
	while(it != pins.end()){
		if(pin != (*it)){
			if(pin->getNode()->_getWorldAABB().intersects((*it)->getNode()->_getWorldAABB())){
				if(!(*it)->getMove() && !(*it)->getPinAttempt()){
					(*it)->pinFallCheck(pin->getPosition(),pin->getVelocity(),pin->getMass());
					if((*it)->getMove() && !(*it)->getBallAttempt()){
						pinsHit++;
					}
				}
			}
		}
		
		++it;
	}
}

void PinManager::update(BowlingBall* ball){
	std::vector<Pin*>::iterator iter = pins.begin();
	
	while(iter != pins.end()){
		if((*iter)->getFell())
			RemovePins((*iter));
		if(ball->getMove()){
			ballCollisions(ball);
		}
		if((*iter)->getMove()){
			pinCollisions((*iter));
		}
		(*iter)->update();
		++iter;
	}
}

void PinManager::resetCheck(){
	std::vector<Pin*>::iterator iter = pins.begin();
	while(iter != pins.end()){
		(*iter)->setBallAttempt(false);
		(*iter)->setPinAttempt(false);
		++iter;
	}
}

bool PinManager::pinsStoped(){
	std::vector<Pin*>::iterator iter = pins.begin();
	while(iter != pins.end()){
		if((*iter)->getMove())
			return false;
		++iter;
	}
	return true;
}