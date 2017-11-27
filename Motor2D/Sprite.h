#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "InterfaceElement.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"


class Sprite :
	public InterfaceElement
{
public:
	Sprite(InterfaceElement::interfacetype _type, uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim);
	~Sprite();
	bool PostUpdate() override;

	SDL_Rect idle_anim;
	SDL_Rect* current_anim;
};

#endif