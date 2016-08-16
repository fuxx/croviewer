/*
 *  cropositionprocessor.cpp
 *  croviewer
 *
 *  Created by fuxx on 09.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#include "cropositionprocessor.h"
#include "croglobal.h"

CroPositionProcessor& CroPositionProcessor::getInstance()
{
	static CroPositionProcessor instance;
	return instance;
}


// @todo : dynamic definition of regions
bool CroPositionProcessor::setUpButtonRegions() 
{
	/*CroButtonRegions(int identifier, float x_min, float x_max, float y_min, float y_max) 
	: int_identifier(identifier), x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max) {};*/
	button_regions.push_back (new CroButtonRegions(ASCII, 420-10, 446+10, 162-10, 171+5));
	button_regions.push_back (new CroButtonRegions(MUSIC, 469-10, 502+10, 162-10, 171+5));
	button_regions.push_back (new CroButtonRegions(HIRES, 525-10, 553+10, 162-10, 171+5));
	button_regions.push_back (new CroButtonRegions(INFO, 576-10, 601+10, 162-10, 171+5));
	
	// music player 
	/*
	 CroMusicButtonRegions(int identifier, int function, int x_min, int x_max, int y_min, int y_max) : CroRegions(identifier, x_min, x_max, y_min, y_max) {};
	 */
	musicbutton_regions.push_back(new CroMusicButtonRegions(BACK, 752-10, 752+8, 675-10, 675+8));
	musicbutton_regions.push_back(new CroMusicButtonRegions(PLAY, 770-10, 770+8, 675-10, 675+8));
	musicbutton_regions.push_back(new CroMusicButtonRegions(PAUSE, 790-10, 790+8, 675-10, 675+8));
	musicbutton_regions.push_back(new CroMusicButtonRegions(STOP, 805-10, 805+8, 675-10, 675+8));
	musicbutton_regions.push_back(new CroMusicButtonRegions(FORWARD, 823-10, 823+8, 675-10, 675+8));
	
	if (0 == button_regions.size()) 
		return false;
	else 
		return true;
}

int CroPositionProcessor::getIdentifierForCoordinate( int x, int y )
{
	for (std::vector<CroButtonRegions*>::iterator i = button_regions.begin(); i != button_regions.end(); ++i)
	{
		int ret_value = (*i)->coordinate_in(x, y);
		if (-1 != ret_value)
			return ret_value;
	}
	return -1;
}

int CroPositionProcessor::getIdentifierForMusicPlayerCoordinate( int x, int y )
{
	for (std::vector<CroMusicButtonRegions*>::iterator i = musicbutton_regions.begin(); i != musicbutton_regions.end(); ++i)
	{
		int ret_value = (*i)->coordinate_in(x, y);
		if (-1 != ret_value)
			return ret_value;
	}
	return -1;
}

int CroPositionProcessor::getPreviewScrollIdentifierForCoordinate( int x, int y )
{
	for (std::vector<CroPreviewScrollButtonRegions*>::iterator i = previewscrollbutton_regions.begin(); i != previewscrollbutton_regions.end(); ++i)
	{
		int ret_value = (*i)->coordinate_in(x, y);
		if (-1 != ret_value)
			return ret_value;
	}
	return -1;
}

std::string CroPositionProcessor::getStringIdentifierForArtistCoordinate( int x, int y )
{
	for (std::vector<CroArtistRegions*>::iterator i = artist_regions.begin(); i != artist_regions.end(); ++i)
	{
		std::string ret_value = (*i)->coordinateIn(x, y);
		if (0 != ret_value.size())
			return ret_value;
	}
	return std::string("");
}

std::string CroPositionProcessor::getStringIdentifierForArtistArtCoordinate( int x,int y )
{
	for (std::vector<CroArtistArtRegions*>::iterator i = artistArt_regions.begin(); i != artistArt_regions.end(); ++i)
	{
		std::string ret_value = (*i)->coordinateIn(x, y);
		if (0 != ret_value.size())
			return ret_value;
	}
	return std::string("");
}

int CroPositionProcessor::getScrollDirectionForCoordinate( int x, int y )
{
	for (std::vector<CroScrollButtonRegions*>::iterator i = scrollbutton_regions.begin(); i != scrollbutton_regions.end(); ++i)
	{
		int ret_value = (*i)->coordinate_in(x, y);
		if (-1 != ret_value)
			return ret_value;
	}
	return -1;
}

int CroPositionProcessor::getImageIdentifierForPreviewCoordinate( int x, int y, bool visibleOnly /*= false*/ )
{
	for (std::vector<CroPreviewImageRegions*>::iterator i = previewimage_regions.begin(); i != previewimage_regions.end(); ++i)
	{
		int ret_value = (*i)->coordinate_in(x, y);
		if (-1 != ret_value)
		{
			return ret_value;
		}
			
	}
	return -1;
}

void CroPositionProcessor::setNewPreviewImage( int identifier, int x_start, int x_end, int y_start, int y_end )
{
	previewimage_regions.push_back (new CroPreviewImageRegions(identifier, x_start, x_end, y_start, y_end));
}


void CroPositionProcessor::setNewArtist( int section, int x_start, int x_end, int y_start, int y_end, std::string artist_name )
{
	artist_regions.push_back (new CroArtistRegions(section, x_start, x_end, y_start, y_end, artist_name));
}

void CroPositionProcessor::setUpArtistVector() 
{
	artist_regions.clear();
}

void CroPositionProcessor::setNewArtistArt( int section, int x_start, int x_end, int y_start, int y_end, std::string artistart_name )
{
	artistArt_regions.push_back (new CroArtistArtRegions(section, x_start, x_end, y_start, y_end, artistart_name));
}

int CroPositionProcessor::getSizeOfAristArt()
{
	return artist_regions.size();
}

void CroPositionProcessor::setUpArtistArtVector() 
{
	artistArt_regions.clear();
}

void CroPositionProcessor::setNewScrollButton( int direction, int x_start, int x_end, int y_start, int y_end )
{
	scrollbutton_regions.push_back (new CroScrollButtonRegions(direction, x_start, x_end, y_start, y_end));
}

void CroPositionProcessor::setNewPreviewScrollButton( int direction, int x_start, int x_end, int y_start, int y_end )
{
	previewscrollbutton_regions.push_back (new CroPreviewScrollButtonRegions(direction, x_start, x_end, y_start, y_end));
}

void CroPositionProcessor::setUpScrollButton()
{
	scrollbutton_regions.clear();
}



