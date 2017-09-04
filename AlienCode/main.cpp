//Praneel Misthry
//BSc Electronic Engineering
//2D C++ Game Development Project

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <ctime>

#include "BaseObject.h"
#include "Globals.h"
#include "Alien.h"
#include "Spaceship.h"
#include "Bullet.h"
#include "AlienBullet.h"
#include "PowerUp.h"
#include "Explosion.h"
#include "Background.h"
#include "Asteroid.h"
#include "SubBoss.h"
#include <list>

using namespace std;

bool keys[] = { false, false, false, false, false, false };
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE, A}; //Enumeration for key input array

//===========================================================================================================
//globals for main.cpp
//============================================================================================================

Spaceship *ship1;  //Created our spaceship object pointer in memory heap
Alien **a1 = new Alien*[8];  //Declaring a dynamic 2d object array
Bullet *bullet;
Explosion *explode;
Background *backdrop;
AlienBullet *alienBullet;
AlienBullet *subBossBullet;
Asteroid *asteroid;
SubBoss *subBoss;

//Create object pointers for the title, level up and game over screens
//These are NOT meant to be part of the gameObjects list!!
Background *introScreen;
Background *ratingScreen;
Background *startScreen;
Background *gameoverScreen;
Background *levelupScreen;
Background *levelupScreen2;
Background *levelupScreen3;
Background *levelupScreen4;
Background *levelupScreen5;

Background *beatgameScreen;
Background *beatgameScreen2;
Background *beatgameScreen3;
Background *beatgameScreen4;
Background *beatgameScreen5;
Background *beatgameScreen6;
Background *beatgameScreen7;

ALLEGRO_SAMPLE_INSTANCE *soundTrack; //Global so the soundtrack can change according to FSM

int level = 1;      //Variable to keep track of level number
int score = 0;      //Keep track of score in a level
int totalScore = 0;  //Total score accumulated in game
int totalLives = 0; //Hold the updated accumulated lives or tries by the player between levels

//These are made global so the state machine can access them
ALLEGRO_BITMAP *backGimage = NULL;
ALLEGRO_BITMAP *midGimage = NULL;
ALLEGRO_BITMAP *foreGimage = NULL;
ALLEGRO_SAMPLE *song = NULL;
ALLEGRO_SAMPLE_ID id1, id2, id3, id4, id5, id6, id7, id8, id9, id10, id11, id12, id13, id14, id15, id16, id17, id18, id19, id20;
ALLEGRO_SAMPLE *titleTrack = NULL;


//Create the updation list of objects
list < BaseObject *> gameObjects;   //Created a list of BaseObject type called gameObjects

//Lists are different from arrays. We need more than just for loops to iterate. To iterate through a list we create iterators
list < BaseObject *>::iterator itr1;  //created an iterator of BaseObject type called itr1
list < BaseObject *>::iterator itr2;  //created an iterator of BaseObject type called itr2

//======================================================================================================================
//prototypes
/*Insert prototypes of necessary global functions here for main.cpp*/
//======================================================================================================================

void __cdecl TakeLife();
void __cdecl enemiesDown();
void _cdecl bossesKilled();
void _cdecl TakeHealth();
void FSM(int &state, int nextState);  //Global function which sets up our simple Finite State Machine
void setupAliens(ALLEGRO_BITMAP *image); //Contains for loop which initializes each alien in the grid
bool allAliensDestroyed();

