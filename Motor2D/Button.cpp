#include "Button.h"
#include "j1Fonts.h"
#include "Label.h"
#include "Sprite.h"
#include "InterfaceElement.h"


Button::Button(uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, const char* font_path, int pSize, RenderMode mode, SDL_Rect* _hovered_anim, SDL_Rect* _pressed_anim)
{
	Sprite::rect.x = _x;
	Sprite::rect.y = _y;
	Sprite::rect.w = _anim->w;
	Sprite::rect.h = _anim->h;
	Label::rect.x = _x;
	Label::rect.y = _y;
	Label::rect.w = 0;
	Label::rect.h = 0;
	render_mode = mode;
	psize = pSize;
	path = font_path;
	Font* aux = App->font->Load(font_path, pSize);
	if (aux != nullptr)
		setFont(aux);
	else LOG("Could not load font: %s", font_path);

	Sprite::tex = _tex;
	Sprite::enabled = _enabled;
	Label::enabled = _enabled;

	if (_anim != NULL)
	{
		idle_anim = *_anim;
	}
	else
	{
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		SDL_QueryTexture(Sprite::tex, NULL, NULL, &rect.w, &rect.h);
		idle_anim = rect;
	}

	if (_hovered_anim == nullptr)
		hovered_anim = *_anim;
	else
		hovered_anim = *_hovered_anim;

	if (_pressed_anim == nullptr)
		pressed_anim = *_anim;
	else
		pressed_anim = *_pressed_anim;

	current_anim = &idle_anim;
}


Button::~Button()
{
}

void Button::OnHover()
{
	current_anim = &hovered_anim;
}
void Button::OnClick()
{
	current_anim = &pressed_anim;
}

bool Button::PostUpdate()
{
	App->render->Blit(Sprite::tex, Sprite::rect.x, Sprite::rect.y, false, current_anim);
	return true;
}