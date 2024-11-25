#include <raylib.h>
#include <iostream>

#define BORDER_SIZE 10

int window_width = 600;
int window_height = 450;

Vector2 windowPos = { 0, 0 };

struct Window_States {

	bool dragging = false;
	bool resizing = false;

} window_states;

Vector2 dragOffset = { 0, 0 };

bool at_right = false;
bool at_bottom = false;

Vector2 mouse_pos = { 0, 0 };

Rectangle navbar = { 0, 0, window_width, 28 };

void CheckWindowDragging() {
	if (CheckCollisionPointRec(mouse_pos, navbar)) {
		window_states.dragging = true;
		dragOffset = mouse_pos;
	}
}

void CheckWindowResizing() {
	if ((at_right || at_bottom) && !window_states.resizing) {
		window_states.resizing = true;
	}
}

void MoveWindow() {
	if (window_states.dragging) {
		Vector2 delta = { mouse_pos.x - dragOffset.x, mouse_pos.y - dragOffset.y};
		SetWindowPosition(windowPos.x + delta.x, windowPos.y + delta.y);
	}
}

void ResizeWindow() {

	if (!window_states.resizing) {
		at_right = mouse_pos.x >= window_width - BORDER_SIZE;
		at_bottom = mouse_pos.y >= window_height - BORDER_SIZE;
	}

	if (at_right && at_bottom) {
		SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
	}
	else if (at_right) {
		SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
	}
	else if (at_bottom) {
		SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
	}
	else {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}

	if (window_states.resizing) {

		if (at_right) window_width = mouse_pos.x;
		if (at_bottom) window_height = mouse_pos.y;

		if (window_width <= 200) window_width = 200;
		if (window_height <= 200) window_height = 200;

		SetWindowSize(window_width, window_height);

	}

	navbar.width = window_width;

}

void drawNavbar() {
	DrawRectangleRec(navbar, { 32, 32, 32, 255 });
}

int main() {
	
	SetConfigFlags(FLAG_WINDOW_UNDECORATED);
	InitWindow(window_width, window_height, "Terminal");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

		windowPos = GetWindowPosition();
		mouse_pos = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			
			CheckWindowDragging();
			CheckWindowResizing();

		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			window_states.dragging = false;
			window_states.resizing = false;
		}

		MoveWindow();
		ResizeWindow();

		BeginDrawing();

		ClearBackground(BLACK);
		
		drawNavbar();

		EndDrawing();

	}

	CloseWindow();

	return 0;
}