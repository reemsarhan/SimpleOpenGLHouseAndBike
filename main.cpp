
#ifdef __APPLE__
#include <GLUTglut.h>
#else

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#endif


using namespace std;

GLfloat Cx=-2,Cy=3,Cz=3;

void MyInit() {
    glClearColor(0.086, 0.62, 0.52, 1);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 8);

    glMatrixMode(GL_MODELVIEW);
}

GLfloat doorAngle = 0, windowAngle = 0, bx = 0, rightWheelAngle = 0, leftWheelAngle = 0, bikeRotationAngle = 0;
GLfloat targetRightWheelAngle = 0, targetLeftWheelAngle = 0;
bool doorOpen = false, windowOpen = false, bikeRotation = false;

void Spin(){
    if(doorOpen){
        if(doorAngle < 90)
            doorAngle += 0.7;
    }
    else{
        if(doorAngle > 0)
            doorAngle -= 0.7;
    }
    if(windowOpen){
        if(windowAngle < 90)
            windowAngle += 0.7;
    }
    else{
        if(windowAngle > 0)
            windowAngle -= 0.7;
    }

    if(rightWheelAngle < targetRightWheelAngle)rightWheelAngle += 5;
    if(leftWheelAngle < targetLeftWheelAngle)leftWheelAngle += 5;

    if(bikeRotation)
        bikeRotationAngle += 0.5;

    glutPostRedisplay();
}

void Key(unsigned char ch,int x,int y){
    switch(ch){

        case 'x': Cx-=0.1;break;
        case 'X': Cx+=0.1;break;
        case 'y': Cy-=0.1;break;
        case 'Y': Cy+=0.1;break;
        case 'z': Cz-=0.1;break;
        case 'Z': Cz+=0.1;break;
        case 'o': doorOpen = true;break;
        case 'c': doorOpen = false;break;
        case 'O': windowOpen = true;break;
        case 'C': windowOpen = false;break;
        case 'f': bx += 0.2;break;
        case 'b': bx -= 0.2;break;
        case 'r': targetRightWheelAngle += 45;break;
        case 'l': targetLeftWheelAngle += 45;break;
    }
    glutPostRedisplay();
}


void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        bikeRotation = true;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        bikeRotation = false;
    }
}

void drawFace(GLdouble p1[], GLdouble p2[], GLdouble p3[], GLdouble p4[]){
    glPushMatrix();
    glBegin(GL_POLYGON);

    glVertex3dv(p1);
    glVertex3dv(p2);
    glVertex3dv(p3);
    glVertex3dv(p4);

    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_LINE_LOOP);

    glColor3d(0, 0, 0);

    glVertex3dv(p1);
    glVertex3dv(p2);
    glVertex3dv(p3);
    glVertex3dv(p4);

    glEnd();
    glPopMatrix();
}

void drawCuboid(double x, double y, double z, double width, double length, double height, double color[]){
    GLdouble p[8][3] = {{x - width / 2, y + height, z},
                        {x + width / 2, y + height, z},
                        {x - width / 2, y, z},
                        {x + width / 2, y, z},

                        {x - width / 2, y + height, z - length},
                        {x + width / 2, y + height, z - length},
                        {x - width / 2, y, z - length},
                        {x + width / 2, y, z - length}
                      };



    //front Face
    glColor3dv(color);
    drawFace(p[0], p[1], p[3], p[2]);

    //back Face
    glColor3dv(color);
    drawFace(p[4], p[5], p[7], p[6]);

    //Top Face
    glColor3dv(color);
    drawFace(p[0], p[1], p[5], p[4]);

    //Bottom Face
    glColor3dv(color);
    drawFace(p[2], p[3], p[7], p[6]);

    //right Face
    glColor3dv(color);
    drawFace(p[1], p[3], p[7], p[5]);

    //left Face
    glColor3dv(color);
    drawFace(p[0], p[2], p[6], p[4]);
}

//------------------
//------------------
//------------------
double floorWidth = 0.7, floorLength = 0.6, floorHeight = 0.45;

void drawFloor(double x, double y, double z){

    double color[3] = {222.0/255,184.0/255,135.0/255};
    drawCuboid(x, y, z, floorWidth, floorLength, floorHeight, color);
}

