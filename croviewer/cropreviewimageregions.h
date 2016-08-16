//
//  cropreviewimageregions.h
//  croviewer
//
//  Created by fuxx on 19.10.10.
//  Copyright (c) 2010 chemical-reaction.org. All rights reserved.
//

#ifndef __CROPREVIEWIMAGEREGIONS__
#define __CROPREVIEWIMAGEREGIONS__

#include "croregions.h"
#include <string>
#include <vector>

class CroPreviewImageRegions : public CroRegions {
public:
	CroPreviewImageRegions(int identifier, int x_min, int x_max, int y_min, int y_max) : CroRegions(identifier, x_min, x_max, y_min, y_max) {};
	virtual ~CroPreviewImageRegions() {}
	int coordinate_in(int x, int y);
	int getMinCoordinateX() { return x_min; }
	int getMinCoordinateY() { return y_min; }
	int getMaxCoordinateX() { return x_max; }
};

#endif