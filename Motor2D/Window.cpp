#include "Window.h"
#include "j1Input.h"
#include "j1Window.h"


Window::Window(uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim) : Sprite(_x,_y, _tex, _enabled, _anim)
{
}


Window::~Window()
{
}

bool Window::PostUpdate()
{
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT && in_focus == true/*prev_mouse.x != Mouse.x && prev_mouse.y != Mouse.y*/)
	{

		for (p2List_item<InterfaceElement*>* current_element = elements.start;
			current_element != nullptr;
			current_element = current_element->next)
		{
			current_element->data->rect.x = Mouse.x + delta_pos_mouse.x + (current_element->data->rect.x - rect.x);
			current_element->data->rect.y = Mouse.y + delta_pos_mouse.y + (current_element->data->rect.y - rect.y);
		}

		//DragWindow();
		rect.x = Mouse.x + delta_pos_mouse.x;
		rect.y = Mouse.y + delta_pos_mouse.y;

	}
	else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP && in_focus == true)
		App->gui->setFocus(nullptr);

	for (p2List_item<InterfaceElement*>* current_element = elements.start;
		current_element != nullptr;
		current_element = current_element->next)
	{
		current_element->data->PostUpdate();
	}

	current_anim = &idle_anim;
	App->render->Blit(tex, rect.x, rect.y, false, current_anim);
	return true;
}

bool Window::PreUpdate()
{
	prev_mouse = Mouse;
	App->input->GetMousePosition(Mouse.x, Mouse.y);
	Mouse.w = CURSOR_WIDTH;
	Mouse.h = CURSOR_WIDTH;

	SDL_Rect result;
	if (SDL_IntersectRect(&rect, &Mouse, &result) == SDL_TRUE)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			App->gui->setFocus(this);
			iPoint p = { rect.x, rect.y }, m = { Mouse.x, Mouse.y };
			delta_pos_mouse = p - m;
		}
	}

	for (p2List_item<InterfaceElement*>* current_element = elements.start;
		current_element != nullptr;
		current_element = current_element->next)
	{
		current_element->data->PreUpdate();
	}
	return true;
}

void Window::DragWindow()
{
	iPoint mousemove;
	App->input->GetMouseMotion(mousemove.x, mousemove.y);
	rect.x += mousemove.x;
	rect.y += mousemove.y;
}

Sprite* Window::AddSprite(float x, float y, SDL_Texture* tex, bool enabled, SDL_Rect* anim)
{
	Sprite* aux = new Sprite(x * rect.w, y * rect.h, tex, enabled, anim);

	elements.add(aux);
	return aux;
}

Label* Window::AddLabel(float x, float y, int psize, const char * font_path, SDL_Color color, Label::RenderMode mode, const char* format, ...)
{
	Label* aux = new Label(x * rect.w, y * rect.h, font_path, psize, mode);
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
	elements.add(aux);

	return aux;
}

Button* Window::AddButton(float _x, float _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, Callback_c callback,
	SDL_Rect* _hovered_anim, SDL_Rect* _pressed_anim, const char* font_path, int pSize, Label::RenderMode mode)
{
	Button* aux = new Button(_x * rect.w, _y * rect.h, _tex, _enabled, _anim, callback, _hovered_anim, _pressed_anim);

	if (_anim != nullptr) {
		_x += _anim->w / 2;
		_y += _anim->h / 2;
	}
	else if (_tex != nullptr) {
		int w, h;
		SDL_QueryTexture(_tex, nullptr, nullptr, &w, &h);
		_x += w / 2;
		_y += h / 2;
	}

	Label* label = new Label(_x * rect.w, _y * rect.h, font_path, pSize, mode);
	aux->setLabel(label);
	elements.add(aux);
	return aux;
}