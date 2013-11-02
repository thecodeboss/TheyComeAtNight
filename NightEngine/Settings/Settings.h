#ifndef Settings_h__
#define Settings_h__

struct GameSettings {

	const char * m_GameTitle;
	unsigned m_ScreenX, m_ScreenY;
	bool m_bFullScreen;
	bool m_TestMode;
	GameSettings(const char * GameTitle, bool bFullScreen = false, unsigned ScreenX = 800, unsigned ScreenY = 600);

};

#endif // Settings_h__
