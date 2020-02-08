#include "Paddle.h"

const double PADDLE_HEIGHT = .2;
const double PADDLE_WIDTH = .1;

Paddle::Paddle(double x, double y)
{
	this->x = x;
	this->y = y;
	this->height = PADDLE_HEIGHT;
	this->width = PADDLE_WIDTH;
}
