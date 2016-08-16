/*
 *  cropositionprocessor.h
 *  croviewer
 *
 *  Created by fuxx on 09.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROPOSITIONPROCESSOR__
#define __CROPOSITIONPROCESSOR__

#include "croartistregions.h"
#include "croartistartregions.h"
#include "crobuttonregions.h"
#include "cromusicbuttonregions.h"
#include "croregions.h"
#include "croscrollbuttonregions.h"
#include "cropreviewscrollbuttonregions.h"
#include "cropreviewimageregions.h"
#include "SDL.h"
#include <vector>

class CroPositionProcessor {
public:
	
	bool setUpButtonRegions();
	int getIdentifierForCoordinate(int x, int y);
	int getIdentifierForMusicPlayerCoordinate(int x, int y);
	int getPreviewScrollIdentifierForCoordinate(int x,  int y);
	int getImageIdentifierForPreviewCoordinate( int x,  int y, bool visibleOnly = false);
	int getScrollDirectionForCoordinate( int x, int y);
	int getSizeOfAristArt();
	
	static CroPositionProcessor &getInstance();
	std::string getStringIdentifierForArtistCoordinate(int x,  int y);
	std::string getStringIdentifierForArtistArtCoordinate(int x,int y);
	std::vector<CroPreviewImageRegions*> previewimage_regions;

	void setNewPreviewImage(int identifier,  int x_start,  int x_end,  int y_start,  int y_end);
	void setNewArtist(int section,  int x_start,  int x_end,  int y_start,  int y_end, std::string artist_name);
	void setNewArtistArt(int section,  int x_start,  int x_end,  int y_start,  int y_end, std::string artistart_name);
	void setNewScrollButton(int direction,  int x_start,  int x_end,  int y_start,  int y_end);
	void setNewPreviewScrollButton(int direction,  int x_start,  int x_end,  int y_start,  int y_end);
	void setUpArtistVector();
	void setUpArtistArtVector();
	void setUpScrollButton();
	void setUpPreviewImageVector();
	
private:
	CroPositionProcessor() {};
	~CroPositionProcessor() {};
	CroPositionProcessor(const CroPositionProcessor &);             // intentionally undefined
	CroPositionProcessor & operator=(const CroPositionProcessor &); // intentionally undefined
	std::vector<CroArtistRegions*> artist_regions;
	std::vector<CroArtistArtRegions*> artistArt_regions;
	std::vector<CroButtonRegions*> button_regions;
	std::vector<CroMusicButtonRegions*> musicbutton_regions;
	std::vector<CroPreviewScrollButtonRegions*> previewscrollbutton_regions;
	std::vector<CroRegions*> regions;
	std::vector<CroScrollButtonRegions*> scrollbutton_regions;
};

#endif