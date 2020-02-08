#pragma once
class Actor
{
public:
	double getX() const { return x; }
	double getY() const { return y; }
	double getHeight() const { return height; }
	double getWidth() const { return width; }

	void setX(const double& x) { this->x = x; }
	void setY(const double& y) { this->y = y; }
	void setHeight(const double& height) { this->height = height; }
	void setWidth(const double& width) { this->width = width; }

	void render();
protected:
	double x, y, height, width;
};

