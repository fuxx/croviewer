/*
 *  croglobal.h
 *  croviewer
 *
 *  Created by fuxx on 08.10.10.
 *  Copyright 2010 chemical-reaction.org. All rights reserved.
 *
 */
#ifndef __CROGLOBAL__
#define __CROGLOBAL__


typedef enum {MAIN, ASCII, HIRES, MUSIC, INFO} ENUM_SECTION;
typedef enum {ARTISTS, FILEVIEW, ARTVIEW} ENUM_LEVEL;
typedef enum  {BACK, PLAY, PAUSE, STOP, FORWARD} ENUM_PLAYERBUTTONSTATE;


const char* const section_char[]={"MAIN","ASCII","HIRES","MUSIC","INFO"};

const int BITMAPFONT_H = 28;
const int BITMAPFONT_W = 32;
const int BITMAPFONT_SPACING = 8;

#ifndef WIN32
const char EXECUTABLE_NAME[] = "/croviewer.app";
#endif

const int VIEW_PREVIEW_START_X = 205;
const int VIEW_PREVIEW_END_X = 820;
const int VIEW_PREVIEW_START_Y = 700;
const int VIEW_PREVIEW_SPACING = 20;

const double VIEW_PREVIEW_MAX_HEIGHT = 50;
const double VIEW_PREVIEW_MAX_WIDTH = 40;
const double VIEW_PREVIEW_BIGGER_MAX_HEIGHT = 400;
const double VIEW_PREVIEW_BIGGER_MAX_WIDTH = 300;

const int VIEW_PREVIEW_SCROLL_BUTTON_LEFT_START_X = 188;
const int VIEW_PREVIEW_SCROLL_BUTTON_LEFT_START_Y = 719;
const int VIEW_PREVIEW_SCROLL_BUTTON_RIGHT_START_X = 830;
const int VIEW_PREVIEW_SCROLL_BUTTON_RIGHT_START_Y = 720;

const int VIEW_SONG_TITLE_TEXT_START_X = 256;
const int VIEW_SONG_TITLE_TEXT_START_Y = 674;

const int VIEW_WINDOW_START_X = 190;
const int VIEW_WINDOW_START_Y = 150;
const int VIEW_WINDOW_END_X = 842;
const int VIEW_WINDOW_END_Y = 650;
const int VIEW_WINDOW_SPACE_BETWEEN_MENU_AND_VIEW_WINDOW = 25;

const int WINDOW_X = 1024;
const int WINDOW_Y = 768;
const int WINDOW_BIT = 32;

const int TRANSFORM_MS = 30;

#ifdef WIN32
const char SCROLL_BUTTON_UP[] = "MAG\\croResources\\Images\\btn_up.png";
const char SCROLL_BUTTON_DOWN[] = "MAG\\croResources\\Images\\btn_down.png";
const char SCROLL_BUTTON_LEFT[] = "MAG\\croResources\\Images\\btn_left.png";
const char SCROLL_BUTTON_RIGHT[] = "MAG\\croResources\\Images\\btn_right.png";
const char MAIN_NFO[] = "MAG\\INFO\\cro.png";
#elif LINUX
const char SCROLL_BUTTON_UP[] = "/MAG/croResources/Images/btn_up.png";
const char SCROLL_BUTTON_DOWN[] = "/MAG/croResources/Images/btn_down.png";
const char SCROLL_BUTTON_LEFT[] = "/MAG/croResources/Images/btn_left.png";
const char SCROLL_BUTTON_RIGHT[] = "/MAG/croResources/Images/btn_right.png";
const char MAIN_NFO[] = "/MAG/INFO/cro.png";
#else
const char SCROLL_BUTTON_UP[] = "/Contents/Resources/croResources/Images/btn_up.png";
const char SCROLL_BUTTON_DOWN[] = "/Contents/Resources/croResources/Images/btn_down.png";
const char SCROLL_BUTTON_LEFT[] = "/Contents/Resources/croResources/Images/btn_left.png";
const char SCROLL_BUTTON_RIGHT[] = "/Contents/Resources/croResources/Images/btn_right.png";
const char MAIN_NFO[] = "/Contents/Resources/croResources/MAG/INFO/cro.png";
#endif // WIN32
// x: 184, y: 416
const int SCROLL_BUTTON_UP_START_X = 815, SCROLL_BUTTON_DOWN_START_X = 815;
const int SCROLL_BUTTON_UP_START_Y = 190, SCROLL_BUTTON_DOWN_START_Y = 640;
const int SCROLL_BUTTON_LEFT_START_X = 80, SCROLL_BUTTON_RIGHT_START_X = 915;
const int SCROLL_BUTTON_LEFT_START_Y = 416, SCROLL_BUTTON_RIGHT_START_Y = 416;
#endif
