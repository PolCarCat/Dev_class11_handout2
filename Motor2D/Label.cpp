#include "Label.h"



Label::Label() : InterfaceElement()
{
}

Label::Label(const char* font_path, int pSize) : InterfaceElement()
{
	font = TTF_OpenFont(font_path, pSize); // Needs to be closed (?)
}

Label::~Label()
{

}


bool Label::Start()
{

}

bool Label::PreUpdate()
{

}

bool Label::PostUpdate()
{

}

bool Label::CleanUp()
{

}

void Label::setAlignment(Label::Alignment alignment)
{
	this->alignment = alignment;
}

Label::Alignment Label::getAlignment() const
{
	return alignment;
}

void Label::setText(const char* string, ...)
{
	if (string != NULL)
	{
		static va_list  ap;

		// Construct the string from variable arguments
		va_start(ap, string);
		this->string.create(string, ap);
		va_end(ap);
	}
}

void Label::setText(p2SString string)
{
	this->string = string;
}

void Label::getString(const char* string) const
{
	string = this->string.GetString();
}

void Label::getString(p2SString& string) const
{
	string = this->string;
}

void Label::setFont(Font* font)
{
	this->font = font;
}

Font* Label::getFont()
{
	return font;
}