#include <vector>

#include "croinit.h"
#include "croevents.h"
#include "croglobal.h"

#ifdef WIN32
#include <Windows.h>
#include "resource.h"
#endif // WIN32





int main( int argc, char* argv[] )
{
	//CroViewer* viewer; // viewer interface
	// Initialisierung von SDL
	SDL_Event ereignis;

	bool fullscreen = true;
#ifdef WIN32
	int runFullscreen = MessageBox(
		NULL,
		(LPCWSTR)L"Run in fullscreen?\n",
		(LPCWSTR)L"Answer me!",
		MB_ICONQUESTION | MB_YESNOCANCEL | MB_DEFBUTTON1
		);
	
	switch (runFullscreen)
	{
	case IDCANCEL:
		exit(0);
		break;
	case IDNO:
		fullscreen = false;
		break;
	}
#elif __APPLE__
	for (int i = 0; i <= argc; i++) 
		if (0 == strcmp(argv[i], "w")) 
			fullscreen = false; 
#endif // WIN32

	/** FIX ME **/
	/* We need system based error messages! */
	if(!CroInit::getInstance().initGraphicInterface(fullscreen))
	{
		printf("exited video\n");
		exit(0);
	}
		
	if(!CroInit::getInstance().initAudioInterface())
	{
		printf("exited audio\n");
		exit(0);
	}
	// File system init
	if (!CroInit::getInstance().initCroFilesystem())
	{
		printf("exited filesystem\n");
		exit(0);
	}
	CroInit::getInstance().getMusicSystem()->playRandomSound();
	CroInit::getInstance().initArtPreview();
	
	/** FIX ME **/
	CroInit::getInstance().getSurfaceInterface()->checkTopLevelMenuAndPaint(576+1, 162+1);
	
	// everything fine? we add key repeat here =)
	SDL_EnableKeyRepeat(125, 15);
	
	while(true) {
		/*if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1))
		{
			printf("Mouse Button 1(left) is pressed.\n");
		}*/
		SDL_WaitEvent(&ereignis);
		CroEvents::getInstance().processEvent(ereignis);		
	}
	return 0;
}


