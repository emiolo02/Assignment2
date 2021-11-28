#include "game.h"

Paddle paddle;

void DrawPaddle(Paddle &pad)
{
	Play::DrawRect({ pad.pos.x - pad.width / 2, pad.pos.y - pad.height / 2 },
		{ pad.pos.x + pad.width / 2, pad.pos.y + pad.height / 2 },
		Play::cWhite,
		true);
}

void UpdatePaddle(Paddle &pad)
{
	if (Play::KeyDown(VK_LEFT) && pad.pos.x > pad.width / 2)
	{
		pad.pos.x -= 5;
	}
	if (Play::KeyDown(VK_RIGHT) && pad.pos.x < DISPLAY_WIDTH - pad.width / 2)
	{
		pad.pos.x += 5;
	}

	DrawPaddle(pad);
}