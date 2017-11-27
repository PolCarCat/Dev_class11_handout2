#include "Sprite.h"
#include "j1Render.h"

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

bool Sprite::PostUpdate()
{
	current_anim = &idle_anim;
	App->render->Blit(tex, rect.x, rect.y,false, current_anim);
	return true;
}
