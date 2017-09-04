#pragma once
#include <string>

#include "BaseObject.h"

using namespace std;

/*Insert Class Declarations Here*/
class Bullet : public BaseObject
{
private:
	void(*enemiesDown)(void);
	void(*bossesKilled)(void);

public:
	Bullet(float x, float y, void(*enemiesDown)(void), void(*bossesKilled)(void), ALLEGRO_BITMAP *iimage);
	
	//Functions to override base class Virtual Functions
	void DestroyObject();
	void UpdateObject();
	void RenderObject();
	void Collided(int objectID);
};

