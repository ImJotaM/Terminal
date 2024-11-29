#include "Terminal.h"

void COMMAND_CD(Terminal* terminal, const std::vector<std::string>& tokens) {
	std::cout << "CD detected!" << std::endl;
}

void Terminal::RegisterCommands() {

	commandHandler.AddCommand("cd", COMMAND_CD);

}
