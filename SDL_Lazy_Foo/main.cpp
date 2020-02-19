#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "data/LTexture.h"
#include "data/Global.h"

/*
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

*/

enum KeyPressFunctions
{
	KEY_PRESS_FUNCTION_U,		// Test draw some shapes with SDL_Rect
	KEY_PRESS_FUNCTION_TOTAL
};

struct common_shapes {
	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
}common_shape;

// TODO: Make viewport class and create each viewport as objects
struct viewports {

};


// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Globals
SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gCurrentSurface = NULL;
SDL_Texture* gTexture = NULL;
SDL_Texture* gStretchedTexture = NULL;
SDL_Surface* gPNGSurface = NULL;
SDL_Texture* gKeyPressTextures[KEY_PRESS_TEXTURE_TOTAL];


// Scene sprites
SDL_Rect gSpriteClips[4];
LTexture gSpriteSheetTexture;

/*
// Texture wrapper class
class LTexture
{
public:
	LTexture();
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

	// Image dimensions
	int mWidth;
	int mHeight;
};
*/

// Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;
LTexture gModulatedTexture;
LTexture gFadeInBackgroundTexture;

// Walking animation
const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClipsAnim[WALKING_ANIMATION_FRAMES];
LTexture gSpriteSheetTextureAnim;

// Frame rate
const int frame_rate = 120;

