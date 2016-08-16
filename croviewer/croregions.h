/*
 *  croregions.h
 *  croviewer
 *
 *  Created by fuxx on 07.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROREGIONS__
#define __CROREGIONS__

#include <string>
#include <vector>

class CroRegions {
public:
	CroRegions(int identifier, int x_min, int x_max, int y_min, int y_max) 
		: int_identifier(identifier), x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max) {};
	virtual ~CroRegions() {}
	
	int coordinate_in(int x, int y);
	void printCoordinates();
protected:
	int int_identifier;
	int x_min, x_max, y_min, y_max;
	
};

#endif