#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
const static char* vsSource = "#version 120 \n\
attribute vec4 aPosition; \n\
attribute vec4 aColor; \n\
varying vec4 vColor; \n\
uniform float udist; \n\
void main(void) { \n\
 gl_Position.x = aPosition.x + udist; \n\
 gl_Position.yzw = aPosition.yzw; \n\
 vColor = aColor; \n\
}";
const static char* fsSource = "#version 120 \n\
varying vec4 vColor; \n\
void main(void) { \n\
 gl_FragColor = vColor; \n\
}";

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;
char buf[1024];
GLuint vbo[3], vao[3];

GLfloat vertices[] = {
	-0.8, -0.8, 0.0, 1.0,
	-0.8, -0.5, 0.0, 1.0,
	-0.5, -0.5, 0.0, 1.0,
};
GLfloat colors[] = {
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
};
GLfloat vertices2[] = {
	+0.3, 0.1, 0.0, 1.0,
	-0.3, 0.1, 0.0, 1.0,
	-0.3, -0.3, 0.0, 1.0,
	+0.3, -0.3, 0.0, 1.0,
};
GLfloat colors2[] = {
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 0.0, 1.0, 1.0,
};
GLfloat vertices3[] = {
	0.8, 0.8, 0.0, 1.0,
	0.7, 0.7, 0.0, 1.0,
	0.75, 0.6, 0.0, 1.0,
	0.85, 0.6, 0.0, 1.0,
	0.9, 0.7, 0.0, 1.0,
};
GLfloat colors3[] = {
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 1.0, 1.0,
};

void myinit(void) {
	GLint status;
	printf("***** 2015113775 ¼Õ¼¼Çù *****\n");
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs); // compile to get .OBJ
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	printf("vs compile status = %s\n", (status == GL_TRUE) ? "true" :"false");
	glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs); // compile to get .OBJ
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	printf("fs compile status = %s\n", (status == GL_TRUE) ? "true" :"false");
	glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
	printf("fs log = [%s]\n", buf);
	// prog: program
	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog); // link to get .EXE
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("program link status = %s\n", (status == GL_TRUE) ? "true" :"false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("link log = [%s]\n", buf);
	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	printf("program validate status = %s\n", (status == GL_TRUE) ? "true" :"false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("validate log = [%s]\n", buf);
	glUseProgram(prog);

	glGenVertexArrays(3, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(3,vbo); ///////////////////////////////////////////////////////////////

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 3 * 4 * sizeof(GLfloat), NULL,GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * 4 * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(GLfloat), 3 * 4 * sizeof(GLfloat),colors);
	
	GLuint loc;
	loc = glGetAttribLocation(prog, "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	loc = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(3 * 4 *sizeof(GLfloat)));
	
	glBindVertexArray(vao[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * 4 * sizeof(GLfloat), NULL,GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * 4 * sizeof(GLfloat), vertices2);
	glBufferSubData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(GLfloat), 4 * 4 * sizeof(GLfloat),colors2);
	loc = glGetAttribLocation(prog, "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	loc = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(4 * 4 *sizeof(GLfloat)));

	glBindVertexArray(vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 5 * 4 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 5 * 4 * sizeof(GLfloat), vertices3);
	glBufferSubData(GL_ARRAY_BUFFER, 5 * 4 * sizeof(GLfloat), 5 * 4 * sizeof(GLfloat), colors3);
	loc = glGetAttribLocation(prog, "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	loc = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(5 * 4 * sizeof(GLfloat)));
}

void mykeyboard(unsigned  char key, int x, int y) {
	switch (key) {
	case 27: // ESCAPE
		exit(0);
		break;
	}
}

float dist = 0;
void mydisplay(void) {
	// clear 
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // gray
	glClear(GL_COLOR_BUFFER_BIT);
	GLuint loc;

	loc = glGetUniformLocation(prog, "udist");
	glUniform1f(loc, dist);

	glBindVertexArray(vao[0]);
	glDrawArrays(GL_POLYGON, 0, 3);

	glBindVertexArray(vao[1]);
	glDrawArrays(GL_POLYGON, 0, 4);

	glBindVertexArray(vao[2]);
	glDrawArrays(GL_POLYGON, 0, 5);

	glFlush();
	glutSwapBuffers();
}
void myreshape(int x, int y)
{
	glViewport(0, 0, x, y);
}

void myidle(void)
{
	dist += 0;
	if (dist > 1.0)
		dist = 0;
	printf("dist %f\n", dist);
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("*** 2015113775 ¼Õ¼¼Çù ***");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	//glutReshapeFunc(myreshape);
	//glutIdleFunc(myidle);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}