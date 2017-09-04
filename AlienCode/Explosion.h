#pragma once

#include <string>
#include "BaseObject.h"

using namespace std;

class Explosion : public BaseObject
{
private:

public:
	Explosion(float ix, float iy, ALLEGRO_BITMAP *iimage);
	~Explosion();

	//Overrider functions
	void DestroyObject(); //vf
	void UpdateObject(); //vf
	void RenderObject(); //vf
	void Collided(int objectID); //vf
};

