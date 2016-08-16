/*
 *  cromusicbuttonregions.h
 *  croviewer
 *
 *  Created by fuxx on 05.12.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROMUSICBUTTONREGIONS__
#define __CROMUSICBUTTONREGIONS__

#include "croregions.h"
#include <vector>

class CroMusicButtonRegions : public CroRegions {
public:
	CroMusicButtonRegions(int identifier, int x_min, int x_max, int y_min, int y_max) : CroRegions(identifier, x_min, x_max, y_min, y_max) {};
	virtual ~CroMusicButtonRegions() {}
};

#endif
