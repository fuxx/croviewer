/*
 *  croinit.cpp
 *  croviewer
 *
 *  Created by fuxx on 09.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#include "croinit.h"
#ifndef WIN32
#include <execinfo.h> 
#endif


CroInit& CroInit::getInstance()
{
	static CroInit instance;
	int initState = 0;
	return instance;
}

// später muss hier ein fs::path übermittelbar sein! 

bool CroInit::initGraphicInterface(bool fullscreen) 
{
	CroViewer *viewer = new CroViewer;
	
	// Fenster erstellen
	if(!viewer->InitCro(WINDOW_X,WINDOW_Y,WINDOW_BIT, fullscreen)) 
	{
		fprintf(stderr, "Failed to init SDL.\n");
		exit(0);
	}
	viewerInterface = viewer;
	CroSurface *surface = new CroSurface(viewer->GetSurface());
	CroInit::viewerInterface = viewer;
	CroInit::surfaceInterface = surface;
	CroInit::scroll_button = new CroScrollButton();
	CroInit::artViewer = new CroArtViewer();
	CroInit::loader = new CroLoader();
	return true;
}

bool CroInit::initCroFilesystem() 
{
	
	CroInit::fileSystem = new CroFile;
	
	initState = CroInit::fileSystem->buildFilesystem();
	return true;
}

bool CroInit::initArtPreview() 
{
	if (0 == initState)
	{
		return false;
	}
	CroInit::artPreview = new CroArtPreview();
	CroInit::artViewer->buildUpArtVector();
	return true;
}

bool CroInit::initAudioInterface() 
{
	musicSystem = new CroMusic();
	if (!musicSystem->initSoundEngine()) 
	{
		fprintf(stderr, "Soundengine init failed...!!!\n");
		return false;
	}
	return true;
}

void CroInit::flipScreen()
{
	//CroInit::backtraceCode();
	SDL_Flip(viewerInterface->GetSurface());
	//printf("-------------------------\n");
}

#ifndef WIN32
void CroInit::backtraceCode() 
{
	void* addresses[10];
	int size;
	size = backtrace(addresses, 10);
	char** symbols = backtrace_symbols(addresses, size);
	int x;
	for (x = 0; x < size; ++x) {
		printf("%s\n", symbols[x]);
	}
	free(symbols);
}
#endif
