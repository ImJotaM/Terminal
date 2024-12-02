#pragma once
#include "Types.h"

class Terminal;

struct TerminalCommands {

	Terminal* terminal;
	
	TerminalCommands(Terminal* terminal) : terminal(terminal) {
		RegisterCommands();
	}

	std::unordered_map<std::string, void (TerminalCommands::*)(std::vector<std::string>&)> commandlist;

	void RegisterCommands();

	void COMMAND_CD(std::vector<std::string>& tokens);

};