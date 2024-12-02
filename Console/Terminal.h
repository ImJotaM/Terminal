#pragma once
#include "Window.h"
#include "Brush.h"
#include "TerminalCommands.h"

namespace fs = std::filesystem;

class Terminal {

public:

	Terminal();

	void Init();

	template<typename... Args>
	void Print(const std::string& text, Args... args);
	template<typename... Args>
	void Print(Color color, const std::string& text, Args... args);

private:

	Window window;
	Brush brush;

	Color bgcolor = { 12, 12, 12, 255 };

	struct TerminalCursor {

		Rectangle_i rect = { 0, 0, 0, 0 };
		Color color = WHITE;

	} cursor;

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

	friend struct TerminalCommands;
	TerminalCommands commands;

	void Loop();

	void GetUserInput();
	void HandleInput();

	std::vector<std::string> GetInputTokens();

	void DrawHistory();
	void DrawUserInput();

};

template<typename ...Args>
inline void Terminal::Print(const std::string& text, Args ...args) {
	
	std::ostringstream stream;

	stream << text;
	((stream << args), ...);

	history.emplace_back(stream.str());

}

template<typename ...Args>
inline void Terminal::Print(Color color, const std::string& text, Args ...args) {
	
	std::ostringstream stream;
	
	stream << text;
	((stream << args), ...);

	history.emplace_back(stream.str(), color);
}
