#pragma once
#include "Types.h"

class Window {

public:

	Window();
	~Window();

	const bool ShouldClose();

	void Update();

	void StartDrawing();
	void FinishDrawing();

	void Clear(Color color);

	int GetTitlebarHeight();
	Vector2 GetWindowScale() {
		return GetWindowScaleDPI();
	}

private:

	struct Screen {
		int width = 0;
		int height = 0;
	} screen;

	struct WindowBorder {
		int size = 0;
		bool at_right = false;
		bool at_bottom = false;
	};

	struct WindowStates {
		bool dragging = false;
		bool resizing = false;
	};

	struct Titlebar {

		Rectangle_i rect = { 0, 0, 0, 0 };
		Color color = { 0x0, 0x0, 0x0, 0xff };

		struct Closebtn {

			int size = 0;
			Vector2_i padding = { 0, 0 };
			Rectangle_i area = { 0, 0, 0, 0 };
			Rectangle_i rect = { 0, 0, 0, 0 };
			Line lines[2] = { {}, {} };

		} closebtn;

	};

	struct WindowData {

		const char* title = "";
		Vector2 scale = { 0.f, 0.f };
		int width = 0;
		int height = 0;
		Vector2_i position = { 0, 0 };
		ConfigFlags flags = FLAG_WINDOW_UNDECORATED;
		int max_FPS = 0;

		WindowBorder border;
		
		WindowStates states;

		Titlebar titlebar;

	} window;

	Vector2_i mouse_pos = { 0, 0 };

	Vector2_i dragOffset = { 0, 0 };

	bool shouldClose = false;

	void CheckWindowDragging();
	void CheckWindowResizing();

	void MoveWindow();
	void ResizeWindow();

	void DrawNavbar();

};
