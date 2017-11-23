#pragma once
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"

class InterfaceElement
{
public:
	InterfaceElement();
	~InterfaceElement();
	enum interfacetype
	{
		BUTTON,
		LABEL,
		SPRITE,
		TEXT_INPUT,
		CHECK_BUTTON
	};


	virtual bool Start() { return true; }
	virtual bool PreUpdate() { return true; }
	virtual bool PostUpdate();
	virtual bool CleanUp() { return true; }
	virtual bool Enable() { return true; }

	SDL_Rect collider;
	float scale;
	SDL_Texture* tex;
	interfacetype type;
	bool enabled;


};

