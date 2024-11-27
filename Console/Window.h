#pragma once
#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

struct Vector2_i {
	
	int x;
	int y;

	Vector2_i() : x(0), y(0) {}
	Vector2_i(int x, int y) : x(x), y(y) {}

	Vector2_i(const Vector2& v) : x(static_cast<int>(v.x)), y(static_cast<int>(v.y)) {}

	operator Vector2() {
		return { static_cast<float>(x), static_cast<float>(y) };
	}

};

struct Rectangle_i {
	
	int x;
	int y;
	int width;
	int height;

	Rectangle_i() : x(0), y(0), width(0), height(0) {}
	Rectangle_i(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}

	Rectangle_i(const Rectangle& r)
		: x(static_cast<int>(r.x)), y(static_cast<int>(r.y)), width(static_cast<int>(r.width)), height(static_cast<int>(r.height)) {}

	operator Rectangle() {
		return { static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height) };
	}

};

struct Line {
	Vector2_i startPos = { 0, 0 };
	Vector2_i endPos = { 0, 0 };
};

class Window {

public:

	Window();
	~Window();

	const bool ShouldClose();

	void Update();

	void StartDrawing();
	void FinishDrawing();

	void Clear(Color color);

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
		int width = 0;
		int height = 0;
		Vector2_i position = { 0, 0 };
		ConfigFlags flags = FLAG_WINDOW_UNDECORATED;
		int max_FPS = 60;

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
