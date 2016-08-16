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

#include "SDL_Bitmap_Font.h"

void SDL_Bitmap_Font::Initialize(char *filename, int width, int height, char FirstCharacter, char LastCharacter, int NumOfRows, int ColumnLength)
{
	surf_Temp = SDL_LoadBMP(filename);
	if(NULL == surf_Temp)
	{
		printf("Error Loading Font Image!\n");
		exit(0);
	}
	surf_Font = SDL_DisplayFormat(surf_Temp);
	if(NULL == surf_Font)
	{
		printf("Error Loading Font Image!\n");
		exit(0);
	}
	
	iWidth = width;
	iHeight = height;
	cFirstCharacter = FirstCharacter;
	cLastCharacter = LastCharacter;
	iNumOfRows = NumOfRows;
	iColumnLength = ColumnLength;
	
	rect_WHUV.w = width;
	rect_WHUV.h = height;
	rect_WHUV.x = 0;
	rect_WHUV.y = 0;
}

void SDL_Bitmap_Font::DrawChar(char character, SDL_Surface *screen)
{
	int iCurrentChar = cFirstCharacter;
	rect_Position.x = iX;
	rect_Position.y = iY;
	
	rect_WHUV.y = 0;
	rect_WHUV.x = 0;
	
	for(int y = 0; y<iNumOfRows; y++)
	{
		for(int x = 0; x< iColumnLength; x++)
		{
			if(iCurrentChar==character)
			{
				goto end;
			}
			else
			{
				rect_WHUV.x += iWidth;
				iCurrentChar++;
			}
		}
		
		rect_WHUV.x = 0;
		rect_WHUV.y += rect_WHUV.h;
		
	}
	
end:
	SDL_BlitSurface(surf_Font, &rect_WHUV, screen, &rect_Position);
}

void SDL_Bitmap_Font::DrawChar(char character, int iX, int iY, SDL_Surface *screen)
{
	int iCurrentChar = cFirstCharacter;
	rect_Position.x = iX;
	rect_Position.y = iY;
	
	rect_WHUV.y = 0;
	rect_WHUV.x = 0;
	
	for(int y = 0; y<iNumOfRows; y++)
	{
		for(int x = 0; x< iColumnLength; x++)
		{
			if(iCurrentChar==character)
			{
				goto end;
			}
			else
			{
				rect_WHUV.x += iWidth;
				iCurrentChar++;
			}
		}
		
		rect_WHUV.x = 0;
		rect_WHUV.y += rect_WHUV.h;
		
	}
	
end:
	SDL_BlitSurface(surf_Font, &rect_WHUV, screen, &rect_Position);
}

void SDL_Bitmap_Font::DrawString(const char *string, SDL_Surface *screen)
{
	int x = iX;
	
	for(unsigned int i=0; i<strlen(string); i++)
	{
		this->DrawChar(string[i], x, iY, screen);
		x += iWidth;
	}
}

void SDL_Bitmap_Font::DrawString(const char *string, int iX, int iY, SDL_Surface *screen)
{
	int x = iX;
	
	for(unsigned int i=0; i<strlen(string); i++)
	{
		this->DrawChar(string[i], x, iY, screen);
		x += iWidth;
	}
}


void SDL_Bitmap_Font::SetTransparentColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetColorKey(surf_Font, SDL_SRCCOLORKEY, SDL_MapRGB(surf_Font->format,r,g,b));
}