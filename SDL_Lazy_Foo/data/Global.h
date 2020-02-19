#pragma once

#include <SDL.h>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Key press textures constants
enum KeyPressTextures
{
	KEY_PRESS_TEXTURE_DEFAULT,
	KEY_PRESS_TEXTURE_UP,
	KEY_PRESS_TEXTURE_DOWN,
	KEY_PRESS_TEXTURE_LEFT,
	KEY_PRESS_TEXTURE_RIGHT,
	KEY_PRESS_TEXTURE_P,
	KEY_PRESS_TEXTURE_T,
	KEY_PRESS_TEXTURE_V,
	KEY_PRESS_TEXTURE_TOTAL
};

// Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

// The window renderer
extern SDL_Renderer* gRenderer;

// Loads individual image
SDL_Surface* loadSurface(std::string path);

// The window we'll be rendering to
extern SDL_Window* gWindow;

// The surface contained by the window
extern SDL_Surface* gScreenSurface;

// The images that correspond to a keypress
// SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// The textures that correspond to a keypress
extern SDL_Texture* gKeyPressTextures[KEY_PRESS_TEXTURE_TOTAL];

// Current displayed image
extern SDL_Surface* gCurrentSurface;

// Current displayed texture
extern SDL_Texture* gTexture;

// Test stretched image
extern SDL_Texture* gStretchedTexture;

// Test PNG image
extern SDL_Surface* gPNGSurface;