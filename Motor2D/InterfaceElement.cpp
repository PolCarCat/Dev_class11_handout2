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