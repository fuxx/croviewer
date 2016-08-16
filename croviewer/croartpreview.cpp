//
//  croartpreview.cp
//  croviewer
//
//  Created by fuxx on 18.10.10.
//  Copyright (c) 2010 chemcal-reaction.org. All rights reserved.
//

#include "croartpreview.h"
#include "croinit.h"
#include "croglobal.h"
#include "crostring.h"
#include "cropreviewimageregions.h"

#include "SDL_rotozoom.h"


CroArtPreview::CroArtPreview()
{
	// get necessary instances 
	g_viewer = CroInit::getInstance().getViewerInterface();
	g_loader = CroInit::getInstance().getLoader();
	g_surface = CroInit::getInstance().getSurfaceInterface();
	g_artViewer = CroInit::getInstance().getArtViewer();
	m_ArtVector = CroInit::getInstance().getFileSystem()->getArtVector();
	
	drawed = false;
	
	// if art vector is empty, we have to process new medias
	// mostly common on startup of the viewer
	if(0 != m_ArtVector.size())
		imagesProcessed = preProcessImages();
	else
		imagesProcessed = false;
	
	// if the images are succesfully processed, we show them
	if(imagesProcessed)
	{
		scroll_x = 0;
		start_x = 0;
		drawImages();
	}
	lastIdentifier = -1;
	
}

/**
 *
 *	preProcessImages()
 *	
 *	Method which runs on startup
 *	It shows a loading bar and iterates over
 *	every element.
 */
bool CroArtPreview::preProcessImages()
{
	g_loader->reset();
	g_loader->setVectorSize(m_ArtVector.size());
	
	// loop over every element in art vector
	for(unsigned int i=0; i < m_ArtVector.size(); ++i) 
	{
		g_loader->updateSatus(i);
		if(strcmp(m_ArtVector.at(i).sectionName.c_str(),section_char[ASCII]) == 0) 
		{
			std::string toUpperName = m_ArtVector.at(i).artistArt;
			std::transform(toUpperName.begin(), toUpperName.end(),toUpperName.begin(),(int (*)(int))toupper);
			std::string copyOfName = m_ArtVector.at(i).artPath;
			std::string artName = CroString::stripExtension(toUpperName);
			this->addImage(ASCII, copyOfName, artName);
			
		} // if
		if(strcmp(m_ArtVector.at(i).sectionName.c_str(),section_char[HIRES]) == 0) 
		{
			std::string toUpperName = m_ArtVector.at(i).artistArt;
			std::transform(toUpperName.begin(), toUpperName.end(),toUpperName.begin(),(int (*)(int))toupper);
			std::string copyOfName = m_ArtVector.at(i).artPath;
			std::string artName = CroString::stripExtension(toUpperName);
			this->addImage(HIRES, copyOfName, artName);
			
		}
	} // for
	g_loader->fadeOut();
	return true;
}

/**
 *
 *	addImage(int section, std::string copyOfName,std::string artName)
 *
 *	Adds new preview images into the preview image container.
 *	It makes realtime resizing of a given element.
 *
 */
bool CroArtPreview::addImage(int section, std::string copyOfName,std::string artName)
{
	// load image into temp surface
	SDL_Surface *image_tmp = IMG_Load(copyOfName.c_str());
	if (NULL == image_tmp)
	{
		//printf("Failed on loading preview: %s\n", copyOfName.c_str());
		return false;
	}
	// optimize image for display format
	SDL_Surface *image = SDL_DisplayFormat(image_tmp);
	// free temp surface
	SDL_FreeSurface(image_tmp);	
	
	// calculate ratio and factor for small pic
	double ratio = (image->w > image->h) ? (VIEW_PREVIEW_MAX_WIDTH/(double)image->w) : (VIEW_PREVIEW_MAX_HEIGHT/(double)image->h);
	// calculate ratio and factor for hover pic
	double ratio_bigger = (image->w > image->h) ? (VIEW_PREVIEW_BIGGER_MAX_WIDTH/(double)image->w) : (VIEW_PREVIEW_BIGGER_MAX_HEIGHT/(double)image->h);
	
	
	// zoom surface wit new calculate ratios
	SDL_Surface *shrinkedImage = zoomSurface(image, ratio, ratio, 1);
	SDL_Surface *shrinkedImageBigger = zoomSurface(image, ratio_bigger, ratio_bigger, 1);
	SDL_FreeSurface(image);
	
	// push new images into preview container
	m_previewContainerVec.push_back(new CroPreviewContainer(section, shrinkedImage, shrinkedImageBigger, copyOfName));
	return true;
}

/**
 *
 *	drawImages(bool internalCall)
 *
 *	If a scroll event cames or it needs simply redrawed
 *	due interaction on the GUI it redraws the bottom
 *	preview bar.
 *
 *	If internalCall is given, the surface wont be flipped.
 *
 */