int main()
{
	//================================================================================================================
	//Temp or Shell Variables
	//================================================================================================================

	bool done = false;
	bool render = false;
	int state = -1;      //FSM variable
	int tempLevel = 0;

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;
	
	float tempX = 0;    //Used to set up grid with regards to spacing
	float tempY = 0;
	int temprandX = 0;  //Used to get index of alien array
	int temprandY = 0;

	int temprandPwrUp = 0;     //Can adjust these to vary difficulty of the game
	int temprandAlBullet = 0;
	int temprandAsteroid = 0;
	int temprandSFX = 0;
	int temprandLost = 0;

	int thisTime = 0;
	int lastTime = 0;
	//====================================================================================================================
	//Project Variables Here
	//====================================================================================================================

	ALLEGRO_BITMAP *subBossImage = NULL;
	ALLEGRO_BITMAP *asteroidImage = NULL;
	ALLEGRO_BITMAP *alienImage = NULL;
	ALLEGRO_BITMAP *shipImage = NULL;
	ALLEGRO_BITMAP *pwrImage = NULL;
	ALLEGRO_BITMAP *explodeImage = NULL;
	ALLEGRO_BITMAP *albulletImage = NULL;
	ALLEGRO_BITMAP *powerBulletImage = NULL;
	ALLEGRO_BITMAP *startImage = NULL;
	ALLEGRO_BITMAP *gameOverImage = NULL;

	ALLEGRO_BITMAP *levelupImage = NULL; //Default Level Up Image
	ALLEGRO_BITMAP *levelupImage2 = NULL; //Other level up images that may be used
	ALLEGRO_BITMAP *levelupImage3 = NULL;
	ALLEGRO_BITMAP *levelupImage4 = NULL;
	ALLEGRO_BITMAP *levelupImage5 = NULL;

	ALLEGRO_BITMAP *beatGameImage = NULL;
	ALLEGRO_BITMAP *contraEndImage = NULL;
	ALLEGRO_BITMAP *groundBattleImage1 = NULL;
	ALLEGRO_BITMAP *groundBattleImage2 = NULL;
	ALLEGRO_BITMAP *groundBattleImage3 = NULL;
	ALLEGRO_BITMAP *femBaddieImage = NULL;
	ALLEGRO_BITMAP *dukeBarImage = NULL;

	ALLEGRO_BITMAP *introImage = NULL;
	ALLEGRO_BITMAP *ESRBImage = NULL;

	ALLEGRO_SAMPLE *playerShot = NULL;
	ALLEGRO_SAMPLE *enemyShot = NULL;
	ALLEGRO_SAMPLE *boom = NULL;
	ALLEGRO_SAMPLE *pwrUp = NULL;
	ALLEGRO_SAMPLE *defeat = NULL;
	ALLEGRO_SAMPLE *stageClear = NULL;
	ALLEGRO_SAMPLE *gameOver = NULL;
	ALLEGRO_SAMPLE *beatGame = NULL;
	ALLEGRO_SAMPLE *gameIntro = NULL;
	ALLEGRO_SAMPLE *creditTheme = NULL;

	ALLEGRO_SAMPLE *dukeAlienBstds = NULL;
	ALLEGRO_SAMPLE *dukeAlienBstds2 = NULL;

	ALLEGRO_SAMPLE *dukeBabesBullets = NULL;
	ALLEGRO_SAMPLE *dukeChewGum = NULL;
	ALLEGRO_SAMPLE *dukeHoldongirls = NULL;
	ALLEGRO_SAMPLE *dukeMidtownexpress = NULL;
	ALLEGRO_SAMPLE *dukeImDukeNukem = NULL;
	ALLEGRO_SAMPLE *dukeRipNewOne = NULL;

	ALLEGRO_SAMPLE *dukeRestinPieces = NULL;
	ALLEGRO_SAMPLE *dukeGood = NULL;
	ALLEGRO_SAMPLE *dukeHell = NULL;
	//ALLEGRO_SAMPLE *dukeMedieval = NULL;  NB This sound clip was causing run time errors due to codec changes
	ALLEGRO_SAMPLE *dukeHail = NULL;
	ALLEGRO_SAMPLE *dukeSort = NULL;
	ALLEGRO_SAMPLE *dukeGetSome = NULL;
	//ALLEGRO_SAMPLE *SKmuaHaha = NULL;
	ALLEGRO_SAMPLE *SKmuaHaha2 = NULL;
	ALLEGRO_SAMPLE *DontMakeMeLaugh = NULL;

	ALLEGRO_SAMPLE *Arrgh = NULL;
	ALLEGRO_SAMPLE *flawlessVictory = NULL;
	ALLEGRO_SAMPLE *youSuck = NULL;
	ALLEGRO_SAMPLE *superb = NULL;
	ALLEGRO_SAMPLE *excellent = NULL;
	ALLEGRO_SAMPLE *outstanding = NULL;
	ALLEGRO_SAMPLE *wellDone = NULL;
	ALLEGRO_SAMPLE *neverWin = NULL;

	//=================================================================================================================
	//Allegro Variables Here
	//=================================================================================================================

	ALLEGRO_DISPLAY *display = NULL;   //Create and initialize allegro display object
	//ALLEGRO_DISPLAY_MODE   disp_data;    //Use for full screen mode

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;  //Create and initialize allegro event que
	ALLEGRO_TIMER *timer;          //Create Allegro timer object to cap the FPS to playable game speed ie 60 FPS standard
	ALLEGRO_FONT *font18;         //Font variable for outputting text. Size 18
	ALLEGRO_FONT *font36;
	ALLEGRO_FONT *comicFont36;
	ALLEGRO_FONT *comicFontB36;
	ALLEGRO_FONT *comicFontBold36;
	ALLEGRO_FONT *gameFont;
	ALLEGRO_FONT *bloodyFont;
	
	//===============================================================================================================
	//Initialize Allegro Functions
	//=================================================================================================================

	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if (!display)										//test display object
		return -1;

	//===============================================================================================================
	//Install Necessary Allegro Addons
	//NB I added all addons I thought we would need later on as well
	//===============================================================================================================

	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();

	//==========================================================================================
	//Initialize Necessary Project images and addons
	//=============================================================================================

	font18 = al_load_font("arial.ttf", 18, 0);  //NB Add the font file arial.ttf in your soln folder
											   //Can access the font files from windows control panel
	font36 = al_load_font("arial.ttf", 36, 0);
	gameFont = al_load_font("Halo3.ttf", 75, 0);
	bloodyFont = al_load_font("Blood.ttf", 105, 0);
	comicFont36 = al_load_font("comic.ttf", 18, 0);
	comicFontB36 = al_load_font("comicbd.ttf", 20, 0);
	comicFontBold36 = al_load_font("comicbd.ttf", 36, 0);

	al_reserve_samples(55);                  //Make allocation for a possible of 55 audio samples

	//NB USE THE CODE BELOW TO EXPERIMENT WITH FULL SCREEN MODE -- NOT RECOMMENDED DUE TO BUGS
	/*al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(disp_data.width, disp_data.height);*/

	//===============================================================================================================
	//                      ADD in our OBJECTS HERE. INITIALIZE AND ADD TO THE LIST
	//===============================================================================================================

	//Set up the backgrounds
	backGimage = al_load_bitmap("farback.png");
	//backGimage = al_load_bitmap("HD Galaxy Wallpaper.png");
	midGimage = al_load_bitmap("starMG.png");
	foreGimage = al_load_bitmap("starfield-front_converted.png");

	//Pass in the first background image to the list
	backdrop = new Background(backGimage, 15);
	gameObjects.push_back(backdrop);

	//Pass in the mid background using same object but different memory location. So this is actually a different variable
	//Using the same pointer to point at a different memory location of the same type of object
	backdrop = new Background(midGimage, 3);
	gameObjects.push_back(backdrop);

	//Pass in the fore background using same object but different memory location. So this is actually a different variable
	backdrop = new Background(foreGimage, 30);
	gameObjects.push_back(backdrop);

	//Pass in the space ship after the backgrounds
	ship1 = new Spaceship;
	shipImage = al_load_bitmap("spaceship_by_arboris.png");
	al_convert_mask_to_alpha(shipImage, al_map_rgb(255, 0, 255));
	ship1->Init(shipImage);
									//AFTER INITIALIZING AN OBJECT LIKE THE SHIP PUSH IT TO OUR LIST
	gameObjects.push_back(ship1);  // Pushed the ship to back of our list
								  //Shows inheritance and polymorphism. Better than an array since we don't know how big
								 //our array should be. With a list of base type objects we can just push and pop --PM.

	//==============================================================================================================================//
	//========    SET UP OF THE ALIENS USING THE SET UP GLOBAL FUNCTION      ======================================================//
	//==============================================================================================================================//
	alienImage = al_load_bitmap("EnemyShip2.png");             //Can change the bitmap during level transition
	//al_convert_mask_to_alpha(alienImage, al_map_rgb(0, 0, 0)); //Since background of alien is black
	al_convert_mask_to_alpha(alienImage, al_map_rgb(255, 0, 255)); //Make background Magenta transparent
	setupAliens(alienImage); //NB This function body automatically adds each alien to the list

	//Alien bullet image  NB USED FOR BOSSES TOO
	albulletImage = al_load_bitmap("EnemyPowerBullet.png");
	al_convert_mask_to_alpha(albulletImage, al_map_rgb(255, 170, 255)); //Since background is magenta
	al_convert_mask_to_alpha(albulletImage, al_map_rgb(255, 255, 255)); //Make white lines transparent

	//Player bullet image
	powerBulletImage = al_load_bitmap("PowerBullet.png");
	al_convert_mask_to_alpha(powerBulletImage, al_map_rgb(255, 0, 255)); //Since background is magenta
	al_convert_mask_to_alpha(powerBulletImage, al_map_rgb(255, 255, 255)); //Make white lines transparent
	
	//Set up PowerUp
	pwrImage = al_load_bitmap("BubbleBobbleHeart.png");
	al_convert_mask_to_alpha(pwrImage, al_map_rgb(255, 170, 255)); //Since background is magenta
	al_convert_mask_to_alpha(pwrImage, al_map_rgb(255, 255, 255)); //Make white lines transparent

	//Set up Explosion
	explodeImage = al_load_bitmap("explosion_3_40_128.png");

	//Set up Astroid image
	asteroidImage = al_load_bitmap("asteroid-1-96.png");

	//Set up sub boss image
	subBossImage = al_load_bitmap("EnemyShip.png");
	al_convert_mask_to_alpha(subBossImage, al_map_rgb(255, 0, 255));  //Make magenta background in frame transparent

	//Set State Screen Backgrounds
	introImage = al_load_bitmap("duke_nukem_forever_large.png");
	ESRBImage = al_load_bitmap("ESRB_M_converted.png");
	startImage = al_load_bitmap("space_battle_not_so_wip_by_theregisteredone.png");
	gameOverImage = al_load_bitmap("unique-wedding-cake-0011.png");

	//Level up image 
	levelupImage = al_load_bitmap("mario-level-up_c_146796.png");
	levelupImage2 = al_load_bitmap("RegularShowContra.png");
	levelupImage3 = al_load_bitmap("DukeOlsentwins.png");
	levelupImage4 = al_load_bitmap("DukeHurts.png");
	levelupImage5 = al_load_bitmap("duke_nukem_vs_battlelord_by_cybopath.png");
	
	//Other state screens
	beatGameImage = al_load_bitmap("BeatGame_converted.png");
	groundBattleImage1 = al_load_bitmap("Duke-GroundBattel2.png");
	groundBattleImage2 = al_load_bitmap("Duke-GroundBattle1.png");
	groundBattleImage3 = al_load_bitmap("Duke-GroundBattle3.png");
	contraEndImage = al_load_bitmap("Contra-End Slide.png");
	femBaddieImage = al_load_bitmap("FemBaddie2.png");
	dukeBarImage = al_load_bitmap("Duke-Winning1.png");

	introScreen = new Background(introImage, 0);
	ratingScreen = new Background(ESRBImage, 0);
	startScreen = new Background(startImage, 0);     //Don't push to list
	gameoverScreen = new Background(gameOverImage, 0); //Don't push to list

	levelupScreen = new Background(levelupImage, 0);
	levelupScreen2 = new Background(levelupImage2, 0);
	levelupScreen3 = new Background(levelupImage3, 0);
	levelupScreen4 = new Background(levelupImage4, 0);
	levelupScreen5 = new Background(levelupImage5, 0);
	
	beatgameScreen = new Background(beatGameImage, 0);
	beatgameScreen2 = new Background(groundBattleImage1, 0);
	beatgameScreen3 = new Background(groundBattleImage2, 0);
	beatgameScreen4 = new Background(groundBattleImage3, 0);
	beatgameScreen5 = new Background(contraEndImage, 0);
	beatgameScreen6 = new Background(femBaddieImage, 0);
	beatgameScreen7 = new Background(dukeBarImage, 0);

	//Set up the game sounds
	playerShot = al_load_sample("Laser_Shoot6.ogg");
	enemyShot = al_load_sample("Laser_Shoot14.ogg");
	pwrUp = al_load_sample("Powerup30.ogg");
	boom = al_load_sample("Explosion2.ogg");
	song = al_load_sample("Stage 1.ogg");
	defeat = al_load_sample("death.ogg");
	stageClear = al_load_sample("Stage Clear.ogg");
	gameOver = al_load_sample("Game Over.ogg");
	beatGame = al_load_sample("01 grabbag theme from duke nukem 3d.ogg");
	titleTrack = al_load_sample("Title.ogg");
	dukeGood = al_load_sample("Damn_Im_good.ogg");
	dukeHell = al_load_sample("See_you_in_hell.ogg");
	//dukeMedieval = al_load_sample("duke - Medievil.ogg"); //Sound clip caused runtime errors
	dukeHail = al_load_sample("Hail_to_the_king_baby.ogg");
	dukeSort = al_load_sample("Let_God_sort_em_out.ogg");
	dukeGetSome = al_load_sample("Come_get_some.ogg");
	//SKmuaHaha = al_load_sample("skahn-Muahaha2.ogg");
	SKmuaHaha2 = al_load_sample("skahn-Muahaha.ogg");
	DontMakeMeLaugh = al_load_sample("skahn-DontMakeMeLaugh.ogg");
	Arrgh = al_load_sample("skahn-hit4.ogg");
	flawlessVictory = al_load_sample("skahn-flawless victory.ogg");
	youSuck = al_load_sample("skahn-yousuck.ogg");
	superb = al_load_sample("sakhn-superb.ogg");
	excellent = al_load_sample("skahn-Excellent.ogg");
	outstanding = al_load_sample("skahn-outstanding.ogg");
	wellDone = al_load_sample("skahn-WellDone.ogg");
	neverWin = al_load_sample("skahn-YouWillNeverWin.ogg");
	gameIntro = al_load_sample("01_Theme Of Solid Snake-MG2.ogg");
	creditTheme = al_load_sample("MGS-MainTheme.ogg");
	dukeAlienBstds = al_load_sample("Duke-AlienBstds1.ogg");
	dukeAlienBstds2 = al_load_sample("Duke-AlienBstds2.ogg");
	dukeRestinPieces = al_load_sample("Duke-RestInPieces.ogg");

	dukeBabesBullets = al_load_sample("Duke - Babes Bullets Bombs.ogg");
	dukeChewGum = al_load_sample("Duke-KickAssChewGum.ogg");
	dukeHoldongirls = al_load_sample("Duke-DontWorryGirls.ogg");
	dukeMidtownexpress = al_load_sample("Duke - Midtown Express.ogg");
	dukeImDukeNukem = al_load_sample("Duke-ImDuke-AlienBsts.ogg");
	dukeRipNewOne = al_load_sample("Duke-RipemNewOne.ogg");

	soundTrack = al_create_sample_instance(song);
	al_set_sample_instance_playmode(soundTrack, ALLEGRO_PLAYMODE_LOOP); //Play level song in a loop

	al_attach_sample_instance_to_mixer(soundTrack, al_get_default_mixer()); //Attach song to the default allegro audio mixer

	//Set the DEFAULT Starting state for the game after objects have been initialized

	//FSM(state, TITLE); //Enter into the TITLE state
	//al_play_sample(titleTrack, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id1); //Play a sound effect

	FSM(state, INTRO);
	al_play_sample(gameIntro, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id7); //Play a sound effect

	//Seed a randomizer for testing
	srand((unsigned)time(NULL));
	rand(); rand(); rand();

	//========================================================================================================
	//INITIALIZE THE TIMER FOR TIMED EVENTS IN THE MAIN GAME LOOP
	//HELPS PROVIDE SMOOTH GAMEPLAY AT 60 FPS
	//==========================================================================================================
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();
	
	static float old_time = 0.0, time, dt;
	time = al_current_time();
	dt = time - old_time;

//========================================================================================================
	/**************************************MAIN GAME LOOP STARTS HERE*************************************/
//========================================================================================================
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//Create some timer variables to update some animations with time
		//static float old_time = 0.0, time, dt;
		
//===========================================================================================
		//CHECK FOR KEY INPUT
//==========================================================================================
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;

			case ALLEGRO_KEY_SPACE:
			{ 
			//NB The space bar is used to transition between states as well as for firing the bullets
			//Hence the space bar performs many functions --> similar to a one button masher game
				if (state == INTRO)
				{
					al_stop_sample(&id7);
					FSM(state, TITLE);

					//Reset Timer Variables
					dt = 0;
					old_time = time;
					dt = time - old_time;

					//Play sample
					al_play_sample(titleTrack, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id1); //Play a sound effect

					//Play duke sound
					al_play_sample(dukeAlienBstds, 1.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id11); //Play a sound effect		
				}

				else if (state == TITLE)
				{
					al_stop_sample(&id1);
					al_stop_sample(&id11);
					FSM(state, PLAYING);  //switch from Title to playing if pressed	
					
					//Reset Timer Variable
					dt = 0;
					old_time = time;
					dt = time - old_time;
				}
				else if (state == PLAYING)
				{
					keys[SPACE] = true;              //Use the space key for bullets once bullet code is done
					bullet = new Bullet(ship1->getX() + 17, ship1->getY(), &enemiesDown, &bossesKilled, powerBulletImage);
					gameObjects.push_back(bullet);  //NB A BULLET IS ONLY CREATED WHEN THE SPACE KEY IS PRESSED
					al_play_sample(playerShot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0); //Play a sound effect
				}		
			} 
				break;

			case ALLEGRO_KEY_A:
			{
				 if (state == LEVEL)
				{
					 if (level <= 6)
					 {
						 FSM(state, PLAYING); //Press A KEY to transition out of the LEVEL state
						 al_stop_sample(&id12);
						 al_stop_sample(&id13);
						 al_stop_sample(&id14);
						 al_stop_sample(&id15);
						 al_stop_sample(&id16);
						 al_stop_sample(&id20);

						 //Reset timer variable
						 dt = 0;
						 old_time = time;
						 dt = time - old_time;
					 }
					 else 
					 {
						 FSM(state, CREDITS);  //After beating the game go to credits state
						 al_play_sample(creditTheme, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id10);

						 //Reset the timer variable
						 dt = 0;
						 old_time = time;
						 dt = time - old_time;
					 }
					
				}
				 else if (state == LOST)
				 {
					 FSM(state, PLAYING);

					 //Reset the time variable
					 dt = 0;
					 old_time = time;
					 dt = time - old_time;
				 }
				 else if (state == PLAYING)
				 {
					 keys[A] = false;
				 }
				 else if (state == CREDITS)
				 {
					 al_stop_sample(&id10);
					 FSM(state, INTRO);

					 //Reset the timer variable
					 dt = 0;
					 old_time = time;
					 dt = time - old_time;

					 //Play intro theme
					 al_play_sample(gameIntro, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id7);
				 }

			}
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;

			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;

			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;

			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;

			case ALLEGRO_KEY_A:
				keys[A] = false;
				break;
			}
		}
