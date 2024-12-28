#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define GLSW 1000
#define GLSH 700

typedef struct {
	int w, s;
} ButtonKeys; ButtonKeys Keys;

typedef struct {
    float x, y, z;
} point;

typedef struct {
    point p1, p2;
} line;
line lines[12];

typedef struct {
    point p1, p2, p3, p4;
} quad;
quad quads[6];

int fr1 = 0, fr2 = 0;
float fov = 10.0;
float zoom = 1.0;

void init() {
    point p1 = {-1, -1, -1};
    point p2 = {-1, -1, 1};
    point p3 = {1, -1, 1};
    point p4 = {1, -1, -1};
    point p5 = {-1, 1, -1};
    point p6 = {-1, 1, 1};
    point p7 = {1, 1, 1};
    point p8 = {1, 1, -1};

    lines[0] = (line) {p1, p2};
    lines[1] = (line) {p2, p3};
    lines[2] = (line) {p3, p4};
    lines[3] = (line) {p4, p1};
    lines[4] = (line) {p5, p6};
    lines[5] = (line) {p6, p7};
    lines[6] = (line) {p7, p8};
    lines[7] = (line) {p8, p5};
    lines[8] = (line) {p1, p5}; 
    lines[9] = (line) {p2, p6};
    lines[10] = (line) {p3, p7};
    lines[11] = (line) {p4, p8};

    quads[0] = (quad) {p1, p2, p3, p4};
    quads[1] = (quad) {p5, p6, p7, p8};
    quads[2] = (quad) {p1, p2, p6, p5};
    quads[3] = (quad) {p2, p3, p7, p6};
    quads[4] = (quad) {p3, p4, p8, p7};
    quads[5] = (quad) {p4, p1, p5, p8};

}

void rotateX(float* y, float* z) {
    float rot = (float) fr1 / 3000.0 * (M_PI);
    float temp_y = *y;
    temp_y = cos(rot) * (*y) - sin(rot) * (*z);
    *z = sin(rot) * (*y) + cos(rot) * (*z);
    *y = temp_y;
}

void rotateY(float* x, float* z) {
    float rot = (float) fr1 / 3000.0 * (M_PI);
    float temp_x = *x;
    temp_x = cos(rot) * (*x) - sin(rot) * (*z);
    *z = sin(rot) * (*x) + cos(rot) * (*z);
    *x = temp_x;
}

void drawLines(){
    for (int x = 0; x < 12; x++) {
        line currentLine = lines[x];
        float rotatedX1 = currentLine.p1.x;
        float rotatedY1 = currentLine.p1.y;
        float rotatedZ1 = currentLine.p1.z;
        float rotatedX2 = currentLine.p2.x;
        float rotatedY2 = currentLine.p2.y;
        float rotatedZ2 = currentLine.p2.z;

        rotateY(&rotatedX1, &rotatedZ1);
        rotateY(&rotatedX2, &rotatedZ2);
        rotateX(&rotatedY1, &rotatedZ1);
        rotateX(&rotatedY2, &rotatedZ2);

        glLineWidth(zoom * 2);
        glColor3ub(255, 255, 255);
	    glBegin(GL_LINES);
	    glVertex2i(GLSW / 2 + (zoom * fov * rotatedX1) / (fov + rotatedZ1)*50.0, GLSH / 2 + (zoom * fov * rotatedY1) / (fov + rotatedZ1)*50.0);
	    glVertex2i(GLSW / 2 + (zoom * fov * rotatedX2) / (fov + rotatedZ2)*50.0, GLSH / 2 + (zoom * fov * rotatedY2) / (fov + rotatedZ2)*50.0);
	    glEnd();
    }
}

