#pragma once
#include "Window.h"
#include "Brush.h"

namespace fs = std::filesystem;

class Terminal {

public:

	Terminal();

	void Init();

private:

	Window window;
	Brush brush;

	struct TextFormat {

		float scale = 0.f;
		int titlebar_height = 0;
		int titlebar_margin = 0;
		int titlebar_offset = 0;
		int fontsize = 0;
		int spacing = 0;

		Font font = {};

	} textformat;

	std::string userInput = "";
	std::vector<Text> history = {};

	fs::path currentPath = "";

	void Loop();

	void GetUserInput();
	void HandleInput();

	std::vector<std::string> GetInputTokens();

	void DrawHistory();
	void DrawUserInput();

};