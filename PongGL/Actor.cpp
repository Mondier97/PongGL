#include "Actor.h"
#include <GL/glut.h>

/*
    The paddles and balls are both just rectangles,
    so their base class is capable of rendering both
    of them.
*/
void Actor::render()
{
    glRectf(x, y, x + width, y + height);
}
