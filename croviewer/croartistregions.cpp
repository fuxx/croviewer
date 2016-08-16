/*
 *  croartistregions.cpp
 *  croviewer
 *
 *  Created by fuxx on 11.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#include "croartistregions.h"

std::string CroArtistRegions::coordinateIn(int x, int y)
{
	if(x > x_min && y > y_min
	   && x < x_max && y < y_max)
	{
		return string_identifier;
	}
	return std::string("");
}