#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "game.h"

int DISPLAY_WIDTH = 640;
int DISPLAY_HEIGHT = 360;
int DISPLAY_SCALE = 2;

void StepFrame(float elapsedTime) 
{
	UpdateBall(paddle);
	UpdateBricks();
	UpdatePaddle(paddle);
}

void SpawnBall()
{
	int objectId = Play::CreateGameObject(
		ObjectType::TYPE_BALL,
		{ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 60 },
		4,
		"ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * 5;
}

void UpdateBall(Paddle pad)
{
	std::vector<int> ballIDs = Play::CollectGameObjectIDsByType(TYPE_BALL);

	for (int ballID : ballIDs)
	{
		GameObject& ball = Play::GetGameObject(ballID);
		if (ball.pos.x >= DISPLAY_WIDTH || ball.pos.x <= 0)
			ball.velocity.x *= -1;
		if (ball.pos.y >= DISPLAY_HEIGHT || ball.pos.y <= 0)
			ball.velocity.y *= -1;

		if (IsColliding(pad, ball))
		{
			Play::PlayAudio("pong");
			ball.velocity.y *= -1;
		}

		Play::UpdateGameObject(ball);
		Play::DrawObject(ball);
	}
}

void SpawnBricks() {
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 36; x++)
		{
			Play::CreateGameObject(TYPE_BRICK, { x * 17 + 22, y * 11 + 20 }, 6, "brick");
		}
	}
}

void UpdateBricks()
{
	std::vector<int> brickIDs = Play::CollectGameObjectIDsByType(TYPE_BRICK);

	for (int brickID : brickIDs)
	{
		GameObject& brick = Play::GetGameObject(brickID);
		Play::UpdateGameObject(brick);
		Play::DrawObject(brick);

		std::vector<int> ballIDs = Play::CollectGameObjectIDsByType(TYPE_BALL);

		for (int ballID : ballIDs)
		{
			GameObject& ball = Play::GetGameObject(ballID);
			if (Play::IsColliding(brick, ball))
			{
				Play::PlayAudio("ping");
				Play::DestroyGameObject(brickID);
				ball.velocity.y *= -1;
			}
		}

	}
}

float Max(float a, float b)
{
	return a > b ? a : b;
}

float Min(float a, float b)
{
	return a < b ? a : b;
}

bool IsColliding(Paddle &pad, GameObject& ball)
{
	Point2f paddleTopLeft = { pad.pos.x - pad.width / 2, pad.pos.y - pad.height / 2 };
	Point2f paddleBottomRight = { pad.pos.x + pad.width / 2, pad.pos.y + pad.height / 2 };

	const float dx = ball.pos.x - Max(paddleTopLeft.x, Min(ball.pos.x, paddleBottomRight.x));
	const float dy = ball.pos.y - Max(paddleTopLeft.y, Min(ball.pos.y, paddleBottomRight.y));

	return (dx * dx + dy * dy) < (ball.radius * ball.radius);
}