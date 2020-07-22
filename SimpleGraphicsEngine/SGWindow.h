#pragma once
#include <string>
#include <SDL.h>

class SGWindow 
{
public:
	SGWindow(const std::string &title, int width, int height);
	~SGWindow();
	inline bool isClosed() const { return _closed; };

	void clear() const;
	void pollEvents();

private:
	bool initialize();

	std::string _title = "Default SGWindow";
	int _width = 600;
	int _height = 800;

	bool _closed = false;

	SDL_Window *_window = nullptr;
	SDL_Renderer* _renderer = nullptr;
};
