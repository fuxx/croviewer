#include "cromusic.h"
#include "croinit.h"
#include "time.h"

CroMusic::CroMusic()
{
	musicPaused = false;
}

bool CroMusic::initSoundEngine() 
{
    result = FMOD::System_Create(&system);
    if (ERRCHECK(result)) 
		return false;
	
    result = system->init(64, FMOD_INIT_NORMAL, NULL);
    if (ERRCHECK(result)) 
		return false;
	
	g_surface = CroInit::getInstance().getSurfaceInterface();
	g_viewer = CroInit::getInstance().getViewerInterface();
	g_preview = CroInit::getInstance().getArtPreview();
	return true;
}

bool CroMusic::checkCoordinate( int x, int y )
{
	if ((x > VIEW_WINDOW_START_X && x < VIEW_WINDOW_END_X) 
		&& (y > VIEW_WINDOW_START_Y+VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW && y < VIEW_WINDOW_END_Y))
	{
		currentArtistArtIdentifier = CroPositionProcessor::getInstance().getStringIdentifierForArtistArtCoordinate(x, y);
		if (0 == currentArtistArtIdentifier.size())
		{
			return false;
		}
		if (CroInit::getInstance().getSurfaceInterface()->getCurrentSection() != MUSIC)
		{
			return false;
		}
		this->playFile(currentArtistArtIdentifier);
		return true;
	}
	else {
		return false;
	}
}

bool CroMusic::checkPlayerCoordinate( int x, int y ) 
{
	int playerState = CroPositionProcessor::getInstance().getIdentifierForMusicPlayerCoordinate(x, y);
	if (-1 == playerState)
	{
		return false;
	}
	
	switch (playerState) {
		case BACK:
			return this->backButton();
			break;
		case PLAY:
			return this->playButton();
			break;
		case PAUSE:
			return this->pauseButton();
			break;
		case STOP:
			return this->stopButton();
			break;
		case FORWARD:
			return this->forwardButton();
			break;
		default:
			return false;
			break;
	}
	return true;
	
}

bool CroMusic::playFile(std::string file, bool externalCall)
{
	if (file.empty())
		return false;
	
	result = system->createSound(file.c_str(), FMOD_HARDWARE|FMOD_LOOP_NORMAL|FMOD_ACCURATETIME, 0, &sound);
    if (this->ERRCHECK(result)) 
		return false;
	
	result = system->playSound(FMOD_CHANNEL_REUSE, sound, false, &channel);
	if (this->ERRCHECK(result)) 
		return false;
	
	std::string songName = getFilenameByIdentifier(file);
	currentPlaying = songName;
	currentPlayingPath = file;
	redrawCurrentPlaying(externalCall);
	return true;
}

bool CroMusic::playFileBackground(std::string file)
{
	if (file.empty())
		return false;
	
	result = system->createSound(file.c_str(), FMOD_HARDWARE|FMOD_LOOP_NORMAL|FMOD_ACCURATETIME, 0, &sound);
    if (ERRCHECK(result)) 
		return false;
	
	result = system->playSound(FMOD_CHANNEL_REUSE, sound, false, &channel);
	if (ERRCHECK(result)) 
		return false;
	return true;
}

bool CroMusic::stopMusic()
{
	if (currentPlaying.empty())
		return false;
	result = sound->release();
    if (ERRCHECK(result)) 
		return false;
	
	currentPlaying.clear();
	this->clearCurrentPlaying();
	return true;
}

bool CroMusic::redrawCurrentPlaying(bool externalCall)
{
	if (0 != currentPlaying.size()) 
	{
		if (!externalCall) 
		{
			g_surface->redraw();
			CroInit::getInstance().flipScreen();
		}
		g_viewer->GetMusicFont().DrawString(currentPlaying.c_str(),256,674,g_viewer->GetSurface());
		return true;
	}
	return false;
}

bool CroMusic::clearCurrentPlaying()
{
	g_surface->redraw(true);
	//CroInit::getInstance().flipScreen();
	return true;
}

