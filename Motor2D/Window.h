#pragma once
#include "Sprite.h"
#include "Button.h"
#include "Label.h"
class Window :
	public Sprite
{
public:
	p2List<Button*> buttons;
	p2List<Label*> labels;
	Window(uint _x = 0, uint _y = 0, SDL_Texture* _tex = nullptr, bool _enabled = false, SDL_Rect* _anim = nullptr);
	~Window();
	void DragWindow();
	bool PostUpdate();
	SDL_Rect Mouse;
	SDL_Rect prev_mouse;
};

