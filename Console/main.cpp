#include <raylib.h>
#include <iostream>

struct Screen {

	int width = 0;
	int height = 0;

};

struct WindowBorder {

	int size = 0;
	bool at_right = false;
	bool at_bottom = false;

};

struct WindowStates {

	bool dragging = false;
	bool resizing = false;

};

struct WindowData {

	const char* title = "";
	int width = 0;
	int height = 0;
	Vector2 position = { 0, 0 };
	ConfigFlags flags = FLAG_WINDOW_UNDECORATED;
	int max_FPS = 60;

	WindowBorder border = { 0, false, false };

	WindowStates states = { false, false };

	Rectangle navbar = { 0, 0, 0, 28 };

};

Screen screen;
WindowData window;

Vector2 dragOffset = { 0, 0 };

Vector2 mouse_pos = { 0, 0 };

void CheckWindowDragging() {
	if (CheckCollisionPointRec(mouse_pos, window.navbar)) {
		window.states.dragging = true;
		dragOffset = mouse_pos;
	}
}

void CheckWindowResizing() {
	if ((window.border.at_right || window.border.at_bottom) && !window.states.resizing) {
		window.states.resizing = true;
	}
}

void MoveWindow() {
	if (window.states.dragging) {
		Vector2 delta = { mouse_pos.x - dragOffset.x, mouse_pos.y - dragOffset.y};
		SetWindowPosition(window.position.x + delta.x, window.position.y + delta.y);
	}
}

void ResizeWindow() {

	if (!window.states.resizing) {
		window.border.at_right = mouse_pos.x >= window.width - window.border.size;
		window.border.at_bottom = mouse_pos.y >= window.height - window.border.size;
	}

	if (window.border.at_right && window.border.at_bottom) {
		SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
	}
	else if (window.border.at_right) {
		SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
	}
	else if (window.border.at_bottom) {
		SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
	}
	else {
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}

	if (window.states.resizing) {

		if (window.border.at_right) window.width = mouse_pos.x;
		if (window.border.at_bottom) window.height = mouse_pos.y;

		if (window.width <= 200) window.width = 200;
		if (window.height <= 200) window.height = 200;

		SetWindowSize(window.width, window.height);

	}

	window.navbar.width = window.width;

}

void drawNavbar() {
	
	DrawRectangleRec(window.navbar, { 32, 32, 32, 255 });

	Vector2 X_offset = { 5, 5 };
	int X_size = 16;
	Rectangle area = { window.width - X_size - X_offset.x , 0 + X_offset.y , X_size, X_size };

	DrawLine(area.x, area.y, area.x + area.width, area.y + area.height, WHITE);
	DrawLine(area.x, area.y + area.height, area.x + area.width, area.y, WHITE);

}

int main() {

	window.title = "Terminal";

	InitWindow(0, 0, "");

	SetWindowTitle(window.title);

	screen.width = GetScreenWidth();
	screen.height = GetScreenHeight();
	
	window.width = screen.width / 2;
	window.height = screen.height / 2;
	SetWindowSize(window.width, window.height);

	window.position.x = (screen.width - window.width) / 2;
	window.position.y = (screen.height - window.height) / 2;
	SetWindowPosition(window.position.x, window.position.y);

	window.flags = FLAG_WINDOW_UNDECORATED;
	SetWindowState(window.flags);

	SetTargetFPS(window.max_FPS);

	window.border.size = 10;
	window.navbar = { 0, 0 };
	window.navbar.width = window.width;
	window.navbar.height = 28;

	while (!WindowShouldClose()) {

		window.position = GetWindowPosition();
		mouse_pos = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			
			CheckWindowDragging();
			CheckWindowResizing();

		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			window.states.dragging = false;
			window.states.resizing = false;
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