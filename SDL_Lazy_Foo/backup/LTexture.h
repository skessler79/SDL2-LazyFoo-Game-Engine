#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

// Texture wrapper class
class LTexture
{
public:
	LTexture(SDL_Renderer* gRenderer);
	~LTexture();

	// Loads image at specified path
	bool loadFromFile(std::string path);

	// Deallocates texture
	void free();

	// Renders texture at given point
	void render(int x, int y);

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:

	// The actual hardware texture
	SDL_Texture* mTexture;

	// SDL Renderer
	SDL_Renderer* gRender;

	// Image dimensions
	int mWidth;
	int mHeight;
};