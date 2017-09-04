#include "PowerUp.h"
#include <string>
#include <iostream>
#include <cstdio>
#include "BaseObject.h"

using namespace std;

PowerUp::PowerUp(float ix, float iy, ALLEGRO_BITMAP *iimage)
{
	BaseObject::Init(ix, iy, 5, 0, -1, 0, 35, 35);
	setObjType(POWER);

	maxFrame = 2; //143;        //Change according to sprite sheet
	curFrame = 0;
	frameCount = 0;
	frameDelay = 10;  //2; 
	frameWidth = 64; //96;
	frameHeight = 57; //96;
	animationColumns = 2; //21;

	if (rand() % 2)        //Appear at random
	animationDirection = 1;
	else
	animationDirection = -1;

	image = iimage;  //
}


PowerUp::~PowerUp()
{
}

void PowerUp::DestroyObject()
{
	BaseObject::DestroyObject();
}

void PowerUp::UpdateObject()
{
	BaseObject::UpdateObject();

	//NB NO BOUNDS CHECKING FOR POWER UPS
	//if it goes off the screen it needs to be created once again to reappear 
	//for the player to catch it

	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame)
		{
			curFrame = 0;
		}
		else if (curFrame <= 0)
		{
			curFrame = maxFrame - 1;
		}
		frameCount = 0;
	}

	if (x + frameWidth < 0)
	{
		Collided(BORDER);
	}
}

void PowerUp::RenderObject()
{
	//Choosing animation scheme similar to the space ship

	BaseObject::RenderObject(); //Call base class virtual function just in case we update it later
	//Also gives us values that were initially set by base class vf before we may override them

	//Animation Updating
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;      //Using a single row for animation so don't need to include it here

	//Allegro drawing bitmap functions set up here for the space ship
	//NB must resolve in main.cpp to avoid unresolved symbols compilation error when building

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - frameWidth / 2, y - frameHeight / 2, 0);
}

void PowerUp::Collided(int iobjectType)
{
	if (iobjectType == PLAYER || iobjectType == BORDER)
	{
		setOnScreen(false);    //If it collides with the player then it dissappears off screen
	}
}