bool CroArtPreview::drawImages(bool internalCall)
{
	// if images not processed return false
	if (imagesProcessed == false)
		return false;
	// we need to check if the bar is already moved due scrolling
	// if we didnt, the calculation is being in chaos and shit is drawn
	if (0 == scroll_x)
		start_x = 0 + VIEW_PREVIEW_START_X;
	else 
		start_x = VIEW_PREVIEW_START_X + scroll_x;

	/** FIX ME **/
	//g_viewer->apply_surface(0, 0, g_viewer->GetBackgroundImage(), g_viewer->GetSurface());
	// redraw music
	CroInit::getInstance().getMusicSystem()->redrawCurrentPlaying(true);
	// we need to iterate over every element
	int l_iIt = 0;
	for (std::vector<CroPreviewContainer*>::iterator it = m_previewContainerVec.begin(); it!=m_previewContainerVec.end(); ++it) 
	{
		// is the current image+spacing within the visible area of X?
		// this prevents drawing out of the viewport
		if ((start_x + ((*it)->getImage()->w + VIEW_PREVIEW_SPACING))  <= VIEW_PREVIEW_END_X
			&& start_x >= VIEW_PREVIEW_START_X)
		{
			// draw image mini preview to bar on given coordinate
			CroInit::getInstance().getSurfaceInterface()
			->DrawIMG((*it)->getImage(), g_viewer, start_x, VIEW_PREVIEW_START_Y);
			
			// tell the container that the image is visible
			// this prevents of showing images that arent in scope, but on coordinates between a image
			(*it)->setVisible(true);
		} else {
			(*it)->setVisible(false);
		}
		// change the coordinates of every element based on start_x and its own width 
		CroPositionProcessor::getInstance().setNewPreviewImage(l_iIt, start_x, ((*it)->getImage()->w + VIEW_PREVIEW_SPACING + start_x), VIEW_PREVIEW_START_Y, /*((*it)->getImage()->h +*/ VIEW_PREVIEW_START_Y+VIEW_PREVIEW_MAX_HEIGHT);
		start_x += ((*it)->getImage()->w + VIEW_PREVIEW_SPACING);
		// select next element
		l_iIt++;
	}
	
	// if its not a internal call, we need to flip the surface
	// this happens mostly due a call on a section banner or 
	// a actual open image in fullscreen
	if (!internalCall)
	{
		CroInit::getInstance().flipScreen();
	}
	
	return true;
}

/**
 *
 *	checkScrollAndDraw(float x, float y, int click = 0)
 *
 *	If a scroll event is called, the bar will recalculate the positions of 
 *	every element in the vector and redraw the bar.
 *
 */
bool CroArtPreview::checkScrollAndDraw( int x, int y, int click )
{
	// if image is not clicked return false;
	if (0 == click)
		return false;

	if (-1 == x && -1 == y)
	{
		y = VIEW_WINDOW_END_Y+1;
	}
		
	// if the y coordinate is in the outer area of the box we return false;
	if (y < VIEW_WINDOW_END_Y)
		return false;
	
	// is CroArtViewer in fullscreen?
	if(CroInit::getInstance().getArtViewer()->inFullscreen())
		return false;
	// get image identifier by a given coordinate
	int scroll_identifier = CroPositionProcessor::getInstance().getPreviewScrollIdentifierForCoordinate(x,y);
	
	// if we didnt find a image, return false
	if (click == SDL_BUTTON_WHEELUP || click == SDL_BUTTON_WHEELDOWN)
	{
		if (scroll_identifier != 1)
			scroll_identifier = click;
	} else {
		if (-1 == scroll_identifier)
			return false;
	}
	
	
	// if we got a direction up or down, we set new position for drawing
	// based on wheel up or down
	if (1 == scroll_identifier) 
	{ 
		//printf("1. current start_x: %d\n",scroll_x);
		if (start_x != 0 && (click == SDL_BUTTON_WHEELDOWN || click > 0)) 
		{
			if ((scroll_x + 5) > 0)
				return false;
			scroll_x += 20;
			start_x = VIEW_PREVIEW_START_X + scroll_x;
		}
	}
	else 
	{
		/*printf("2. current start_x: %d\n",scroll_x);
		printf("x_max: %d\n",CroPositionProcessor::getInstance().previewimage_regions.back()->getMaxCoordinateX());
		printf("VPS %d VPE %d SPACE %d\n", VIEW_PREVIEW_START_X, VIEW_PREVIEW_END_X, VIEW_PREVIEW_SPACING);*/
		if (start_x != 0 && (click == SDL_BUTTON_WHEELDOWN) || (click == 1 && scroll_identifier == 2))
		{
			int lastMaxX = CroPositionProcessor::getInstance().previewimage_regions.back()->getMaxCoordinateX();
			if ((lastMaxX + 5) < VIEW_PREVIEW_END_X)
				return false;
			scroll_x -= 20;
			start_x = VIEW_PREVIEW_START_X + scroll_x;
		} else if (start_x != 0 && (click == SDL_BUTTON_WHEELUP))
		{
			if ((scroll_x + 5) > 0)
				return false;
			scroll_x += 20;
			start_x = VIEW_PREVIEW_START_X + scroll_x;			
		}
	}

	// if images process (they need to be ;) we redraw the images bar with/without new coordinates)
	if(imagesProcessed)
	{
		this->redrawSurfaceWithTop();
		this->drawImages();
	}
	return true;
}

