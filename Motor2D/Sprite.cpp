#include "Sprite.h"
#include "j1Render.h"

Sprite::Sprite(uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim) : InterfaceElement()
{
	type = SPRITE;
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
		idle_anim.x = 0;
		idle_anim.y = 0;
		SDL_QueryTexture(tex, NULL, NULL, &idle_anim.w, &idle_anim.h);
	}

	rect.w = idle_anim.w;
	rect.h = idle_anim.h;

	current_anim = &idle_anim;
}


Sprite::~Sprite()
{
}

bool Sprite::PostUpdate()
{
	bool ret = InterfaceElement::PostUpdate();

	current_anim = &idle_anim;

	if (in_focus)
	App->render->Blit(tex, rect.x, rect.y, false, current_anim);
	return ret;
}
