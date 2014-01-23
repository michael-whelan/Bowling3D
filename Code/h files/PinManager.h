#ifndef __PINMANAGER_h_
#define __PINMANAGER_h_

#include <Ogre.h>
#include "Pin.h"
#include "BowlingBall.h"
#include <vector>

using namespace std;

class PinManager
{
public:
	PinManager();
	void PlacePins(Ogre::SceneManager*);
	void RemovePins();
	void replacePins();
	bool collisions(BowlingBall*);
	int getHitPins();

private:
	std::vector<Pin*> pins;
	std::vector<Pin*>::iterator it;
	int pinsHit;
};




#endif