void drawTriangle(GLdouble p1[], GLdouble p2[], GLdouble p3[]){

    glPushMatrix();
    glBegin(GL_TRIANGLES);

    glVertex3dv(p1);
    glVertex3dv(p2);
    glVertex3dv(p3);

    glEnd();
    glPopMatrix();


    glPushMatrix();
    glBegin(GL_LINE_LOOP);

    glColor3d(0, 0, 0);

    glVertex3dv(p1);
    glVertex3dv(p2);
    glVertex3dv(p3);

    glEnd();
    glPopMatrix();
}

double roofHeight = 0.5;

void drawRoof(double x, double y, double z){
    GLdouble p[6][3] = {{x - floorWidth / 2, y, z},
                        {x + floorWidth / 2, y, z},
                        {x, y + roofHeight, z},

                        {x - floorWidth / 2, y, z - floorLength},
                        {x + floorWidth / 2, y, z - floorLength},
                        {x, y + roofHeight, z - floorLength}
                      };

    //Front triangle
    //glColor3d(139.0 / 255, 69.0 / 255, 19.0 / 255);
    glColor3d(98.0 / 255, 42.0 / 255, 15.0 / 255);
    drawTriangle(p[0], p[1], p[2]);

    //Back triangle
    //glColor3d(139.0 / 255, 69.0 / 255, 19.0 / 255);
    glColor3d(98.0 / 255, 42.0 / 255, 15.0 / 255);
    drawTriangle(p[3], p[4], p[5]);

    //Right face
    //glColor3d(139.0 / 255, 69.0 / 255, 19.0 / 255);
    glColor3d(98.0 / 255, 42.0 / 255, 15.0 / 255);
    drawFace(p[1], p[3], p[5], p[4]);

    //Left face
    //glColor3d(139.0 / 255, 69.0 / 255, 19.0 / 255);
    glColor3d(98.0 / 255, 42.0 / 255, 15.0 / 255);
    drawFace(p[0], p[3], p[5], p[2]);

}


double windowWidth = 0.2, windowHeight = 0.2;

void drawWindow(double x, double y, double z){

    GLdouble p[6][3] = {{x, y, z},
                             {x + windowWidth / 2, y, z},
                             {x + windowWidth / 2, y + windowHeight, z},
                             {x, y + windowHeight, z},
                             {x - windowWidth / 2, y + windowHeight, z},
                             {x - windowWidth / 2, y, z}
                            };

    //Right face
    glColor3d(1, 1, 1);
    drawFace(p[0], p[3], p[2], p[1]);

    for(int i = 0; i < 6; ++i)p[i][2] += 0.01;
    glPushMatrix();
    glColor3d(139.0 / 255, 69.0 / 255, 19.0 / 255);
    glTranslated(x + windowWidth / 2, y, z);
    glRotated(windowAngle, 0, 1, 0);
    glTranslated(-(x + windowWidth / 2), -y, -z);
    drawFace(p[0], p[3], p[2], p[1]);
    glPopMatrix();
    for(int i = 0; i < 6; ++i)p[i][2] -= 0.01;

    //Left face
    glColor3d(1, 1, 1);
    drawFace(p[0], p[3], p[4], p[5]);

    for(int i = 0; i < 6; ++i)p[i][2] += 0.01;
    glPushMatrix();
    glColor3d(139.0 / 255, 69.0 / 255, 19.0 / 255);
    glTranslated(x - windowWidth / 2, y, z);
    glRotated(-windowAngle, 0, 1, 0);
    glTranslated(-(x - windowWidth / 2), -y, -z);
    drawFace(p[0], p[3], p[4], p[5]);
    glPopMatrix();
    for(int i = 0; i < 6; ++i)p[i][2] -= 0.01;
}

double doorWidth = 0.15, doorHeight = 0.3;

void drawDoor(double x, double y, double z){
    GLdouble p[4][3] = {{x - doorWidth / 2, y, z},
                        {x + doorWidth / 2, y, z},
                        {x - doorWidth / 2, y + doorHeight, z},
                        {x + doorWidth / 2, y + doorHeight, z}
                       };

    glColor3d(1, 1, 1);
    drawFace(p[0], p[2], p[3], p[1]);

    p[0][2] += 0.01;
    p[1][2] += 0.01;
    p[2][2] += 0.01;
    p[3][2] += 0.01;

    glColor3d(98.0 / 255, 42.0 / 255, 15.0 / 255);
    glPushMatrix();
    glTranslated(x + doorWidth / 2, y, z);
    glRotated(doorAngle, 0, 1, 0);
    glTranslated(-(x + doorWidth / 2), -y, -z);
    drawFace(p[0], p[2], p[3], p[1]);
    glPopMatrix();
}

