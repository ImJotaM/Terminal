#include "Terminal.h"

Terminal::Terminal() : commands(this) {

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

		window.Clear(bgcolor);

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
		history.emplace_back(currentPath.string() + "> " + userInput + '\n');
		HandleInput();
	}

}

void Terminal::HandleInput() {

	std::vector<std::string> tokens = GetInputTokens();

	if (!tokens.empty()) {

		auto command = commands.commandlist.find(tokens[0]);

		if (command != commands.commandlist.end()) {
			(commands.*(command->second))(tokens);
		} else {
			history.emplace_back("Command not found");
			history.emplace_back("\n");
		}

	}

	userInput.clear();

}

std::vector<std::string> Terminal::GetInputTokens() {

	std::vector<std::string> tokens = {};

	std::stringstream ss(userInput);
	std::string token;

	while (ss >> token) {
		tokens.push_back(token);
	}

	return tokens;
}

void Terminal::DrawHistory() {

	for (int i = 0; i < history.size(); i++) {

		history[i].position = { 12, textformat.titlebar_offset + textformat.fontsize * i };
		history[i].fontsize = textformat.fontsize;
		history[i].spacing = textformat.spacing;

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

	Vector2_i textSize = MeasureTextEx(textformat.font, out.text.c_str(), static_cast<float>(out.fontsize), static_cast<float>(out.spacing));
	cursor.rect.x = 12 + textSize.x + 1;
	cursor.rect.y = out.position.y + textSize.y - 4;
	cursor.rect.width = textformat.fontsize / 2;
	cursor.rect.height = 4;

	DrawRectangleRec(cursor.rect, cursor.color);

}
