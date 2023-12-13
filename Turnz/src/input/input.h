#pragma once
#include <SDL2/SDL.h>
#include <map>

class Input {
public:
	
	enum KeyCode {
		QUIT, ANY,
		A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
		ALPHA_1, ALPHA_2, ALPHA_3, ALPHA_4, ALPHA_5, ALPHA_6, ALPHA_7, ALPHA_8, ALPHA_9, ALPHA_0,
		SPACE, ESCAPE, UP, DOWN, LEFT, RIGHT, RIGHT_SHIFT, LEFT_SHIFT, RIGHT_CONTROL, LEFT_CONTROL,
		ENTER, TAB, LEFT_ALT, RIGHT_ALT, BACKSPACE
	};
	static std::map<KeyCode, bool> keyStates;
	static void InitKeyStates();

	static const Uint8* keyboadStateArray;
	static void UpdateInput();
	static SDL_Event event;

};