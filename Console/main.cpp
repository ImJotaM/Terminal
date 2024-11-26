#include "Window.h"

int main() {

	Window window;

	while (!window.ShouldClose()) {

		window.Update();

		window.StartDrawing();

		window.Clear({12, 12, 12, 255});
		
		window.FinishDrawing();

	}

	return 0;
}