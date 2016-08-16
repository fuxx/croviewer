#include "crosurface.h"
#include "croinit.h"

CroSurface::CroSurface(SDL_Surface *screen) { 
	CroPositionProcessor::getInstance().setUpButtonRegions();
	currentLevel = 0;
	lastSection = 0;
}

// called when mouse is moved
bool CroSurface::checkInput( int x, int y )
{
	return false;
}

void CroSurface::saveState( int x, int y )
{
	lastState_x = x;
	lastState_y = y;
}

bool CroSurface::checkTopLevelMenuAndPaint( int x, int y, bool scrolling, int scrollDirection, bool externalCall )
{
	//printf("checkTopLevelMenuAndPaint\n");
	int sectionIdentifier = CroPositionProcessor::getInstance().getIdentifierForCoordinate(x, y);
	if (sectionIdentifier == INFO)
	{
		/*** DIRTY ***/
		this->SetSection(INFO);
		this->SetLevel(FILEVIEW);
		char fullpath[4096];
#ifdef WIN32
		strcpy_s(fullpath, CroFile::buildPath(MAIN_NFO));
#elif LINUX 
		strcpy(fullpath, CroFile::buildPath(MAIN_NFO));	
#else
		strcpy(fullpath, CroFile::buildPath(MAIN_NFO));
#endif // _DEBUG
		std::string info(fullpath);
		return CroInit::getInstance().getArtViewer()->showArt(info);
		
	}
	if (0 == scrollDirection) 
	{
		scrollDirection = CroPositionProcessor::getInstance().getScrollDirectionForCoordinate(x, y);
		if (SDL_BUTTON_WHEELDOWN == scrollDirection || SDL_BUTTON_WHEELUP == scrollDirection)
		{
			x = -1;
			y = -1;
			scrolling = true;
		}
		
	}
	
	bool drawScrollButtonUp = false;
	bool drawScrollButtonDown = false;
	
	if (-1 != x && -1 != y) 
	{
		if (sectionIdentifier == -1)
			return false;
		start_x = VIEW_WINDOW_START_X;
		start_y = VIEW_WINDOW_START_Y;
		CroPositionProcessor::getInstance().setUpArtistArtVector();
		if (!externalCall)
			this->saveState(x, y);
	}
	else 
	{
		if (getCurrentLevel() != ARTISTS)
			return false;
		
		if (scrollDirection == SDL_BUTTON_WHEELDOWN)
		{
			if (!(VIEW_WINDOW_END_Y >= (start_y + ((BITMAPFONT_H + BITMAPFONT_SPACING) * artistVectorSize))))
			{	
				start_y -= (BITMAPFONT_H + BITMAPFONT_SPACING);
				drawScrollButtonUp = true;
			}
			else
				return false;
		}
		else 
		{
			if ((VIEW_WINDOW_START_Y >= (start_y + (BITMAPFONT_H + BITMAPFONT_SPACING)))) 
			{
				start_y += (BITMAPFONT_H + BITMAPFONT_SPACING);
				drawScrollButtonDown = true;
			}
			else
			{
				if (!externalCall)
					return false;	
			}
		}
		sectionIdentifier = getCurrentSection();
	}
	
	// init video/file system and get viewer/font
	CroViewer* viewer = CroInit::getInstance().getViewerInterface();
	std::vector<ArtistPaths> artist_Vector = CroInit::getInstance().getFileSystem()->getArtistVector();
	if (!externalCall)
		viewer->apply_surface(0, 0, viewer->GetBackgroundImage(), viewer->GetSurface());
	if(drawScrollButtonUp)
		CroInit::getInstance().getScrollButton()->drawButtonUp();
	if(drawScrollButtonDown)
		CroInit::getInstance().getScrollButton()->drawButtonDown();
	
	// clear coordinate vector
	CroPositionProcessor::getInstance().setUpArtistVector();

	artistVectorSize = 0;
	// draw and save coordinates
	for(unsigned int i=0; i < artist_Vector.size(); ++i) 
	{
		if(strcmp(artist_Vector.at(i).sectionName.c_str(),section_char[sectionIdentifier]) == 0) 
		{
			std::string toUpperName = artist_Vector.at(i).artistName;
			std::string copyOfName = std::string(artist_Vector.at(i).artistName);
#ifdef WIN32
			std::transform(toUpperName.begin(), toUpperName.end(), toUpperName.begin(), toupper);
#else // end win32 - apple / linux
			std::transform(toUpperName.begin(), toUpperName.end(), toUpperName.begin(), (int(*)(int)) std::toupper);
#endif 
			
			
			start_y+=(BITMAPFONT_H+BITMAPFONT_SPACING);
			if ((start_y < VIEW_WINDOW_END_Y) && (start_y > VIEW_WINDOW_START_Y))
			{	
				viewer->GetMainFont().DrawString(toUpperName.c_str(),start_x,start_y,viewer->GetSurface());
				
			} else {
				if (!drawScrollButtonDown) 
				{
					if ((start_y-(BITMAPFONT_H+BITMAPFONT_SPACING)) > VIEW_WINDOW_START_Y)
						CroInit::getInstance().getScrollButton()->drawButtonDown();
				}
				if (!drawScrollButtonUp) 
				{
					if ((start_y-(BITMAPFONT_H-BITMAPFONT_SPACING)) < VIEW_WINDOW_START_Y)
						CroInit::getInstance().getScrollButton()->drawButtonUp();
				}
			}
			CroPositionProcessor::getInstance().setNewArtist(
															 CroSurface::getCurrentSection(), 
															 start_x, VIEW_WINDOW_END_X-100,
															 start_y, 
															 start_y + BITMAPFONT_H,
															 copyOfName);
		} // if
	} // for
	
	artistVectorSize = CroPositionProcessor::getInstance().getSizeOfAristArt();
	
	if (scrolling) 
	{
		if (scrollDirection == SDL_BUTTON_WHEELDOWN) 
		{
			start_y -= ((BITMAPFONT_H+BITMAPFONT_SPACING) * artistVectorSize);
		} 
		else 
		{
			start_y += -((BITMAPFONT_H+BITMAPFONT_SPACING) * artistVectorSize);
		}
	} 
	else 
	{
		start_y = start_y - ((BITMAPFONT_H+BITMAPFONT_SPACING) * artistVectorSize);
	}
	
	// setting current section and set level to artists
	this->SetSection(sectionIdentifier);
    this->SetLevel(ARTISTS);
	// reset draw status
	CroInit::getInstance().getArtViewer()->isDrawed = false;
	if (!externalCall)
	{
		if(!CroInit::getInstance().getArtPreview()->drawImages())
			CroInit::getInstance().flipScreen();
	}
	return true;
}

