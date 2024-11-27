#include "Terminal.h"

Terminal::Terminal() {

}

void Terminal::Init() {
	Loop();
}

void Terminal::Loop() {

	Font font = LoadFontEx("resources/fonts/SegoeUIVF.ttf", 18, nullptr, 0);

	fs::path currentPath = fs::current_path();

	std::vector<std::string> history = { };
	std::string input = "";

	while (!window.ShouldClose()) {

		window.Update();

		int key = GetCharPressed();

		if (key >= 32 && key <= 126) {
			input += (char)key;
		}

		if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
			if (!input.empty()) {
				input.pop_back();
			}
		}

		if (IsKeyPressed(KEY_ENTER)) {
			
			history.push_back(currentPath.string() + "> " + input + '\n');

			if (input.substr(0, 2) == "cd" && input.length() >= 3) {
				std::string newDir = input.substr(3);
				if (fs::exists(currentPath / newDir)) {
					currentPath = currentPath / newDir;
				}
				else {
					history.push_back("Path not founded");
					history.push_back("\n");
				}
			}
			else if (input.substr(0, 2) == "ls") {
				for (const auto& entry : fs::directory_iterator(currentPath)) {
					history.push_back(entry.path().filename().string() + '\n');
				}
				history.push_back("\n");
			}
			else if (input.substr(0, 3) == "cls") {
				history.clear();
			}


			input.clear();
		}

		window.StartDrawing();

		window.Clear({ 12, 12, 12, 255 });
		
		for (int i = 0; i < history.size(); i++) {
			DrawTextEx(font, history[i].c_str(), {12.f, 30.f + 18.f * i}, 18, 0, WHITE);
		}

		std::string out = currentPath.string() + "> " + input;
		DrawTextEx(font, out.c_str(), { 12.f, 30.f + 18.f * history.size()}, 18, 0, WHITE);

		window.FinishDrawing();

	}

}
