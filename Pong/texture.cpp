#include "texture.h"

//so this part makes a texture to do all the fancy things with
texture::texture()
{
	//The initial texture and height/width which is nothing
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

texture::~texture()
{
	//deallocates the texture
	free();
}

//this part returns true or false if the texture can be loaded
bool texture::loadFromFile( std::string path)
{
	//get rid of preexisting texture
	free();

	//we create a pointer to grab the new texture
	SDL_Texture* newTexture = NULL;

	//now we load the image into loaded surface
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	//check if problem with pullingin the image
	if (loadedSurface = NULL)
	{
		cout << "Unable to load image" << path.c_str() << "SDL Error: " << SDL_GetError() << endl;
	}

	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to create texture" << path.c_str() << "SDL Error :" << SDL_GetError() << endl;
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	/*put new texture into mtexture pointer and then return
	and return that its a success*/
	mTexture = newTexture;
	return mTexture != NULL;
}