#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void myinit(void)
{
	printf("%s\n", glGetString(GL_VERSION));
}
void mykeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}
void mydisplay(void)
{
	glClearColor(0.68F, 0.0F, 0.9F, 1.0F);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(900, 600);
	glutInitWindowPosition(200, 500); // 화면에서 제일 왼쪽 위의 좌표값(0,0)

	glutCreateWindow("2015113775_손세협");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}