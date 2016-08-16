/*    SDL_Bitmap_Font Library v0.01
 *    
 *    SDL_Bitmap_Font library is a library for SDL
 *  that makes loading and displaying Bitmap 
 *  Fonts very easy.
 *  Copyright (C) 2005 Brandon Fogerty
 *  
 *  Written By: Brandon Fogerty
 *  http://www.brandonfogerty.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  The Author simply requests
 * that a demo of the finished product
 * be sent to him.
 *
 *  The Author's email address is 
 *
 *	  bfogerty@gmail.com
 *
 *          Thank you!
 *
 *     GOD Bless you Always!!!
 */

#ifndef __FONT__
#define __FONT__

//#include "Globals.h"
#include <SDL.h>
#include <string.h>

class SDL_Bitmap_Font
{
private:
	
	SDL_Surface *surf_Font;
	SDL_Surface *surf_Temp;
	int iWidth;
	int iHeight;
	char cFirstCharacter;
	char cLastCharacter;
	
	int iNumOfRows;
	int iColumnLength;
	
	SDL_Rect rect_WHUV;
	SDL_Rect rect_Position;
	
public:
	int iX;
	int iY;
	
	void Initialize(char *filename, int width, int height, char FirstCharacter, char LastCharacter, int NumOfRows, int ColumnLength);
	
	void DrawChar(char character, SDL_Surface *screen);
	void DrawChar(char character, int iX, int iY, SDL_Surface *screen);
	void DrawString(const char *string, SDL_Surface *screen);
	void DrawString(const char *string, int iX, int iY, SDL_Surface *screen);
	
	void SetTransparentColor(Uint8 r, Uint8 g, Uint8 b);
	
};

#endif