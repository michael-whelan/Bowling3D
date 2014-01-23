#ifndef COLLISONMANAGER_H
#define COLLISONMANAGER_H


//#include "BaseApplication.h"
#include "BowlingBall.h"
#include "Pin.h"

class CollisionManager {

public:
	
	CollisionManager();
	bool checkCollisions(BowlingBall*, Pin*);	
};

#endif
