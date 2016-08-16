/*
 *  croartviewer.cpp
 *  croviewer
 *
 *  Created by fuxx on 18.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */
#include <stdexcept>
#include "croartviewer.h"
#include "croglobal.h"
#include "croinit.h"
#include "cropositionprocessor.h"

CroArtViewer::CroArtViewer() 
{
	artImage = NULL;
	isDrawed = false;
	artVectorExist = false;
}

bool CroArtViewer::checkArtAtCoordinate(int x, int y)
{
	if (isDrawed)
		return false;
	
	currentArtistArtIdentifier = CroPositionProcessor::getInstance().getStringIdentifierForArtistArtCoordinate(x, y);
	if (0 == currentArtistArtIdentifier.size())
	{
		return false;
	}
	if (CroInit::getInstance().getSurfaceInterface()->getCurrentSection() == MUSIC)
	{
		return false;
	}
	else 
	{
		return this->showArt(currentArtistArtIdentifier);
	}
	return false;
}

bool CroArtViewer::showArtInFullscreen(std::string identifier) 
{
	// dirty hack for left/right button
	/** FIX ME **/
	currentArtistArtIdentifier = identifier;
	
	// check file exists
	SDL_Surface* artImage_temp = IMG_Load(identifier.c_str());
	if (artImage_temp == NULL) 
	{
		isDrawed = false;
		return false;
	}	
	
	if (NULL != artImage) {
		SDL_FreeSurface(artImage);
	}
	artImage = SDL_DisplayFormat(artImage_temp);
	SDL_FreeSurface(artImage_temp);
	
	start_y = 0;
	return (CroArtViewer::scrollArt(1, true, VIEW_WINDOW_START_X+1, VIEW_WINDOW_START_Y+1, false, true));
}

bool CroArtViewer::transformImageWithNewImage(std::string identifier, bool fullscreen) 
{
	if (currentArtistArtIdentifier == identifier || artImage == NULL)
		return false;

	// preload new image
	// check file exists
	SDL_Surface* artImage_temp = IMG_Load(identifier.c_str());
	
	if (artImage_temp == NULL) 
	{
		isDrawed = false;
		return false;
	}
	CroInit::getInstance().getSurfaceInterface()->SetLevel(ARTVIEW);
	
	artImage = SDL_DisplayFormat(artImage_temp);
	SDL_FreeSurface(artImage_temp);
	
	if (artImage == NULL)
		return false;
	
	for(int i = 0; i <=(VIEW_WINDOW_END_X-VIEW_WINDOW_START_X); i+=30)
	{

		if (artImage->w <= i)
		{
			return true;
		}
		
		CroInit::getInstance().getSurfaceInterface()
		->DrawIMG(artImage, CroInit::getInstance().getViewerInterface(), 
				  VIEW_WINDOW_START_X+5,
				  VIEW_WINDOW_START_Y+VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW, 
				  i,
				  (VIEW_WINDOW_END_Y - VIEW_WINDOW_START_Y-30),
				  0, 0);
		CroInit::getInstance().flipScreen();
		SDL_Delay(this->delay());
	}
	return true;
}

Uint32 CroArtViewer::delay(void)
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

