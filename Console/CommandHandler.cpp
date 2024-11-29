#include "CommandHandler.h"

void CommandHandler::AddCommand(const std::string& command, std::function<void(Terminal*, const std::vector<std::string>&)> func) {
	commands[command] = func;
}

bool CommandHandler::HandleTokens(Terminal* terminal, const std::vector<std::string>& tokens) {

	if (tokens.empty()) {
		return true;
	}

	const std::string& command = tokens[0];

	auto it = commands.find(command);

	if (it != commands.end()) {

		it->second(terminal, tokens);

		return true;

	} else {
		return false;
	}

}
