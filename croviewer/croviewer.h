#ifndef __CROVIEWER__
#define __CROVIEWER__

#include <stdlib.h>
#include <sstream>
#include <iostream>                     
#include "SDL.h"
#include "SDL_Bitmap_Font.h"
#include "SDL_image.h"


using namespace std;

class CroViewer
{
  public:
    CroViewer();
    ~CroViewer();
	
	bool m_fullscreen;

	void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
	bool InitCro(int width, int height, int bit, bool fullscreen = true);
    bool SetCursor(bool set);
    void SetIcon(char* resname);
	
	SDL_Surface* GetSurface();  
	SDL_Surface* GetScreenSurface() { return screen; }
	SDL_Surface* GetBackgroundImage() { return background_image; }
	
	SDL_Bitmap_Font GetMainFont() { return main_bitmap_font; }
	SDL_Bitmap_Font GetMusicFont() { return music_bitmap_font; }
    
  private:
    SDL_Surface *screen, *icon, *background_image, *background_temp;
	SDL_Bitmap_Font main_bitmap_font, music_bitmap_font;
	
};
#endif