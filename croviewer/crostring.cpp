/*
 *  crostring.cpp
 *  croviewer
 *
 *  Created by fuxx on 11.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */

#include "crostring.h"

std::string CroString::stripExtension(const std::string& fileName)
{
	const int length = fileName.length();
	for (int i=0; i!=length; ++i)
	{
		if (fileName[i]=='.') 
		{
			return fileName.substr(0,i);
		}
	}
	return fileName;
}

char* CroString::itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
		
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}