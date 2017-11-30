#include "Button.h"
#include "j1Fonts.h"
#include "InterfaceElement.h"
#include "j1Input.h"


Button::Button(uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, void (*Click)(const char*), SDL_Rect* _hovered_anim, SDL_Rect* _pressed_anim)
	: Sprite(_x, _y, _tex, _enabled, _anim)
{
	type = BUTTON;

	if (_hovered_anim == nullptr)
		hovered_anim = *_anim;
	else
		hovered_anim = *_hovered_anim;

	if (_pressed_anim == nullptr)
		pressed_anim = *_anim;
	else
		pressed_anim = *_pressed_anim;

	current_anim = &idle_anim;

	OnClick = Click;
}


Button::~Button()
{
}

void Button::OnHover()
{
	//LOG("Hover");
}


bool Button::PostUpdate()
{
	SDL_Rect Mouse;
	App->input->GetMousePosition(Mouse.x, Mouse.y);
	Mouse.w = CURSOR_WIDTH;
	Mouse.h = CURSOR_WIDTH;

	SDL_Rect result;
	if (SDL_IntersectRect(&rect, &Mouse, &result) == SDL_TRUE)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			current_anim = &pressed_anim;
			OnClick("Clicked!");
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_IDLE)
		{
			current_anim = &hovered_anim;
			OnHover();
		}
		
	}
	else
	{
		current_anim = &idle_anim;
	}

	App->render->Blit(tex, rect.x, rect.y, false, current_anim);
	return true;
}

void Button::setLabel(Label * label)
{
	this->label = label;
}
