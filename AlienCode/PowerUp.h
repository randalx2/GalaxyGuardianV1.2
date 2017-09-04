#pragma once
#include <string>

#include "BaseObject.h"

using namespace std;

class PowerUp : public BaseObject
{
private:

public:
	PowerUp(float ix, float iy, ALLEGRO_BITMAP *iimage); //Overloading constructor
	~PowerUp();

	//Overrider functions
	void DestroyObject(); //vf
	void UpdateObject(); //vf
	void RenderObject(); //vf
	void Collided(int objectID); //vf
};



