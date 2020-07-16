/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once
#include "../MainHeader.h"
#include "../Menu.h"

#include "Classes/Vector.h"
#include "Classes/CUserCmd.h"

class CHooks 
{
public:
	void init();
	void shutdown();
};

inline CHooks * Hooks;