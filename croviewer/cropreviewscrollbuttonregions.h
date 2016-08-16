/*
 *  cropreviewscrollbuttonregions.h
 *  croviewer
 *
 *  Created by fuxx on 03.11.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROPREVIEWSCROLLBUTTONREGIONS__
#define __CROPREVIEWSCROLLBUTTONREGIONS__

#include "crobuttonregions.h"
#include <vector>

class CroPreviewScrollButtonRegions : public CroButtonRegions {
public:
	CroPreviewScrollButtonRegions(int identifier, int x_min, int x_max, int y_min, int y_max) : CroButtonRegions(identifier, x_min, x_max, y_min, y_max) {};
	virtual ~CroPreviewScrollButtonRegions() {};
	int getMinCoordinateX() { return x_min; };
	int getMinCoordinateY() { return y_min; };
	
};

#endif