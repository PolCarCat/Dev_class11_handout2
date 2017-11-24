#include "Label.h"
#include "j1Fonts.h"


Label::Label() : InterfaceElement()
{
}

Label::Label(iPoint pos, const char* font_path, int pSize, FontColor color) : InterfaceElement()
{
	this->collider = { pos.x, pos.y, 0, 0 };
	setFont(App->font->Load(font_path, pSize));
	Enable(true);
	//this->color = color;
}

Label::~Label()
{

}


bool Label::Start()
{
	return true;
}

bool Label::PreUpdate()
{
	return true;
}

bool Label::PostUpdate()
{
	TTF_RenderText_Shaded(font, string.GetString(), { 255, 255, 255, 255 }, { 0, 0, 0, 0 });
	return true;
}

bool Label::CleanUp()
{
	return true;
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

void Label::setFont(const char* font_path, int pSize)
{
	font = App->font->Load(font_path, pSize);
}

Font* Label::getFont()
{
	return font;
}