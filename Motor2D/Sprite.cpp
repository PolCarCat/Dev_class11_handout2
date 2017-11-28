#include "Sprite.h"
#include "j1Render.h"

Sprite::Sprite(InterfaceElement::interfacetype _type, uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim) :InterfaceElement()
{
	type = _type;
	tex = _tex;
	rect.x = _x;
	rect.y = _y;
	rect.w = 0;
	rect.h = 0;
	enabled = _enabled;

	if (_anim != NULL)
	{
		idle_anim = *_anim;
	}
	else
	{
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
		idle_anim = rect;
	}

}


Sprite::~Sprite()
{
}

bool Sprite::PostUpdate()
{
	current_anim = &idle_anim;
	App->render->Blit(tex, rect.x, rect.y,false, current_anim);
	return true;
}
