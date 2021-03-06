/*
 * Copyright (C) 2019  Mike Goppold von Lobsdorf
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * Drawing implementation for primitive graphics routines
 */

void Draw1::drawTriangle(
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3) {
	
	glBegin(GL_TRIANGLES);
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y2, z2);
		glVertex3f(x3, y3, z3);
	glEnd();
}

void Draw1::drawScene() {
	if(FALSE) {
		glClearColor(1,1,0,1);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}

	if(TRUE) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		drawTriangle(
			0.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f);
	}
}

int doubleBufferedAttribList [] = {
	GLX_RGBA, GLX_DOUBLEBUFFER,
	GLX_RED_SIZE, 4,
	GLX_GREEN_SIZE, 4,
	GLX_BLUE_SIZE, 4,
	GLX_DEPTH_SIZE, 16,
	None
};

static Bool WaitForNotify(Display *d, XEvent *e, char *arg) {
	return (e->type == MapNotify) && (e->xmap.window == (Window)arg);
}

int Draw1::main() {
	Display *dpy;
	XEvent event;
	Window win;
	GLXContext gl2Context;
	XSetWindowAttributes swa;

	dpy = XOpenDisplay(0);
	if(dpy == NULL) {
		printf("Could not open the display\n");
		return 1;
	}

	XVisualInfo* vi = NULL;
	//Attempt to create a double buffered window
	vi = glXChooseVisual(dpy, DefaultScreen(dpy), doubleBufferedAttribList);
	if(vi == NULL) {
		printf("Could not create a double buffered window\n");
		return 1;
	}


	//Create a GL 2.1 context
	gl2Context = glXCreateContext(dpy, vi, 0, GL_TRUE);

	if(gl2Context == NULL) {
		printf("Could not create a GL 2.1 context, please check your graphics drivers\n");
		return 1;
	}

	Colormap cmap = XCreateColormap(dpy,
		RootWindow(dpy, vi->screen),
		vi->visual, AllocNone);

	swa.colormap = cmap;
	swa.border_pixel = 0;
	swa.event_mask = StructureNotifyMask;

	win = XCreateWindow(dpy, RootWindow(dpy, vi->screen),
		0, 0, 640, 480, 0, vi->depth, InputOutput, vi->visual,
		CWBorderPixel | CWColormap | CWEventMask, &swa);
	XMapWindow(dpy, win);
	XIfEvent(dpy, &event, WaitForNotify, (char*)win);

	glXMakeCurrent(dpy, win, gl2Context);
	
	drawScene();
	
	glXSwapBuffers(dpy, win);

	sleep(10);	
	return 0;
}
