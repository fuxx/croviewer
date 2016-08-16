/*
 *  croartistartregions.h
 *  croviewer
 *
 *  Created by fuxx on 11.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */
#ifndef __CROARTISTARTREGIONS__
#define __CROARTISTARTREGIONS__

#include "croartistregions.h"
#include <string>
#include <vector>

class CroArtistArtRegions : public CroArtistRegions {
public:
	CroArtistArtRegions(int identifier, int x_min, int x_max, int y_min, int y_max, std::string str_identifier) 
		: CroArtistRegions(identifier, x_min, x_max, y_min, y_max, str_identifier) { };
};

#endif
