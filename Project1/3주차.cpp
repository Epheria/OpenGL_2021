#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

void myinit(void) {

}

void mykeyboard(unsigned char key, int x, int y) {
	printf("keyboard : %c ( %d, %d ) \n", key, x, y);
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

int count = 0;

void mydisplay(void) {
	printf("in mydisplay (%d)\n", count++);
	glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2015113775 ¼Õ¼¼Çù");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);

	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}