bool CroArtViewer::showArt(std::string identifier) 
{
	// dirty hack for left/right button
	/** FIX ME **/
	if (currentArtistArtIdentifier != identifier && artImage != NULL)
	{
		this->transformImageWithNewImage(identifier, false);
	}
	
	currentArtistArtIdentifier = identifier;
	
	// check file exists
	SDL_Surface* artImage_temp = IMG_Load(identifier.c_str());
	if (artImage_temp == NULL) 
	{
		isDrawed = false;
		return false;
	}	
	// set fullscreen back to false
	isFullscreen = false;
	// clean up coordinate array
	CroPositionProcessor::getInstance().setUpArtistArtVector();
	
	// set section to artview
	CroInit::getInstance().getSurfaceInterface()->SetLevel(ARTVIEW);
	
	// clear background
	CroInit::getInstance()
	.getViewerInterface()->apply_surface(
										 0, 
										 0, 
										 CroInit::getInstance().getViewerInterface()->GetBackgroundImage(), 
										 CroInit::getInstance().getViewerInterface()->GetSurface());
	if (NULL != artImage) {
		SDL_FreeSurface(artImage);
	}
	artImage = SDL_DisplayFormat(artImage_temp);
	SDL_FreeSurface(artImage_temp);
	
	if (artImage->w > (VIEW_WINDOW_END_X - VIEW_WINDOW_START_X))
	{
		x_coordinate = VIEW_WINDOW_START_X+5;
	}
	else 
	{
		x_coordinate = VIEW_WINDOW_START_X + (((VIEW_WINDOW_END_X - VIEW_WINDOW_START_X) / 2) - ((artImage->w / 2)));
	}
	
	// calculate y image size for center view
	if (artImage->h > (VIEW_WINDOW_END_Y - (VIEW_WINDOW_START_Y+VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW)))
	{
		y_coordinate = VIEW_WINDOW_START_Y+VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW;
	}
	else 
	{
		y_coordinate = VIEW_WINDOW_START_X + (((VIEW_WINDOW_END_Y - VIEW_WINDOW_START_Y) / 2) - ((artImage->h / 2)))-30;
	}
	
	
	
	CroInit::getInstance().getSurfaceInterface()
	->DrawIMG(artImage, CroInit::getInstance().getViewerInterface(), 
			  x_coordinate,
			  y_coordinate, 
			  (VIEW_WINDOW_END_X - VIEW_WINDOW_START_X-15),
			  (VIEW_WINDOW_END_Y - VIEW_WINDOW_START_Y-30),
			  0, 0);
	if (CroInit::getInstance().getSurfaceInterface()->getCurrentSection() != INFO) 
	{
		CroInit::getInstance().getScrollButton()->drawButtonLeft(isFullscreen);
		CroInit::getInstance().getScrollButton()->drawButtonRight(isFullscreen);
	}
	
	if(!CroInit::getInstance().getArtPreview()->drawImages())
		CroInit::getInstance().flipScreen();
	start_y = 0;
	isFullscreen = false;
	isDrawed = true;
	image_click_count = 0;
	return true;
}

bool CroArtViewer::scrollArt(int direction, bool img_click, int x, int y, bool externalCall, bool fullscreenCall)
{
	if (CroInit::getInstance().getSurfaceInterface()->getCurrentLevel() != ARTVIEW)
		return false;
	if (!isDrawed)
		return false;
	if (x > 0 && y > 0) 
	{
		if (VIEW_WINDOW_END_Y < y)
			return false;
	}
	
	if (direction == SDL_BUTTON_WHEELDOWN)
	{
		// is fullscreen? doesnt match the picture isnt fully drawed 
		// dont draw if size goes over Y
		if (isFullscreen) {
			if (((artImage->h) <= (start_y + 20)+WINDOW_Y) && (artImage->h < start_y+WINDOW_Y))
				return false;
			else 
				start_y += 20;
		} 
		else 
		{
			// dont draw if size goes over Y.
			if (artImage->h - (VIEW_WINDOW_END_Y - VIEW_WINDOW_START_Y) >= (start_y + 20))
			{	
				start_y += 20;
			}
			else
			{
				return false;
			}
		}
	}
	else if (direction == SDL_BUTTON_WHEELUP)
	{
		if (0 <= (start_y - 20))
		{	
			start_y -= 20;
		}
		else
		{
			return false;
		}
	}
	else if (direction == 1)
	{
		
	}
	else 
	{
		if (!externalCall && !isFullscreen)
			return false;
	}
	int x_coordinate = 0;
	int y_coordinate = 0;
	// is full screen? this method checks current state of image and switches between fullscreen
	if (!fullscreenCall) {
		if (img_click)
		{
			if (image_click_count % 2)
			{
				isFullscreen = false;
				image_click_count++;
				
			} else {
				if ((x > VIEW_WINDOW_START_X && x < VIEW_WINDOW_END_X) 
					&& (y > VIEW_WINDOW_START_Y+VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW && y < VIEW_WINDOW_END_Y))
				{
					isFullscreen = true;
					image_click_count--;
				}
			}
		} 
	} else {
		isFullscreen = true;
		image_click_count = 1;
	}
	// we need a calucaltion outside the fullscreen for fitting to view port
	if (!isFullscreen) 
	{
		if (artImage->w > (VIEW_WINDOW_END_X - VIEW_WINDOW_START_X))
		{
			x_coordinate = VIEW_WINDOW_START_X+5;
		}
		else 
		{
			x_coordinate = VIEW_WINDOW_START_X + (((VIEW_WINDOW_END_X - VIEW_WINDOW_START_X) / 2) - ((artImage->w / 2)));
		}
		
		// calculate y image size for center view
		
		if (artImage->h > (VIEW_WINDOW_END_Y - (VIEW_WINDOW_START_Y+VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW)))
		{
			y_coordinate = VIEW_WINDOW_START_Y+VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW;
		}
		else 
		{
			y_coordinate = VIEW_WINDOW_START_X + (((VIEW_WINDOW_END_Y - VIEW_WINDOW_START_Y) / 2) - ((artImage->h / 2)))-30;
		}
		
		
		// clear background
		CroInit::getInstance()
		.getViewerInterface()->apply_surface(
											 0, 
											 0, 
											 CroInit::getInstance().getViewerInterface()->GetBackgroundImage(), 
											 CroInit::getInstance().getViewerInterface()->GetSurface());
		
		// draw image
		CroInit::getInstance().getSurfaceInterface()
		->DrawIMG(artImage, CroInit::getInstance().getViewerInterface(), 
				  x_coordinate,
				  y_coordinate, 
				  (VIEW_WINDOW_END_X - VIEW_WINDOW_START_X-15),
				  (VIEW_WINDOW_END_Y - VIEW_WINDOW_START_Y-30),
				  0, start_y);	
		
		// left/right button with fullscreen status
		if (CroInit::getInstance().getSurfaceInterface()->getCurrentSection() != INFO) 
		{
			CroInit::getInstance().getScrollButton()->drawButtonLeft(isFullscreen);
			CroInit::getInstance().getScrollButton()->drawButtonRight(isFullscreen);
		}
		
		if(!CroInit::getInstance().getArtPreview()->drawImages(true) || !externalCall)
			CroInit::getInstance().flipScreen();
	} 
	else 
	{
		// calculate y image size for center view
		if (artImage->h < (WINDOW_Y))
		{
			y_coordinate = ((WINDOW_Y / 2 ) - (artImage->h / 2));
		} 
		else 
		{
			y_coordinate = 0;
		}
		
		if (artImage->w < (WINDOW_X))
		{
			x_coordinate = ((WINDOW_X / 2 ) - (artImage->w / 2));
		} 
		else 
		{
			x_coordinate = 0;
		}
		
		SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
		CroInit::getInstance().getSurfaceInterface()
		->DrawIMG(artImage, CroInit::getInstance().getViewerInterface(),
				  x_coordinate, 
				  y_coordinate, 
				  WINDOW_X,
				  WINDOW_Y,
				  0, start_y);
		if (CroInit::getInstance().getSurfaceInterface()->getCurrentSection() != INFO) 
		{
			CroInit::getInstance().getScrollButton()->drawButtonLeft(isFullscreen);
			CroInit::getInstance().getScrollButton()->drawButtonRight(isFullscreen);
		}
		CroInit::getInstance().flipScreen();
	}
	return true;
}

