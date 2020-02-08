#include "Ball.h"
#include <random>

const double BALL_WIDTH = .1f;
const double BALL_HEIGHT = .1f;

int getRandInt(int lower, int upper)
{
	std::random_device rd;
	std::mt19937 engine(rd());

	const std::uniform_int_distribution<> distribution(lower, upper);

	return distribution(engine);
}


Ball::Ball(double x, double y)
{
	this->x = x;
	this->y = y;
	this->height = BALL_HEIGHT;
	this->width = BALL_WIDTH;
	this->direction = (Direction)getRandInt(0, 3);
}

Victor Ball::checkVictory()
{
	if (x <= -1.0)
	{
		return Victor::Player1;
	}
	else if (x >= 1)
	{
		return Victor::Player2;
	}
	return Victor::None;
}

/*
	Check if the ball has collided with a paddle and
	make it bounce if it has
*/
void Ball::handleCollision(Paddle p1, Paddle p2)
{
	// if its colliding with a paddle, reverse the
	// direction
	if (checkPaddleCollision(p1) || checkPaddleCollision(p2)) 
	{
		// if its going left, make it go right in 
		// a random direction and vice versa
		if ((int)direction <= 1)
		{
			direction = (Direction)getRandInt(2, 3);
		}
		else 
		{
			direction = (Direction)getRandInt(0, 1);
		}
	}
}

/*
	Change the ball's x position based on the direction it going in
*/
void Ball::move(const Paddle& paddle1, const Paddle& paddle2)
{
	switch (direction)
	{
	case Ball::Direction::LeftUp:
		x -= .01;
		y += .01;

		if (checkPaddleCollision(paddle1))
			direction = Ball::Direction::RightUp;
		else if (checkWallCollision())
			direction = Ball::Direction::LeftDown;

		break;
	case Ball::Direction::LeftDown:
		x -= .01;
		y -= .01;

		if (checkPaddleCollision(paddle1))
			direction = Ball::Direction::RightDown;
		else if (checkWallCollision())
			direction = Ball::Direction::LeftUp;

		break;
	case Ball::Direction::RightUp:
		x += .01;
		y += .01;

		if (checkPaddleCollision(paddle2))
			direction = Ball::Direction::LeftUp;
		else if (checkWallCollision())
			direction = Ball::Direction::RightDown;
		break;
	case Ball::Direction::RightDown:
		x += .01;
		y -= .01;

		if (checkPaddleCollision(paddle2))
			direction = Ball::Direction::LeftDown;
		else if (checkWallCollision())
			direction = Ball::Direction::RightUp;
	}
}

void Ball::resetPosition()
{
	x = 0.0;
	y = 0.0;
	direction = (Direction)getRandInt(0, 3);
}

/*
	Check if a ball has collided with a paddle
*/
bool Ball::checkPaddleCollision(Paddle p) const
{
	const bool collisionX = x + width >= p.getX() &&
		p.getX() + p.getWidth() >= x;

	const bool collisionY = y + height >= p.getY() &&
		p.getY() + p.getHeight() >= y;

	return collisionX && collisionY;
}

bool Ball::checkWallCollision() const
{
	if (y <= -1.0 || y >= .9)
	{
		return true;
	}
	
	return false;
}
