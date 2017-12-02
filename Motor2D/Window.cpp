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

	prev_mouse = Mouse;
	App->input->GetMousePosition(Mouse.x, Mouse.y);
	Mouse.w = CURSOR_WIDTH;
	Mouse.h = CURSOR_WIDTH;

	SDL_Rect result;
	if (SDL_IntersectRect(&rect, &Mouse, &result) == SDL_TRUE)
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			locked = true;
			iPoint p = { rect.x, rect.y }, m = { Mouse.x, Mouse.y };
			delta_pos_mouse = p - m;
		}
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT && locked == true/*prev_mouse.x != Mouse.x && prev_mouse.y != Mouse.y*/)
	{
		//DragWindow();
		rect.x = Mouse.x + delta_pos_mouse.x;
		rect.y = Mouse.y + delta_pos_mouse.y;
	}
	else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP && locked == true)
		locked = false;

	current_anim = &idle_anim;
	App->render->Blit(tex, rect.x, rect.y, false, current_anim);
	return true;
}

void Window::DragWindow()
{
	iPoint mousemove;
	App->input->GetMouseMotion(mousemove.x, mousemove.y);
	rect.x += mousemove.x;
	rect.y += mousemove.y;
}

Sprite* Window::AddSprite(uint x, uint y, SDL_Texture* tex, bool enabled, SDL_Rect* anim)
{
	Sprite* aux = new Sprite(x, y, tex, enabled, anim);

	elements.add(aux);
	return aux;
}

Label* Window::AddLabel(int x, int y, int psize, const char * font_path, SDL_Color color, Label::RenderMode mode, const char* format, ...)
{
	Label* aux = new Label(x, y, font_path, psize, mode);
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

Button* Window::AddButton(uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, Callback_c callback,
	SDL_Rect* _hovered_anim, SDL_Rect* _pressed_anim, const char* font_path, int pSize, Label::RenderMode mode)
{
	Button* aux = new Button(_x, _y, _tex, _enabled, _anim, callback, _hovered_anim, _pressed_anim);

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

	Label* label = new Label(_x, _y, font_path, pSize, mode);
	aux->setLabel(label);
	elements.add(aux);
	return aux;
}