void drawBuilding(){

    int numFloors = 4;
    for(int i = 0; i < numFloors; ++i){
        double x = 0, y = -i * (floorHeight + 0.003) + 0.7, z = 0;
        drawFloor(x, y, z);
        if(i != numFloors - 1){
            drawWindow(x - floorWidth / 4, y + floorHeight / 4, z + 0.001);
            drawWindow(x + floorWidth / 4, y + floorHeight / 4, z + 0.001);
        }
        else{
            drawDoor(x, y, z + 0.001);
        }

        if(i == 0){
           drawRoof(x, y + floorHeight, z);
        }

    }
}

//------------------
//------------------
//------------------
double wheelDist = 0.2, wheelInnerRadius = 0.02, wheelOuterRadius = 0.05, wheelSides = 10, wheelRings = 10;
double bikeWidth = wheelDist + wheelOuterRadius * 2, bikeLength = 0.02, bikeHeight = 0.01;

void drawBikeBody(double x, double y, double z){
    double color[3] = {0, 0, 0};

    //Draw bottom
    drawCuboid(x, y, z, bikeWidth, bikeLength, bikeHeight, color);

    //Draw handle
    drawCuboid(x + bikeWidth / 3, y + bikeHeight, z, bikeWidth / 16, bikeLength / 4, bikeHeight * 11, color);
    drawCuboid(x + bikeWidth / 3, y + bikeHeight + bikeHeight * 11, z + 0.15,
               bikeWidth / 16, 0.15 * 2 + bikeLength / 4, bikeHeight * 3, color);

    //Draw Chair
    drawCuboid(x, y + bikeHeight, z, bikeWidth / 4, bikeLength, bikeHeight * 3, color);
}

void drawWheel(double x, double y, double z, double angle){
    glPushMatrix();

    glTranslated(x, y, z);
    glRotated(angle, 0, 0, 1);

    glutSolidTorus(wheelInnerRadius, wheelOuterRadius, wheelSides, wheelRings);

    glPopMatrix();
}

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); // get the current angle

        float x = r * cosf(theta); // calculate the x component
        float y = r * sinf(theta); // calculate the y component

        glVertex2f(x + cx, y + cy); // output vertex
    }
    glEnd();
}

void drawBicycle(){

    double x = -0.1, y = -3 * (floorHeight + 0.003) + 0.7, z = 2;

    //Left wheel
    glPushMatrix();
    glTranslated(x, y - 0.01, 0.001 - floorLength / 2);
    glRotated(bikeRotationAngle, 0, 1, 0);
    glTranslated(-x, -(y - 0.01), -(0.001 - floorLength / 2));
    drawWheel(x + bx, y, z, leftWheelAngle);
    glPopMatrix();

    //Right wheel
    glPushMatrix();
    glTranslated(x, y - 0.01, 0.001 - floorLength / 2);
    glRotated(bikeRotationAngle, 0, 1, 0);
    glTranslated(-x, -(y - 0.01), -(0.001 - floorLength / 2));
    drawWheel(x + wheelDist + bx, y, z, rightWheelAngle);
    glPopMatrix();

    //Bike body
    glPushMatrix();
    glTranslated(x, y - 0.01, 0.001 - floorLength / 2);
    glRotated(bikeRotationAngle, 0, 1, 0);
    glTranslated(-x, -(y - 0.01), -(0.001 - floorLength / 2));
    drawBikeBody(x + wheelDist / 2 + bx, y + wheelOuterRadius + 0.01, z);
    glPopMatrix();


    //Circular Road
    double roadInnerRadius = bx * bx + (z - (0.001 - floorLength / 2)) * (z - (0.001 - floorLength / 2)), roadOuterRadius = roadInnerRadius + 2;
    glPushMatrix();
    glTranslated(x, y - 0.01, 0.001 - floorLength / 2);
    glRotated(90, 1, 0, 0);
    glTranslated(-x, -(y - 0.01), -(0.001 - floorLength / 2));
    drawCircle(x, y - 0.01, roadInnerRadius / 2 - 0.7, 10000);
    drawCircle(x, y - 0.01, roadOuterRadius / 2 - 0.7, 10000);
    glPopMatrix();
}


void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(Cx, Cy, Cz, 0.005, 0.01, -0.01, 0, 1, 0);

    drawBuilding();
    drawBicycle();

    glutSwapBuffers();
}


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    glutInitWindowPosition(50, 20);
    glutInitWindowSize(1800, 1000);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Graphics Project");
    MyInit();
    glutIdleFunc(Spin);
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(Key);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}
