//
//  croartpreview.h
//  croviewer
//
//  Created by fuxx on 18.10.10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef __CROARTPREVIEW__
#define __CROARTPREVIEW__

#include "cropreviewcontainer.h"
#include "croviewer.h"
#include "crofile.h"
#include "cropositionprocessor.h"
#include "crosurface.h"
#include "croartviewer.h"
#include "croloader.h"

class CroArtPreview
{
public:
	CroArtPreview();
	~CroArtPreview();
	bool checkScrollAndDraw(int x, int y, int click);
	bool checkMouseOverAndDraw(int x, int y, int click);
	bool drawImages(bool internalCall = false);
	bool drawImageWithIdentifier(int identifier, int current_x, int current_y);
	
private:
	bool drawed, previewClicked, imagesProcessed;
	int lastIdentifier, start_x, scroll_x;
	
	bool addImage(int section, std::string copyOfName,std::string artName);
	void drawImg(SDL_Surface* img, int x, int y);
	bool preProcessImages();
	void redrawSurfaceWithTop();
	
	CroArtViewer* g_artViewer;
	CroLoader* g_loader;
	CroSurface* g_surface;
	CroViewer* g_viewer;
	
	SDL_Surface* m_transparentLayer;
	std::vector<CroPreviewContainer*> m_previewContainerVec;
	std::vector<ArtistArtPaths> m_ArtVector;
};

#endif
