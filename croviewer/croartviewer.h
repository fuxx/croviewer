/*
 *  croartviewer.h
 *  croviewer
 *
 *  Created by fuxx on 18.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROARTVIEWER__
#define __CROARTVIEWER__

//#include "Globals.h"
#include <string>
#include "crofile.h"
#include "SDL.h"

class CroArtViewer {
public:
	CroArtViewer();
	~CroArtViewer();
	
	bool isDrawed;
	bool artVectorExist;
	
	bool buildUpArtVector();
	bool checkArtAtCoordinate(int x, int y);
	bool checkCoordinateForRightLeftScroll(int x, int y);
	bool inFullscreen() { return isFullscreen; };
	bool playMusic(std::string identifier);
	bool scrollArt(int direction, bool img_click = false, int x = 0, int y = 0, bool externalCall = false, bool fullscreenCall = false);
	bool showArt(std::string identifier);
	bool showArtInFullscreen(std::string identifier);
	
private:
	
	bool isFullscreen;
	int start_x, start_y;
	int image_click_count;
	int x_coordinate, y_coordinate;
	
	Uint32 delay(void);
	
	bool transformImageWithNewImage(std::string identifier, bool fullscreen = false);
	SDL_Surface* artImage;
	std::string currentArtistArtIdentifier;
	std::vector<ArtistArtPaths> artViewer_Vector;
};

#endif