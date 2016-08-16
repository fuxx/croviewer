//
//  cropreviewcontainer.h
//  croviewer
//
//  Created by fuxx on 18.10.10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef __CROPREVIEWCONTAINER__
#define __CROPREVIEWCONTAINER__

#include <string>
#include <vector>
#include "SDL.h"

class CroPreviewContainer 
{
public:
	CroPreviewContainer(int identifier, SDL_Surface* image, SDL_Surface* image_bigger, std::string str_identifier) 
	:  m_identifier (identifier), m_image(image), m_imageBigger(image_bigger), m_str_identifier(str_identifier) {};
	virtual ~CroPreviewContainer() {}

	bool isVisible() { return m_visible; }
	int getIdentifier() { return m_identifier; };
	void setVisible(bool setVisibility) { m_visible = setVisibility; }
	
	std::string getPathString() { return m_str_identifier; };
	
	SDL_Surface* getImage() { return m_image; };
	SDL_Surface* getImageBigger() { return m_imageBigger; };
protected:
	
	
	bool m_visible;
	int m_identifier;
	
	SDL_Surface* m_image;
	SDL_Surface* m_imageBigger;
	
	std::string m_str_identifier;
	
};

#endif