//==========================================================================================================
		//GAME UPDATE ==>UPDATE THE FPS AND FRAMES ACCORDINGLY FOR SMOOTH GAMEPLAY
//=========================================================================================================
  else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//Initialize the timer variables
			time = al_current_time();
			dt = time - old_time;

			//UPDATE FPS===========
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

	//=======================================================================================================
	//  MOVE THE SHIP ACCORDINGLY //
	//=========================================================================================================
			//Take into consideration the state transition here before allowing gameplay
			if (state == PLAYING)
			{
				if (keys[UP])
				{
					ship1->mvUp();
				}
				else if (keys[DOWN])
				{
					ship1->mvDOWN();
				}
				else
				{
					ship1->animationReset(1);
				}  //Refer to sprite sheet -- PM

				if (keys[LEFT])
				{
					ship1->mvLEFT();
				}
				else if (keys[RIGHT])
				{
					ship1->mvRIGHT();
				}
				else
				{
					ship1->animationReset(0);
				}  //Refer to sprite sheet -- PM


				//Attempt to create an alien bullet randomly if there are still aliens onscreen
				//Adjust frequency of enemy fire as we go up a level
				//As we increase in level we increase enemy bullet fire and speed of their ships
				switch (level)
				{
				case 1: temprandAlBullet = 75;
					break;

				case 2: temprandAlBullet = 50;
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							a1[i][j].setspeedX(1.5);  //Speed up each alien at level 3
						}
					}
					break;

				case 3: temprandAlBullet = 25;
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							a1[i][j].setspeedX(2.5);  //Speed up each alien at level 3
						}
					}
					break;

				case 4: temprandAlBullet = 20;
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							a1[i][j].setspeedX(3.0);  //Speed up each alien at level 4
						}
					}
					break;

				case 5: temprandAlBullet = 15;
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							a1[i][j].setspeedX(3.5);  //Speed up each alien at level 5
						}
					}
					break;

				default: temprandAlBullet = 50;
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							a1[i][j].setspeedX(0.5);  //Reset back to default speed
						}
					}
					break;
				}

				if (rand() % temprandAlBullet == 0)
					{
						temprandX = rand() % 8;
						temprandY = rand() % 6;
						if (a1[temprandX][temprandY].getOnScreen()) //IF AN ALIEN IS STILL ONSCREEN
						{
							alienBullet = new AlienBullet(a1[temprandX][temprandY].getX() - (106 / 2), a1[temprandX][temprandY].getY(), albulletImage, &TakeHealth);
							gameObjects.push_back(alienBullet);
							al_play_sample(enemyShot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						}
					}
				
				//Create the random objects like power ups here just before the updation loop 
				//Reduce the frequency of health power ups as we go up in levels to increase difficulty

				switch (level)
				{
				case 1: 
					temprandPwrUp = 30;
					temprandAsteroid = 50;
					break;

				case 2: 
					temprandPwrUp = 40;
					temprandAsteroid = 40;
					break;

				case 3: 
					temprandPwrUp = 50;
					temprandAsteroid = 30;
					break;

				case 4: 
					temprandPwrUp = 75;
					temprandAsteroid = 30;
					break;

				case 5: 
					temprandPwrUp = 100;
					temprandAsteroid = 25;
					break;

				default: 
					temprandPwrUp = 50;
					temprandAsteroid = 50;
					break;
				}

				if (rand() % temprandPwrUp == 0)
				{
					PowerUp *pwr = new PowerUp(width, 30 + rand() % (height - 60), pwrImage);
					gameObjects.push_back(pwr);
				}

				//check if all the aliens from the grid where destroyed then bring in some random screen enemies
				//NB ALL OTHER RANDOM ENEMIES CAN COME IN THE SAME WAY AS THE ASTEROIDS after the alien army is defeated

				if (allAliensDestroyed())  //Check if there are no remaining alien army ships on screen
				{
					if (rand() % temprandAsteroid == 0)
					{
						asteroid = new Asteroid(width, 30 + rand() % (height - 60), asteroidImage, &TakeLife);
						gameObjects.push_back(asteroid);
					}
				}

				if (level >= 6)     //NB The state machine removes the original alien grid for level 6 already
				{
					if (rand() % 100 == 0)
					{
						asteroid = new Asteroid(width, 30 + rand() % (height - 60), asteroidImage, &TakeLife);
						gameObjects.push_back(asteroid);
					}

					if (rand() % 50 == 0)
					{
						//MEET THE BOSS ;-)...In the midst of an asteriod storm
						subBoss = new SubBoss(width, 30 + rand() % (height - 60), subBossImage, &TakeLife, &enemiesDown, &bossesKilled);
						gameObjects.push_back(subBoss);

						//Bullets for the boss
						if (subBoss->getOnScreen())
						{
							if (rand() % 5 == 0)  //Randomizer determines the frequency of enemy fire
							{
								subBossBullet = new AlienBullet(subBoss->getX() - (142 / 2), subBoss->getY(), albulletImage, &TakeHealth);
								gameObjects.push_back(subBossBullet);
								al_play_sample(enemyShot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
							}
						}
					}				
				}

				//Global score updation based on enemies killed
				//10 points per standard enemy and power up and 50 for each boss
				score = ship1->getEnemiesDestroyed() * 10 + ship1->getPwrup() * 10 + ship1->getBossesDestroyed() * 50;
				totalLives = ship1->getTries();        //Hold the tries accumulated in present level for future use

				//Set up the random variable for some other SFX
				temprandSFX = rand() % 4;   //For 5 possibilities

				//=========================================================================================================//
				//                       UPDATE OBJECTS USING THE LIST
				//=========================================================================================================//
				for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); ++itr1)
				{
					(*itr1)->UpdateObject();
				}

				//=================================================================================================================//
				//                     COLLISION DETECTION ENGINE USING THE LIST
				//==================================================================================================================//

				for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); ++itr1)
				{
					if (!(*itr1)->onScreenCollide()) //if object is both not on screen and collidable move on to the next one
						continue;
					for (itr2 = itr1; itr2 != gameObjects.end(); ++itr2) //itr2 starts pointing at itr1 object upon collision detection
					{
						if (!(*itr2)->onScreenCollide()) // again if object is both not on screen and collidable move on to the next one
							continue;
						if ((*itr1)->getObjType() == (*itr2)->getObjType())  //We don't care if alike objects collide with each other
							continue;
						if ((*itr1)->getCollision((*itr2))) //Check if the objects of differing types have collided
						{
							(*itr1)->Collided((*itr2)->getObjType());
							(*itr2)->Collided((*itr1)->getObjType()); //Tell the 2 objects that they collided into each other

							//Testing out explosions and collisions. Change this to only create an explosion for collision with certain
							//objects ie aliens with bullets and NOT spaceship with powerups
							//Also adjust for bullets with enemies and enemies with spaceship
							//Create an explosion between the average of the 2 objects coordinates
							if (((*itr1)->getObjType() == BULLET) && ((*itr2)->getObjType() == ALIEN))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								if (rand() % 25 == 0)
								{
									al_play_sample(dukeGood, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								}
								if (ship1->getEnemiesDestroyed() == 48)
								{
									if (rand() % 3 == 0)
									{
										al_play_sample(dukeRestinPieces, 1.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									else
									{
										al_play_sample(dukeHell, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									
								}
								if (score == 250 || score == 500 || score == 750 || score == 1000 || score == 1250 || score == 1500)
								{
									if (temprandSFX == 0)
									{
										al_play_sample(superb, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 1)
									{
										al_play_sample(excellent, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 2)
									{
										al_play_sample(outstanding, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 3)
									{
										al_play_sample(wellDone, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
								}
							}

							if (((*itr2)->getObjType() == BULLET) && ((*itr1)->getObjType() == ALIEN))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								if (rand() % 25 == 0)
								{
									al_play_sample(dukeGood, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								}
								if (ship1->getEnemiesDestroyed() == 48)
								{
									if (rand() % 3 == 0)
									{
										al_play_sample(dukeRestinPieces, 1.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									else
									{
										al_play_sample(dukeHell, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
								}
								if (score == 250 || score == 500 || score == 750 || score == 1000 || score == 1250 || score == 1500)
								{
									if (temprandSFX == 0)
									{
										al_play_sample(superb, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 1)
									{
										al_play_sample(excellent, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 2)
									{
										al_play_sample(outstanding, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 3)
									{
										al_play_sample(wellDone, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
								}
							}

							if (((*itr1)->getObjType() == PLAYER) && ((*itr2)->getObjType() == ALIEN))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);	
								al_play_sample(Arrgh, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id9);
							}

							if (((*itr2)->getObjType() == PLAYER) && ((*itr1)->getObjType() == ALIEN)) 
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								al_play_sample(Arrgh, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id9);
							}

							//Considerations for collisions with an alien bullet
							if (((*itr1)->getObjType() == ALIENBULLET) && ((*itr2)->getObjType() == PLAYER))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
							}

							if (((*itr2)->getObjType() == ALIENBULLET) && ((*itr1)->getObjType() == PLAYER))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
							}

							//Considerations for collisions with power up objects
							if (((*itr1)->getObjType() == POWER) && ((*itr2)->getObjType() == PLAYER))
							{
								al_play_sample(pwrUp, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								if (rand() % 25 == 0)
								{
									al_play_sample(dukeHail, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id17);
								}
								if (ship1->getPwrup() == 30 || ship1->getPwrup() == 60 || ship1->getPwrup() == 90)
								{
									al_play_sample(dukeGetSome, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}

							if (((*itr2)->getObjType() == POWER) && ((*itr1)->getObjType() == PLAYER))
							{
								al_play_sample(pwrUp, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								if (rand() % 25 == 0)
								{
									al_play_sample(dukeHail, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id17);
								}
								if (ship1->getPwrup() == 30 || ship1->getPwrup() == 60 || ship1->getPwrup() == 90)
								{
									al_play_sample(dukeGetSome, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								}
							}

							//Considerations for collisions with random enemies
							if (((*itr1)->getObjType() == BULLET) && ((*itr2)->getObjType() == ENEMY))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								if (rand() % 15 == 0)
								{
									al_play_sample(dukeSort, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id18);
								}
								if (score == 250 || score == 500 || score == 750 || score == 1000 || score == 1250 || score == 1500)
								{
									if (temprandSFX == 0)
									{
										al_play_sample(superb, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 1)
									{
										al_play_sample(excellent, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 2)
									{
										al_play_sample(outstanding, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 3)
									{
										al_play_sample(wellDone, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
								}
							}

							if (((*itr2)->getObjType() == BULLET) && ((*itr1)->getObjType() == ENEMY))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								if (rand() % 15 == 0)
								{
									al_play_sample(dukeSort, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id18);
								}
								if (score == 250 || score == 500 || score == 750 || score == 1000 || score == 1250 || score == 1500)
								{
									if (temprandSFX == 0)
									{
										al_play_sample(superb, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 1)
									{
										al_play_sample(excellent, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 2)
									{
										al_play_sample(outstanding, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 3)
									{
										al_play_sample(wellDone, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
								}
							}

							if (((*itr1)->getObjType() == PLAYER) && ((*itr2)->getObjType() == ENEMY))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								al_play_sample(Arrgh, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id9);
							}

							if (((*itr2)->getObjType() == PLAYER) && ((*itr1)->getObjType() == ENEMY))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								al_play_sample(Arrgh, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id9);
							}

							//Considerations for BOSSES
							if (((*itr1)->getObjType() == BULLET) && ((*itr2)->getObjType() == BOSS))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								if (rand() % 25 == 0)
								{
									al_play_sample(dukeHell, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id19);
								}
								if (score == 250 || score == 500 || score == 750 || score == 1000 || score == 1250 || score == 1500)
								{
									if (temprandSFX == 0)
									{
										al_play_sample(superb, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 1)
									{
										al_play_sample(excellent, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 2)
									{
										al_play_sample(outstanding, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 3)
									{
										al_play_sample(wellDone, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
								}
							}

							if (((*itr2)->getObjType() == BULLET) && ((*itr1)->getObjType() == BOSS))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								if (rand() % 25 == 0)
								{
									al_play_sample(dukeHell, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id19);
								}
								if (score == 250 || score == 500 || score == 750 || score == 1000 || score == 1250 || score == 1500)
								{
									if (temprandSFX == 0)
									{
										al_play_sample(superb, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 1)
									{
										al_play_sample(excellent, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 2)
									{
										al_play_sample(outstanding, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
									if (temprandSFX == 3)
									{
										al_play_sample(wellDone, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
									}
								}
							}

							if (((*itr1)->getObjType() == PLAYER) && ((*itr2)->getObjType() == BOSS))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								al_play_sample(Arrgh, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id9);
							}

							if (((*itr2)->getObjType() == PLAYER) && ((*itr1)->getObjType() == BOSS))
							{
								explode = new Explosion(((*itr1)->getX() + (*itr2)->getX()) / 2, ((*itr1)->getY() + (*itr2)->getY()) / 2, explodeImage);
								gameObjects.push_back(explode);
								al_play_sample(boom, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
								al_play_sample(Arrgh, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id9);

							}

						}

					}
				}

				//Accounting for State changes if the player dies
				if (ship1->getTries() <= 0)
				{
					rand(); rand(); rand();
					temprandLost = rand() % 4;  //4 possibilities

					al_stop_sample(&id9);
					al_stop_sample(&id17);
					al_stop_sample(&id18);
					al_stop_sample(&id19);
					
					al_play_sample(gameOver, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id4);
					FSM(state, LOST);

					//reset timer variable
					dt = 0;
					old_time = time;
					dt = time - old_time;

					if (temprandLost == 1)
					{
						al_play_sample(neverWin, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					}
			
					else if (temprandLost == 2)
					{
						al_play_sample(DontMakeMeLaugh, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					}
					else if (temprandLost == 3)
					{
						al_play_sample(youSuck, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					}
					else
					{
						al_play_sample(SKmuaHaha2, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
					}
				}

				//Increment the level number if you defeat enough aliens

				if (level < 6)
				{
					if (ship1->getEnemiesDestroyed() >= 68) //ADDED MORE THAN 48 FOR TESTING
					{
						al_play_sample(stageClear, 1.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id2);
						/*if (ship1->getHealth() >= 100)
						{
							al_play_sample(flawlessVictory, 1.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						}*/
						al_stop_sample(&id17);
						al_stop_sample(&id18);
						al_stop_sample(&id19);
						al_stop_sample(&id9);
						FSM(state, LEVEL);
						level++;

						//Rest Timer Variable
						dt = 0;
						old_time = time;
						dt = time - old_time;

						//Play a special soundclip for the render state based on level number
						if (level == 2)
						{
							al_play_sample(dukeBabesBullets, 1.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id12);
						}
						else if (level == 3)
						{
							al_play_sample(dukeChewGum, 1.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id13);
						}
						else if (level == 4)
						{
							al_play_sample(dukeHoldongirls, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id14);
						}
						else if (level == 5)
						{
							al_play_sample(dukeMidtownexpress, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id15);
						}
						else if (level == 6)
						{
							al_play_sample(dukeRipNewOne, 2.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id20);
						}
					
					}
				}

				else if (level >= 6) //Special allowance for bosses level
				{
					if (ship1->getBossesDestroyed() >= 25)  //Kill 25 boss objects to win
					{
						al_stop_sample(&id17);
						al_stop_sample(&id18);
						al_stop_sample(&id19);
						al_stop_sample(&id9);

						al_play_sample(beatGame, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id3);
						al_play_sample(dukeImDukeNukem, 2.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0); //Play a sound effect	
						FSM(state, LEVEL);  //Make allocation for end screen in render section
						level++;

						//Rest Timer Variable
						dt = 0;
						old_time = time;
						dt = time - old_time;
					}
				}

				//Speed up our player ship if he obtained enough powerups
				if (ship1->getPwrup() >= 10)
				{
					ship1->setspeedX(10);
					ship1->setspeedY(10);
				}
				else if (ship1->getPwrup() >= 20)
				{
					ship1->setspeedX(15);
					ship1->setspeedY(15);
				}
				else
				{
					ship1->setspeedX(6);
					ship1->setspeedY(6);
				}
	
			}
			
			//FREE UP MEMORY AS SOON AS AN OBJECT GOES OFF SCREEN
			//HELPS US PUT MORE AND MORE OBJECTS ON SCREEN WITHOUT AFFECTING MEMORY TOO MUCH
			//NB THIS DOES NOT DELETE THE ALIEN ARRAY FROM MEMORY. This only occurs at end of the code
			//THE ALIENS WILL HAVE TO BE SEPARATELY ERASED ONE BY ONE AFTER COLLISSION WITH A BULLET

			for (itr1 = gameObjects.begin(); itr1 != gameObjects.end();)  //we leave out the ++itr1 part here since the body updates
			{
				if ((!(*itr1)->getOnScreen()) && ((*itr1)->getObjType() != ALIEN))
				{
					delete (*itr1);
					itr1 = gameObjects.erase(itr1);  //NB We don't call the destroy method here since we don't 
				}                                   //want to destroy the bitmap images at this stage

				else
				{
					itr1++;
				}
			}

			//Erase the aliens from the list if they were hit by a bullet
			//Attempting to delete each alien using this method was causing errors so we just set it to erase the aliens from the list
			//Hopefully erasing the aliens at the end using the conventional method will prevent memory leaks.
			for (itr1 = gameObjects.begin(); itr1 != gameObjects.end();)  //we leave out the ++itr1 part here since the body updates
			{
				if ((!(*itr1)->getOnScreen()) && ((*itr1)->getObjType() == ALIEN))
				{
					//delete (*itr1);
					//delete(&itr1);
					itr1 = gameObjects.erase(itr1);  //NB We don't call the destroy method here since we don't 
				}                                   //want to destroy the bitmap images at this stage

				else
				{
					itr1++;
				}
			}

	//======================================================================================================
			//RENDER==>UPDATE THE OBJECT'S POSITION ON SCREEN AND DRAW IT ACCORDINGLY
	//======================================================================================================

			if (render && al_is_event_queue_empty(event_queue)) //ONLY DRAW WHEN EVENT QUE IS EMPTY FOR SMOOTH GAMEPLAY
			{
				render = false;
				//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 145, 0, "FPS: %i", gameFPS); //display FPS on screen
				
				//=========================================================================================================//
				//                       RENDER OBJECTS USING THE LIST
				//=========================================================================================================//

				//FSM CONSIDERATIONS
				if (state == INTRO)
				{
					//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 145, 0, "Time Passed: %f", dt);
					al_draw_textf(gameFont, al_map_rgb(190, 202, 207), 30, 250, 0, "Group 14 Presents");
					//al_draw_textf(font36, al_map_rgb(190, 202, 207), 80, 550, 0, "PRESS SPACE BAR TO BEGIN BATTLE");
				
					if (dt > 12 && dt <= 17)
					{
						al_clear_to_color(al_map_rgb(0,0,0));
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 145, 0, "Time Passed: %f", dt);
						al_draw_text(gameFont, al_map_rgb(190, 202, 207), 350, 200, 0, "A");
						al_draw_text(gameFont, al_map_rgb(190, 202, 207), 30, 250, 0, "Bad Dog Studios");
						al_draw_text(gameFont, al_map_rgb(190, 202, 207), 300, 300, 0, "Game");
					}

					else if (dt > 17 && dt <= 22)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 145, 0, "Time Passed: %f", dt);
						al_draw_text(bloodyFont, al_map_rgb(148, 4, 21), 20, 250, 0, "ChupaCabra Game Engine");
					}

					else if (dt > 22 && dt <= 27)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						ratingScreen->RenderObject();
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 145, 0, "Time Passed: %f", dt);
					}
					else if (dt > 27)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						introScreen->RenderObject();

						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 145, 0, "Time Passed: %f", dt);
						al_draw_text(gameFont, al_map_rgb(190, 202, 207), 30, 20, 0, "Galaxy Guardian");
						al_draw_text(gameFont, al_map_rgb(190, 202, 207), 50, 250, 0, "The Alien Wars");
						al_draw_textf(font36, al_map_rgb(190, 202, 207), 80, 550, 0, "PRESS SPACE BAR FOR MENU");
					}
									
				}

				else if (state == TITLE)
				{
					startScreen->RenderObject();

					//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 145, 0, "Time Passed: %f", dt);
					//al_draw_textf(gameFont, al_map_rgb(190, 202, 207), 50, 250, 0, "Galaxy Guardian");
					al_draw_text(gameFont, al_map_rgb(190, 202, 207), 30, 20, 0, "Galaxy Guardian");
					al_draw_text(gameFont, al_map_rgb(190, 202, 207), 50, 250, 0, "The Alien Wars");
					al_draw_textf(font36, al_map_rgb(190, 202, 207), 80, 550, 0, "PRESS SPACE BAR TO BEGIN BATTLE");

				}

				else if (state == PLAYING)
				{
					//Start Rendering once we are in the playing state 
					
					for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); ++itr1)
					{
						(*itr1)->RenderObject();
					}

						al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "TRIES: %i  ENEMIES KILLED: %i",
							ship1->getTries(), ship1->getEnemiesDestroyed());

						al_draw_textf(font18, al_map_rgb(255, 0, 255), 280, 5, 0, "P-UPS: %i",
							ship1->getPwrup());

						al_draw_textf(font18, al_map_rgb(255, 0, 255), 380, 5, 0, "HEALTH: %i",
						ship1->getHealth());

						al_draw_textf(font18, al_map_rgb(255, 0, 255), 505, 5, 0, "LEVEL: %i", level);
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 500, 5, 0, "TOTAL SCORE: %i", totalScore);
						al_draw_textf(font18, al_map_rgb(255, 0, 255), 580, 5, 0, " CURRENT SCORE: %i", score);
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 145, 0, "FPS: %i", gameFPS); //display FPS on screen

						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 45, 0, "Time Passed: %f", dt);

						if (level >= 6)
						{
							al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 25, 0, "BOSSES DOWN: %i", ship1->getBossesDestroyed());
						}
				}

				else if (state == LOST)
				{
					gameoverScreen->RenderObject();
					//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 45, 0, "Time Passed: %f", dt);
					al_draw_textf(bloodyFont, al_map_rgb(148, 4, 21), 200, 200, 0, "GAME OVER");
					al_draw_textf(font36, al_map_rgb(190, 202, 207), 65, 550, 0, "PRESS THE 'A' KEY TO RESUME BATTLE");
					al_draw_textf(font36, al_map_rgb(190, 202, 207), 225, 50, 0, "TOTAL SCORE: %i", totalScore);
				}

				else if (state == LEVEL)
				{
					if (level <= 2)
					{
						levelupScreen->RenderObject();
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 45, 0, "Time Passed: %f", dt);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 250, 0, "LEVEL %i CLEARED", level - 1);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 290, 0, "TOTAL SCORE: %i", totalScore);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 5, 550, 0, "PRESS THE 'A' KEY TO PROGRESS BATTLE");
					}
					else if (level == 3)
					{
						levelupScreen2->RenderObject();
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 45, 0, "Time Passed: %f", dt);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 340, 0, "LEVEL %i CLEARED", level - 1);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 380, 0, "TOTAL SCORE: %i", totalScore);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 5, 550, 0, "PRESS THE 'A' KEY TO PROGRESS BATTLE");
					}
					else if (level == 4)
					{
						levelupScreen3->RenderObject();
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 45, 0, "Time Passed: %f", dt);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 250, 0, "LEVEL %i CLEARED", level - 1);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 290, 0, "TOTAL SCORE: %i", totalScore);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 5, 550, 0, "PRESS THE 'A' KEY TO PROGRESS BATTLE");
					}
					else if (level == 5)
					{
						levelupScreen4->RenderObject();
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 45, 0, "Time Passed: %f", dt);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 250, 0, "LEVEL %i CLEARED", level - 1);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 290, 0, "TOTAL SCORE: %i", totalScore);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 5, 550, 0, "PRESS THE 'A' KEY TO PROGRESS BATTLE");
					}
					else if (level == 6)
					{
						levelupScreen5->RenderObject();
						//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 45, 0, "Time Passed: %f", dt);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 250, 0, "LEVEL %i CLEARED", level - 1);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 225, 290, 0, "TOTAL SCORE: %i", totalScore);
						al_draw_textf(comicFontBold36, al_map_rgb(255, 0, 255), 5, 550, 0, "PRESS THE 'A' KEY TO PROGRESS BATTLE");
					}

					else  //At this point start rendering the beatgame graphics
					{
						if (dt <= 15)
						{
							beatgameScreen2->RenderObject();
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 3, 0, "Upon Vanquishing alien spaceships Duke's Spaceship ran out of gas!");
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 20, 0, "Not one to quit, Duke decided to continue the fight on foot");
						}
						else if (dt > 15 && dt <= 30)
						{
							beatgameScreen3->RenderObject();
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 3, 0, "Duke engaged the invaders with Extreme Prejudice!");
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 20, 0, "Talk about being Xenophobic! But they were after Earth's babes after all.");
						}
						else if (dt > 30 && dt <= 45)
						{
							beatgameScreen4->RenderObject();
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 3, 0, "The invaders had hit up Duke's favourite 'Gentlemen's Club'.");
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 20, 0, "Luckily the main man arrived just in time to save his favourite dancer.");
							al_draw_textf(comicFontB36, al_map_rgb(255, 0, 255), 3, 40, 0, "Looks like Duke won't be saving his tip money after all.");
						}
						else if (dt > 45 && dt <= 60)
						{
							beatgameScreen5->RenderObject();
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 3, 0, "Human ground forces got their machismo back and brought the pain!");
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 20, 0, "With most of the babes already indoctrinated by the alien invaders,");
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 40, 0, "..these military men had to do something with their pent up testosterone!");
						}
						
						else if (dt > 60 && dt <= 75)
						{
							beatgameScreen6->RenderObject();
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 3, 0, "Unbeknownst to our hero, the Alien man hating dominatrix Borg Queen...");
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 20, 0, "...was already planning a second assault on earth after her forces regroup.");
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 40, 0, "We were safe from her wrath, but it was on borrowed time!");
						}
						else if (dt > 75 && dt <= 90)
						{
							beatgameScreen7->RenderObject();
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 3, 0, "Duke decided to kick back and get some R&R.");
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 20, 0, "Despite a long intense battle, it seems he was..");
							al_draw_textf(comicFontB36, al_map_rgb(255, 255, 255), 3, 40, 0, "..ready for MORE ACTION....of another sort hee hee");
						}
						else if (dt > 90)
						{
							beatgameScreen->RenderObject();
							//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 45, 0, "Time Passed: %f", dt);
							//al_draw_textf(font36, al_map_rgb(255, 0, 255), 225, 50, 0, "GAME CLEARED");
							al_draw_textf(font36, al_map_rgb(255, 255, 255), 225, 520, 0, "TOTAL SCORE: %i", totalScore);
							al_draw_textf(font36, al_map_rgb(255, 255, 255), 45, 550, 0, "PRESS THE 'A' KEY FOR CREDITS ROLL");
						}
						
					}
				
				}

				else if (state == CREDITS)
				{
					al_clear_to_color(al_map_rgb(0, 0, 0));
					//al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 145, 0, "Time Passed: %f", dt);

					if (dt <= 5)
					{
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "BASEOBJECT CLASS DESIGN");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Sanath Maharaj");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 180, 0, "Praneel Misthry");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 220, 0, "Cheyenne Pillay");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 260, 0, "Eustacia Rajman");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 300, 0, "Aashutoshh Rampersadh");
					}
					else if (dt > 5 && dt <= 10)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "COLLISSION GAME ENGINE");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Sanath Maharaj");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 180, 0, "Praneel Misthry");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 220, 0, "Cheyenne Pillay");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 260, 0, "Eustacia Rajman");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 300, 0, "Aashutoshh Rampersadh");
					}
					else if (dt > 10 && dt <= 15)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "ALIEN CLASS DESIGN");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Eustacia Rajman");
					}
					else if (dt > 15 && dt <= 20)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "ALL BULLET CLASSES");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Cheyenne Pillay");
					}
					else if (dt > 20 && dt <= 25)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 50, 100, 0, "RANDOM ENEMIES / POWER UPS");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Aashutoshh Rampersadh");
					}
					else if (dt > 25 && dt <= 30)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 50, 100, 0, "BACKGROUNDS AND BOSSES");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Sanath Maharaj");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 180, 0, "Praneel Misthry");
					}
					else if (dt > 30 && dt <= 35)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 50, 100, 0, "EXPLOSIONS & ASTEROIDS CLASSES");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Aashutoshh Rampersadh");
					}
					else if (dt > 35 && dt <= 40)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "PLAYER SPACESHIP CLASS");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Sanath Maharaj");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 180, 0, "Praneel Misthry");
					}
					else if (dt > 40 && dt <= 45)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "FINITE STATE MACHINE DESIGN");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Sanath Maharaj");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 180, 0, "Praneel Misthry");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 220, 0, "Cheyenne Pillay");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 260, 0, "Eustacia Rajman");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 300, 0, "Aashutoshh Rampersadh");
					}
					else if (dt > 45 && dt <= 50)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "SPRITE ANIMATION TESTING");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Praneel Misthry");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 180, 0, "Aashutoshh Rampersadh");
					}
					else if (dt > 50 && dt <= 55)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "ARTWORK SELECTION");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Cheyenne Pillay");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 180, 0, "Eustacia Rajman");
					}
					else if (dt > 55 && dt <= 60)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "SOUNDTRACK SELECTION");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Cheyenne Pillay");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 180, 0, "Sanath Maharaj");
					}
					else if (dt > 60 && dt <= 65)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 100, 0, "SOUND EFFECTS SELECTION");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 140, 0, "Praneel Misthry");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 180, 0, "Aashutoshh Rampersadh");
					}
					else if (dt > 65 && dt <= 70)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 80, 100, 0, "SPECIAL THANKS / ASSETS USED");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 140, 0, "Konami Computer Entertainment Japan");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 180, 0, "Deviant Art");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 220, 0, "3D REALMS");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 100, 260, 0, "MIDWAY / Nether Realm Studios");
					}
					else if (dt > 70 && dt <=75)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 10, 260, 0, "THANK YOU FOR PLAYING FROM GROUP 14");
					}
					else if (dt > 75)
					{
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 260, 0, "THE END");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 340, 0, "Press 'A' to play again");
						al_draw_textf(font36, al_map_rgb(255, 255, 255), 200, 380, 0, "Press 'Esc' to quit");
					}


				}

				//FLIP BUFFERS
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}

		}

	}

	//============================================================================================================//                                                                 
	//                                 DESTROY ANY PROJECT OBJECTS USED   
	//Release Resources============================================================================================//
	//NB Whatever resources you add later in the project must be removed here to prevent
	//memory leaks. -- PM==========================================================================================//
	//Delete all objects except the ones pointed to by the alien array pointerss
	for (itr1 = gameObjects.begin(); itr1 != gameObjects.end() && ((*itr1)->getObjType() != ALIEN);)  //we leave out the ++itr1 part here since the body updates
	{
		(*itr1)->DestroyObject();
		delete (*itr1); //Delete the objects themselves
		itr1 = gameObjects.erase(itr1);  //Remove this index of itr1 completely then return back to the next
	}

	//Delete the alien array objects separately
	for (int i = 0; i < 8; ++i) {
		delete[] a1[i];
	}
	delete[] a1;