void drawPlanes() {
    // Sort planes
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5 - x; y++) {
                float rotatedX1 = quads[y].p1.x;
                float rotatedY1 = quads[y].p1.y;
                float rotatedZ1 = quads[y].p1.z;
                float rotatedX2 = quads[y].p2.x;
                float rotatedY2 = quads[y].p2.y;
                float rotatedZ2 = quads[y].p2.z;
                float rotatedX3 = quads[y].p3.x;
                float rotatedY3 = quads[y].p3.y;
                float rotatedZ3 = quads[y].p3.z;
                float rotatedX4 = quads[y].p4.x;
                float rotatedY4 = quads[y].p4.y;
                float rotatedZ4 = quads[y].p4.z;
                rotateY(&rotatedX1, &rotatedZ1);
                rotateY(&rotatedX2, &rotatedZ2);
                rotateY(&rotatedX3, &rotatedZ3);
                rotateY(&rotatedX4, &rotatedZ4);
                rotateX(&rotatedY1, &rotatedZ1);
                rotateX(&rotatedY2, &rotatedZ2);
                rotateX(&rotatedY3, &rotatedZ3);
                rotateX(&rotatedY4, &rotatedZ4);
                float AavgZ = (rotatedZ1 + rotatedZ2 + rotatedZ3 + rotatedZ4) / 4.0;

                rotatedX1 = quads[y+1].p1.x;
                rotatedY1 = quads[y+1].p1.y;
                rotatedZ1 = quads[y+1].p1.z;
                rotatedX2 = quads[y+1].p2.x;
                rotatedY2 = quads[y+1].p2.y;
                rotatedZ2 = quads[y+1].p2.z;
                rotatedX3 = quads[y+1].p3.x;
                rotatedY3 = quads[y+1].p3.y;
                rotatedZ3 = quads[y+1].p3.z;
                rotatedX4 = quads[y+1].p4.x;
                rotatedY4 = quads[y+1].p4.y;
                rotatedZ4 = quads[y+1].p4.z;
                rotateY(&rotatedX1, &rotatedZ1);
                rotateY(&rotatedX2, &rotatedZ2);
                rotateY(&rotatedX3, &rotatedZ3);
                rotateY(&rotatedX4, &rotatedZ4);
                rotateX(&rotatedY1, &rotatedZ1);
                rotateX(&rotatedY2, &rotatedZ2);
                rotateX(&rotatedY3, &rotatedZ3);
                rotateX(&rotatedY4, &rotatedZ4);
                float BavgZ = (rotatedZ1 + rotatedZ2 + rotatedZ3 + rotatedZ4) / 4.0;

                if (AavgZ < BavgZ) {
                    quad temp = quads[y];
                    quads[y] = quads[y+1];
                    quads[y+1] = temp;
                }
        }
    }

    for (int x = 0; x < 6; x++) {
        quad currentQuad = quads[x];
        float rotatedX1 = currentQuad.p1.x;
        float rotatedY1 = currentQuad.p1.y;
        float rotatedZ1 = currentQuad.p1.z;
        float rotatedX2 = currentQuad.p2.x;
        float rotatedY2 = currentQuad.p2.y;
        float rotatedZ2 = currentQuad.p2.z;
        float rotatedX3 = currentQuad.p3.x;
        float rotatedY3 = currentQuad.p3.y;
        float rotatedZ3 = currentQuad.p3.z;
        float rotatedX4 = currentQuad.p4.x;
        float rotatedY4 = currentQuad.p4.y;
        float rotatedZ4 = currentQuad.p4.z;

        rotateY(&rotatedX1, &rotatedZ1);
        rotateY(&rotatedX2, &rotatedZ2);
        rotateY(&rotatedX3, &rotatedZ3);
        rotateY(&rotatedX4, &rotatedZ4);
        rotateX(&rotatedY1, &rotatedZ1);
        rotateX(&rotatedY2, &rotatedZ2);
        rotateX(&rotatedY3, &rotatedZ3);
        rotateX(&rotatedY4, &rotatedZ4);

        point centerPoint = (point) {(rotatedX1 + rotatedX2 + rotatedX3 + rotatedX4) / 4.0, (rotatedY1 + rotatedY2 + rotatedY3 + rotatedY4) / 4.0, (rotatedZ1 + rotatedZ2 + rotatedZ3 + rotatedZ4) / 4.0};

        glLineWidth(zoom * 2);
        glColor3ub((centerPoint.x + 1) / 2 * 255, (centerPoint.y + 1) / 2 * 255, (centerPoint.z + 1) / 2 * 255);
	    glBegin(GL_QUADS);
	    glVertex2i(GLSW / 2 + (zoom * fov * rotatedX1) / (fov + rotatedZ1)*50.0, GLSH / 2 + (zoom * fov * rotatedY1) / (fov + rotatedZ1)*50.0);
	    glVertex2i(GLSW / 2 + (zoom * fov * rotatedX2) / (fov + rotatedZ2)*50.0, GLSH / 2 + (zoom * fov * rotatedY2) / (fov + rotatedZ2)*50.0);
        glVertex2i(GLSW / 2 + (zoom * fov * rotatedX3) / (fov + rotatedZ3)*50.0, GLSH / 2 + (zoom * fov * rotatedY3) / (fov + rotatedZ3)*50.0);
	    glVertex2i(GLSW / 2 + (zoom * fov * rotatedX4) / (fov + rotatedZ4)*50.0, GLSH / 2 + (zoom * fov * rotatedY4) / (fov + rotatedZ4)*50.0);
	    glEnd();
    }
}

void clearBackground(){
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, GLSH);
    glVertex2i(GLSW, GLSH);
    glVertex2i(GLSW, 0);
    glEnd();
}

void takeInput() {
    if (Keys.w == 1 && Keys.s == 0)
        zoom *= 1.1;
    else if (Keys.w == 0 && Keys.s == 1)
        zoom /= 1.1;
}

void display() { 
    if(fr1-fr2>=50) {
        fr2 = fr1;
        clearBackground();
        takeInput();
        drawLines();
        drawPlanes();
        glutSwapBuffers();
        glutReshapeWindow(GLSW, GLSH);
    }
    fr1 = glutGet(GLUT_ELAPSED_TIME);
    glutPostRedisplay();
}

void ButtonDown(unsigned char key, int x, int y) {
	if (key == 'w') Keys.w=1;
	if (key == 's') Keys.s=1;
	glutPostRedisplay();
}

void ButtonUp(unsigned char key, int x, int y) {
	if (key == 'w') Keys.w=0;
	if (key == 's') Keys.s=0;
	glutPostRedisplay();
}

int main (int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(GLSW / 2, GLSH / 2);
	glutInitWindowSize(GLSW, GLSH);
	glutCreateWindow("Renderer");
	gluOrtho2D(0, GLSW, 0, GLSH);
	init();
    glutKeyboardFunc(ButtonDown);
	glutKeyboardUpFunc(ButtonUp);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}