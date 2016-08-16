/*
 *  croscrollbutton.h
 *  croviewer
 *
 *  Created by fuxx on 17.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROSCROLLBUTTON__
#define __CROSCROLLBUTTON__

//#include "Globals.h"
#include <string.h>
#include "SDL.h"

#include "croglobal.h"
#include "cropositionprocessor.h"
#include "crosurface.h"
#include "croviewer.h"

enum SCOLL_BUTTON_DIRECTION {
	UP,
	DOWN,
	LEFT=10,
	RIGHT=11
};

class CroScrollButton {
public:
	CroScrollButton();
	~CroScrollButton();
	bool drawButtonUp();
	bool drawButtonDown();
	bool drawButtonLeft(bool fullscreen);
	bool drawButtonRight(bool fullscreen);
	bool drawButtonHighlight(bool fullscreen, int x_start, int x_end, int y_start, int y_end);
	bool hideButtonUp();
	bool hideButtonDown();
	bool hideButtonLeft();
	bool hideButtonRight();
private:
	void addEvents();
	bool initButtonUp();
	bool initButtonDown();
	bool initButtonRight();
	bool initButtonLeft();
	
	CroSurface* m_surface;
	CroViewer* m_viewer;
	
	SDL_Surface* button_up, *button_down, *button_up_temp, *button_down_temp;
	SDL_Surface* button_left, *button_right, *button_left_temp, *button_right_temp;
	
	
};


#endif