//=============================================================================================
//PROJECT OBJECTS TO DESTROY OUTSIDE THE LIST
//============================================================================================

introScreen->DestroyObject();
ratingScreen->DestroyObject();
startScreen->DestroyObject();
gameoverScreen->DestroyObject();

levelupScreen->DestroyObject();
levelupScreen2->DestroyObject();
levelupScreen3->DestroyObject();
levelupScreen4->DestroyObject();
levelupScreen5->DestroyObject();

beatgameScreen->DestroyObject();
beatgameScreen2->DestroyObject();
beatgameScreen3->DestroyObject();
beatgameScreen4->DestroyObject();
beatgameScreen5->DestroyObject();
beatgameScreen6->DestroyObject();
beatgameScreen7->DestroyObject();

delete ratingScreen;
delete introScreen;
delete startScreen;
delete gameoverScreen;

delete levelupScreen;
delete levelupScreen2;
delete levelupScreen3;
delete levelupScreen4;
delete levelupScreen5;

delete beatgameScreen;
delete beatgameScreen2;
delete beatgameScreen3;
delete beatgameScreen4;
delete beatgameScreen5;
delete beatgameScreen6;
delete beatgameScreen7;

al_destroy_bitmap(dukeBarImage);
al_destroy_bitmap(contraEndImage);
al_destroy_bitmap(femBaddieImage);
al_destroy_bitmap(groundBattleImage1);
al_destroy_bitmap(groundBattleImage2);
al_destroy_bitmap(groundBattleImage3);
al_destroy_bitmap(introImage);
al_destroy_bitmap(ESRBImage);
al_destroy_bitmap(beatGameImage);
al_destroy_bitmap(subBossImage);
al_destroy_bitmap(asteroidImage);
al_destroy_bitmap(startImage);

