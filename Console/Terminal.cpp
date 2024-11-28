#include "Terminal.h"

Terminal::Terminal() {

	textformat.scale = window.GetWindowScale().x;

	textformat.titlebar_height = window.GetTitlebarHeight();
	textformat.titlebar_margin = 2;
	textformat.titlebar_offset = textformat.titlebar_height + textformat.titlebar_margin;

	textformat.fontsize = 16;
	textformat.fontsize = static_cast<int>(textformat.fontsize * textformat.scale);

	textformat.spacing = 0;

	textformat.font = LoadFontEx("resources/fonts/SegoeUIVF.ttf", textformat.fontsize, nullptr, 0);
	
	currentPath = fs::current_path();

}

void Terminal::Init() {
	Loop();
}

void Terminal::Loop() {

	while (!window.ShouldClose()) {

		window.Update();

		GetUserInput();

		window.StartDrawing();

		window.Clear({ 12, 12, 12, 255 });

		DrawHistory();
		DrawUserInput();

		window.FinishDrawing();

	}

}

void Terminal::GetUserInput() {

	int key = GetCharPressed();

	if (key >= 32 && key <= 126) {
		userInput += (char)key;
	}

	if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
		if (!userInput.empty()) {
			userInput.pop_back();
		}
	}

	if (IsKeyPressed(KEY_ENTER)) {
		HandleInput();
	}

}

void Terminal::HandleInput() {

	history.emplace_back(currentPath.string() + "> " + userInput + '\n');

	std::vector<std::string> tokens = GetInputTokens();

	for (int i = 0; i < tokens.size(); i++) {

		if (tokens[i] == "cd") {

			if (i + 1 != tokens.size()) {

				std::string newDir = tokens[i + 1];

				if (fs::exists(currentPath / newDir)) {
					currentPath = currentPath / newDir;
				} else {
					history.emplace_back("Path not founded.");
					history.emplace_back("\n");
				}

			} else {
				history.emplace_back("Insert a path after \'cd\'");
				history.emplace_back("\n");
			}

		} else if (tokens[i] == "ls") {

			for (const auto& entry : fs::directory_iterator(currentPath)) {
				history.emplace_back(entry.path().filename().string() + '\n');
			}

			history.emplace_back("\n");

		} else if (tokens[i] == "cls") {
			
			history.clear();
		
		} else {

			history.emplace_back("\'" + tokens[i] + "\' command not founded.");

		}

	}

	userInput.clear();

}

std::vector<std::string> Terminal::GetInputTokens() {

	std::vector<std::string> tokens = {};

	std::string buf = "";

	for (size_t i = 0; i < userInput.length(); i++) {
		if (userInput[i] != ' ') {
			buf += userInput[i];
			if (i + 1 == userInput.length()) {
				tokens.push_back(buf);
			}
		} else {
			tokens.push_back(buf);
			buf.clear();
		}
	}

	return tokens;
}

void Terminal::DrawHistory() {

	for (int i = 0; i < history.size(); i++) {

		history[i].position = { 12, textformat.titlebar_offset + textformat.fontsize * i };
		history[i].fontsize = textformat.fontsize;
		history[i].spacing = textformat.spacing;
		history[i].color = WHITE;

		brush.DrawText(history[i], textformat.font);
	}

}

void Terminal::DrawUserInput() {

	Text out;

	out.text = currentPath.string() + "> " + userInput;
	out.position = { 12, textformat.titlebar_offset + textformat.fontsize * history.size() };
	out.fontsize = textformat.fontsize;
	out.spacing = textformat.spacing;
	out.color = WHITE;

	brush.DrawText(out, textformat.font);

}
