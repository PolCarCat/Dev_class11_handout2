#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "InterfaceElement.h"
#include "Sprite.h"
#include "Label.h"

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
	InterfaceElement* AddInterface_Element(InterfaceElement::interfacetype type, SDL_Rect size, SDL_Texture* tex, bool enabled = true);
	Sprite* AddSprite(InterfaceElement::interfacetype type, SDL_Rect size, SDL_Texture* tex, bool enabled, SDL_Rect anim);
	Label* AddLabel(int x, int y, int psize, const char* font_path, Label::FontColor color, const char* string, ...);
	const SDL_Texture* GetAtlas() const;


private:
	p2List<InterfaceElement*> elements;
	p2List<Sprite*> sprites;
	p2List<Label*> labels;
	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__