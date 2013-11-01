#include "Settings.h"

GameSettings::GameSettings( const char * GameTitle, bool bFullScreen /* = false*/, unsigned ScreenX /* = 800*/, unsigned ScreenY /* = 600*/ )
	: m_GameTitle(GameTitle)
	, m_ScreenX(ScreenX)
	, m_ScreenY(ScreenY)
	, m_bFullScreen(bFullScreen)
{

}

