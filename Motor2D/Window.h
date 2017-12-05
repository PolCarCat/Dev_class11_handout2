#pragma once
#include "Sprite.h"
#include "Button.h"
#include "Label.h"
class Window :
	public Sprite
{
public:
	Window(uint _x = 0, uint _y = 0, SDL_Texture* _tex = nullptr, bool _enabled = false, SDL_Rect* _anim = nullptr);
	~Window();

	void DragWindow();
	bool PostUpdate() override;
	bool PreUpdate() override;

	Sprite* AddSprite(float x, float y, SDL_Texture* tex, bool enabled = true, SDL_Rect* anim = NULL);
	Label* AddLabel(float x, float y, int psize, const char* font_path, SDL_Color color, Label::RenderMode mode, const char* format, ...);
	Button* AddButton(float _x, float _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, Callback_c callback, SDL_Rect* _hovered_anim = nullptr,
		SDL_Rect* _pressed_anim = nullptr, const char* font_path = nullptr, int pSize = -1, Label::RenderMode mode = Label::BLENDED);

	void Focus();
	
	InterfaceElement* onfocus = nullptr;

	SDL_Rect Mouse;
	bool locked = false;
	iPoint delta_pos_mouse;
};

