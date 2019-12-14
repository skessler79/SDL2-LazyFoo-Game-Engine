#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
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

// Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

// The window renderer
SDL_Renderer* gRenderer = NULL;

// Loads individual image
SDL_Surface* loadSurface(std::string path);

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// The images that correspond to a keypress
// SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// The textures that correspond to a keypress
SDL_Texture* gKeyPressTextures[KEY_PRESS_TEXTURE_TOTAL];

// Current displayed image
SDL_Surface* gCurrentSurface = NULL;

// Current displayed texture
SDL_Texture* gTexture = NULL;

// Test stretched image
SDL_Texture* gStretchedTexture = NULL;

// Test PNG image
SDL_Surface* gPNGSurface = NULL;

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

			// Set default current surface
			gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT];

			/// MAIN LOOP
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
						default:
							gTexture = gKeyPressTextures[KEY_PRESS_TEXTURE_DEFAULT];
							break;
						}
					}
				}

				// Apply the image
				//SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

				// Update the surface
				//SDL_UpdateWindowSurface(gWindow);

				

				// Update Screen
				SDL_RenderPresent(gRenderer);
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
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
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

	return success;
}

void close()
{
	// Free loaded texture images
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

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