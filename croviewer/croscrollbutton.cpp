/*
 *  croscrollbutton.cpp
 *  croviewer
 *
 *  Created by fuxx on 17.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#include "croscrollbutton.h"
#include "croinit.h"

CroScrollButton::CroScrollButton()
{
	m_surface = CroInit::getInstance().getSurfaceInterface();
	m_viewer = CroInit::getInstance().getViewerInterface();
	button_up = NULL;
	button_down = NULL;
	button_left = NULL;
	button_right = NULL;
	this->initButtonUp();
	this->initButtonDown();
	
	/** FIX ME **/
	/* needs to be loaded a better way */ 
	CroPositionProcessor::getInstance().
	setNewPreviewScrollButton(
							  1, 
							  VIEW_PREVIEW_SCROLL_BUTTON_LEFT_START_X, 
							  VIEW_PREVIEW_SCROLL_BUTTON_LEFT_START_X+button_up->h, 
							  VIEW_PREVIEW_SCROLL_BUTTON_LEFT_START_Y, 
							  VIEW_PREVIEW_SCROLL_BUTTON_LEFT_START_Y+button_up->w);
	CroPositionProcessor::getInstance().
	setNewPreviewScrollButton(
							  2, 
							  VIEW_PREVIEW_SCROLL_BUTTON_RIGHT_START_X, 
							  VIEW_PREVIEW_SCROLL_BUTTON_RIGHT_START_X+button_up->h, 
							  VIEW_PREVIEW_SCROLL_BUTTON_RIGHT_START_Y, 
							  VIEW_PREVIEW_SCROLL_BUTTON_RIGHT_START_Y+button_up->w);
	/** FIXME **/
	
}

CroScrollButton::~CroScrollButton()
{
	SDL_FreeSurface(button_up);
	SDL_FreeSurface(button_down);
	SDL_FreeSurface(button_left);
	SDL_FreeSurface(button_right);
}

bool CroScrollButton::drawButtonUp() 
{
	if (!this->initButtonUp())
		return false;
	m_surface->DrawIMG(button_up, m_viewer, SCROLL_BUTTON_UP_START_X, SCROLL_BUTTON_UP_START_Y);
	this->addEvents();
	return true;
}

bool CroScrollButton::drawButtonDown() 
{
	if (!this->initButtonDown())
		return false;
	m_surface->DrawIMG(button_down, m_viewer, SCROLL_BUTTON_DOWN_START_X, SCROLL_BUTTON_DOWN_START_Y);
	this->addEvents();
	return true;
}

bool CroScrollButton::drawButtonLeft(bool fullscreen) 
{
	if (!this->initButtonLeft())
		return false;
	if (!fullscreen) 
	{
		this->drawButtonHighlight(fullscreen, 0, VIEW_WINDOW_START_X, (SCROLL_BUTTON_LEFT_START_Y-(button_left->h*2)), (SCROLL_BUTTON_LEFT_START_Y+(button_left->h*2)+button_left->h));
		m_surface->DrawIMG(button_left, m_viewer, SCROLL_BUTTON_LEFT_START_X, SCROLL_BUTTON_LEFT_START_Y);
	}
	else 
	{
		m_surface->DrawIMG(button_left, m_viewer, 0, SCROLL_BUTTON_LEFT_START_Y);
	}
	this->addEvents();
	return true;
}

bool CroScrollButton::drawButtonRight(bool fullscreen) 
{
	if (!this->initButtonRight())
		return false;
	
	if (!fullscreen) 
	{
		//this->drawButtonHighlight(fullscreen, SCROLL_BUTTON_RIGHT_START_X-button_right->w, SCROLL_BUTTON_RIGHT_START_X, VIEW_WINDOW_START_Y+VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW, VIEW_WINDOW_END_Y);
		this->drawButtonHighlight(fullscreen, VIEW_WINDOW_END_X, WINDOW_X, (SCROLL_BUTTON_RIGHT_START_Y-(button_right->h*2)), (SCROLL_BUTTON_RIGHT_START_Y+(button_right->h*2)+button_left->h));
		m_surface->DrawIMG(button_right, m_viewer, SCROLL_BUTTON_RIGHT_START_X-button_right->w, SCROLL_BUTTON_RIGHT_START_Y);
	}
	else
	{
		m_surface->DrawIMG(button_right, m_viewer, WINDOW_X-button_right->w, SCROLL_BUTTON_RIGHT_START_Y);
	}

	this->addEvents();
	return true;
}

