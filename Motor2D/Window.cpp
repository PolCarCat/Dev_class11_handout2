#include "Window.h"
#include "j1Input.h"


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
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT && prev_mouse.x != Mouse.x && prev_mouse.y != Mouse.y)
		{
			DragWindow();
		}
	}

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