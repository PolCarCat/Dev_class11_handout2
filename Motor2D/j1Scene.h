#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class Sprite;
class Label;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* debug_tex;
	Sprite* banner;
	Label* text;
	int i = 0;

	SDL_Texture* atlas;
	SDL_Texture* nasty_buttons;
	SDL_Texture* left_logo;
	SDL_Texture* right_logo;
	SDL_Texture* ESBR_logo;
};

#endif // __j1SCENE_H__