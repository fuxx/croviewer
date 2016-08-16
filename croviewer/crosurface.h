#ifndef __CROSURFACE__
#define __CROSURFACE__

//#include "Globals.h"
#include <string.h>
#include "SDL.h"

#include "croartistregions.h"
#include "crofile.h"
#include "croglobal.h"

#include "cropositionprocessor.h"
#include "crostring.h"
#include "croviewer.h"

class CroSurface
{
private:

	int artistVectorSize;
	int foundFilesForArtist;
	int currentSection;
	int currentLevel;
	int lastSection;
	int lastState_x;
	int lastState_y;
	int scroll;  
	int scrolled_x, scrolled_y, max_scrollable_x, max_scrollable_y, start_x, start_y;
	
	SDL_Event ereignis;
	SDL_Surface *image;
	SDL_Surface *art;
	SDL_Surface *back;
	
	
	std::string currentArtist;
	std::string currentArtistIdentifier;
	std::string oldArtistIdentifier;
	
	void saveState(int x, int y);
	void setMaxScrollableX(int pixel) { max_scrollable_x = pixel; };
	void setMaxScrollableY(int pixel) { max_scrollable_y = pixel; };
	void setScrolledX(int pixel) { scrolled_x = pixel; };
	void setScrolledY(int pixel) { scrolled_y = pixel; };
	
public:
	int startx,starty;

	
	
	CroSurface(SDL_Surface *screen);
	
	bool checkInput(int x, int y);
	bool checkTopLevelMenuAndPaint(int x = -1, int y = -1, bool scrolling = false, int scrollDirection = 0, bool externalCall = false);
	bool checkArtistAndPaint(int x = -1, int y = -1, bool scrolling = false, int scrollDirection = 0, bool externalCall = false);
	bool checkScrollingListAndDraw(int x, int y, int scrollDirection = 0);
	
	int getCurrentSection() { return currentSection; };
	int getCurrentLevel() { return currentLevel; };
	int getLastStateX() { return lastState_x; };
	int getLastStateY() { return lastState_y; };
	
	bool redraw(bool external = false);
	
	void DrawIMG(SDL_Surface *img, CroViewer *viewer, int x, int y);
	void DrawIMG(SDL_Surface *img, CroViewer *viewer, int x, int y, int w, int h, int x2, int y2);
	bool DrawIMGWithSize(SDL_Surface *img, CroViewer *viewer, int x_cor, int y_cor, Uint16 width, Uint16 height);
	
	void SetSection(int setSection) { currentSection = setSection; };
	void SetLevel(int setLevel) { currentLevel = setLevel; };
	
	std::string getCurrentArtist() { return currentArtist; };
	
};

#endif