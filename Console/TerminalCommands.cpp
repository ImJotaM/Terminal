#include "TerminalCommands.h"
#include "Terminal.h"

void TerminalCommands::RegisterCommands() {
	commandlist["cd"] = &TerminalCommands::COMMAND_CD;
	commandlist["ls"] = &TerminalCommands::COMMAND_LS;
	commandlist["cls"] = &TerminalCommands::COMMAND_CLS;
	commandlist["mkdir"] = &TerminalCommands::COMMAND_MKDIR;
	commandlist["rm"] = &TerminalCommands::COMMAND_RM;
	commandlist["mkfile"] = &TerminalCommands::COMMAND_MKFILE;
}

void TerminalCommands::COMMAND_CD(std::vector<std::string>& tokens) {
	
	if (tokens.size() <= 1) {
		return;
	}

	fs::path is_rel = tokens[1];
	fs::path newpath = "";

	if (is_rel.is_absolute()) {
		newpath = tokens[1];
	} else {
		newpath = terminal->currentPath / tokens[1];
	}

	newpath = fs::weakly_canonical(newpath);

	if (fs::exists(newpath)) {
		terminal->currentPath = newpath;
	} else {
		terminal->Print(RED, "Path not founded.");
		terminal->Print("\n");
	}

}

void TerminalCommands::COMMAND_LS(std::vector<std::string>& tokens) {
	
	for (auto& entry : fs::directory_iterator(terminal->currentPath)) {
		
		if (fs::is_directory(entry.path())) {
			terminal->Print(BLUE, entry.path().filename().string());
		} else {
			terminal->Print(entry.path().filename().string());
		}

	}

	terminal->Print("\n");

}

void TerminalCommands::COMMAND_CLS(std::vector<std::string>& tokens) {
	terminal->history.clear();
}

void TerminalCommands::COMMAND_MKDIR(std::vector<std::string>& tokens) {

	if (tokens.size() <= 1) {
		return;
	}

	fs::path is_rel = tokens[1];
	fs::path newdir = "";

	if (is_rel.is_absolute()) {
		newdir = tokens[1];
	} else {
		newdir = terminal->currentPath / tokens[1];
	}

	if (fs::exists(newdir)) {
		terminal->Print(RED, "Directory \'", tokens[1], "\' already exist.");
	} else {

		fs::create_directory(newdir);

		if (fs::exists(newdir)) {
			terminal->Print(BLUE, "Directory \'", tokens[1], "\' created.");
		} else {
			terminal->Print(RED, "Failed to create \'", tokens[1], "\' directory.");
		}

	}

}

void TerminalCommands::COMMAND_RM(std::vector<std::string>& tokens) {

	if (tokens.size() <= 1) {
		return;
	}

	fs::path is_rel = tokens[1];
	fs::path target = "";

	if (is_rel.is_absolute()) {
		target = tokens[1];
	} else {
		target = terminal->currentPath / tokens[1];
	}

	if (fs::exists(target)) {

		fs::remove(target);

		if (fs::exists(target)) {
			terminal->Print(RED, "Failed to remove \'", tokens[1], "\'.");
		} else {
			terminal->Print(BLUE, "\'", tokens[1], "\' removed.");
		}

	} else {
		terminal->Print(RED, "\'", tokens[1], "\' doesn't exist.");
	}


}

void TerminalCommands::COMMAND_MKFILE(std::vector<std::string>& tokens) {

	if (tokens.size() <= 1) {
		return;
	}

	fs::path is_rel = tokens[1];
	fs::path newfile = "";

	if (is_rel.is_absolute()) {
		newfile = tokens[1];
	} else {
		newfile = terminal->currentPath / tokens[1];
	}

	if (fs::exists(newfile)) {
		terminal->Print(RED, "File \'", tokens[1], "\' already exist.");
	} else {

		std::fstream file(newfile, std::ios::out);

		if (fs::exists(newfile)) {
			terminal->Print(BLUE, "File \'", tokens[1], "\' created.");
		} else {
			terminal->Print(RED, "Failed to create \'", tokens[1], "\' file.");
		}

	}

}
