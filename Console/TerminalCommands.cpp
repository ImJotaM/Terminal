#include "TerminalCommands.h"
#include "Terminal.h"

void TerminalCommands::RegisterCommands() {
	commandlist["cd"] = &TerminalCommands::COMMAND_CD;
}

void TerminalCommands::COMMAND_CD(std::vector<std::string>& tokens) {
	


}
