#include <iostream>

#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <windows.h>
	#include <gl/gl.h>
	#include <gl/glu.h>
    #include <gl/glut.h>
#endif

void init_camera(void);

void draw_scene(void);

void display(void);

void init (void);