void CroScrollButton::addEvents()
{
	CroPositionProcessor::getInstance().setUpScrollButton();
	// scrolling up
	if (button_up != NULL)
		CroPositionProcessor::getInstance().
		setNewScrollButton(
						   SDL_BUTTON_WHEELUP, 
						   SCROLL_BUTTON_UP_START_X, 
						   SCROLL_BUTTON_UP_START_X+button_up->w, 
						   SCROLL_BUTTON_UP_START_Y, 
						   SCROLL_BUTTON_UP_START_Y+button_up->h);

	if (button_down != NULL) {
		CroPositionProcessor::getInstance().
		setNewScrollButton(SDL_BUTTON_WHEELDOWN, 
						   SCROLL_BUTTON_DOWN_START_X, 
						   SCROLL_BUTTON_DOWN_START_X+button_down->w, 
						   SCROLL_BUTTON_DOWN_START_Y, 
						   SCROLL_BUTTON_DOWN_START_Y+button_down->h);
		
	}
	
	if (button_left != NULL) {		
		// fullscreen
		CroPositionProcessor::getInstance().
		setNewScrollButton(LEFT, 
						   0, 
						   0+button_left->w+100, 
						   0, 
						   WINDOW_Y);		// normal screen
		CroPositionProcessor::getInstance().
		setNewScrollButton(LEFT, 
						   0, 
						   VIEW_WINDOW_START_X, 
						   (SCROLL_BUTTON_LEFT_START_Y-(button_left->h*2)), 
						   (SCROLL_BUTTON_LEFT_START_Y+(button_left->h*2)+button_left->h));
		
	}
	
	if (button_right != NULL) {
		// fullscreen
		CroPositionProcessor::getInstance().
		setNewScrollButton(RIGHT, 
						   WINDOW_X-button_right->w-50, 
						   WINDOW_X, 
						   0, 
						   WINDOW_Y);
		// normal screen
		CroPositionProcessor::getInstance().
		setNewScrollButton(RIGHT, 
						   VIEW_WINDOW_END_X, 
						   WINDOW_X, 
						   (SCROLL_BUTTON_RIGHT_START_Y-(button_right->h*2)), 
						   (SCROLL_BUTTON_RIGHT_START_Y+(button_right->h*2)+button_left->h));
		
	}
	
	// scrolling down
}

bool CroScrollButton::initButtonUp()
{
	if (button_up != NULL)
		return true;
	
	button_up_temp = IMG_Load(CroFile::buildPath(SCROLL_BUTTON_UP));
	if (!button_up_temp)
		return false;
	
	button_up = SDL_DisplayFormatAlpha(button_up_temp);
	SDL_FreeSurface(button_up_temp);

	if (button_up != NULL)
		return true;
	return false;
}

bool CroScrollButton::initButtonLeft()
{
	if (button_left != NULL)
		return true;
	
	button_left_temp = IMG_Load(CroFile::buildPath(SCROLL_BUTTON_LEFT));
	if (!button_left_temp)
		return false;
	
	button_left = SDL_DisplayFormatAlpha(button_left_temp);
	SDL_FreeSurface(button_left_temp);
	
	if (button_left != NULL)
		return true;
	return false;
}

bool CroScrollButton::initButtonRight()
{
	if (button_right != NULL)
		return true;
	
	button_right_temp = IMG_Load(CroFile::buildPath(SCROLL_BUTTON_RIGHT));
	if (!button_right_temp)
		return false;
	
	button_right = SDL_DisplayFormatAlpha(button_right_temp);
	SDL_FreeSurface(button_right_temp);
	
	if (button_right != NULL)
		return true;
	return false;
}

bool CroScrollButton::initButtonDown()
{
	if (button_down != NULL)
		return true;
	button_down_temp = IMG_Load(CroFile::buildPath(SCROLL_BUTTON_DOWN));
	if (!button_down_temp)
		return false;
	
	button_down = SDL_DisplayFormatAlpha(button_down_temp);
	SDL_FreeSurface(button_down_temp);
	
	if (button_down != NULL)
		return true;
	return false;
}

bool CroScrollButton::drawButtonHighlight(bool fullscreen, int x_start, int x_end, int y_start, int y_end) 
{
	SDL_Surface* temp_highlight = SDL_CreateRGBSurface (m_viewer->GetSurface()->flags|SDL_SRCALPHA, 
													 x_end-x_start, y_end-y_start, m_viewer->GetSurface()->format->BitsPerPixel, 
													 m_viewer->GetSurface()->format->Rmask, m_viewer->GetSurface()->format->Gmask, 
													 m_viewer->GetSurface()->format->Bmask, 
													 m_viewer->GetSurface()->format->Amask); 
	SDL_Surface* highlight_source = SDL_DisplayFormat(temp_highlight);
	SDL_FreeSurface(temp_highlight);
	SDL_SetAlpha (highlight_source, SDL_SRCALPHA, 150); 
	m_viewer->apply_surface(x_start, y_start, highlight_source, m_viewer->GetSurface());
	SDL_FreeSurface(highlight_source);
	return true;	
}

