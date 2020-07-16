/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "Vector.h"

#define IN_ATTACK        (1 << 0)
#define IN_JUMP            (1 << 1)
#define IN_DUCK            (1 << 2)
#define IN_FORWARD        (1 << 3)
#define IN_BACK            (1 << 4)
#define IN_USE            (1 << 5)
#define IN_CANCEL        (1 << 6)
#define IN_LEFT            (1 << 7)
#define IN_RIGHT        (1 << 8)
#define IN_MOVELEFT        (1 << 9)
#define IN_MOVERIGHT    (1 << 10)
#define IN_ATTACK2        (1 << 11)
#define IN_RUN            (1 << 12)
#define IN_RELOAD        (1 << 13)
#define IN_ALT1            (1 << 14)
#define IN_ALT2            (1 << 15)
#define IN_SCORE        (1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED        (1 << 17)    // Player is holding the speed key
#define IN_WALK            (1 << 18)    // Player holding walk key
#define IN_ZOOM            (1 << 19)    // Zoom key for HUD zoom
#define IN_WEAPON1        (1 << 20)    // weapon defines these bits
#define IN_WEAPON2        (1 << 21)    // weapon defines these bits
#define IN_BULLRUSH        (1 << 22)
#define IN_GRENADE1        (1 << 23)    // grenade 1
#define IN_GRENADE2        (1 << 24)    // grenade 2
#define IN_ATTACK3        (1 << 25)

class CUserCmd
{
public:
	enum {
		BTN_IN_ATTACK = 1 << 0,
		BTN_IN_JUMP = 1 << 1,
		BTN_IN_DUCK = 1 << 2,
		BTN_IN_FORWARD = 1 << 3,
		BTN_IN_BACK = 1 << 4,
		BTN_IN_USE = 1 << 5,
		BTN_IN_MOVELEFT = 1 << 9,
		BTN_IN_MOVERIGHT = 1 << 10,
		BTN_IN_ATTACK2 = 1 << 11,
		BTN_IN_SCORE = 1 << 16,
		BTN_IN_BULLRUSH = 1 << 22
	};

	// For matching server and client commands for debugging
	int		command_number;

	// the tick the client created this command
	int		tick_count;

	// Player instantaneous view angles.
	Vector	viewangles;
	// Intended velocities
	//	forward velocity.
	float	forwardmove;
	//  sideways velocity.
	float	sidemove;
	//  upward velocity.
	float	upmove;
	// Attack button states
	byte		buttons;
	// Impulse command issued.
	byte    impulse;
	// Current weapon id
	int		weaponselect;
	int		weaponsubtype;

	int		random_seed;	// For shared random functions

	short	mousedx;		// mouse accum in x from create move
	short	mousedy;		// mouse accum in y from create move

	// Client only, tracks whether we've predicted this command at least once
	bool	hasbeenpredicted;
};