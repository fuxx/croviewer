/*
 *  croregions.cpp
 *  croviewer
 *
 *  Created by fuxx on 07.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#include "croregions.h"

int CroRegions::coordinate_in(int x, int y)
{
	if(x > x_min && y > y_min
	   && x < x_max && y < y_max)
	{
		return int_identifier;
	}
	else 
	{
		return -1;
	}
}

void CroRegions::printCoordinates()
{
	//printf("x_min: %d x_max: %d y_min: %d y_max: %d\n", x_min, x_max, y_min, y_max);
}