/*
 *  croevents.cpp
 *  croviewer
 *
 *  Created by fuxx on 09.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#include "croevents.h"
#include "SDL.h"

CroEvents::CroEvents()
{
	g_artViewer = CroInit::getInstance().getArtViewer();
	g_artPreview = CroInit::getInstance().getArtPreview();
	g_musicPlayer = CroInit::getInstance().getMusicSystem();
	g_surface = CroInit::getInstance().getSurfaceInterface();
	g_viewer = CroInit::getInstance().getViewerInterface();
	mx = 0;
	my = 0;
	ms = 0;
}

CroEvents& CroEvents::getInstance()
{
	static CroEvents instance;
	return instance;
}

bool CroEvents::processEvent(SDL_Event event) 
{
	switch (event.type) 
	{
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) 
		{
			case SDLK_UP:
				if (g_surface->checkScrollingListAndDraw(VIEW_WINDOW_START_X+1, VIEW_WINDOW_START_Y+1, 4))
					break;
				else if (g_artViewer->scrollArt(SDL_BUTTON_WHEELUP))
					break;
				break;
			case SDLK_DOWN:
				if (g_surface->checkScrollingListAndDraw(VIEW_WINDOW_START_X+1, VIEW_WINDOW_START_Y+1, 5))
					break;
				else if (g_artViewer->scrollArt(SDL_BUTTON_WHEELDOWN))
					break;								
				break;
			case SDLK_LEFT:
				g_artPreview->checkScrollAndDraw(-1, -1, SDL_BUTTON_WHEELUP);
				break;
			case SDLK_RIGHT:
				g_artPreview->checkScrollAndDraw(-1, -1, SDL_BUTTON_WHEELDOWN);
				break;
			case SDLK_s:
				CroInit::getInstance().getMusicSystem()->stopMusic();
				break;
			case SDLK_p:
				CroInit::getInstance().getMusicSystem()->playFile(CroInit::getInstance().getMusicSystem()->getCurrentPlayingPath());
				break;
			case SDLK_q:
				exit(0);
			case SDLK_ESCAPE:
				exit(0);
			default:
				break;
		} 
			break;
		case SDL_MOUSEMOTION:
			if(g_surface->checkInput(event.motion.x, event.motion.y))
				break;
			if(g_artPreview->checkMouseOverAndDraw(event.motion.x, event.motion.y, 0))
				break;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch(event.button.button) {
				case 0:
					break;
				case 1:
					// on left button click
					if (g_surface->checkTopLevelMenuAndPaint(event.motion.x, event.motion.y))
						break;
					else if (g_musicPlayer->checkPlayerCoordinate(event.motion.x, event.motion.y))
						break;
					else if(g_artViewer->checkCoordinateForRightLeftScroll(event.motion.x, event.motion.y))
						break;
					else if (g_artViewer->checkArtAtCoordinate(event.motion.x, event.motion.y))
						break;
					else if (g_musicPlayer->checkCoordinate(event.motion.x, event.motion.y))
						break;
					else if (g_surface->checkArtistAndPaint(event.motion.x, event.motion.y))
						break;
					else if(g_artViewer->scrollArt(1, true, event.motion.x, event.motion.y))
						break;
					else if (g_artPreview->checkMouseOverAndDraw(event.motion.x, event.motion.y, 1))
						break;
					else if (g_artPreview->checkScrollAndDraw(event.motion.x, event.motion.y, 1))
						break;
					else 
						//printf("Not found possible function for processing click on x: %d y: %d\n", event.motion.x, event.motion.y);
						break;
				case SDL_BUTTON_WHEELUP:
					if (g_surface->checkScrollingListAndDraw(event.motion.x, event.motion.y, SDL_BUTTON_WHEELUP))
						break;
					else if (g_artPreview->checkScrollAndDraw(event.motion.x, event.motion.y, SDL_BUTTON_WHEELUP))
						break;
					else if (g_artViewer->scrollArt(SDL_BUTTON_WHEELUP))
						break;
					break;
				case SDL_BUTTON_WHEELDOWN:
					if (g_surface->checkScrollingListAndDraw(event.motion.x, event.motion.y, SDL_BUTTON_WHEELDOWN))
						break;
					else if (g_artPreview->checkScrollAndDraw(event.motion.x, event.motion.y, SDL_BUTTON_WHEELDOWN))
						break;
					else if (g_artViewer->scrollArt(SDL_BUTTON_WHEELDOWN))
						break;
					break;
				default:
					break;
			}
			//printf("x: %d, y: %d\n", event.motion.x, event.motion.y);
			break;
		case SDL_QUIT:
			exit(0);
	} 
	
	// check for mouse left button pressed
	/*if (SDL_GetMouseState(&mx, &my)&SDL_BUTTON(1))
	{
		printf("Mouse Button 1(left) is pressed.\n");
	}*/
	return true;
}

bool CroEvents::routeEvent(SDL_Event event) 
{
	return true;
}


