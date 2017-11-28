#include "Button.h"
#include "j1Fonts.h"
#include "InterfaceElement.h"
#include "j1Input.h"


Button::Button(uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, SDL_Rect* _hovered_anim, SDL_Rect* _pressed_anim) : Sprite()
{
	rect.x = _x;
	rect.y = _y;
	rect.w = _anim->w;
	rect.h = _anim->h;
	tex = _tex;
	enabled = _enabled;

	if (_anim != NULL) {
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
	SDL_Rect Mouse;
	App->input->GetMousePosition(Mouse.x, Mouse.y);
	Mouse.w = CURSOR_WIDTH;
	Mouse.h = CURSOR_WIDTH;

	SDL_Rect result;
	if ((bool)SDL_IntersectRect(&rect, &Mouse, &result))
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN || App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			current_anim = &pressed_anim;
		else
			current_anim = &hovered_anim;
	}
	else
	{
		current_anim = &idle_anim;
	}

	App->render->Blit(Sprite::tex, Sprite::rect.x, Sprite::rect.y, false, current_anim);
	return true;
}

void Button::setLabel(Label * label)
{
	label = label;
}
