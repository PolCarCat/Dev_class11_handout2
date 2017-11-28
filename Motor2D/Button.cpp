#include "Button.h"
#include "j1Fonts.h"
#include "Label.h"
#include "Sprite.h"
#include "InterfaceElement.h"


Button::Button(uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, const char* font_path, int pSize, RenderMode mode)
{
	Sprite::rect.x = _x;
	Sprite::rect.y = _y;
	Sprite::rect.w = 0;
	Sprite::rect.h = 0;
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
}


Button::~Button()
{
}

void Button::OnClick()
{

}

bool Button::PostUpdate()
{
	return true;
}