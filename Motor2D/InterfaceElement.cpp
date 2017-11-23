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
}

bool InterfaceElement::Start()
{

}

bool InterfaceElement::PreUpdate()
{

}

bool InterfaceElement::PostUpdate()
{

}

bool InterfaceElement::CleanUp()
{

}