/**
 *
 *	drawImageWithIdentifier(int identifier, int current_x, int current_y)
 *
 *	Trys to render a bigger preview image on a given identifier and coordinates.
 */
bool CroArtPreview::drawImageWithIdentifier(int identifier, int current_x, int current_y)
{
	//printf("identifier %d\n");
	if (imagesProcessed == false)
		return false;
	
	SDL_Surface* previewImage = m_previewContainerVec.at(identifier)->getImageBigger();
	start_x = VIEW_PREVIEW_START_X;
	if(!this->drawImages(true))
		return false;
	
	this->drawImg(previewImage, (current_x), (current_y - previewImage->h));
	return true;
}

/**
 *
 *	drawImg(SDL_Surface* img, int x, int y)
 *
 *	Draws a given image on given coordinates.
 *	It redraws sections menus or anything else,
 *	if other elements are present.
 */
void CroArtPreview::drawImg(SDL_Surface* img, int x, int y)
{
	// image offset
	SDL_Rect offset;
	//Give the offsets to the rectangle
	if ( (x+img->w) > WINDOW_X)
		offset.x = (WINDOW_X - img->w);
	else
		offset.x = x;
	
	offset.y = y;
	this->redrawSurfaceWithTop();
	this->drawImages(true);
	SDL_BlitSurface(img, NULL, g_viewer->GetSurface(), &offset);
	CroInit::getInstance().flipScreen();
}

/**
 *
 *	checkMouseOverAndDraw(float x, float y, int click = 0)
 *
 *	Checks the preview image bar for a mouse over.
 *	If a picture is found for the given coordinate,
 *	a bigger preview image will be drawn on a overlay.
 */
bool CroArtPreview::checkMouseOverAndDraw( int x, int y, int click )
{
	
	if (imagesProcessed == false)
		return false;
	
	if (g_surface->getCurrentLevel() > ARTVIEW && click == 0)
		return false;
	
	if ((g_artViewer->inFullscreen() && g_artViewer->isDrawed))
		return false;
	
	if ((y > VIEW_PREVIEW_START_Y) && (y < (VIEW_PREVIEW_START_Y + VIEW_PREVIEW_BIGGER_MAX_HEIGHT))
		&& (x > VIEW_PREVIEW_START_X) && (x < (VIEW_PREVIEW_END_X - VIEW_PREVIEW_SPACING)))
	{
		
		int image_identifier = CroPositionProcessor::getInstance().getImageIdentifierForPreviewCoordinate((int)(x-scroll_x), y);
		if (previewClicked && image_identifier == lastIdentifier)
		{
			return false;
		} 
		
		if (-1 != image_identifier)
		{
			if (0 == click) 
			{
				if (!m_previewContainerVec.at(image_identifier)->isVisible())
					return false;
				
				/* FIX */
				if(this->drawImageWithIdentifier(image_identifier, x, y)) 
				{
					drawed = true;
					previewClicked = false;
				} 
				return drawed;
			} 
			else
			{
				g_surface->SetSection(ASCII);
				g_artViewer->showArt(m_previewContainerVec.at(image_identifier)->getPathString());
				previewClicked = true;
				lastIdentifier = image_identifier;
				return true;
			}
		}
		return false;
	} 
	else 
	{
		// reset after leaving Y are
		if (drawed && !previewClicked)
		{
			this->redrawSurfaceWithTop();
			start_x = VIEW_PREVIEW_START_X + scroll_x;
			this->drawImages(true);
			CroInit::getInstance().flipScreen();
			drawed = false;
		}
		return false;
	}
	return true;
}

void CroArtPreview::redrawSurfaceWithTop()
{
	
	// redraw background and show picture
	g_viewer->apply_surface(0, 0, g_viewer->GetBackgroundImage(), g_viewer->GetSurface());
	
	// is something else to draw?
	if(lastIdentifier == -1 || lastIdentifier >= 0)
	{
		if (g_surface->getCurrentLevel() == ARTISTS) 
		{
			g_surface->checkTopLevelMenuAndPaint(g_surface->getLastStateX(), g_surface->getLastStateY(), false, 0, true);
		}
		else if (g_surface->getCurrentLevel() == FILEVIEW) 
		{
			g_surface->checkArtistAndPaint(-1, -1, false, 0, true);
		} 
		else if (g_surface->getCurrentLevel() > FILEVIEW)
		{
			g_artViewer->scrollArt(0, false, 0, 0, true);
		}
		lastIdentifier = -1;
	} 
	else 
	{
		
	}	
}
