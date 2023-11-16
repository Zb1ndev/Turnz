#include <SDL2/SDL.h>
#include "input.h"

bool Input::GetInput(Input::KeyCode key) {

	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (key) {
			// App Buttons
			case Input::KeyCode::QUIT:
				return event.type == SDL_QUIT;
			case Input::KeyCode::ANY:
				return event.type == SDL_KEYDOWN;
			// Keyboard Input
			case Input::KeyCode::RIGHT_ALT:
				return event.key.keysym.sym == SDLK_RALT;
			case Input::KeyCode::LEFT_ALT:
				return event.key.keysym.sym == SDLK_LALT;
			case Input::KeyCode::ENTER:
				return event.key.keysym.sym == SDLK_RETURN;
			case Input::KeyCode::TAB:
				return event.key.keysym.sym == SDLK_TAB;
			case Input::KeyCode::BACKSPACE:
				return event.key.keysym.sym == SDLK_BACKSPACE;
			case Input::KeyCode::SPACE:
				return event.key.keysym.sym == SDLK_SPACE;
			case Input::KeyCode::ESCAPE:
				return event.key.keysym.sym == SDLK_ESCAPE;
			case Input::KeyCode::UP:
				return event.key.keysym.sym == SDLK_UP;
			case Input::KeyCode::DOWN:
				return event.key.keysym.sym == SDLK_DOWN;
			case Input::KeyCode::LEFT:
				return event.key.keysym.sym == SDLK_LEFT;
			case Input::KeyCode::RIGHT:
				return event.key.keysym.sym == SDLK_RIGHT;
			case Input::KeyCode::RIGHT_SHIFT:
				return event.key.keysym.sym == SDLK_RSHIFT;
			case Input::KeyCode::LEFT_SHIFT:
				return event.key.keysym.sym == SDLK_LSHIFT;
			case Input::KeyCode::RIGHT_CONTROL:
				return event.key.keysym.sym == SDLK_RCTRL;
			case Input::KeyCode::LEFT_CONTROL:
				return event.key.keysym.sym == SDLK_LCTRL;
			case Input::KeyCode::ALPHA_0:
				return event.key.keysym.sym == SDLK_0;
			case Input::KeyCode::ALPHA_1:
				return event.key.keysym.sym == SDLK_1;
			case Input::KeyCode::ALPHA_2:
				return event.key.keysym.sym == SDLK_2;
			case Input::KeyCode::ALPHA_3:
				return event.key.keysym.sym == SDLK_3;
			case Input::KeyCode::ALPHA_4:
				return event.key.keysym.sym == SDLK_4;
			case Input::KeyCode::ALPHA_5:
				return event.key.keysym.sym == SDLK_5;
			case Input::KeyCode::ALPHA_6:
				return event.key.keysym.sym == SDLK_6;
			case Input::KeyCode::ALPHA_7:
				return event.key.keysym.sym == SDLK_7;
			case Input::KeyCode::ALPHA_8:
				return event.key.keysym.sym == SDLK_8;
			case Input::KeyCode::ALPHA_9:
				return event.key.keysym.sym == SDLK_9;
			case Input::KeyCode::A:
				return event.key.keysym.sym == SDLK_a;
			case Input::KeyCode::B:
				return event.key.keysym.sym == SDLK_b;
			case Input::KeyCode::C:
				return event.key.keysym.sym == SDLK_c;
			case Input::KeyCode::D:
				return event.key.keysym.sym == SDLK_d;
			case Input::KeyCode::E:
				return event.key.keysym.sym == SDLK_e;
			case Input::KeyCode::F:
				return event.key.keysym.sym == SDLK_f;
			case Input::KeyCode::G:
				return event.key.keysym.sym == SDLK_g;
			case Input::KeyCode::H:
				return event.key.keysym.sym == SDLK_h;
			case Input::KeyCode::I:
				return event.key.keysym.sym == SDLK_i;
			case Input::KeyCode::J:
				return event.key.keysym.sym == SDLK_j;
			case Input::KeyCode::K:
				return event.key.keysym.sym == SDLK_k;
			case Input::KeyCode::L:
				return event.key.keysym.sym == SDLK_l;
			case Input::KeyCode::M:
				return event.key.keysym.sym == SDLK_m;
			case Input::KeyCode::N:
				return event.key.keysym.sym == SDLK_n;
			case Input::KeyCode::O:
				return event.key.keysym.sym == SDLK_o;
			case Input::KeyCode::P:
				return event.key.keysym.sym == SDLK_p;
			case Input::KeyCode::Q:
				return event.key.keysym.sym == SDLK_q;
			case Input::KeyCode::R:
				return event.key.keysym.sym == SDLK_r;
			case Input::KeyCode::S:
				return event.key.keysym.sym == SDLK_s;
			case Input::KeyCode::T:
				return event.key.keysym.sym == SDLK_t;
			case Input::KeyCode::U:
				return event.key.keysym.sym == SDLK_u;
			case Input::KeyCode::V:
				return event.key.keysym.sym == SDLK_v;
			case Input::KeyCode::W:
				return event.key.keysym.sym == SDLK_w;
			case Input::KeyCode::X:
				return event.key.keysym.sym == SDLK_x;
			case Input::KeyCode::Y:
				return event.key.keysym.sym == SDLK_y;
			case Input::KeyCode::Z:
				return event.key.keysym.sym == SDLK_z;
		}
	}
	else { return false; }
		
}