al_destroy_bitmap(levelupImage);
al_destroy_bitmap(levelupImage2);
al_destroy_bitmap(levelupImage3);
al_destroy_bitmap(levelupImage4);
al_destroy_bitmap(levelupImage5);

al_destroy_bitmap(gameOverImage);
al_destroy_bitmap(powerBulletImage);
al_destroy_bitmap(albulletImage);
al_destroy_bitmap(backGimage);
al_destroy_bitmap(midGimage);
al_destroy_bitmap(foreGimage);
al_destroy_bitmap(explodeImage);
al_destroy_bitmap(pwrImage);
al_destroy_bitmap(shipImage);
al_destroy_bitmap(alienImage);

al_destroy_sample(dukeChewGum);
al_destroy_sample(dukeHoldongirls);
al_destroy_sample(dukeMidtownexpress);
al_destroy_sample(dukeImDukeNukem);
al_destroy_sample(dukeBabesBullets);
al_destroy_sample(dukeRipNewOne);

al_destroy_sample(dukeRestinPieces);
al_destroy_sample(dukeAlienBstds2);
al_destroy_sample(dukeAlienBstds);
al_destroy_sample(creditTheme);
al_destroy_sample(gameIntro);
al_destroy_sample(neverWin);
al_destroy_sample(wellDone);
al_destroy_sample(outstanding);
al_destroy_sample(excellent);
al_destroy_sample(superb);
al_destroy_sample(youSuck);
al_destroy_sample(flawlessVictory);
al_destroy_sample(Arrgh);
al_destroy_sample(DontMakeMeLaugh);
al_destroy_sample(SKmuaHaha2);
//al_destroy_sample(SKmuaHaha);
al_destroy_sample(dukeGetSome);
al_destroy_sample(dukeSort);
al_destroy_sample(dukeHail);
//al_destroy_sample(dukeMedieval);   //Left out due to errors at run time
al_destroy_sample(dukeHell);
al_destroy_sample(dukeGood);
al_destroy_sample(beatGame);
al_destroy_sample(titleTrack);
al_destroy_sample(gameOver);
al_destroy_sample(stageClear);
al_destroy_sample(defeat);
al_destroy_sample(pwrUp);
al_destroy_sample(playerShot);
al_destroy_sample(enemyShot);
al_destroy_sample(boom);
al_destroy_sample(song);
al_destroy_sample_instance(soundTrack);

