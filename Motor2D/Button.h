
#include "Sprite.h"
#include "Label.h"

class Button :

	public Label,
	public Sprite
{
public:
	Button(uint _x, uint _y, SDL_Texture* _tex, bool _enabled, SDL_Rect* _anim, const char* font_path, int pSize, RenderMode mode, SDL_Rect* _hovered_anim = nullptr, SDL_Rect* _pressed_anim = nullptr);
	~Button();
	
	enum STATE {
		IDLE,
		PRESSED,
		HOVERED,
		DISABLED
	}state;

	SDL_Rect pressed_anim;
	SDL_Rect hovered_anim;
	SDL_Rect disalbed_anim;


	void OnHover();
	void OnClick();
	bool PostUpdate();

};
