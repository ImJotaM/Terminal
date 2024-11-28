#pragma once
#include "Types.h"

struct Drawable {
	virtual void Draw() = 0;
	virtual ~Drawable() = default;
};