//=======================================================================
//DESTROY SHELL OBJECTS
//========================================================================

al_destroy_font(comicFontBold36);
al_destroy_font(comicFont36);
al_destroy_font(comicFontB36);
al_destroy_font(bloodyFont);
al_destroy_font(font36);
al_destroy_font(gameFont);
al_destroy_font(font18);
al_destroy_event_queue(event_queue);
al_destroy_timer(timer);
al_destroy_display(display);

	return 0;
}

void setupAliens(ALLEGRO_BITMAP *image)
{
	float tempX = 0;
	float tempY = 0;
	for (int i = 0; i < 8; i++)
	{
		a1[i] = new Alien[6];   //Each row is a set of 6 aliens --> 8 rows of 6 aliens each
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			tempX = tempX + 114;
			a1[i][j].InitAlien(800 + tempX, 120 + tempY, image, TakeLife);  //Initialize each alien
			gameObjects.push_back(&a1[i][j]);
		}
		tempX = 0;
		tempY = tempY + 49;
	}

}

bool allAliensDestroyed()
{
	int deadCount = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (!(a1[i][j].getOnScreen()))
			{
				deadCount++;
			}
		}
	}
	if (deadCount >= 48)
		return true;
	else
		return false;
}



void __cdecl enemiesDown()   //Fully global function to add a score point
{
	ship1->bodyCount();
}

