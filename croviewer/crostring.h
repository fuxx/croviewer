/*
 *  crostring.h
 *  croviewer
 *
 *  Created by fuxx on 11.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#ifndef __CROSTRING__
#define __CROSTRING__
#include <string>

class CroString
{
public:
	static std::string stripExtension(const std::string& fileName);
	static char* itoa(int val, int base);
	
};
#endif
