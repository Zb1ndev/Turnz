#include "input.h"
#include "../application/application.h"

SDL_Event Input::event;
const Uint8* Input::keyboadStateArray;
glm::vec2 Input::mousePosition;
std::map<Input::KeyCode, bool> Input::keyStates;

glm::vec2 Input::MousePosToViewPort() {

	int windowX, windowY;
	SDL_GetWindowPosition(Application::instance->window, &windowX, &windowY);

	return glm::vec2(
		((Input::mousePosition.x / Application::instance->width) * 2) - 1,
		((-Input::mousePosition.y / Application::instance->height) * 2) + 1
	);

}

void Input::InitKeyStates() {
	keyStates = std::map<KeyCode, bool>{

		{Input::QUIT, false}, {Input::ANY, false}, {Input::TAB, false},
		{Input::BACKSPACE, false}, {Input::SPACE, false},
		{Input::ENTER, false}, {Input::ESCAPE, false},

		{Input::ALPHA_0, false}, {Input::ALPHA_1, false}, {Input::ALPHA_2, false},
		{Input::ALPHA_3, false}, {Input::ALPHA_4, false}, {Input::ALPHA_5, false}, 
		{Input::ALPHA_6, false}, {Input::ALPHA_7, false}, {Input::ALPHA_8, false}, 
		{Input::ALPHA_9, false}, 
		
		{Input::LEFT_ALT, false}, {Input::LEFT_CONTROL, false}, {Input::LEFT_SHIFT, false},
		{Input::RIGHT_ALT, false}, {Input::RIGHT_CONTROL, false}, {Input::RIGHT_SHIFT, false}, 

		{Input::UP, false}, {Input::DOWN, false}, {Input::LEFT, false}, {Input::RIGHT, false},

		{Input::A, false},{Input::B, false},{Input::C, false},{Input::D, false},{Input::E, false},
		{Input::F, false},{Input::G, false},{Input::H, false},{Input::I, false},{Input::J, false},
		{Input::K, false},{Input::L, false},{Input::M, false},{Input::N, false},{Input::O, false},
		{Input::P, false},{Input::Q, false},{Input::R, false},{Input::S, false},{Input::T, false},
		{Input::U, false},{Input::V, false},{Input::W, false},{Input::X, false},{Input::Y, false},
		{Input::Z, false}

	};
}
void Input::UpdateInput() {

	Input::keyboadStateArray = SDL_GetKeyboardState(NULL);
	SDL_PollEvent(&Input::event);

	int x, y;
	SDL_GetMouseState(&x, &y);
	mousePosition.x = x;
	mousePosition.y = y;

	keyStates[ANY] = (event.type == SDL_KEYDOWN);
	keyStates[QUIT] = (event.type == SDL_QUIT);

	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {

		keyStates[ENTER] = keyboadStateArray[SDL_SCANCODE_RETURN];
		keyStates[BACKSPACE] = keyboadStateArray[SDL_SCANCODE_BACKSPACE];
		keyStates[SPACE] = keyboadStateArray[SDL_SCANCODE_SPACE];
		keyStates[TAB] = keyboadStateArray[SDL_SCANCODE_TAB];
		keyStates[ESCAPE] = keyboadStateArray[SDL_SCANCODE_ESCAPE];
			
		keyStates[LEFT_SHIFT] = keyboadStateArray[SDL_SCANCODE_LSHIFT];
		keyStates[LEFT_CONTROL] = keyboadStateArray[SDL_SCANCODE_LCTRL];
		keyStates[LEFT_ALT] = keyboadStateArray[SDL_SCANCODE_LALT];
		keyStates[LEFT] = keyboadStateArray[SDL_SCANCODE_LEFT];

		keyStates[RIGHT_SHIFT] = keyboadStateArray[SDL_SCANCODE_RSHIFT];
		keyStates[RIGHT_CONTROL] = keyboadStateArray[SDL_SCANCODE_RCTRL];
		keyStates[RIGHT_ALT] = keyboadStateArray[SDL_SCANCODE_RALT];
		keyStates[RIGHT] = keyboadStateArray[SDL_SCANCODE_RIGHT];

		keyStates[ALPHA_0] = keyboadStateArray[SDL_SCANCODE_0];
		keyStates[ALPHA_1] = keyboadStateArray[SDL_SCANCODE_1];
		keyStates[ALPHA_2] = keyboadStateArray[SDL_SCANCODE_2];
		keyStates[ALPHA_3] = keyboadStateArray[SDL_SCANCODE_3];
		keyStates[ALPHA_4] = keyboadStateArray[SDL_SCANCODE_4];
		keyStates[ALPHA_5] = keyboadStateArray[SDL_SCANCODE_5];
		keyStates[ALPHA_6] = keyboadStateArray[SDL_SCANCODE_6];
		keyStates[ALPHA_7] = keyboadStateArray[SDL_SCANCODE_7];
		keyStates[ALPHA_8] = keyboadStateArray[SDL_SCANCODE_8];
		keyStates[ALPHA_9] = keyboadStateArray[SDL_SCANCODE_9];

		keyStates[A] = keyboadStateArray[SDL_SCANCODE_A];
		keyStates[B] = keyboadStateArray[SDL_SCANCODE_B];
		keyStates[C] = keyboadStateArray[SDL_SCANCODE_C];
		keyStates[D] = keyboadStateArray[SDL_SCANCODE_D];
		keyStates[E] = keyboadStateArray[SDL_SCANCODE_E];
		keyStates[F] = keyboadStateArray[SDL_SCANCODE_F];
		keyStates[G] = keyboadStateArray[SDL_SCANCODE_G];
		keyStates[H] = keyboadStateArray[SDL_SCANCODE_H];
		keyStates[I] = keyboadStateArray[SDL_SCANCODE_I];
		keyStates[J] = keyboadStateArray[SDL_SCANCODE_J];
		keyStates[K] = keyboadStateArray[SDL_SCANCODE_K];
		keyStates[L] = keyboadStateArray[SDL_SCANCODE_L];
		keyStates[M] = keyboadStateArray[SDL_SCANCODE_M];
		keyStates[N] = keyboadStateArray[SDL_SCANCODE_N];
		keyStates[O] = keyboadStateArray[SDL_SCANCODE_O];
		keyStates[P] = keyboadStateArray[SDL_SCANCODE_P];
		keyStates[Q] = keyboadStateArray[SDL_SCANCODE_Q];
		keyStates[R] = keyboadStateArray[SDL_SCANCODE_R];
		keyStates[S] = keyboadStateArray[SDL_SCANCODE_S];
		keyStates[T] = keyboadStateArray[SDL_SCANCODE_T];
		keyStates[U] = keyboadStateArray[SDL_SCANCODE_U];
		keyStates[V] = keyboadStateArray[SDL_SCANCODE_V];
		keyStates[W] = keyboadStateArray[SDL_SCANCODE_W];
		keyStates[X] = keyboadStateArray[SDL_SCANCODE_X];
		keyStates[Y] = keyboadStateArray[SDL_SCANCODE_Y];
		keyStates[Z] = keyboadStateArray[SDL_SCANCODE_Z];

	}

}
