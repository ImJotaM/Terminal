#include "Brush.h"

void Brush::DrawText(Text& text, Font& font) {

	DrawTextEx(font, text.text.c_str(), text.position, static_cast<float>(text.fontsize), static_cast<float>(text.spacing), text.color);

}
