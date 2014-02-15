#ifndef __PINMANAGER_h_
#define __PINMANAGER_h_

#include <Ogre.h>
#include "Pin.h"
#include "BowlingBall.h"
#include <vector>

//FMOD includes
#pragma comment(lib,"fmodex_vc.lib") 
#include "fmod.hpp"


using namespace std;

class PinManager
{
public:
	PinManager();
	void PlacePins(Ogre::SceneManager*);//sets the pins up in there triangle formation
	void RemovePins(Pin*);//takes pins off the board
	void replacePins();//replaces pins on the board
	void ballCollisions(BowlingBall*);//checks the ball against the pins for collision
	void pinCollisions(Pin*);//checks pin vs pin collisions
	void update(BowlingBall*);//runs through the pins and calls on the methods as needed
	int getHitPins();//returns the number of pins hit
	void resetCheck();//checks if the game can be reset
	bool pinsStoped();//checks if all pins have stopped moving

private:
	std::vector<Pin*> pins;
	std::vector<Pin*>::iterator it;
	int pinsHit;//the amount of pins struck this turn.
		FMOD::System *FMODsys; //the FMOD sytem
	FMOD_RESULT result;
		FMOD::Sound *pinHit;
		FMOD::Channel *chanPin;
};




#endif