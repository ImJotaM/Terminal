#pragma once
#include "Window.h"

namespace fs = std::filesystem;

class Terminal {

public:

	Terminal();

	void Init();

private:

	Window window;

	void Loop();

};