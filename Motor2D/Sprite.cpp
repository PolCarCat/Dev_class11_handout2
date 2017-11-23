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
	App->render->Blit(tex, position.x, position.y, current_anim);
}
