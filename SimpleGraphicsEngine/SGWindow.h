#pragma once
#include <string>
#include <SDL.h>

class SGWindow 
{
public:
	SGWindow(const std::string &title, int width, int height);
	~SGWindow();
	inline bool isClosed() const { return _closed; };

	void Clear() const;
	void PollEvents();
	int LockFrame(Uint32** pixels, int* pitch);
	void UnlockFrame();
	//int updateFrame(Uint32 *pixels);
	
	void Wait(Uint32 milliseconds);


private:
	bool Initialize();

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

