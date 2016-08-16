/*
 *  croartistregions.h
 *  croviewer
 *
 *  Created by fuxx on 11.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */
#ifndef __CROARTISTREGIONS__
#define __CROARTISTREGIONS__

#include "croregions.h"
#include <string>
#include <vector>

class CroArtistRegions : public CroRegions {
public:
	CroArtistRegions(int identifier, int x_min, int x_max, int y_min, int y_max) : CroRegions(identifier, x_min, x_max, y_min, y_max) {};
	CroArtistRegions(int identifier, int x_min, int x_max, int y_min, int y_max, std::string str_identifier) 
		: CroRegions(identifier, x_min, x_max, y_min, y_max) { string_identifier = str_identifier; };
	
	std::string coordinateIn(int x, int y);
	std::string getIdentifier() { return string_identifier; };
private:
	std::string string_identifier;
};

#endif