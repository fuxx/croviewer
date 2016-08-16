/*
 *  crobuttonregions.h
 *  croviewer
 *
 *	This class just 
 *
 *  Created by fuxx on 08.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROBUTTONREGIONS__
#define __CROBUTTONREGIONS__

#include "croregions.h"
#include <vector>

class CroButtonRegions : public CroRegions {
public:
	CroButtonRegions(int identifier, int x_min, int x_max, int y_min, int y_max) : CroRegions(identifier, x_min, x_max, y_min, y_max) {};
	virtual ~CroButtonRegions() {}
	int getMinCoordinateX() { return x_min; }
	int getMinCoordinateY() { return y_min; }
	
};

#endif