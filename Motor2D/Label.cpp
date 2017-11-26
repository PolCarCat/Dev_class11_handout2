#include "Label.h"
#include "j1Fonts.h"
#include "SDL\include\SDL.h"


Label::Label() : InterfaceElement()
{
}

Label::Label(int x, int y, const char* font_path, int pSize, FontColor color) : InterfaceElement()
{
	collider.x = x;
	collider.y = y;
	collider.w = 0;
	collider.h = 0;
	setFont(App->font->Load(font_path, pSize));
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
	bool ret = true;
	if (font != nullptr && text_changed) {
		SDL_Color fg, bg;
		fg.r = 255;
		fg.g = 255;
		fg.b = 255;
		fg.a = 255;

		bg.r = 0;
		bg.g = 0;
		bg.b = 0;
		bg.a = 0;
		
		if (tex != nullptr)
			SDL_DestroyTexture(tex);

		SDL_Surface* temp = TTF_RenderText_Blended(font, string.GetString(), fg);

		if (temp != nullptr) {
			tex = SDL_CreateTextureFromSurface(App->render->renderer, temp);
			SDL_FreeSurface(temp);
			temp = nullptr;
		}
		else {
			LOG("Error creating texture from font surface: %s", SDL_GetError());
			ret = false;
		}
		text_changed = false;
	}
	return ret;
}

bool Label::PostUpdate()
{
	if (font != nullptr) {
		App->render->Blit(tex, collider.x, collider.y, false);
	}
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

void Label::setString(const char* format, ...)
{
	if (format != NULL)
	{
		static va_list  ap;
		static char tmp[TMP_STRING_SIZE];

		va_start(ap, format);
		int res = vsnprintf_s(tmp, TMP_STRING_SIZE, format, ap);
		va_end(ap);

		if (res > 0)
			string.create(tmp);

		text_changed = true;
	}
}

void Label::setString(p2SString string)
{
	this->string = string;
	text_changed = true;
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
	text_changed = true;
}

void Label::setFont(const char* font_path, int pSize)
{
	font = App->font->Load(font_path, pSize);
	text_changed = true;
}

Font* Label::getFont()
{
	return font;
}