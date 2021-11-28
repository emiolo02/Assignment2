#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "constants.h"
#include "paddle.h"

void StepFrame(float elapsedTime);

void SpawnBall();
void UpdateBall(Paddle pad);

void SpawnBricks();
void UpdateBricks();

void DrawPaddle(Paddle &pad);
void UpdatePaddle(Paddle &pad);

bool IsColliding(Paddle &pad, GameObject &ball);
