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
	App->render->Blit(tex, collider.x, collider.y, current_anim);
	return true;
}