bool CroSurface::checkArtistAndPaint( int x /*= -1*/, int y /*= -1*/, bool scrolling /*= false*/, int scrollDirection /*= 0*/, bool externalCall /*= false*/ )
{
	//printf("checkArtistAndPaint\n");
	if(CroSurface::getCurrentLevel() > FILEVIEW)
		return false;
	
	bool drawScrollButtonUp = false;
	bool drawScrollButtonDown = false;
	bool interfaceRedrawed = false;
	if (0 == scrollDirection) 
	{
		scrollDirection = CroPositionProcessor::getInstance().getScrollDirectionForCoordinate(x, y);
		if (SDL_BUTTON_WHEELDOWN == scrollDirection || SDL_BUTTON_WHEELUP == scrollDirection)
		{
			x = -1;
			y = -1;
			scrolling = true;
		}
		
	}
	
	if (scrolling) 
	{
		if (getCurrentLevel() != FILEVIEW)
			return false;
	}
	
	if (-1 != x && -1 != y) 
	{
		if ((x > VIEW_WINDOW_START_X && x < VIEW_WINDOW_END_X) 
			&& (y > VIEW_WINDOW_START_Y+VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW && y < VIEW_WINDOW_END_Y))
		{
			
			currentArtistIdentifier = CroPositionProcessor::getInstance().getStringIdentifierForArtistCoordinate(x, y);
			if (currentArtistIdentifier.empty() && (getCurrentSection() == lastSection) && getCurrentSection() == MUSIC)
			{
				interfaceRedrawed = true;
				currentArtistIdentifier = oldArtistIdentifier; 
			} else  {
				oldArtistIdentifier = currentArtistIdentifier;
				lastSection = getCurrentSection();
				interfaceRedrawed = false;
			}
			if (0 == currentArtistIdentifier.size())
				return false;
			
			start_x = VIEW_WINDOW_START_X;
			start_y = VIEW_WINDOW_START_Y;
			if (!externalCall)
				this->saveState(x, y);
			if (externalCall)
				this->SetLevel(ARTISTS);
		} else {
			return false;
		}
		
	} 
	else 
	{
		if (scrollDirection == SDL_BUTTON_WHEELDOWN) 
		{
			if (!(VIEW_WINDOW_END_Y >= (start_y + ((BITMAPFONT_H + BITMAPFONT_SPACING) * foundFilesForArtist))))
			{
				start_y -= (BITMAPFONT_H + BITMAPFONT_SPACING);
				drawScrollButtonUp = true;
			}
			else 
				return false;
		} 
		else if (scrollDirection == SDL_BUTTON_WHEELUP)
		{	
			if ((VIEW_WINDOW_START_Y >= (start_y + (BITMAPFONT_H + BITMAPFONT_SPACING))))
			{
				start_y += (BITMAPFONT_H + BITMAPFONT_SPACING);
				drawScrollButtonDown = true;
			}
			else
				return false;
		}
	}
	
	// init video/file system and get viewer/font
	CroViewer* viewer = CroInit::getInstance().getViewerInterface();
	std::vector<ArtistArtPaths> art_Vector = CroInit::getInstance().getFileSystem()->getArtVector();
	CroPositionProcessor::getInstance().setUpArtistVector();
	CroPositionProcessor::getInstance().setUpArtistArtVector();
	
	// apply to surface
    viewer->apply_surface(0, 0, viewer->GetBackgroundImage(), viewer->GetSurface());
	if(drawScrollButtonUp)
		CroInit::getInstance().getScrollButton()->drawButtonUp();
	if(drawScrollButtonDown)
		CroInit::getInstance().getScrollButton()->drawButtonDown();
	
	foundFilesForArtist = 0;
	
	for(unsigned int i=0; i < art_Vector.size(); ++i) 
	{
		if(strcmp(art_Vector.at(i).sectionName.c_str(),section_char[CroSurface::getCurrentSection()]) == 0) 
		{
			if(art_Vector.at(i).artistName.compare(currentArtistIdentifier) == 0) 
			{
				std::string toUpperName = art_Vector.at(i).artistArt;
				std::transform(toUpperName.begin(), toUpperName.end(),toUpperName.begin(),(int (*)(int))toupper);
				std::string copyOfName = art_Vector.at(i).artPath;
				std::string artName = CroString::stripExtension(toUpperName);
				
				// pre calculate start_y
				start_y+=(BITMAPFONT_H+BITMAPFONT_SPACING);
				if ((start_y < VIEW_WINDOW_END_Y) && (start_y > VIEW_WINDOW_START_Y))
				{
					// cat string if size is more the defined max window
					if ((artName.size()) > ((VIEW_WINDOW_END_X - VIEW_WINDOW_START_X) / BITMAPFONT_W))
						artName = artName.substr(0, ((VIEW_WINDOW_END_X - VIEW_WINDOW_START_X) / BITMAPFONT_W));
					
					viewer->GetMainFont().DrawString(artName.c_str(),start_x,start_y,viewer->GetSurface());
					
				}
				else 
				{
					if (!drawScrollButtonDown) 
					{
						if ((start_y-(BITMAPFONT_H+BITMAPFONT_SPACING)) > VIEW_WINDOW_START_Y)
							CroInit::getInstance().getScrollButton()->drawButtonDown();
					}
					if (!drawScrollButtonUp) 
					{
						if ((start_y-(BITMAPFONT_H-BITMAPFONT_SPACING)) < VIEW_WINDOW_START_Y)
							CroInit::getInstance().getScrollButton()->drawButtonUp();
					}
				}
				
				foundFilesForArtist++;
				CroPositionProcessor::getInstance().setNewArtistArt(
																	CroSurface::getCurrentSection(), 
																	start_x, VIEW_WINDOW_END_X-100,
																	start_y, 
																	start_y + BITMAPFONT_H,
																	copyOfName);
			}
		} // if
	} // for
	
	if (!externalCall)
	{
		if(!CroInit::getInstance().getArtPreview()->drawImages())
			CroInit::getInstance().flipScreen();
	}
	if (scrolling) 
	{
		if (scrollDirection == SDL_BUTTON_WHEELDOWN) 
		{
			start_y -= ((BITMAPFONT_H+BITMAPFONT_SPACING) * foundFilesForArtist);
		} 
		else 
		{
			start_y += -((BITMAPFONT_H+BITMAPFONT_SPACING) * foundFilesForArtist);
		}
	} 
	else 
	{
		start_y = start_y - ((BITMAPFONT_H+BITMAPFONT_SPACING) * foundFilesForArtist);
	}
	
	this->SetLevel(FILEVIEW);
	if (!externalCall) 
	{
		CroPositionProcessor::getInstance().setUpArtistVector();
		
	}
	// reset drawed
	CroInit::getInstance().getArtViewer()->isDrawed = false;
	
	return !interfaceRedrawed;
}

