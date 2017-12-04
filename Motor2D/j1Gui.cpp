#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Window.h"
#include "Sprite.h"
#include "Button.h"
#include "Window.h"

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

	App->win->GetWindowSize(gui_size.x, gui_size.y);
	scale = App->win->GetScale();

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	//Labels
	p2List_item<InterfaceElement*>* current_element = elements.start;
	while (current_element != NULL)
	{
		if (current_element->data->isEnabled())
			current_element->data->PreUpdate();
		current_element = current_element->next;
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	//Sprites
	/*p2List_item<Sprite*>* current_sprite = sprites.start;
	while (current_sprite != NULL)
	{
		if (current_sprite->data->enabled)
			current_sprite->data->PostUpdate();
		current_sprite = current_sprite->next;
	}

	//Labels
	p2List_item<Label*>* current_label = labels.start;
	while (current_label != NULL)
	{
		if (current_label->data->enabled)
			current_label->data->PostUpdate();
		current_label = current_label->next;
	}*/

	p2List_item<InterfaceElement*>* current_element = elements.start;
	while (current_element != NULL)
	{
		if (current_element->data->isEnabled())
			current_element->data->PostUpdate();
		current_element = current_element->next;
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
	return nullptr;
}

uiPoint j1Gui::GetGuiSize()
{
	return gui_size;
}

void j1Gui::setFocus(InterfaceElement * elem)
{
	if (focused_item != nullptr)
		focused_item->in_focus = false;
	focused_item = elem;
	if (focused_item != nullptr)
		focused_item->in_focus = true;
}

InterfaceElement * j1Gui::getFocusedItem()
{
	return focused_item;
}

InterfaceElement * j1Gui::AddElement(InterfaceElement * elem)
{
	if (elements.find(elem) < 0)
		elements.add(elem);

	return elem;
}

Sprite* j1Gui::AddSprite(float x, float y, SDL_Texture* tex, bool enabled, SDL_Rect* anim, InterfaceElement* parent)
{
	uint w = (parent == nullptr) ? gui_size.x : parent->rect.w;
	uint h = (parent == nullptr) ? gui_size.y : parent->rect.h;

	Sprite* aux = new Sprite(x * w / scale, y * h / scale, tex, enabled, anim);

	if (parent != nullptr)
		aux->SetParent(parent);
	else elements.add(aux);
	return aux;
}

Label* j1Gui::AddLabel(float x, float y, int psize, InterfaceElement* parent, const char * font_path, SDL_Color color, Label::RenderMode mode, const char* format, ...)
{
	uint w = (parent == nullptr) ? gui_size.x / scale : parent->rect.w;
	uint h = (parent == nullptr) ? gui_size.y / scale : parent->rect.h;

	Label* aux = new Label(x * w, y * h, font_path, psize, mode);
	aux->setColor(color);

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

	if (parent != nullptr)
		aux->SetParent(parent);
	else elements.add(aux);
	return aux;
}

Button* j1Gui::AddButton(float _x, float _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, Callback_c callback, SDL_Rect* _hovered_anim, SDL_Rect* _pressed_anim, InterfaceElement* parent)
{
	uint w = (parent == nullptr) ? gui_size.x / scale : parent->rect.w;
	uint h = (parent == nullptr) ? gui_size.y / scale : parent->rect.h;

	Button* aux = new Button(_x * w, _y * h, _tex, _enabled, _anim, callback, _hovered_anim, _pressed_anim);

	if (parent != nullptr)
		aux->SetParent(parent);
	else elements.add(aux);
	return aux;
}

Window* j1Gui::AddWindow(float x, float y, SDL_Texture* tex, bool enabled, SDL_Rect* anim, InterfaceElement* parent)
{
	uint w = (parent == nullptr) ? gui_size.x / scale : parent->rect.w;
	uint h = (parent == nullptr) ? gui_size.y / scale : parent->rect.h;

	Window* aux = new Window(x * w, y * h, tex, enabled, anim);

	if (parent != nullptr)
		aux->SetParent(parent);
	else elements.add(aux);
	return aux;
}
// class Gui ---------------------------------------------------
