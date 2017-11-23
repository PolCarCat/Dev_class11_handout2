#ifndef __LABEL_H__
#define __LABEL_H__

#include "InterfaceElement.h"
#include "SDL_ttf\include\SDL_ttf.h"

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

	Label();
	Label(const char* font_path, int pSize);
	~Label();

	bool Start() override;
	bool PreUpdate() override;
	bool PostUpdate() override;
	bool CleanUp() override;

	void setAlignment(Alignment alignment);
	Alignment getAlignment() const;
	void setText(const char* string, ...);
	void setText(p2SString string);
	void getString(const char* string) const;
	void getString(p2SString& string) const;
	void setFont(Font* font);
	void setFont(const char* font_path, int pSize);
	Font* getFont();

private:
	Font* font = nullptr;
	p2SString string;
	Alignment alignment;
};

#endif