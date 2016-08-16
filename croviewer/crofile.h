#ifndef __CROFILE__
#define __CROFILE__

#include <string>
#include <vector>
#include "boost/filesystem.hpp" 
#include "boost/filesystem/operations.hpp" 
#include "boost/filesystem/fstream.hpp" 

namespace fs = boost::filesystem;

struct MagPaths {
	std::string sectionName;
	std::string sectionPath;
	MagPaths(std::string sectionName, std::string sectionPath) : sectionName(sectionName),sectionPath(sectionPath) {}
}; // This holds data over cRo-viewer available sections

struct ArtistPaths {
	std::string sectionName;
	std::string artistName;
	std::string artistPath;
	int startX, startY, endX, endY;
	ArtistPaths(std::string sectionName, std::string artistName, std::string artistPath) : sectionName(sectionName), 
    artistName(artistName), artistPath(artistPath) {}
};

struct ArtistArtPaths {
	std::string sectionName;
	std::string artistName;
	std::string artistArt;
	std::string artPath;
	int startX, startY, endX, endY;
	ArtistArtPaths(std::string sectionName, std::string artistName, std::string artistArt, std::string artPath)
    : sectionName(sectionName), artistName(artistName), artistArt(artistArt), artPath(artPath) {}
	
};

class CroFile {
public:
	CroFile();
	virtual ~CroFile();
	int buildFilesystem();
	static char* getCurrentWorkingPath();
	static char* buildPath(const char* filename);
	std::vector<MagPaths>& getSectionVector();
	std::vector<ArtistPaths>& getArtistVector();
	std::vector<ArtistArtPaths>& getArtVector();
	static std::string getFilenameForGivenPath(std::string path);
	CroFile* getCroFileObj();	
private:
	int setSections();
	int setArtists();
	int setArts();
	
	// making it dynamic
	fs::path sectionPath;
	fs::path artistPath;
	fs::path artPath;	

	std::vector<MagPaths> section_Vector; 
	std::vector<ArtistPaths> artist_Vector;
	std::vector<ArtistArtPaths> art_Vector;
};

#endif
