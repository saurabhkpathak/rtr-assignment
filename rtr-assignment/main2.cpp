/*
  Simple Demo for GLSL 2.0
  www.lighthouse3d.com
  (slightly modified)

*/
#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GL/glut.h>
#include "textfile.h"


GLuint v,f,p;
float lpos[4] = {1,0.5,1,0};
float rot = 0; 


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);


}


void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0, 
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lpos);
	glPushMatrix();
	glRotatef(rot, 0, 1, 0);
	glutSolidTeapot(1);
	glPopMatrix();
	glutSwapBuffers();
}


void setFragmentShader() {

	char *vs = NULL, *fs = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("refraction.vert");
	fs = textFileRead("refraction.frag");

	const char * ff = fs;
	const char * vv = vs;

	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);

	free(vs); free(fs);

	glCompileShader(v);
	glCompileShader(f);

	p = glCreateProgram();
	glAttachShader(p, f);
	glAttachShader(p, v);

	glLinkProgram(p);
	glUseProgram(p);
}

/*void setShader(int choice) {
	switch (choice) {
	case 1:
		setFragmentShader();
		break;
	case 2:
		setDiffuseShader();
		break;
	case 3:
		setPhongShader();
		break;
	case 4:
		setToonShader();
		break;
	case 5:
		setGoochShader();
		break;
	case 6:
		setGlossyShader();
		break;
	default:
		setFragmentShader();
	}
}*/

void processNormalKeys(unsigned char key, int x, int y) {

	switch (key)
	{
	case 27: 
		exit(0);
	case 'a':
		rot -= 5;
		break;
	case 'd':
		rot += 5;
		break;
	/*case '1':
		setShader(1);
		break;
	case '2':
		setShader(2);
		break;
	case '3':
		setShader(3);
		break;
	case '4':
		setShader(4);
		break;
	case '5':
		setShader(5);
		break;
	case '6':
		setShader(6);
		break;*/
	}

	glutPostRedisplay();
}


int main3(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("GLSL Example");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,0.0,0.0,1.0);
//	glEnable(GL_CULL_FACE);

	glewInit();
	
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}

	// 1: fragment Shader
	// 2. Diffuse Shader
	// 3. Phong Shader
	// 4. Toon Shader
	// 5. Gooch Shader0
	// 6. Glossy Shader
	setFragmentShader();

	glutMainLoop();

	return 0;
}

