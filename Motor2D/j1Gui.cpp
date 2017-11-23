#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "InterfaceElement.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	SDL_Rect rect{ 485, 829, 328, 103 };
	AddSprite(InterfaceElement::SPRITE, { 10,10,10,10 }, atlas, true, rect);

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	p2List_item<Sprite*>* current_sprite = sprites.start;
	while (current_sprite != NULL)
	{
		current_sprite->data->PostUpdate();
		current_sprite = current_sprite->next;
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

InterfaceElement* j1Gui::AddInterface_Element(InterfaceElement::interfacetype type, SDL_Rect size, SDL_Texture* tex, bool enabled)
{
	InterfaceElement* aux = new InterfaceElement;
	aux->type = type;
	aux->collider = size;
	aux->tex = tex;
	aux->enabled = enabled;

	elements.add(aux);

	return aux;
}

Sprite* j1Gui::AddSprite(InterfaceElement::interfacetype type, SDL_Rect size, SDL_Texture* tex, bool enabled, SDL_Rect anim)
{
	Sprite* aux = new Sprite;
	aux->type = type;
	aux->collider = size;
	aux->tex = tex;
	aux->enabled = enabled;
	aux->idle_anim = anim;

	sprites.add(aux);

	return aux;
}
// class Gui ---------------------------------------------------

