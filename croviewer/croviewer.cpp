#include "croinit.h"
#include "crofile.h"
#include "croglobal.h"
#include "croviewer.h"
#include "SDL_rotozoom.h"

// WIN 32 HACK
/*******************************/
#ifdef WIN32
#include <Windows.h>
#include "SDL_syswm.h"

WNDPROC oldProc;
HICON icon;
HICON iconSm;
HWND hwnd;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_SETCURSOR)
	{
		if (LOWORD(lParam) == HTCLIENT)
		{
			::SetCursor(::LoadCursor(NULL, IDC_ARROW));
			return TRUE;
		}
	}

	return ::CallWindowProc(oldProc, hwnd, msg, wParam, lParam);
}

void init_win32()
{
	HINSTANCE handle = ::GetModuleHandle(NULL);
	icon = ::LoadIcon(handle, L"icon-logo");
	iconSm  = (HICON)::LoadImage(GetModuleHandle(NULL), L"icon-logo", IMAGE_ICON, 16, 16, 0);

	SDL_SysWMinfo wminfo;
	SDL_VERSION(&wminfo.version)
		if (SDL_GetWMInfo(&wminfo) != 1)
		{
			// error: wrong SDL version
		}

		hwnd = wminfo.window;

		::SetClassLong(hwnd, GCL_HICON, (LONG) icon);
		if(iconSm)
			::SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)iconSm);

		oldProc = (WNDPROC) ::SetWindowLong(hwnd, GWL_WNDPROC, (LONG) WndProc);
}
#endif // WIN32
/*******************************/
// END WIN 32 HACK

CroViewer::CroViewer() {
	screen = NULL;
}

bool CroViewer::InitCro(int width, int height, int bit, bool fullscreen) 
{
	
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "SDL konnte nicht initialisiert werden: %s\n", SDL_GetError());
		return false;
	}
#ifdef WIN32
	init_win32();
#endif // WIN32

	Uint32 startOptions = SDL_FULLSCREEN;
	if (!fullscreen)
		startOptions = SDL_SWSURFACE;

	// @todo check for aviblity of fullscreen mode
	screen = SDL_SetVideoMode(width, height, bit, startOptions); //	|SDL_NOFRAME
	if (screen == NULL ) {
		return false;
	}
	
	// Titel ;o
	SDL_WM_SetCaption ("cRo discmag", NULL);
	
	// Image in das Surface übergeben
#ifdef WIN32
	background_temp = IMG_Load(CroFile::buildPath("MAG\\croResources\\Images\\cro.jpg"));
#elif LINUX
	background_temp = IMG_Load(CroFile::buildPath("/MAG/croResources/Images/cro.jpg"));
#else
	background_temp = IMG_Load(CroFile::buildPath("/Contents/Resources/croResources/Images/cro.jpg"));
#endif
	if (NULL == background_temp)
	{
		printf(IMG_GetError());
		printf("Failed on loading background image\n");
		exit(1);
	}
	
	background_image = SDL_DisplayFormat(background_temp);
	SDL_FreeSurface(background_temp);
	
	// load bitmap font
#ifdef WIN32
	main_bitmap_font.Initialize(CroFile::buildPath("MAG\\croResources\\Fonts\\275.bmp"), BITMAPFONT_W, BITMAPFONT_H,' ',' ',6,10);
	main_bitmap_font.SetTransparentColor(0,0,0);
	music_bitmap_font.Initialize(CroFile::buildPath("MAG\\croResources\\Fonts\\164.bmp"), 16, 10,' ',' ',4,20);
	music_bitmap_font.SetTransparentColor(0,0,0);
#elif LINUX
	main_bitmap_font.Initialize(CroFile::buildPath("/MAG/croResources/Fonts/275.bmp"), BITMAPFONT_W, BITMAPFONT_H,' ',' ',6,10);
	main_bitmap_font.SetTransparentColor(0,0,0);
	music_bitmap_font.Initialize(CroFile::buildPath("/MAG/croResources/Fonts/164.bmp"), 16, 10,' ',' ',4,20);
	music_bitmap_font.SetTransparentColor(0,0,0);
#else
	main_bitmap_font.Initialize(CroFile::buildPath("/Contents/Resources/croResources/Fonts/275.bmp"), BITMAPFONT_W, BITMAPFONT_H,' ',' ',6,10);
	main_bitmap_font.SetTransparentColor(0,0,0);
	music_bitmap_font.Initialize(CroFile::buildPath("/Contents/Resources/croResources/Fonts/164.bmp"), 16, 10,' ',' ',4,20);
	music_bitmap_font.SetTransparentColor(0,0,0);
#endif 
	return true;
}

SDL_Surface* CroViewer::GetSurface() 
{
	return screen;
}

void CroViewer::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
	//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;
	
	//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
	
	//Blit the surface
	SDL_BlitSurface( source, NULL, destination, &offset );
}


bool CroViewer::SetCursor(bool set) {
	if(SDL_ShowCursor(set))
		return true;
	else
		return false;
}

void CroViewer::SetIcon(char* resname) 
{
	
}

CroViewer::~CroViewer() 
{ }