int main(int argc, char* argv[])
{
	// Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");;
	}
	else
	{
		// Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;

			// Modulation components
			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;
			Uint8 a = 255;

			// Current animation frame
			int frame = 0;

			// Angle of rotation
			double degrees = 0;

			// Flip type
			SDL_RendererFlip flipType = SDL_FLIP_NONE;

			// Set default current surface
			// gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT];
			// Render background texture to screen
			gBackgroundTexture.render(0, 0);
			// gFadeInBackgroundTexture.render(0, 0);

			// Render Foo to the screen
			gFooTexture.render(240, 190);

			// Render top left sprite
			gSpriteSheetTexture.render(0, 0, &gSpriteClips[0]);

			// Render top right sprite
			gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1]);

			// Render bottom left sprite
			gSpriteSheetTexture.render(0, SCREEN_HEIGHT - gSpriteClips[2].h, &gSpriteClips[2]);

			// Render bottom right sprite
			gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[3].w, SCREEN_HEIGHT - gSpriteClips[3].h, &gSpriteClips[3]);

			/// --------
			/// MAIN LOOP
			/// --------
			// While application is running
			while (!quit)
			{
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					// User presses a key
					else if (e.type == SDL_KEYDOWN)
					{
						// Select surfaces based on key press
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_UP];
							break;

						case SDLK_DOWN:
							gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_DOWN];
							break;

						case SDLK_LEFT:
							gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_LEFT];
							break;

						case SDLK_RIGHT:
							gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_RIGHT];
							break;

						case SDLK_p:
							gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_P];
							break;

						case SDLK_t:
							gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_T];
							break;

						case SDLK_v:
							// Clear screen
							SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
							SDL_RenderClear(gRenderer);

							gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_V];
							// Top left corner viewport
							SDL_Rect topLeftViewport;
							topLeftViewport.x = 0;
							topLeftViewport.y = 0;
							topLeftViewport.w = SCREEN_WIDTH / 2;
							topLeftViewport.h = SCREEN_HEIGHT / 2;
							SDL_RenderSetViewport(gRenderer, &topLeftViewport);

							// Render texture to screen
							SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

							// Top right corner viewport
							SDL_Rect topRightViewport;
							topRightViewport.x = SCREEN_WIDTH / 2;
							topRightViewport.y = 0;
							topRightViewport.w = SCREEN_WIDTH / 2;
							topRightViewport.h = SCREEN_HEIGHT / 2;
							SDL_RenderSetViewport(gRenderer, &topRightViewport);

							// Render texture to screen
							SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

							// Top left corner viewport
							SDL_Rect bottomViewport;
							bottomViewport.x = 0;
							bottomViewport.y = SCREEN_HEIGHT / 2;
							bottomViewport.w = SCREEN_WIDTH;
							bottomViewport.h = SCREEN_HEIGHT / 2;
							SDL_RenderSetViewport(gRenderer, &bottomViewport);

							// Render texture to screen
							SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
							break;

						case SDLK_u:
							/// Doesn't work
							
							// Clear screen
							SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
							SDL_RenderClear(gRenderer);
							printf("'u' pressed\n");

							// Render red filled quad
							SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
							SDL_RenderFillRect(gRenderer, &common_shape.fillRect);
							
							// Render green outlined quad
							SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
							SDL_RenderDrawRect(gRenderer, &common_shape.outlineRect);

							// Draw blue horizontal line
							SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
							SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

							// Draw vertical line of yellow dots
							SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
							for (int i = 0; i < SCREEN_HEIGHT; i += 4)
							{
								SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
							}
							break;

						
						/// Modulation colors
						// Increase red
						case SDLK_q:
							// Cap if over 255
							if (r + 32 > 255)
							{
								r = 255;
							}
							// Increment otherwise
							else
							{
								r += 32;
							}
							break;

						// Increase green
						case SDLK_w:
							// Cap if over 255
							if (g + 32 > 255)
							{
								g = 255;
							}
							// Increment otherwise
							else
							{
								g += 32;
							}
							break;

						// Increase blue
						case SDLK_e:
							// Cap if over 255
							if (b + 32 > 255)
							{
								b = 255;
							}
							// Increment otherwise
							else
							{
								b += 32;
							}
							break;

						// Decrease red
						case SDLK_a:
							// Cap if below 0
							if (r - 32 < 0)
							{
								r = 0;
							}
							// Decrement otherwise
							else
							{
								r -= 32;
							}
							break;

						// Decrease green
						case SDLK_s:
							// Cap if below 0
							if (g - 32 < 0)
							{
								g = 0;
							}
							// Decrement otherwise
							else
							{
								g -= 32;
							}
							break;

						// Decrease blue
						case SDLK_d:
							// Cap if below 0
							if (b - 32 < 0)
							{
								b = 0;
							}
							// Decrement otherwise
							else
							{
								b -= 32;
							}
							break;
							

						/*
						// Increase alpha on w
						case SDLK_w:
							// Cap if over 255
							if(a + 32 > 255)
							{
								a = 255;
							}
							// Increment otherwise
							else
							{
								a += 32;
							}
							break;

						// Decrease alpha on s
						case SDLK_s:
							// Cap if below 0
							if (a - 32 < 0)
							{
								a = 0;
							}
							// Decrement otherwise
							else
							{
								a -= 32;
							}
							break;
							*/

						default:
							gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT];
							break;
						}
					}
				}

				// Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				// Modulate and render texture
				gBackgroundTexture.setColor(r, g, b);
				gBackgroundTexture.render(0, 0);

				// Render current frame (foo_anim)
				SDL_Rect* currentClip = &gSpriteClipsAnim[frame / (4 * frame_rate / 60)];
				gSpriteSheetTextureAnim.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);

				// Render fade-in and fade-out background
				// gFadeInBackgroundTexture.render(0, 0);
				// gModulatedTexture.setAlpha(a);
				// gModulatedTexture.render(0, 0);

				// Apply the image
				//SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// Update the surface
				//SDL_UpdateWindowSurface(gWindow);

				// Update Screen
				SDL_RenderPresent(gRenderer);

				// Go to next frame
				++frame;

				// Cycle animation
				// Adjust denominator for frame rate
				if (frame / (4 * frame_rate / 60) >= WALKING_ANIMATION_FRAMES)
				{
					frame = 0;
				}
			}

			// Apply a stretched image on quit
			/*
			SDL_Rect stretchRect;
			stretchRect.x = 0;
			stretchRect.y = 0;
			stretchRect.w = SCREEN_WIDTH;
			stretchRect.h = SCREEN_HEIGHT;
			*/
			SDL_RenderCopy(gRenderer, gStretchedTexture, NULL, NULL);
			//SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

			// Update the surface
			SDL_RenderPresent(gRenderer);
			//SDL_UpdateWindowSurface(gWindow);

			// Delay
			SDL_Delay(1000);
		}
	}

	// Free Resources and close SDL
	close();

	return 0;
}

bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error : %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error : %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG Loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error %s\n", IMG_GetError());
					success = false;
				}
				
				else
				{
					/*
					// Get window surface
					gScreenSurface = SDL_GetWindowSurface(gWindow);
					*/
				}
				
			}
		}
	}

	return success;
}

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load default surface
	gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT] = loadTexture("graphics/images/press.png");
	if (gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	// Load up surface
	gKeyPressTextures[KEY_PRESS_TEXTURE_UP] = loadTexture("graphics/images/up.png");
	if (gKeyPressTextures[KEY_PRESS_TEXTURE_UP] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	// Load down surface
	gKeyPressTextures[KEY_PRESS_TEXTURE_DOWN] = loadTexture("graphics/images/down.png");
	if (gKeyPressTextures[KEY_PRESS_TEXTURE_DOWN] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	// Load left surface
	gKeyPressTextures[KEY_PRESS_TEXTURE_LEFT] = loadTexture("graphics/images/left.png");
	if (gKeyPressTextures[KEY_PRESS_TEXTURE_LEFT] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	// Load right surface
	gKeyPressTextures[KEY_PRESS_TEXTURE_RIGHT] = loadTexture("graphics/images/right.png");
	if (gKeyPressTextures[KEY_PRESS_TEXTURE_RIGHT] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	// Load stretching surface
	gStretchedTexture = loadTexture("graphics/images/stretch.png");
	if (gStretchedTexture == NULL)
	{
		printf("Failed to load stretching image!\n");
		success = false;
	}

	// Load PNG surface on P key
	gKeyPressTextures[KEY_PRESS_TEXTURE_P] = loadTexture("graphics/images/loaded.png");
	if (gKeyPressTextures[KEY_PRESS_TEXTURE_P] == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}
	
	// Load PNG texture on T key
	gKeyPressTextures[KEY_PRESS_TEXTURE_T] = loadTexture("graphics/images/texture.png");
	if (gKeyPressTextures[KEY_PRESS_TEXTURE_T] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	// Load viewports
	gKeyPressTextures[KEY_PRESS_TEXTURE_V] = loadTexture("graphics/images/viewport.png");
	if (gKeyPressTextures[KEY_PRESS_TEXTURE_V] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	// Load Foo texture
	if (!gFooTexture.loadFromFile("graphics/images/foo.png"))
	{
		printf("Failed to load Foo texture image!\n");
		success = false;
	}

	// Load background texture
	if (!gBackgroundTexture.loadFromFile("graphics/images/background.png"))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	// Load sprite sheet texture
	if (!gSpriteSheetTexture.loadFromFile("graphics/spritesets/dots.png"))
	{
		printf("Failed to load spritesheet texture!\n");
		success = false;
	}
	else
	{
		// Set top left sprite
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 100;
		gSpriteClips[0].h = 100;

		// Set top right sprite
		gSpriteClips[1].x = 100;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 100;
		gSpriteClips[1].h = 100;

		// Set bottom left sprite
		gSpriteClips[2].x = 0;
		gSpriteClips[2].y = 100;
		gSpriteClips[2].w = 100;
		gSpriteClips[2].h = 100;

		// Set bottom right sprite
		gSpriteClips[3].x = 100;
		gSpriteClips[3].y = 100;
		gSpriteClips[3].w = 100;
		gSpriteClips[3].h = 100;
	}

	// Load sprite sheet texture animated (foo_anim)
	if (!gSpriteSheetTextureAnim.loadFromFile("graphics/spritesets/foo_anim.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		// Set sprite clips anim
		gSpriteClipsAnim[0].x = 0;
		gSpriteClipsAnim[0].y = 0;
		gSpriteClipsAnim[0].w = 64;
		gSpriteClipsAnim[0].h = 205;

		gSpriteClipsAnim[1].x = 64;
		gSpriteClipsAnim[1].y = 0;
		gSpriteClipsAnim[1].w = 64;
		gSpriteClipsAnim[1].h = 205;

		gSpriteClipsAnim[2].x = 128;
		gSpriteClipsAnim[2].y = 0;
		gSpriteClipsAnim[2].w = 64;
		gSpriteClipsAnim[2].h = 205;

		gSpriteClipsAnim[3].x = 196;
		gSpriteClipsAnim[3].y = 0;
		gSpriteClipsAnim[3].w = 64;
		gSpriteClipsAnim[3].h = 205;
	}

	// Load front alpha texture
	if (!gModulatedTexture.loadFromFile("graphics/images/fadeout.png"))
	{
		printf("Failed to load front texture!\n");
		success = false;
	}
	else
	{
		// Set standard alpha blending
		gModulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	}

	// Load fade in background texture
	if (!gFadeInBackgroundTexture.loadFromFile("graphics/images/fadein.png"))
	{
		printf("Failed to load fade in background texture!\n");
		success = false;
	}

	return success;
}

void close()
{
	// Free loaded texture images
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;
	gFooTexture.free();
	gBackgroundTexture.free();

	/*
	// Deallocate surface
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_FreeSurface(gKeyPressSurfaces[i]);
		gKeyPressSurfaces[i] = NULL;
	}
	*/

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
	IMG_Quit();
}


SDL_Surface* loadSurface(std::string path)
{
	// The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else
	{
		
		// Convert surface to screen format
		// ex: 24 bit bitmap to whatever bit the display is
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize images %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}


SDL_Texture* loadTexture(std::string path)
{

	// The final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

