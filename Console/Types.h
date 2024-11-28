#pragma once
#include "GlobalLibs.h"

struct Vector2_i {

	int x;
	int y;

	Vector2_i() : x(0), y(0) {}
	
	template<typename T_X, typename T_Y>
	Vector2_i(T_X x, T_Y y) : x(static_cast<int>(x)), y(static_cast<int>(y)) {}
	
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
	
	template<typename T_X, typename T_Y, typename T_W, typename T_H>
	Rectangle_i(T_X x, T_Y y, T_W w, T_H h) : x(static_cast<int>(x)), y(static_cast<int>(y)), width(static_cast<int>(w)), height(static_cast<int>(h)) {}

	Rectangle_i(const Rectangle& r)
		: x(static_cast<int>(r.x)), y(static_cast<int>(r.y)), width(static_cast<int>(r.width)), height(static_cast<int>(r.height)) {
	}

	operator Rectangle() {
		return { static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height) };
	}

};

struct Line {
	Vector2_i startPos = { 0, 0 };
	Vector2_i endPos = { 0, 0 };
};

struct Text {
	
	std::string text = "";
	int fontsize = 0;
	Vector2_i position = { 0, 0 };
	int spacing = 0;

	Color color = { 0xff, 0xff, 0xff, 0xff };
};