bool CroSurface::checkScrollingListAndDraw( int x, int y, int scrollDirection /*= 0*/ )
{
	//printf("checkScrollingListAndDraw\n");
	if (this->getCurrentLevel() > FILEVIEW)
		return false;
	if (this->getCurrentLevel() < ARTISTS)
		return false;
	
	if ((x > VIEW_WINDOW_START_X && x < VIEW_WINDOW_END_X) 
		&& (y > VIEW_WINDOW_START_Y && y < VIEW_WINDOW_END_Y))
	{
		if(this->checkTopLevelMenuAndPaint(-1, -1, true, scrollDirection))
			return true;
		else if(this->checkArtistAndPaint(-1, -1, true, scrollDirection))
			return true;
		else return false;
	}
	return false;
}

// Blit an image on the screen surface
void CroSurface::DrawIMG(SDL_Surface *img,CroViewer *viewer, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_BlitSurface(img, NULL, viewer->GetSurface(), &dest);
}


void CroSurface::DrawIMG(SDL_Surface *img, CroViewer *viewer,int x, int y,
						 int w, int h, int x2, int y2)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_Rect dest2;
	dest2.x = x2;
	dest2.y = y2;
	dest2.w = w;
	dest2.h = h;
	SDL_BlitSurface(img, &dest2, viewer->GetSurface(), &dest);
}

bool CroSurface::DrawIMGWithSize(SDL_Surface *img, CroViewer *viewer, int x_cor, int y_cor,
								 Uint16 width, Uint16 height)
{
	return true;
}

bool CroSurface::redraw(bool external)
{
	CroViewer* viewer = CroInit::getInstance().getViewerInterface();
	
	
	if (this->getCurrentLevel() == ARTISTS) 
	{
		viewer->apply_surface(0, 0, viewer->GetBackgroundImage(), viewer->GetSurface());
		this->checkTopLevelMenuAndPaint(-1, -1, false, 0, true);
	}
	else if (this->getCurrentLevel() == FILEVIEW) 
	{
		viewer->apply_surface(0, 0, viewer->GetBackgroundImage(), viewer->GetSurface());
		this->checkArtistAndPaint(-1, -1, false, 0, true);
	}
	else if (this->getCurrentLevel() > FILEVIEW)
	{
		CroInit::getInstance().getArtViewer()->scrollArt(0, false, 0, 0, true);
	}
	else 
	{
		return false;
	}
	if(!CroInit::getInstance().getArtPreview()->drawImages())
		CroInit::getInstance().flipScreen();
	
	return true;
}