bool CroArtViewer::playMusic(std::string identifier)
{
	return true;
}

bool CroArtViewer::buildUpArtVector() 
{
	for (std::vector<ArtistArtPaths>::iterator i = CroInit::getInstance().getFileSystem()->getArtVector().begin(); 
		 i != CroInit::getInstance().getFileSystem()->getArtVector().end(); ++i)
	{
		if(strcmp((*i).sectionName.c_str(),section_char[MUSIC]) != 0) 
		{
			if ((*i).artPath.size() > 0)
				artViewer_Vector.push_back((*i));
		}
	}
	
	return true;
}

bool CroArtViewer::checkCoordinateForRightLeftScroll(int x, int y) 
{
	if (!isDrawed)
		return false;
	
	// get direction
	int direction = CroPositionProcessor::getInstance().getScrollDirectionForCoordinate(x, y);
	if (-1 == direction) 
		return false;
	
	// try to select current art
	for(unsigned int i=0; i < artViewer_Vector.size(); ++i) 
	{
		if(artViewer_Vector.at(i).artPath.compare(currentArtistArtIdentifier) == 0) 
		{
			if (direction == LEFT) 
			{
				if (-1 == (i-1)) 
				{
					return false;
				} 
				else 
				{
					--i;
					if (!isFullscreen)
					{
						this->showArt(artViewer_Vector.at(i).artPath);
					}
					else 
					{
						this->showArtInFullscreen(artViewer_Vector.at(i).artPath);
					}
					return true;
				}
				
			}
			else if (direction == RIGHT) 
			{
				if ((artViewer_Vector.size()-1) < (i+1)) 
				{
					return false;
				} 
				else 
				{
					++i;
					if (!isFullscreen)
					{
						this->showArt(artViewer_Vector.at(i).artPath);
					}
					else 
					{
						this->showArtInFullscreen(artViewer_Vector.at(i).artPath);
					}
					return true;
				}
			}
		}
	}
	return false;
}

CroArtViewer::~CroArtViewer() 
{
	if(NULL != artImage) 
	{
		SDL_FreeSurface(artImage);
	}
}
