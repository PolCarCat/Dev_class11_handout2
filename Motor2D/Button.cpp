#include "Button.h"
#include "j1Fonts.h"
#include "InterfaceElement.h"
#include "j1Input.h"


Button::Button(uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, Callback_c callback, SDL_Rect* _hovered_anim, SDL_Rect* _pressed_anim)
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

	OnClick = callback;
}


Button::~Button()
{
}

void Button::OnHover()
{
}

bool Button::PreUpdate()
{
	return label->PreUpdate();
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
			label->setString("Left mouse button click");
			OnClick("Left mouse button click");
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
		{
			current_anim = &pressed_anim;
			label->setString("Right mouse button click");
			OnClick("Right mouse button click");
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_IDLE && App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_IDLE)
		{
			current_anim = &hovered_anim;
			label->setString("Hovered");
			OnHover();
		}
	}
	else
	{
		current_anim = &idle_anim;
		label->setString("Idle");
	}

	App->render->Blit(tex, rect.x, rect.y, false, current_anim);

	label->PostUpdate();
	return true;
}

void Button::setLabel(Label * label)
{
	this->label = label;
}
