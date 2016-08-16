//
//  cropreviewimageregions.cp
//  croviewer
//
//  Created by fuxx on 19.10.10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "cropreviewimageregions.h"
int CroPreviewImageRegions::coordinate_in(int x, int y)
{
	if(x >= x_min && y >= y_min && x <= x_max && y <= y_max)
	{
		return int_identifier;
	}
	else 
	{
		return -1;
	}
}