#pragma once
#include <string>
#include <SDL.h>

struct FrameInfo
{
	void* pixels;
	int pitch;
};

class SGWindow 
{
public:
	SGWindow(const std::string &title, int width, int height);
	~SGWindow();
	inline bool isClosed() const { return _closed; };

	void clear() const;
	void pollEvents();
	int lockFrame(FrameInfo frameInfo);
	void unlockFrame(FrameInfo frameInfo);
	
	void wait(Uint32 milliseconds);


private:
	bool initialize();

	std::string _title = "Default SGWindow";
	int _width = 600;
	int _height = 800;

	bool _closed = false;

	void* pixels;
	int pitch;

	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;
	SDL_Texture *_texture = nullptr;
};

