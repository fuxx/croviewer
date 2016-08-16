
#ifndef __CROMUSIC__
#define __CROMUSIC__
#include <string>
#include <stdio.h>
#include "croartpreview.h"
#include "crosurface.h"
#include "croviewer.h"
#include "fmod.hpp"
#include "fmod_errors.h"
/*#ifndef WIN32
#include "wincompat.h"
#endif*/

class CroMusic {
public:
	CroMusic();
	~CroMusic();
	bool callBackSoundFinished();
	bool checkCoordinate(int x, int y);
	bool checkPlayerCoordinate(int x, int y);
	bool clearCurrentPlaying();
	bool initSoundEngine();
	bool playFile(std::string file, bool externalCall = false);
	bool playFileBackground(std::string file);
	bool playRandomSound();
	bool redrawCurrentPlaying(bool external = false);
	bool stopMusic();
	
	
	
	std::string getCurrentPlayingTitle() { return currentPlaying; };
	std::string getCurrentPlayingPath() { return currentPlayingPath; };
private:
	
	bool ERRCHECK(FMOD_RESULT result);
	bool backButton();
	bool forwardButton();
	bool pauseButton();
	bool pauseMusic();
	bool playButton();
	bool stopButton();
	
	
	bool musicPaused;
	
	CroArtPreview* g_preview;
	CroSurface* g_surface;
	CroViewer* g_viewer;
	
	FMOD::Channel *channel;	
    FMOD::Sound *sound;
	FMOD::System *system;
    FMOD_RESULT result;
    
	std::string currentArtistArtIdentifier;
	std::string currentPlaying;
	std::string currentPlayingPath;
	
	std::string getFilenameByIdentifier(std::string identifier);
	
};

#endif
