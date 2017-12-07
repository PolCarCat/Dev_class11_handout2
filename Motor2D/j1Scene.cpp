#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "Window.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	// TODO 3: Create the banner (rect {485, 829, 328, 103}) and the text "Hello World"
	atlas = App->tex->Load(App->gui->atlas_file_name.GetString());
	left_logo = App->tex->Load("wow/Glues-Logo-Left.png");
	right_logo = App->tex->Load("wow/Glues-Logo-Right.png");
	ESBR_logo = App->tex->Load("wow/Glues-ESRBRating.png");
	nasty_buttons = App->tex->Load("textures/buttons.png");

	SDL_Rect rect{ 485, 829, 328, 103 };
	//AddSprite({ 10,10,10,10 }, atlas, true, rect);

	App->gui->AddSprite(0.5f * App->gui->GetGuiSize().x / App->win->GetScale(), 0.85f * App->gui->GetGuiSize().y / App->win->GetScale(), ESBR_logo);


	int win_x, win_y;
	win_x = 0.5f * App->gui->GetGuiSize().x / App->win->GetScale();
	win_y = 0.5f * App->gui->GetGuiSize().y / App->win->GetScale();
	SDL_Texture* gui_atlas = App->tex->Load("gui/atlas.png");
	int tex_w, tex_h;
	App->render->GetTextureDimensions(gui_atlas, &tex_w, &tex_h);
	SDL_Rect win_rect{ 0, 512, 484, 512 };
	Window* win = App->gui->AddWindow(win_x, win_y, gui_atlas, true, &win_rect);
	win->SetAnchor(0.5f, 0.5f);

	/*banner = App->gui->AddSprite(1.0f * win->rect.w, 0.0f * win->rect.h, right_logo, true, nullptr);
	banner->SetParent(win);
	banner->SetAnchor(0.5f, 0.5f);*/

	text->SetParent(win);
	text->SetAnchor(0.5f, 0.5f);

	SDL_Rect idle{ 0, 110, 230, 71 };
	SDL_Rect hovered{ 411, 166, 230, 71 };
	SDL_Rect pressed{ 641, 166, 230, 71 };

	Button* button = nullptr;

	for (uint i = 0; i < 4; i++)
	{
		button = App->gui->AddButton(0.0f * win->rect.w, (-0.3 + 0.2f*i) * win->rect.h, gui_atlas, true, &idle, &doSomething, &hovered, &pressed);
		button->SetParent(win);
		button->SetAnchor(0.5f, 0.5f);

		text = App->gui->AddLabel((0.5f - button->GetAnchorX()) * button->rect.w, (0.5f - button->GetAnchorY()) * button->rect.h,
			30, "fonts/open_sans/OpenSans-Bold.ttf", { 200, 200, 200, 255 }, Label::RenderMode::BLENDED, "Button #%d", i);
		text->SetParent(button);
		text->SetAnchor(0.5f, 0.5f);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		/*
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}*/
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
	{
		/*
		if(origin_selected == true)
		{
		App->pathfinding->CreatePath(origin, p);
		origin_selected = false;
		}
		else
		{
		origin = p;
		origin_selected = true;
		}*/
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---
	//if (i > 999) i = 0; //Proves de memoria a les labels
	//text->setSize(i++);
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		//App->render->camera.x -= floor(200.0f * dt);
		banner->SetAnchor(banner->GetAnchorX() - 0.1f, banner->GetAnchorY());
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->gui->debug_draw = !App->gui->debug_draw;




	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	//App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void doSomething(const char* message)
{
	LOG("%s", message);
	//App->render->ShakeIt(1.0f, 10);
}