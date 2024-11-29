#pragma once
#include "GlobalLibs.h"

class Terminal;

class CommandHandler {

public:

	void AddCommand(const std::string& command, std::function<void(Terminal*, const std::vector<std::string>&)> func);

	bool HandleTokens(Terminal* terminal, const std::vector<std::string>& tokens);

private:

	std::unordered_map<std::string, std::function<void(Terminal*, const std::vector<std::string>&)>> commands;
	
};