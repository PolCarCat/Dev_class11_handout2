#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "InterfaceElement.h"
#include "Sprite.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	InterfaceElement* AddInterface_Element(InterfaceElement::interfacetype type, fPoint pos, SDL_Rect size, SDL_Texture* tex, bool enabled = true);
	Sprite* AddSprite(InterfaceElement::interfacetype type, fPoint pos, SDL_Rect size, SDL_Texture* tex, bool enabled, SDL_Rect anim);
	const SDL_Texture* GetAtlas() const;


private:
	p2List<InterfaceElement*> elements;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__