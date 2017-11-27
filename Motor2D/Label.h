#ifndef __LABEL_H__
#define __LABEL_H__

#include "InterfaceElement.h"
#include "SDL_ttf\include\SDL_ttf.h"
#include "SDL\include\SDL_pixels.h"

typedef _TTF_Font Font;

class Label :
	public InterfaceElement
{
public:
	enum Alignment {
		CENTERED,
		LEFT,
		RIGHT
	};

	enum FontColor {
		COLOR_TRANSPARENT = -1,
		COLOR_WHITE,
		COLOR_BLACK,
		COLOR_GREY,
		COLOR_RED,
		COLOR_BLUE,
		COLOR_YELLOW,
		COLOR_GREEN,
		COLOR_BROWN,
		COLOR_ORANGE,
		COLOR_CYAN,
		COLOR_PURPLE,
		COLOR_PINK
	};

	Label();
	Label(int x, int y, const char* font_path, int pSize);
	~Label();

	bool Start() override;
	bool PreUpdate() override;
	bool PostUpdate() override;
	bool CleanUp() override;

	void setAlignment(Alignment alignment);
	Alignment getAlignment() const;
	void setColor(FontColor fg, FontColor bg = COLOR_TRANSPARENT);
	void getColor(FontColor* fg, FontColor* bg);
	void setString(const char* string, ...);
	void setString(p2SString string);
	void getString(const char* string) const;
	void getString(p2SString& string) const;
	void setFont(Font* font);
	void setFont(const char* font_path, int pSize);
	Font* getFont();

private:
	Font* font = nullptr;
	SDL_Color color_fg, color_bg;
	p2SString string;
	Alignment alignment;
	bool text_changed = false;
};

#endif