/*
 *  croloader.cpp
 *  croviewer
 *
 *  Created by fuxx on 03.12.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#include "croloader.h"
#include "croinit.h"
#include "croglobal.h"
#include "crostring.h"
#include "crofile.h"
#include "crowatermark.h"
#include "SDL_rotozoom.h"
#include "SDL_thread.h"

CroLoader::CroLoader() 
{
	// viewer
	g_viewer = CroInit::getInstance().getViewerInterface();
	// loader background image
	this->loadLoaderImage();
	// get current size of art vector
	// reset percent 
	percent = 0;
	positionCurrent = 0;
	tempRotate = 0;
	
	// initiate temp rect where we can draw tex
	dest.y = 0;
	dest.w = (WINDOW_X/100);
	dest.h = 5;
	dest.y = WINDOW_Y-dest.h;
	// init new thread and draw the awesome naked man
	thread = SDL_CreateThread(&staticThread,this);
	if ( thread == NULL ) 
	{
        fprintf(stderr, "Couldnt start thread: %s\n", SDL_GetError());
        exit(0);
    }
}

bool CroLoader::updateSatus(int currentPosition)
{
	positionCurrent = currentPosition;
	percent = (currentPosition*100)/vector_Size;
	// calculate percentage
	dest.x = 0;
	dest.w = (WINDOW_X/100)*percent;
	SDL_FillRect( g_viewer->GetSurface(), &dest, SDL_MapRGB(g_viewer->GetSurface()->format, percent*2, percent*2, 0) );
	return true;
}

bool CroLoader::fadeOut()
{
	if (thread != NULL)
		SDL_KillThread(thread);
	SDL_Surface* temp_source = SDL_CreateRGBSurface (g_viewer->GetSurface()->flags|SDL_SRCALPHA, 
												g_viewer->GetSurface()->w, g_viewer->GetSurface()->h, g_viewer->GetSurface()->format->BitsPerPixel, 
												g_viewer->GetSurface()->format->Rmask, g_viewer->GetSurface()->format->Gmask, 
												g_viewer->GetSurface()->format->Bmask, 
												g_viewer->GetSurface()->format->Amask); 
	SDL_Surface* source = SDL_DisplayFormat(temp_source);
	SDL_FreeSurface(temp_source);
	
	g_viewer->apply_surface(0, 0, source, g_viewer->GetSurface());
	SDL_FillRect(g_viewer->GetSurface(), 0, SDL_MapRGB(g_viewer->GetSurface()->format, 0, 0, 0));

    for (int alpha=255; alpha>0; --alpha) 
    { 
		SDL_FillRect(g_viewer->GetSurface(), 0, SDL_MapRGB(g_viewer->GetSurface()->format, alpha, alpha, alpha));
		g_viewer->apply_surface(0, 0, g_viewer->GetBackgroundImage(), g_viewer->GetSurface());
        SDL_SetAlpha (source, SDL_SRCALPHA, alpha) ; 
		g_viewer->apply_surface(0, 0, source, g_viewer->GetSurface());
		CroInit::getInstance().flipScreen();
		SDL_Delay(10); 
		alpha-=4;
    }
	
	return true;
}

bool CroLoader::reset()
{
	percent = 0;
	// initiate temp rect where we can draw tex
	dest.w = (WINDOW_X/100);
	dest.h = 5;
	dest.y = (WINDOW_Y-dest.h);
	buffer = NULL;
	return true;
}

bool CroLoader::setVectorSize(int size)
{
	vector_Size = size;
	return true;
}

void CroLoader::loadLoaderImage()
{
	// Image in das Surface übergeben
	SDL_Surface* loader_temp;
#ifdef WIN32
	loader_temp = IMG_Load(CroFile::buildPath("MAG\\croResources\\Images\\loading.png"));
#elif LINUX
	loader_temp = IMG_Load(CroFile::buildPath("/MAG/croResources/Images/loading.png"));
#else
	loader_temp = IMG_Load(CroFile::buildPath("/Contents/Resources/croResources/Images/loading.png"));
#endif
	if (NULL == loader_temp)
	{
		printf(IMG_GetError());
		printf("Failed on loading background image\n");
		exit(1);
	}
	loaderBackground = SDL_DisplayFormat(loader_temp);
	SDL_FreeSurface(loader_temp);
	
	// load cro watermark image
	// Image in das Surface übergeben
	loader_temp = NULL;
	loader_temp = IMG_ReadXPMFromArray(cro_watermark_xpm);
	if (NULL == loader_temp)
	{
		printf(IMG_GetError());
		printf("Failed on loading background image\n");
		exit(1);
	}
	watermarkImage = SDL_DisplayFormat(loader_temp);
	SDL_FreeSurface(loader_temp);
}

int CroLoader::setLoaderImageWithData()
{
	if (percent < 98)
	{
		tempRotate++;
	}
	else 
	{
		return(0);
	}
	SDL_FillRect(g_viewer->GetSurface(), &g_viewer->GetSurface()->clip_rect, SDL_MapRGB(g_viewer->GetSurface()->format, 0, 0, 0));
	SDL_Surface *temp = rotozoomSurface (loaderBackground, tempRotate, 1, 1);
	if ( !temp )
	{
		return (0);
	}
	g_viewer->apply_surface(0, 0, temp, g_viewer->GetSurface());
	g_viewer->apply_surface((WINDOW_X-watermarkImage->w), (WINDOW_Y-watermarkImage->h), watermarkImage, g_viewer->GetSurface());
	// calculate percentage
	dest.x = 0;
	dest.w = (WINDOW_X/100)*percent;
	SDL_FillRect( g_viewer->GetSurface(), &dest, SDL_MapRGB(g_viewer->GetSurface()->format, percent*2, percent*2, 0) );
	SDL_FreeSurface(temp);
	CroInit::getInstance().flipScreen();
	SDL_Delay(this->delay());
	setLoaderImageWithData();
	return (1);
}

Uint32 CroLoader::delay(void)
{
    static Uint32 nextTime = 0;
    Uint32 now;
	
    now = SDL_GetTicks();
    if ( nextTime <= now ) {
        nextTime = now+TRANSFORM_MS;
        return(0);
    }
    return(nextTime-now);
}

int CroLoader::staticThread(void *pData)
{
	return ((CroLoader*)pData)->setLoaderImageWithData(); 
}
