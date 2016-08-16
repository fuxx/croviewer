#include <crofile.h>
#ifdef WIN32
#include <Windows.h>
#endif // WIN32
#include "croglobal.h"
#ifdef LINUX
#include <string.h>
#endif
namespace fs = boost::filesystem;
CroFile::CroFile() {}
CroFile::~CroFile() {}

std::vector<MagPaths>& CroFile::getSectionVector() { return section_Vector; }
std::vector<ArtistPaths>& CroFile::getArtistVector() { return artist_Vector; }
std::vector<ArtistArtPaths>& CroFile::getArtVector() { return art_Vector; }

int CroFile::buildFilesystem()
{

	char fullpath[4096];
#ifdef WIN32
	strcpy_s(fullpath, CroFile::buildPath("MAG"));
#elif LINUX 
	strcpy(fullpath, CroFile::buildPath("/MAG"));	
#else
	strcpy(fullpath, CroFile::buildPath("/Contents/Resources/croResources/MAG"));
#endif // _DEBUG
	sectionPath = fs::path(fullpath); // mag path - sections

	int size = CroFile::setSections();
	if (0 == size)
		return 0;
	CroFile::setArtists();
	CroFile::setArts();
	return size;
	
}

int CroFile::setSections()
{
	if(fs::is_directory(sectionPath)) 
	{
		// search for sections
		for(fs::directory_iterator end, file(sectionPath); file != end; ++file) 
		{
			std::string sectionnametmp = file->filename();
			std::string sectionpathtmp = file->string();
			if (sectionnametmp.compare("croResources") != 0 && sectionnametmp.compare("INFO"))
				section_Vector.push_back(MagPaths(sectionnametmp, sectionpathtmp));
		}
	} else {
		printf("We are fucked up\n");
		return 0;
	}
	return section_Vector.size();
}

int CroFile::setArtists() 
{
	if (0 == section_Vector.size()) {
		return 0;
	}
	// search for artists
	for(unsigned int i=0; i < section_Vector.size(); ++i) 
	{
		artistPath = fs::path(sectionPath / section_Vector.at(i).sectionName.c_str());
		for(fs::directory_iterator end, file(artistPath); file != end; ++file) 
		{
			std::string sectionName = section_Vector.at(i).sectionName.c_str();
			std::string artistName = file->filename();
			std::string artistPath = file->string();
			artist_Vector.push_back(ArtistPaths(sectionName, artistName, artistPath));
		}
	}
	return artist_Vector.size();
}
	
int CroFile::setArts()
{
	if (0 == artist_Vector.size()) {
		return 0;
	}
	for(unsigned int i=0; i < artist_Vector.size(); ++i) 
	{
		artPath = fs::path(sectionPath / artist_Vector.at(i).sectionName.c_str() / artist_Vector.at(i).artistName.c_str());	
		for(fs::directory_iterator end, file(artPath); file != end; ++file) 
		{
			std::string sectionName = artist_Vector.at(i).sectionName.c_str();
			std::string artistName = artist_Vector.at(i).artistName.c_str();
			std::string artistArt = file->filename();
			std::string artPath= file->string();
			if (artistArt.compare("Thumbs.db") != 0 && artistArt.compare("Desktop.ini") != 0)
				art_Vector.push_back(ArtistArtPaths(sectionName, artistName, artistArt, artPath));
		}
	}
	return art_Vector.size();
}

char* CroFile::getCurrentWorkingPath()
{
	char path[4096] = "\0";

#ifdef __APPLE__
	strcpy(path, getcwd(NULL,0));
	strcat(path, EXECUTABLE_NAME);
#elif LINUX
	strcpy(path, getcwd(NULL,0));
#else
	GetCurrentDirectoryA(4096,(char *)path);
	strcat_s(path, "\\");
#endif
	return path;
}

char* CroFile::buildPath(const char* filename)
{
	char fileWithFullPath[4096] = "\0";
	char *currentWorkingPath = CroFile::getCurrentWorkingPath();
#ifdef WIN32
	strcpy_s(fileWithFullPath, currentWorkingPath);
	strcat_s(fileWithFullPath, filename);
#elif LINUX
	strcpy(fileWithFullPath, currentWorkingPath);
	strcat(fileWithFullPath, filename);
#else
	strcpy(fileWithFullPath, currentWorkingPath);
	strcat(fileWithFullPath, filename);
#endif
	return fileWithFullPath;
}

std::string getFilenameForGivenPath(const std::string& path) 
{
	fs::path p(path);
	std::string filename = p.file_string();
	return path;
}


