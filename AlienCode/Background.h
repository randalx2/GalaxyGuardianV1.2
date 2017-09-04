#pragma once

#include <string>
#include "BaseObject.h"

using namespace std;

class Background : public BaseObject
{
private:

public:
	Background(ALLEGRO_BITMAP *iimage, float ispeedX);
	~Background();

	//Overrider Functions
	void DestroyObject(); //vf
	void UpdateObject(); //vf
	void RenderObject(); //vf
};



