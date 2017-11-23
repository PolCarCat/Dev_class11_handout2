#pragma once
#include "InterfaceElement.h"
#include "SDL_ttf\include\SDL_ttf.h"

class Label :
	public InterfaceElement
{
public:
	Label();
	~Label();

	bool Start() override;
	bool PreUpdate() override;
	bool PostUpdate() override;
	bool CleanUp() override;

private:
	_TTF_Font* font;
};

