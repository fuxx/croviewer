/*
 *  croloader.h
 *  croviewer
 *
 *  Created by fuxx on 03.12.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROLOADER__
#define __CROLOADER__
#include "croviewer.h"
#include "SDL.h"

class CroLoader 
{
public:
	CroLoader();
	bool updateSatus(int currentPosition);
	bool fadeOut();
	bool reset();
	bool setVectorSize(int size);
private:
	CroViewer* g_viewer;
	int percent, positionCurrent, vector_Size;
	char* buffer;
	SDL_Rect dest;
	SDL_Rect destText;
	SDL_Surface* loaderBackground;
	SDL_Surface* watermarkImage;
	SDL_Thread* thread;
	void loadLoaderImage();
	int setLoaderImageWithData();
	Uint32 delay(void);
protected:
	int tempRotate;
	static int staticThread(void *pData);
};

#endif