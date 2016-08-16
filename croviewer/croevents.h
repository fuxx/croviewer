/*
 *  croevents.h
 *  croviewer
 *
 *  Created by fuxx on 09.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROEVENTS__
#define __CROEVENTS__
#include "SDL.h"
#include "croinit.h"
#include "croglobal.h"

class CroEvents {
public:
	static CroEvents &getInstance();
	
	bool processEvent(SDL_Event event);
	bool routeEvent(SDL_Event event);
private:
	CroEvents();
	~CroEvents() {};
	CroEvents(const CroEvents &);             // intentionally undefined
	CroEvents & operator=(const CroEvents &); // intentionally undefined
	
	int mx,my;
	Uint8 ms;
	
	CroArtViewer* g_artViewer;
	CroArtPreview* g_artPreview;
	CroMusic* g_musicPlayer;
	CroSurface* g_surface; // surface interface	
	CroViewer* g_viewer; // viewer interface
};

#endif