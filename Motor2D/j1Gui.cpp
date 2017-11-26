#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "Sprite.h"

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
	//Labels
	p2List_item<Label*>* current_label = labels.start;
	while (current_label != NULL)
	{
		current_label->data->PreUpdate();
		current_label = current_label->next;
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	//Sprites
	p2List_item<Sprite*>* current_sprite = sprites.start;
	while (current_sprite != NULL)
	{
		current_sprite->data->PostUpdate();
		current_sprite = current_sprite->next;
	}

	//Labels
	p2List_item<Label*>* current_label = labels.start;
	while (current_label != NULL)
	{
		current_label->data->PostUpdate();
		current_label = current_label->next;
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
Label* j1Gui::AddLabel(int x, int y, int psize, const char * font_path, Label::FontColor color, const char* format, ...)
{
	Label* aux = new Label(x, y, font_path, psize, color);

	if (format != NULL)
	{
		va_list  ap;
		char buffer[TMP_STRING_SIZE];

		va_start(ap, format);
		int res = vsprintf_s(buffer, TMP_STRING_SIZE, format, ap);
		va_end(ap);

		if (res > 0) {
			aux->setString(buffer);
		}
	}
	labels.add(aux);

	return aux;
}
// class Gui ---------------------------------------------------

