#include "InterfaceElement.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Gui.h"



InterfaceElement::InterfaceElement() : enabled(true), scale(App->win->GetScale())
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
	bool ret = true;

	for (p2List_item<InterfaceElement*>* current_element = elements.start;
		current_element != nullptr && ret == true;
		current_element = current_element->next)
	{
		ret = current_element->data->PostUpdate();
	}

	if (App->gui->debug_draw) {
		App->render->DrawQuad(rect, 0, 0, 255, 255, false, false);
		App->render->DrawLine(rect.x, rect.y + rect.h * anchor_point.y, rect.x + rect.w, rect.y + rect.h * anchor_point.y, 0, 0, 255, 255, false);
		App->render->DrawLine(rect.x + rect.w * anchor_point.x, rect.y, rect.x + rect.w * anchor_point.x, rect.y + rect.h, 0, 0, 255, 255, false);
	}

	return ret;
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

InterfaceElement::interfacetype InterfaceElement::getType() const
{
	return type;
}

void InterfaceElement::SetAnchor(float x, float y)
{
	/*rect.x += anchor_point.x * rect.w;
	rect.y += anchor_point.y * rect.h;*/

	anchor_point.x = x;
	anchor_point.y = y;

	rect.x -= anchor_point.x * rect.w;
	rect.y -= anchor_point.y * rect.h;
}

void InterfaceElement::GetAnchor(float & x, float & y) const
{
	x = anchor_point.x;
	y = anchor_point.y;
}

float InterfaceElement::GetAnchorX() const
{
	return anchor_point.x;
}

float InterfaceElement::GetAnchorY() const
{
	return anchor_point.y;
}

InterfaceElement * InterfaceElement::AddElement(InterfaceElement * elem)
{
	return elements.add(elem)->data;
}

void InterfaceElement::SetParent(InterfaceElement * parent)
{
	if (this->parent != nullptr)	// Erase the element from its previous parent if it already has one
	{
		int index = this->parent->elements.find(this);
		if (index > -1)
			this->parent->elements.del(this->parent->elements.At(index));
	}

	this->parent = parent;
	if (parent != nullptr)
	{
		parent->AddElement(this);
		rel_pos.x = rect.x - parent->rect.x;
		rel_pos.y = rect.y - parent->rect.y;
	}
	else {
		rel_pos.x = rect.x;
		rel_pos.y = rect.y;

		App->gui->AddElement(this);
	}
}

void InterfaceElement::SetFocus()
{
	p2List_item<IE*>* curr = parent->elements.start;

	while (curr != NULL)
	{
		curr->data->in_focus = false;
		curr = curr->next;
	}
	this->in_focus = true;
}