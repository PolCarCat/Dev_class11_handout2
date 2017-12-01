#include "InterfaceElement.h"
#include "j1Render.h"



InterfaceElement::InterfaceElement() : enabled(true)
{
}


InterfaceElement::~InterfaceElement()
{
}


bool InterfaceElement::Enable(bool enable)
{
	this->enabled = enable;
	return this->enabled;
}

bool InterfaceElement::isEnabled()
{
	return enabled;
}

bool InterfaceElement::Start()
{
	return true;
}

bool InterfaceElement::PreUpdate()
{
	return true;
}

bool InterfaceElement::PostUpdate()
{
	return true;
}

bool InterfaceElement::CleanUp()
{
	return true;
}

SDL_Rect InterfaceElement::getRect() const
{
	return rect;
}

int InterfaceElement::getPositionX() const
{
	return rect.x;
}

int InterfaceElement::getPositionY() const
{
	return rect.y;
}

void InterfaceElement::setPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void InterfaceElement::setPositionX(int x)
{
	rect.x = x;
}

void InterfaceElement::setPositionY(int y)
{
	rect.y = y;
}

void InterfaceElement::setScale(float scale)
{
	this->scale = scale;
}

float InterfaceElement::getScale() const
{
	return scale;
}

IE::interfacetype InterfaceElement::getType() const
{
	return type;
}
