#include "Window.h"

Window::Window() {

	InitWindow(0, 0, "");

	screen.width = GetScreenWidth();
	screen.height = GetScreenHeight();

	window.title = "Terminal";
	SetWindowTitle(window.title);
	
	window.scale = GetWindowScaleDPI();

	window.width = screen.width / 2;
	window.height = screen.height / 2;

	window.width = static_cast<int>(window.width * window.scale.x);
	window.height = static_cast<int>(window.height * window.scale.y);

	SetWindowSize(window.width, window.height);

	window.position.x = (screen.width - window.width) / 2;
	window.position.y = (screen.height - window.height) / 2;

	SetWindowPosition(window.position.x, window.position.y);

	window.flags = FLAG_WINDOW_UNDECORATED;
	SetWindowState(window.flags);

	window.max_FPS = 60;
	SetTargetFPS(window.max_FPS);

	window.border.size = 10;
	window.border.at_right = false;
	window.border.at_bottom = false;

	window.titlebar.rect.height = 28;
	window.titlebar.rect.height = static_cast<int>(window.titlebar.rect.height * window.scale.y);

	window.titlebar.color = { 32, 32, 32, 255 };

}

Window::~Window() {
	CloseWindow();
}

const bool Window::ShouldClose() {
	return shouldClose;
}

void Window::Update() {
	
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

}

void Window::StartDrawing() {
	BeginDrawing();
	DrawNavbar();
}

void Window::FinishDrawing() {
	EndDrawing();
}

void Window::Clear(Color color) {
	ClearBackground(color);
}

int Window::GetTitlebarHeight() {
	return window.titlebar.rect.height;;
}

void Window::CheckWindowDragging() {

	if (CheckCollisionPointRec(mouse_pos, window.titlebar.rect)) {
		window.states.dragging = true;
		dragOffset = mouse_pos;
	}

}

void Window::CheckWindowResizing() {
	if ((window.border.at_right || window.border.at_bottom) && !window.states.resizing) {
		window.states.resizing = true;
	}
}

void Window::MoveWindow() {
	if (window.states.dragging) {
		Vector2_i delta = { mouse_pos.x - dragOffset.x, mouse_pos.y - dragOffset.y };
		SetWindowPosition(window.position.x + delta.x, window.position.y + delta.y);
	}
}

void Window::ResizeWindow() {

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

}

void Window::DrawNavbar() {

	Titlebar* titlebar = &window.titlebar;

	titlebar->rect.width = window.width;
	DrawRectangleRec(titlebar->rect, titlebar->color);

	/////////////////////////////////////////////////////////////////
	//                                                             //
	// TO DO:                                                      //
	//                                                             //
	// Remove 'area' element of window.titlebar.closebtn.area and  //
	// calc rect and other values directly.                        //
	//                                                             //
	/////////////////////////////////////////////////////////////////

	Titlebar::Closebtn* closebtn = &window.titlebar.closebtn;
	
	closebtn->area = { window.width - closebtn->size - closebtn->padding.x , closebtn->padding.y , closebtn->size, closebtn->size };

	closebtn->size = 10;
	closebtn->padding = { 12, 8 };
	closebtn->rect = { 
		closebtn->area.x - closebtn->padding.x, 0,
		window.width, titlebar->rect.height
	};

	closebtn->lines[0] = { 
		{ closebtn->area.x, closebtn->area.y },
		{ closebtn->area.x + closebtn->area.width, closebtn->area.y + closebtn->area.height }
	};

	closebtn->lines[1] = {
		{ closebtn->area.x, closebtn->area.y + closebtn->area.height },
		{ closebtn->area.x + closebtn->area.width, closebtn->area.y }
	};

	if (CheckCollisionPointRec(mouse_pos, closebtn->rect)) {
		DrawRectangleRec(closebtn->rect, RED);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			shouldClose = true;
		}
	}

	DrawLineEx(closebtn->lines[0].startPos, closebtn->lines[0].endPos, 1, WHITE);
	DrawLineEx(closebtn->lines[1].startPos, closebtn->lines[1].endPos, 1, WHITE);

}
