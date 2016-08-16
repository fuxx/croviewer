/*
 *  croinit.h
 *  croviewer
 *
 *  Created by fuxx on 09.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROINIT__
#define __CROINIT__

#include "crofile.h"
#include "cromusic.h"
#include "croscrollbutton.h"
#include "croartviewer.h"
#include "crosurface.h"
#include "croviewer.h"
#include "croartpreview.h"
#include "cromusic.h"
#include "croloader.h"
#include "SDL.h"
#include "SDL_Bitmap_Font.h"

class CroInit {
public: 
	static CroInit &getInstance();
	
	void flipScreen();
	bool initArtPreview();
	bool initAudioInterface();
	bool initBitmapFontInterace();
	bool initCroFilesystem();
	bool initGraphicInterface(bool fullscreen = true);
	void initPreviewInterface();
	
	// getter
	CroArtViewer* getArtViewer() { return artViewer; };
	CroArtPreview* getArtPreview() { return artPreview; };
	CroFile* getFileSystem() { return fileSystem; };
	CroLoader* getLoader() { return loader; };
	CroMusic* getMusicSystem() { return musicSystem; };
	CroScrollButton* getScrollButton() { return scroll_button; };
	CroSurface* getSurfaceInterface() { return surfaceInterface; };
	CroViewer* getViewerInterface() { return viewerInterface; };
	
private:
	CroInit() {};
	~CroInit() {};
	CroInit(const CroInit &);             // intentionally undefined
	CroInit & operator=(const CroInit &); // intentionally undefined
	
	int initState;
	
	void backtraceCode(void);
	
	CroArtViewer* artViewer;
	CroArtPreview* artPreview;
	CroFile *fileSystem;
	CroLoader* loader;
	CroMusic *musicSystem;
	CroScrollButton *scroll_button;
	CroSurface *surfaceInterface;
	CroViewer *viewerInterface;
	
	SDL_Bitmap_Font *bitmap_font;
	
};

#endif