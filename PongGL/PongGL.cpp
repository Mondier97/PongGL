/*
	Samuel Mondier 2/5/2020

	This program is a Pong clone created with the freeGlut wrapper
	for opengl.
*/

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Ball.h"
#include "Paddle.h"

const int WINDOW_WIDTH = 720;
const int WINDOW_HEIGHT = 720;

Paddle paddle1(-0.9, 0.0);
Paddle paddle2(.8, 0.0);
Ball ball(0.0, 0.0);

int player1Score = 0;
int player2Score = 0;

bool keys[256] = {0};

void renderScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1.0, 1.0, 1.0);

	if (keys['w'])
	{
		if (paddle1.getY() < .8)
		{
			paddle1.setY(paddle1.getY() + .05);
		}
	}
	else if (keys['s'])
	{
		if (paddle1.getY() > -1.0)
		{
			paddle1.setY(paddle1.getY() - .05);
		}
	}
	
	if (keys[GLUT_KEY_UP])
	{
		if (paddle2.getY() < .8)
		{
			paddle2.setY(paddle2.getY() + .05);
		}
	}
	else if (keys[GLUT_KEY_DOWN])
	{
		if (paddle2.getY() > -1.0)
		{
			paddle2.setY(paddle2.getY() - .05);
		}
	}

	glRasterPos2d(.45, 0);
	for (char c : std::to_string(player1Score)) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}

	glRasterPos2d(-.45, 0);
	for (char c : std::to_string(player2Score))
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}

	paddle1.render();
	paddle2.render();
	ball.render();

	glutSwapBuffers();
}

/*
	This gets called every 60th of a second to update the screen
*/
void tick(int)
{
	ball.move(paddle1, paddle2);

	switch (ball.checkVictory())
	{
	case Victor::Player1:
		player1Score++;
		ball.resetPosition();
		break;
	case Victor::Player2:
		player2Score++;
		ball.resetPosition();
	}

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, tick, 0);
}

int main(int argc, char** argv) 
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("PongGL");

	// register callbacks
	glutDisplayFunc(renderScene);

	glutKeyboardFunc([](unsigned char key, int, int) 
	{
		keys[key] = true;
	});
	glutSpecialFunc([](int key, int, int) 
	{
		keys[key] = true;
	});

	glutKeyboardUpFunc([](unsigned char key, int, int) 
	{
		keys[key] = false;
	});
	glutSpecialUpFunc([](int key, int, int) 
	{
		keys[key] = false;
	});

	glutTimerFunc(1000 / 60, tick, 0);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}