std::string CroMusic::getFilenameByIdentifier(std::string identifier)
{
	std::vector<ArtistArtPaths> art_Vector = CroInit::getInstance().getFileSystem()->getArtVector();
	for(unsigned int i=0; i < art_Vector.size(); ++i) 
	{
		if(strcmp(art_Vector.at(i).sectionName.c_str(),section_char[MUSIC]) == 0) 
		{
			if(art_Vector.at(i).artPath.compare(identifier.c_str()) == 0) 
			{
				std::string toUpperName = art_Vector.at(i).artistArt;
				std::transform(toUpperName.begin(), toUpperName.end(),toUpperName.begin(),(int (*)(int))toupper);
				std::string copyOfName = art_Vector.at(i).artPath;
				std::string artName = CroString::stripExtension(toUpperName);
				return artName;
			}
		}
	}
	return std::string("");
}

bool CroMusic::ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("Music error! (%d) %s\n", result, FMOD_ErrorString(result));
		return true;
    }
	return false;
}

bool CroMusic::backButton() 
{
	if (0 == currentPlayingPath.size())
		return false;
	
	std::vector<ArtistArtPaths> art_Vector = CroInit::getInstance().getFileSystem()->getArtVector();
	for(unsigned int i=0; i < art_Vector.size(); ++i) 
	{
		if(strcmp(art_Vector.at(i).sectionName.c_str(),section_char[MUSIC]) == 0) 
		{
			if(art_Vector.at(i).artPath.compare(currentPlayingPath.c_str()) == 0) 
			{
				for(unsigned int j=(i-1); j > 0; --j) 
				{
					if(strcmp(art_Vector.at(j).sectionName.c_str(),section_char[MUSIC]) == 0) 
					{
						if (this->playFile(art_Vector.at(j).artPath))
							return true;
					}
				}
			}
		}
	}
	return false;
	
}

bool CroMusic::forwardButton()
{
	if (0 == currentPlayingPath.size())
		return false;
	
	std::vector<ArtistArtPaths> art_Vector = CroInit::getInstance().getFileSystem()->getArtVector();
	for(unsigned int i=0; i < art_Vector.size(); ++i) 
	{
		if(strcmp(art_Vector.at(i).sectionName.c_str(),section_char[MUSIC]) == 0) 
		{
			if(art_Vector.at(i).artPath.compare(currentPlayingPath.c_str()) == 0) 
			{
				if (art_Vector.size() < (i+1))
					return false;
				
				for(unsigned int j=(i+1); j < art_Vector.size(); ++j) 
				{
					if(strcmp(art_Vector.at(j).sectionName.c_str(),section_char[MUSIC]) == 0) 
					{
						if (this->playFile(art_Vector.at(j).artPath))
							return true;
					}
				}
			}
		}
	}
	return false;
}

bool CroMusic::pauseMusic()
{
	bool paused = false;
	channel->getPaused(&paused);
	if (paused)
		channel->setPaused(false);
	else 
		channel->setPaused(true);
	return true;
}

bool CroMusic::pauseButton()
{
	return this->pauseMusic();
}

bool CroMusic::playButton()
{
	bool paused = false;
	channel->getPaused(&paused);
	if (paused)
		paused = pauseMusic();
	
	if (!paused) 
	{
		if (0 != currentPlayingPath.size())
			this->playFile(currentPlayingPath);
	}
	return true;
}

bool CroMusic::stopButton()
{
	this->stopMusic();
	return true;
}

bool CroMusic::playRandomSound()
{
	std::vector<ArtistArtPaths> art_Vector = CroInit::getInstance().getFileSystem()->getArtVector();
	
	// build temp vector with music only
	std::vector<ArtistArtPaths> music_Vector;
	for(unsigned int i=0; i < art_Vector.size(); ++i) 
	{
		if(strcmp(art_Vector.at(i).sectionName.c_str(),section_char[MUSIC]) == 0) 
		{
			music_Vector.push_back(art_Vector.at(i));
		}
	}
	
	// play random track
	srand(time(NULL));
	for(unsigned int i=(rand() % music_Vector.size()); i < music_Vector.size(); ++i) 
	{
		if (this->playFile(music_Vector.at(i).artPath, true))
			return true;
	}
	// clear memory
	music_Vector.clear();
	return false;
}

bool CroMusic::callBackSoundFinished() 
{
	return true;//this->forwardButton();
}

CroMusic::~CroMusic() 
{
	result = sound->release();
    ERRCHECK(result);
    result = system->close();
}