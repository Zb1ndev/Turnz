#include <SDL2/SDL.h>
#include <iostream>

#include "input/input.h"
#include "application/application.h"
#include "renderer/renderer.h"

void Start() {

	

}

void Update() {
	


}

void OnClose() {



}

int main(int argc, char** argv) {
	Application app = Application("Turnz", 640, 480, &Start, &Update, &OnClose);
	return 0;
}