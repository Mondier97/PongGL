#pragma once
#include "Actor.h"
#include "Paddle.h"

enum class Victor {
	Player1,
	Player2,
	None
};

class Ball : public Actor
{
public:
	Ball(double x, double y);

	Victor checkVictory();
	void handleCollision(Paddle p1, Paddle p2);
	void move(const Paddle& paddle1, const Paddle& paddle2);
	void resetPosition();
private:
	enum class Direction {
		LeftUp,
		LeftDown,
		RightUp,
		RightDown
	};

	Direction direction;
	bool checkPaddleCollision(Paddle p) const;
	bool checkWallCollision() const;
};

