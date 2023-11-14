#include <iostream>
#include <string>
#include <SDL.h>
#include "math/math.h"
#include "application/application.h"

int main(int argc, char** argv) {

	Application app = Application("Turnz", 640, 480);
	app.Run();

	return 0;

}