void __cdecl TakeLife()   //Fully global function to lose a try
{
	ship1->loseTry();
}

void _cdecl TakeHealth() //Fully global functions to lose 25 points of health
{
	ship1->loseHealth();
}

void _cdecl bossesKilled()
{
	ship1->bossesDown();
}

void FSM(int &state, int nextState)
{
	if (state == INTRO)
	{

	}

	else if (state == TITLE)         //What happens when you LEAVE the TITLE state
	{
		al_stop_sample(&id1);
	}

	else if (state == PLAYING) //What happens when you LEAVE the playing state
	{
		//When leaving the playing state remove all objects from the list which are not meant to be permanent
		//For our game the player and background are permanent and should not be removed from the screen on leaving the playing state.

		for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); itr1++)
		{
			if ((*itr1)->getObjType() != PLAYER && (*itr1)->getObjType() != MISC) 
			{
				(*itr1)->setOnScreen(false);   //Remove uneccessary objects from the display
											  //No need to explicitly delete them as the update algorithm takes care of this
											 //if objects are not meant to be on screen
			}
		}

		//Special care to be taken for the aliens
		//The previous array of aliens will get erased from screen and removed from the list upon leaving the playing state
		//BUT we must ensure that the original alien layout will be ready when we eventually enter the playing state again
		//hence we repeat the set up of aliens here

		ALLEGRO_BITMAP *alienImage = NULL;
		alienImage = al_load_bitmap("EnemyShip2.png");
		al_convert_mask_to_alpha(alienImage, al_map_rgb(0, 0, 0)); //Since background of alien is black
		al_convert_mask_to_alpha(alienImage, al_map_rgb(255, 0, 255));

		setupAliens(alienImage);
		al_stop_sample_instance(soundTrack);
	}

	else if (state == LOST)   //What happens when you LEAVE the lost state
	{

	}

	else if (state == LEVEL)  //What happens when you LEAVE the level transition state
	{
		//Upon leaving the LEVEL transition state pass in a new background based on level variable
		//NB THE ORDER IN WHICH THE BACKGROUNDS ARE PASSED IS DIFFERENT FROM main()
		//Some foregrounds and backgrounds have been switched to give the illusion of the ship travelling behind a planet in some levels
		//This is due to the order in which the ship, background and aliens get rendered after a level transition
		//By default we start at level 1 always so start taking into consideration level 2 onwards

		if (level == 2)
		{
			//send up the soundtrack
			song = al_load_sample("Waterfall.ogg");
			soundTrack = al_create_sample_instance(song);
			al_set_sample_instance_playmode(soundTrack, ALLEGRO_PLAYMODE_LOOP); //Play level song in a loop
			al_attach_sample_instance_to_mixer(soundTrack, al_get_default_mixer()); //Attach song to the default allegro audio mixer

			backGimage = al_load_bitmap("xfx_by_apocalypticart4-d58zmlp.png");
			midGimage = al_load_bitmap("starMG.png");
			foreGimage = al_load_bitmap("starfield-front_converted.png");

			//Pass in the mid background using same object but different memory location. So this is actually a different variable
			//Using the same pointer to point at a different memory location of the same type of object
			backdrop = new Background(midGimage, 3);
			gameObjects.push_front(backdrop);

			//Pass in the first background image to the list
			backdrop = new Background(backGimage, 15);
			gameObjects.push_front(backdrop);

			//Pass in the fore background using same object but different memory location. So this is actually a different variable
			backdrop = new Background(foreGimage, 30);
			gameObjects.push_back(backdrop);
		} 

		else if (level == 3)
		{
			//Set up Soundtrack
			song = al_load_sample("MG2-Lv1ST.ogg");
			soundTrack = al_create_sample_instance(song);
			al_set_sample_instance_playmode(soundTrack, ALLEGRO_PLAYMODE_LOOP); //Play level song in a loop
			al_attach_sample_instance_to_mixer(soundTrack, al_get_default_mixer()); //Attach song to the default allegro audio mixer

			backGimage = al_load_bitmap("balance_by_apocalypticart4-d4f42s4_converted.png");
			midGimage = al_load_bitmap("starMG.png");
			foreGimage = al_load_bitmap("starfield-front_converted.png");

			//Pass in the mid background using same object but different memory location. So this is actually a different variable
			//Using the same pointer to point at a different memory location of the same type of object
			backdrop = new Background(midGimage, 5);
			gameObjects.push_front(backdrop);

			//Pass in the first background image to the list
			backdrop = new Background(backGimage, 20);
			gameObjects.push_front(backdrop);

			//Pass in the fore background using same object but different memory location. So this is actually a different variable
			backdrop = new Background(foreGimage, 30);
			gameObjects.push_back(backdrop);
		}

		else if (level == 4)
		{
			//Set up Soundtrack
			song = al_load_sample("MGS-Encounter.ogg");
			soundTrack = al_create_sample_instance(song);
			al_set_sample_instance_playmode(soundTrack, ALLEGRO_PLAYMODE_LOOP); //Play level song in a loop
			al_attach_sample_instance_to_mixer(soundTrack, al_get_default_mixer()); //Attach song to the default allegro audio mixer

			backGimage = al_load_bitmap("radiance_by_apocalypticart4-d4sqhs2.png");
			midGimage = al_load_bitmap("starMG.png");
			foreGimage = al_load_bitmap("starfield-front_converted.png");

			//Pass in the mid background using same object but different memory location. So this is actually a different variable
			//Using the same pointer to point at a different memory location of the same type of object
			backdrop = new Background(midGimage, 5);
			gameObjects.push_front(backdrop);

			//Pass in the first background image to the list
			backdrop = new Background(backGimage, 25);
			gameObjects.push_front(backdrop);

			//Pass in the fore background using same object but different memory location. So this is actually a different variable
			backdrop = new Background(foreGimage, 30);
			gameObjects.push_back(backdrop);
		}

		else if (level == 5)
		{
			//song = al_load_sample("Contra- ScaryIntro.ogg");
			song = al_load_sample("Castlevania SOTN - Prologue.ogg");
			soundTrack = al_create_sample_instance(song);
			al_set_sample_instance_playmode(soundTrack, ALLEGRO_PLAYMODE_LOOP); //Play level song in a loop
			al_attach_sample_instance_to_mixer(soundTrack, al_get_default_mixer()); //Attach song to the default allegro audio mixer

			backGimage = al_load_bitmap("blue_by_tozzie-d308bp9.png");
			midGimage = al_load_bitmap("starMG.png");
			foreGimage = al_load_bitmap("starfield-front_converted.png");

			//Pass in the mid background using same object but different memory location. So this is actually a different variable
			//Using the same pointer to point at a different memory location of the same type of object
			backdrop = new Background(midGimage, 5); //3
			gameObjects.push_front(backdrop);

			//Pass in the first background image to the list
			backdrop = new Background(backGimage, 25); //1
			gameObjects.push_front(backdrop);

			//Pass in the fore background using same object but different memory location. So this is actually a different variable
			backdrop = new Background(foreGimage, 30); //5
			gameObjects.push_back(backdrop);
		}

		else if (level == 6)
		{
			//BOSS CODE HERE!!
			//Enter the soundtrack and backgrounds for the boss stage
			//Back in main(), make allowance for a boss character to appear after level 5!!
			//Then make further allowances to successfully allow the player to beat the game

			//Remove the aliens grid and background but keep everything else
			for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); itr1++)
			{
			if ((*itr1)->getObjType() != PLAYER && (*itr1)->getObjType() != MISC)
			{
			(*itr1)->setOnScreen(false);   //Remove uneccessary objects from the display
			//No need to explicitly delete them as the update algorithm takes care of this
			//if objects are not meant to be on screen
			}
			}

			//Add in boss soundtrack
			song = al_load_sample("BaneBoss.ogg");
			soundTrack = al_create_sample_instance(song);
			al_set_sample_instance_playmode(soundTrack, ALLEGRO_PLAYMODE_LOOP); //Play level song in a loop
			al_attach_sample_instance_to_mixer(soundTrack, al_get_default_mixer()); //Attach song to the default allegro audio mixer
			//================================================================================//
			//======= ADD IN BOSS BACKGROUND HERE ============================================//
			//==================================================================================//
			//backGimage = al_load_bitmap("space_by_aloneinspace-d5oznhy_converted.png");
			backGimage = al_load_bitmap("HD Galaxy Wallpaper.png");
			midGimage = al_load_bitmap("starMG.png");
			foreGimage = al_load_bitmap("starfield-front_converted.png");

			//Pass in the mid background using same object but different memory location. So this is actually a different variable
			//Using the same pointer to point at a different memory location of the same type of object
			backdrop = new Background(midGimage, 3);
			gameObjects.push_front(backdrop);

			//Pass in the first background image to the list
			backdrop = new Background(backGimage, 15);
			gameObjects.push_front(backdrop);

			//Pass in the fore background using same object but different memory location. So this is actually a different variable
			backdrop = new Background(foreGimage, 30);
			gameObjects.push_back(backdrop);
		}
		else
		{
			song = al_load_sample("Stage 1.ogg");
			soundTrack = al_create_sample_instance(song);
			al_set_sample_instance_playmode(soundTrack, ALLEGRO_PLAYMODE_LOOP); //Play level song in a loop
			al_attach_sample_instance_to_mixer(soundTrack, al_get_default_mixer()); //Attach song to the default allegro audio mixer

			backGimage = al_load_bitmap("farback.png");
			midGimage = al_load_bitmap("starMG.png");
			foreGimage = al_load_bitmap("starfield-front_converted.png");

			//Pass in the mid background using same object but different memory location. So this is actually a different variable
			//Using the same pointer to point at a different memory location of the same type of object
			backdrop = new Background(midGimage, 3);
			gameObjects.push_front(backdrop);

			//Pass in the first background image to the list
			backdrop = new Background(backGimage, 15);
			gameObjects.push_front(backdrop);

			//Pass in the fore background using same object but different memory location. So this is actually a different variable
			backdrop = new Background(foreGimage, 30);
			gameObjects.push_back(backdrop);
		}
	}

	else if (state == CREDITS) //What happens upon leaving the credit state
	{
		
	}

	state = nextState;

	if (state == INTRO)  //What happens when you ENTER the INTRO state
	{
		al_stop_sample(&id10);
	}

	else if (state == TITLE)        //What happens when you ENTER the TITLE state
	{
		al_stop_sample(&id3);
		al_play_sample(titleTrack, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &id8);
		level = 1;
		totalScore = 0;   //Reset user score upon game finish
	}

	else if (state == PLAYING) //What happens when you ENTER the playing state
	{
						 //When entering the playing state simply initialize our ship
						//The init method is convenient here since our ship didn't get destroyed at this point
		ship1->Init(); //Don't need to pass the bitmap in at this point as an argument
		al_stop_sample(&id8);
		al_stop_sample(&id1);
		al_stop_sample(&id2);
		al_stop_sample(&id4);
		al_stop_sample(&id5);
		
		al_play_sample_instance(soundTrack);
	}

	else if (state == LOST)   //What happens when you ENTER the LOST state
	{
		//totalScore = 0;                    //Decided making the player lose his score on game over was too evil ;-)
		totalScore = totalScore + score + 10;   //Update total game score 
	}

	else if (state == LEVEL) //What happens when you ENTER the LEVEL transition state
	{
		totalScore = totalScore + score + 10; //Update total game score
		
		//Upon Entering a level transition remove everything except the player and aliens from the list
		//by setting its onscreen value to false. The updation algorithm in main will automatically take care of deletion
		for (itr1 = gameObjects.begin(); itr1 != gameObjects.end(); itr1++)
		{
			if ((*itr1)->getObjType() != PLAYER && (*itr1)->getObjType() != ALIEN) 
			{
				(*itr1)->setOnScreen(false);   //Remove the previous backgrounds and other MISC items
			}
		}

	}

	else if (state == CREDITS)  //What happens when you ENTER the credits state
	{
		al_stop_sample(&id3);  //Stop the beat game sound sample
	}

}

