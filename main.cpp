#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <cstdlib>
#include <ctime>
using namespace std;

float boatA=0.0f;
float boatAspeed = 0.5f;
float boatB= 0.0f;
float boatBspeed = 0.5f;
float cloud = 0.0f;
float cloudSpeed = 0.5f;
float move33 = 0.0f;
float move33speed = 4.0f;
float rotationAngle = 0.0f;
float trainX =0.0f;
float trainSpeed = 1.0f;
float turbineAngle = 0.0f;
float rainDropY[100];
float rainDropX[100];
bool isTrainMoving = true;
bool isRotating = true;
bool isDay = true;
bool Blink = false;
bool isPlaneMoving = true;
bool isRaining = false;



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initScreen()
{
    glColor3f(1.0, 1.0, 1.0);   //white color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1500,0,700);
}

/////////////////////////////////////////////////////////// ALL Functions ////////////////////////////////////////////////////////////

void drawCircle(float centerX, float centerY, float radius, float rColor, float gColor, float bColor) {
    glColor3f(rColor, gColor, bColor);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float pi = 3.1416;
        float angle = (i * 2 * pi) / 180;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}

void drawWheel(float cx, float cy)
{
    float radius = 6.0f;
    int segments = 100;

    glColor3f(0.1f, 0.1f, 0.1f); // Black
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++)
    {
        float angle = 2.0f * 3.1416f * i / segments;
        float x = cx + cos(angle) * radius;
        float y = cy + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();
}

void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void toggle(int value)
{
    Blink = !Blink;                 // Toggle the boolean
    glutPostRedisplay();
    glutTimerFunc(100, toggle, 0);

}

void toggle2(int value)
{
    Blink = !Blink;                 // Toggle the boolean
    glutPostRedisplay();                    // Request redraw

}

////////////////////////////////////////////////// ALL Update Function ////////////////////


void boatUpdate()
{
    //boat  A moving from left to right
    boatA += boatAspeed;

    if(boatA >1800)
        boatA = -300;

         //boat  B moving from right to left
    boatB -= boatBspeed;

    if(boatB < -900)
        boatB = 1800;
}

void trainUpdate()
{
    if(isTrainMoving){
        trainX += trainSpeed;

    if(trainX > 1500)
        trainX =-600;
    }

}

void turbineUpdate(int value)
{
    turbineAngle += 7.0f;
    if (turbineAngle > 360.0f) turbineAngle -= 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, turbineUpdate, 0);  // ~60 FPS
}

void PlaneMove(int value)
{
    if (isPlaneMoving) {
        move33 -= move33speed;
        if (move33 < -1800) {
            move33 = 1800;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(20, PlaneMove, 0);  // Correct function pointer usage
}

void updateRain() {
    for (int i = 0; i < 100; i++) {
        rainDropY[i] -= 15;  // Move drops down
        if (rainDropY[i] < 0) {
            rainDropY[i] = 800;  // Reset to top
            rainDropX[i] = rand() % 1500;  // Random X position
        }
    }
}

void MovingPart(int value) {
    cloud += cloudSpeed;
    if (cloud > 1500)
        cloud = -150;
    if (isRaining)
        updateRain();
    glutPostRedisplay();
    glutTimerFunc(20, MovingPart, 0);
}

void Rain(int value)
{
    if (isRaining)
        updateRain();
    glutPostRedisplay();
    glutTimerFunc(16, Rain, 0);
}


//////////////////////////////////////////////////////////////////////// Drawing /////////////////////////////////////////////////////////


///////////////////////////////////////////////Upper Side/////////////////////////////////////////////////
void sky()
{
    if(isDay)
    {
    glColor3f(0.60f, 0.81f, 0.98f); // Sky blue color (RGB) Day
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(1500,0);
    glVertex2f(1500,700);
    glVertex2f(0,700);
    glEnd();}

    else{
    glColor3ub(11,12,40); // Sky dark blue color (RGB) Night
    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(1500,0);
    glVertex2f(1500,700);
    glVertex2f(0,700);
    glEnd();

    if(Blink){
        drawCircle(1100,600,1,1.0,1.0,1.0);
    drawCircle(1200,660,1,1.0,1.0,1.0);
    drawCircle(1300,550,1,1.0,1.0,1.0);
    drawCircle(100,600,1,1.0,1.0,1.0);
    drawCircle(200,550,1,1.0,1.0,1.0);
    drawCircle(400,600,1,1.0,1.0,1.0);
    drawCircle(300,640,1,1.0,1.0,1.0);
    drawCircle(800,600,1,1.0,1.0,1.0);
    drawCircle(600,670,1,1.0,1.0,1.0);
    }
    else{
    drawCircle(1100,600,1,0.0,0.0,0.0);
    drawCircle(1200,660,1,0.0,0.0,0.0);
    drawCircle(1300,550,1,0.0,0.0,0.0);
    drawCircle(100,600,1,0.0, 0.0, 0.0);
    drawCircle(200,550,1,0.0, 0.0, 0.0);
    drawCircle(400,600,1,0.0, 0.0, 0.0);
    drawCircle(300,640,1,0.0, 0.0, 0.0);
    drawCircle(800,600,1,0.0, 0.0, 0.0);
    drawCircle(600,670,1,0.0, 0.0, 0.0);
    }

    }



}

void drawPlane()
{
    glPushMatrix();

    glTranslatef(move33, 0.0f, 0.0f);     // Movement
    glScalef(0.5f, 0.5f, 1.0f);          // Scale to 50%

    glTranslatef(1100.0f, 690.0f, 0.0f); // Adjust position after scaling

    // Plane Base
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(-30, 600);
        glVertex2f(100, 600);
        glVertex2f(100, 650);
        glVertex2f(-30, 650);
    glEnd();

    // Plane Front Bottom
    glColor3f(0.0, 0.0, 0.5);
    glBegin(GL_QUADS);
        glVertex2f(-60, 610);
        glVertex2f(-30, 600);
        glVertex2f(-30, 625);
        glVertex2f(-60, 625);
    glEnd();

    // Plane Front Top
    glColor3f(0.4, 0.0, 0.4);
    glBegin(GL_QUADS);
        glVertex2f(-60, 625);
        glVertex2f(-30, 625);
        glVertex2f(-30, 650);
        glVertex2f(-40, 650);
    glEnd();

    // Lower Wing
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_QUADS);
        glVertex2f(20, 580);
        glVertex2f(60, 580);
        glVertex2f(50, 620);
        glVertex2f(10, 620);
    glEnd();

    // Upper Wing
    glBegin(GL_QUADS);
        glVertex2f(0, 650);
        glVertex2f(40, 650);
        glVertex2f(50, 690);
        glVertex2f(15, 690);
    glEnd();

    // Tail Fin
    glBegin(GL_QUADS);
        glVertex2f(80, 650);
        glVertex2f(100, 650);
        glVertex2f(100, 690);
        glVertex2f(90, 690);
    glEnd();

    glPopMatrix();
}





void drawCloud(){
    glPushMatrix();
    glTranslatef(cloud,0.0,0.0);
    //cloud 1
    drawCircle(30, 600, 30,1.0,1.0,1.0);
    drawCircle(70, 600, 30,1.0,1.0,1.0);
    drawCircle(110, 600, 30,1.0,1.0,1.0);
    drawCircle(70, 620, 30,1.0,1.0,1.0);

    //cloud 2
    drawCircle(200, 650, 30,1.0,1.0,1.0);
    drawCircle(240, 650, 30,1.0,1.0,1.0);
    drawCircle(280, 650, 30,1.0,1.0,1.0);
    drawCircle(240, 670, 30,1.0,1.0,1.0);

    glPopMatrix();
}

void sun()
{
    if(isDay){
        drawCircle(700,600,30,1.0,0.70,0.0);
    }
    else{
        drawCircle(700,600,30,1.0,1.0,1.0);
    }

}

void drawRain() {
    glColor3f(1.0, 1.0, 1.0);  // Light blue raindrops
    for (int i = 0; i < 100; i++) {
        glBegin(GL_LINES);
        glVertex2f(rainDropX[i], rainDropY[i]);
        glVertex2f(rainDropX[i], rainDropY[i] - 10);
        glEnd();
    }
}

void drawHill()
{
    glPushMatrix();
    glScalef(1.5,1.35,1.);
    // Green hill 2
    glColor3f(0.1, 0.35, 0.09);
    glBegin(GL_POLYGON);
    glVertex2f(485.1471331652317, 325.5892345736768);
    glVertex2f(450.8281643952328, 311.4578944919123);
    glVertex2f(422.2290237535669, 302.7099220603438);
    glVertex2f(401.3684741090577, 292.9525681943637);
    glVertex2f(724.7069935989501, 287.9056610223049);
    glVertex2f(771.4750000600271, 354.5248356934802);
    glVertex2f(737.1560312900282, 382.1145949007345);
    glVertex2f(712.5944163860092, 402.975144545244);
    glVertex2f(682.3129733536572, 428.5461408836749);
    glVertex2f(673.9014614002261, 431.9107456650473);
    glVertex2f(666.1628704030695, 431.9107456650473);
    glVertex2f(658.76073988405, 426.5273780148514);
    glVertex2f(638.5731111958154, 411.3866564986752);
    glVertex2f(602.9083005132675, 389.1802649416168);
    glVertex2f(561.5236617023863, 366.3009524282838);
    glVertex2f(508.6993666348388, 339.7205746554412);
    glEnd();

    // Green hill 3
    glColor3f(0.06, 0.38, 0.04);
    glBegin(GL_POLYGON);
    glVertex2f(655.2613949161106, 331.8265529875498);
    glVertex2f(631.1674600767025, 327.1632107605675);
    glVertex2f(612.5140911687736, 323.6657040903308);
    glVertex2f(588.0315444771169, 315.1162433408633);
    glVertex2f(553.0564777747503, 296.4628744329342);
    glVertex2f(805.654181736287, 294.5198151716916);
    glVertex2f(803.7111224750445, 355.5318759747096);
    glVertex2f(781.560246896879, 362.526889315183);
    glVertex2f(764.4613253979442, 364.8585604286741);
    glVertex2f(738.812943149542, 364.4699485764256);
    glVertex2f(720, 360);
    glVertex2f(700.7289816291872, 348.9254744864848);
    glVertex2f(677.4122704942761, 338.4329544757746);
    glEnd();
    // Green hill 2
    glColor3f(0.1, 0.35, 0.09);
    glBegin(GL_POLYGON);
    glVertex2f(485.1471331652317, 325.5892345736768);
    glVertex2f(450.8281643952328, 311.4578944919123);
    glVertex2f(422.2290237535669, 302.7099220603438);
    glVertex2f(401.3684741090577, 292.9525681943637);
    glVertex2f(724.7069935989501, 287.9056610223049);
    glVertex2f(771.4750000600271, 354.5248356934802);
    glVertex2f(737.1560312900282, 382.1145949007345);
    glVertex2f(712.5944163860092, 402.975144545244);
    glVertex2f(682.3129733536572, 428.5461408836749);
    glVertex2f(673.9014614002261, 431.9107456650473);
    glVertex2f(666.1628704030695, 431.9107456650473);
    glVertex2f(658.76073988405, 426.5273780148514);
    glVertex2f(638.5731111958154, 411.3866564986752);
    glVertex2f(602.9083005132675, 389.1802649416168);
    glVertex2f(561.5236617023863, 366.3009524282838);
    glVertex2f(508.6993666348388, 339.7205746554412);
    glEnd();

    // Green hill 3
    glColor3f(0.06, 0.38, 0.04);
    glBegin(GL_POLYGON);
    glVertex2f(655.26, 331.83);
    glVertex2f(631.17, 327.16);
    glVertex2f(612.51, 323.67);
    glVertex2f(588.03, 315.12);
    glVertex2f(553.06, 296.46);
    glVertex2f(805.65, 294.52);
    glVertex2f(803.71, 355.53);
    glVertex2f(781.56, 362.53);
    glVertex2f(764.46, 364.86);
    glVertex2f(738.81, 364.47);
    glVertex2f(720.00, 360.00);
    glVertex2f(700.73, 348.93);
    glVertex2f(677.41, 338.43);
    glVertex2f(510.35, 405.34);
    glVertex2f(466.34, 428.20);
    glVertex2f(423.47, 453.35);
    glVertex2f(387.47, 435.06);
    glVertex2f(343.46, 409.91);
    glVertex2f(315.45, 392.77);
    glVertex2f(254.29, 360.19);
    glVertex2f(204.00, 327.61);
    glVertex2f(136.92, 290.25);
    glVertex2f(496.14, 275.56);
    glVertex2f(590.37, 371.05);
    glEnd();

    // Green Hill 2
    glColor3f(0.1f, 0.35f, 0.09f);
    glBegin(GL_POLYGON);
    glVertex2f(485.15f, 325.59f);
    glVertex2f(450.83f, 311.46f);
    glVertex2f(422.23f, 302.71f);
    glVertex2f(401.37f, 292.95f);
    glVertex2f(724.71f, 287.91f);
    glVertex2f(771.48f, 354.52f);
    glVertex2f(737.16f, 382.11f);
    glVertex2f(712.59f, 402.98f);
    glVertex2f(682.31f, 428.55f);
    glVertex2f(673.90f, 431.91f);
    glVertex2f(666.16f, 431.91f);
    glVertex2f(658.76f, 426.53f);
    glVertex2f(638.57f, 411.39f);
    glVertex2f(602.91f, 389.18f);
    glVertex2f(561.52f, 366.30f);
    glVertex2f(508.70f, 339.72f);
    glEnd();

    // Green hill 3
    glColor3f(0.06, 0.38, 0.04);
    glBegin(GL_POLYGON);
    glVertex2f(655.2613949161106, 331.8265529875498);
    glVertex2f(631.1674600767025, 327.1632107605675);
    glVertex2f(612.5140911687736, 323.6657040903308);
    glVertex2f(588.0315444771169, 315.1162433408633);
    glVertex2f(553.0564777747503, 296.4628744329342);
    glVertex2f(805.654181736287, 294.5198151716916);
    glVertex2f(803.7111224750445, 355.5318759747096);
    glVertex2f(781.560246896879, 362.526889315183);
    glVertex2f(764.4613253979442, 364.8585604286741);
    glVertex2f(738.812943149542, 364.4699485764256);
    glVertex2f(720, 360);
    glVertex2f(700.7289816291872, 348.9254744864848);
    glVertex2f(677.4122704942761, 338.4329544757746);
    glEnd();


    // Extra Green Hill 1
glColor3f(0.07f, 0.45f, 0.10f);
glBegin(GL_POLYGON);
    glVertex2f(50.00f, 280.00f);
    glVertex2f(100.00f, 330.00f);
    glVertex2f(150.00f, 360.00f);
    glVertex2f(200.00f, 370.00f);
    glVertex2f(250.00f, 360.00f);
    glVertex2f(300.00f, 340.00f);
    glVertex2f(350.00f, 310.00f);
    glVertex2f(400.00f, 280.00f);
glEnd();

// Extra Green Hill 2
glColor3f(0.05f, 0.30f, 0.08f);
glBegin(GL_POLYGON);
    glVertex2f(800.00f, 290.00f);
    glVertex2f(850.00f, 320.00f);
    glVertex2f(900.00f, 350.00f);
    glVertex2f(950.00f, 360.00f);
    glVertex2f(1000.00f, 355.00f);
    glVertex2f(1050.00f, 340.00f);
    glVertex2f(1100.00f, 310.00f);
    glVertex2f(1150.00f, 280.00f);
glEnd();

// Extra Distant Hill
glColor3f(0.03f, 0.25f, 0.07f);  // Darker green for depth
glBegin(GL_POLYGON);
    glVertex2f(1100.00f, 300.00f);
    glVertex2f(1150.00f, 340.00f);
    glVertex2f(1200.00f, 360.00f);
    glVertex2f(1250.00f, 355.00f);
    glVertex2f(1300.00f, 340.00f);
    glVertex2f(1350.00f, 310.00f);
    glVertex2f(1500.00f, 280.00f);
glEnd();

// Base Hill Range (left side)
    glColor3f(0.08f, 0.4f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 270.0f);
        glVertex2f(40.0f, 300.0f);
        glVertex2f(80.0f, 330.0f);
        glVertex2f(120.0f, 350.0f);
        glVertex2f(160.0f, 340.0f);
        glVertex2f(200.0f, 320.0f);
        glVertex2f(240.0f, 300.0f);
        glVertex2f(280.0f, 270.0f);
    glEnd();

    // Left Hill Cluster
    glColor3f(0.05f, 0.30f, 0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(150.0f, 290.0f);
        glVertex2f(200.0f, 330.0f);
        glVertex2f(250.0f, 350.0f);
        glVertex2f(300.0f, 340.0f);
        glVertex2f(350.0f, 320.0f);
        glVertex2f(400.0f, 290.0f);
    glEnd();

    // Mid-Range Hills already defined by you earlier...

    // Right Hill Cluster
    glColor3f(0.07f, 0.35f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(950.0f, 290.0f);
        glVertex2f(1000.0f, 330.0f);
        glVertex2f(1050.0f, 360.0f);
        glVertex2f(1100.0f, 370.0f);
        glVertex2f(1150.0f, 360.0f);
        glVertex2f(1200.0f, 340.0f);
        glVertex2f(1250.0f, 310.0f);
        glVertex2f(1300.0f, 280.0f);
    glEnd();

    // Distant Far-Right Hill
    glColor3f(0.04f, 0.28f, 0.07f);
    glBegin(GL_POLYGON);
        glVertex2f(1250.0f, 300.0f);
        glVertex2f(1300.0f, 340.0f);
        glVertex2f(1350.0f, 360.0f);
        glVertex2f(1400.0f, 355.0f);
        glVertex2f(1450.0f, 340.0f);
        glVertex2f(1500.0f, 310.0f);
    glEnd();

// Extra Hill between (1100, 400) to (1400, 400)
glColor3f(0.07f, 0.45f, 0.12f);  // Bright green
glBegin(GL_POLYGON);
    glVertex2f(1100.0f, 400.0f);
    glVertex2f(1150.0f, 450.0f);
    glVertex2f(1200.0f, 480.0f);
    glVertex2f(1250.0f, 490.0f);
    glVertex2f(1300.0f, 480.0f);
    glVertex2f(1350.0f, 450.0f);
    glVertex2f(1400.0f, 400.0f);
glEnd();


    glPopMatrix();
}

void drawWTower()
{
    glColor3f(1.0f, 1.0f, 1.0f);  // Bright green
glBegin(GL_QUADS);
    glVertex2f(1100 + 100, 400.0f);
    glVertex2f(1190 + 100, 400.0f);
    glColor3ub(192,192,192);
    glVertex2f(1170 + 100, 650.0f);
    glVertex2f(1120 + 100, 650.0f);
glEnd();

// Windows - 3 horizontal black rectangles
    glColor3f(0.0f, 0.0f, 0.0f);  // Black windows
    for (int i = 0; i < 4; i++)
    {
        float y = 420.0f + i * 60;
        glBegin(GL_QUADS);
            glVertex2f(1225.0f, y);
            glVertex2f(1265.0f, y);
            glVertex2f(1265.0f, y + 20);
            glVertex2f(1225.0f, y + 20);
        glEnd();
    }
    // Red light on top
    if(Blink){
        drawCircle(1245,655,6,1.0,0.0,0.0);
    glEnd();
    }

}


////////////////////////////////////////////////////// Middle Side ////////////////////////////////////////////////////////////

void river()
{
 ///Main river water
if(isDay)
    glColor3f(0.173f, 0.451f, 0.729f);// deep blue
else
    glColor3ub(42,54,66); // Muted Gray-Blue Water Shadow
    glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(1500,0);
        glVertex2f(1500, 400);
        glVertex2f(0, 400);
    glEnd();




}


void drawGround()
{
    // 🌾 Left ground
    glBegin(GL_QUADS);
    glColor3ub(193,200,107);  // Bottom left (darker)
        glVertex2f(0, 100);
        glVertex2f(10, 100);
    glColor3ub(193,200,107);  // Top right (lighter)
        glVertex2f(400, 400);
        glVertex2f(0, 400);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(193,200,107); // Bottom left (darker)
        glVertex2f(0, 100);
        glVertex2f(10, 100);
        glVertex2f(20, 140);
        glVertex2f(40, 160);
        glVertex2f(30, 200);
        glVertex2f(50, 220);
        glVertex2f(40, 250);
        glVertex2f(60, 270);
        glVertex2f(50, 300);
        glVertex2f(70, 320);
        glColor3ub(193,200,107);
        glVertex2f(90, 350);
        glVertex2f(130, 370);
        glVertex2f(200, 400);
        glVertex2f(210, 400);
        glVertex2f(240, 300);
        glVertex2f(230, 200);
        glVertex2f(310, 400);
        glVertex2f(450, 400);
    glEnd();
    // 🌾 Right ground (symmetric)
    glBegin(GL_QUADS);
    glColor3ub(193,200,107);
        glVertex2f(1080, 100);
        glVertex2f(1500, 100);
    glColor3ub(193,200,107);
        glVertex2f(1500, 400);
        glVertex2f(1200, 400);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(193,200,107);  // Bottom left (darker)
        glVertex2f(1080, 100);
        glVertex2f(1090, 100);
        glVertex2f(1100, 140);
        glVertex2f(1140, 160);
        glVertex2f(1130, 200);
        glVertex2f(1150, 220);
        glVertex2f(1140, 250);
        glVertex2f(1160, 270);
        glVertex2f(1250, 300);
        glVertex2f(1070, 320);
        glColor3ub(193,200,107);
        glVertex2f(1090, 350);
        glVertex2f(1130, 370);
        glVertex2f(1200, 400);
        glVertex2f(1210, 400);
        glVertex2f(1240, 300);
        glVertex2f(1230, 200);
        glVertex2f(1310, 400);
        glVertex2f(1150, 400);
    glEnd();

    // 🏠 House 1 (left)
    float baseX = 1300, baseY = 350;
    glColor3f(0.8f, 0.3f, 0.3f); // House body
    glBegin(GL_QUADS);
        glVertex2f(baseX, baseY);
        glVertex2f(baseX + 80, baseY);
        glVertex2f(baseX + 80, baseY + 60);
        glVertex2f(baseX, baseY + 60);
    glEnd();

    glColor3f(0.5f, 0.2f, 0.1f); // Roof
    glBegin(GL_TRIANGLES);
        glVertex2f(baseX - 10, baseY + 60);
        glVertex2f(baseX + 40, baseY + 90);
        glVertex2f(baseX + 90, baseY + 60);
    glEnd();

    // 🏠 House 2 (farther left)
    baseX = 1390; baseY = 360;
    glColor3f(0.3f, 0.5f, 0.8f); // House body
    glBegin(GL_QUADS);
        glVertex2f(baseX, baseY);
        glVertex2f(baseX + 60, baseY);
        glVertex2f(baseX + 60, baseY + 50);
        glVertex2f(baseX, baseY + 50);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f); // Roof
    glBegin(GL_TRIANGLES);
        glVertex2f(baseX - 5, baseY + 50);
        glVertex2f(baseX + 30, baseY + 75);
        glVertex2f(baseX + 65, baseY + 50);
    glEnd();
}


void bridge()
{
    // Bridge base/platform
    if(isDay)
    glColor3f(0.4f, 0.4f, 0.4f); // Grey
    else
    glColor3ub(70,70,70);
    glBegin(GL_QUADS);
        glVertex2f(0, 250);
        glVertex2f(1500, 250);
        glVertex2f(1500, 300);
        glVertex2f(0, 300);
    glEnd();

    // Vertical supports (pillars under bridge)
    glColor3f(0.2f, 0.2f, 0.2f); // Dark grey
    for (int i = 0; i <= 1500; i += 100)
    {
        glBegin(GL_QUADS);
            glVertex2f(i, 200);
            glVertex2f(i + 20, 200);
            glVertex2f(i + 20, 250);
            glVertex2f(i, 250);
        glEnd();
    }

    // Railings
    glColor3f(0.6f, 0.6f, 0.6f); // Light grey
    glBegin(GL_LINES);
    for (int i = 0; i <= 1500; i += 40)
    {
        glVertex2f(i, 300);
        glVertex2f(i, 320);
    }
    // Top horizontal railing
    glVertex2f(0, 320);
    glVertex2f(1500, 320);
    glEnd();

    // =====================================
    //Suspension Tower 1 (left)
    float tower1X = 500;
    float towerBaseY = 300;
    float towerTopY = 500;


   if(isDay)
    glColor3f(0.2f, 0.2f, 0.2f); // Tower color
    else
         glColor3ub(28,31,38);
    glBegin(GL_QUADS);
        glVertex2f(tower1X - 5, towerBaseY);
        glVertex2f(tower1X + 5, towerBaseY);
        glVertex2f(tower1X + 5, towerTopY);
        glVertex2f(tower1X - 5, towerTopY);
    glEnd();


    // Suspension Tower 2 (right)
    float tower2X = 1000;
    glBegin(GL_QUADS);
        glVertex2f(tower2X - 5, towerBaseY);
        glVertex2f(tower2X + 5, towerBaseY);
        glVertex2f(tower2X + 5, towerTopY);
        glVertex2f(tower2X - 5, towerTopY);
    glEnd();


    // =====================================
    // Cables from Tower 1
    glColor3f(0.0f, 0.0f, 0.0f); // Black cables
    glBegin(GL_LINES);
    for (int offset = -120; offset <= 120; offset += 20)
    {
        glVertex2f(tower1X, towerTopY);
        glVertex2f(tower1X + offset, towerBaseY);
    }

    // Cables from Tower 2
    for (int offset = -120; offset <= 120; offset += 20)
    {
        glVertex2f(tower2X, towerTopY);
        glVertex2f(tower2X + offset, towerBaseY);
    }

    if(Blink)
    {
        drawCircle(500, 500, 6, 1.0, 1.0, 0.0);   // Yellow circle 1
        drawCircle(1000, 500, 6, 1.0, 1.0, 0.0);  // Yellow circle 2

    }
    glEnd();
}


void drawMetroTrain()
{
    float baseY = 310;
    float carWidth = 120;
    float carHeight = 60;
    float spacing = 0;
    int numCars = 4;

    // ---- Train Cars ----
    for (int i = 0; i < numCars; i++)
    {
        float x = trainX + i * (carWidth + spacing);

        // Silver body
        glColor3f(0.85f, 0.85f, 0.85f);
        glBegin(GL_QUADS);
            glVertex2f(x, baseY);
            glVertex2f(x + carWidth, baseY);
            glVertex2f(x + carWidth, baseY + carHeight);
            glVertex2f(x, baseY + carHeight);
        glEnd();

        // Green top stripe
        glColor3f(0.0f, 0.4f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(x, baseY -5 + carHeight - 8);
            glVertex2f(x + carWidth, baseY-5 + carHeight - 8);
            glVertex2f(x + carWidth, baseY + carHeight - 5);
            glVertex2f(x, baseY + carHeight - 5);
        glEnd();

        // Red door (1 per car)
        glColor3f(0.9f, 0.0f, 0.0f);
        float doorX = x +35  + carWidth / 2 - 7;
        glBegin(GL_QUADS);
            glVertex2f(doorX, baseY + 5);
            glVertex2f(doorX + 15, baseY + 5);
            glVertex2f(doorX + 15, baseY + carHeight - 5);
            glVertex2f(doorX, baseY + carHeight - 5);
        glEnd();

        // Windows (dark glass)
        glColor3f(0.1f, 0.1f, 0.1f);
        for (int w = 0; w < 3; w++)
        {
            float winX = x + 10 + w * 30;
            float winY = baseY + 15;
            glBegin(GL_QUADS);
                glVertex2f(winX, winY);
                glVertex2f(winX + 18, winY);
                glVertex2f(winX + 18, winY + 25);
                glVertex2f(winX, winY + 25);
            glEnd();
        }

        // Wheels
        drawWheel(x + 20, baseY - 5);
        drawWheel(x + 40, baseY - 5);
        drawWheel(x + carWidth - 30, baseY - 5);
        drawWheel(x + carWidth - 50, baseY - 5);
    }

    // ---- Roof Equipment (optional) ----
    for (int i = 0; i < numCars; i++)
    {
        float x = trainX + i * (carWidth + spacing);
        glColor3f(0.3f, 0.3f, 0.3f); // Dark gray vents
        glBegin(GL_QUADS);
            glVertex2f(x + 20, baseY + carHeight + 1);
            glVertex2f(x + 60, baseY + carHeight + 1);
            glVertex2f(x + 60, baseY + carHeight + 10);
            glVertex2f(x + 20, baseY + carHeight + 10);
        glEnd();
    }
}



void drawTurbine(float baseX, float baseY)
{
    // Tower
    if(isDay)
    glColor3f(0.7f, 0.7f, 0.7f);  // Light gray
   else
     glColor3ub(31,31,37);
    glBegin(GL_QUADS);
        glVertex2f(baseX - 5, baseY);
        glVertex2f(baseX + 5, baseY);
        glVertex2f(baseX + 5, baseY + 150);
        glVertex2f(baseX - 5, baseY + 150);
    glEnd();

    // Hub (center of turbine
    if(isDay)
    glColor3f(0.3f, 0.3f, 0.3f);  // Dark gray
    else
    glColor3ub(44,48,56);// Moonlit Metallic Gray
    float cx = baseX;
    float cy = baseY + 150;
    float radius = 8.0f;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= 100; i++)
        {
            float angle = 2.0f * 3.1416f * i / 100;
            glVertex2f(cx + cos(angle) * radius, cy + sin(angle) * radius);
        }
    glEnd();

    // Blades
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    glRotatef(turbineAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.9f, 0.9f, 0.9f);  // Blade color
    for (int i = 0; i < 3; i++)
    {
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.0f, 40.0f);
            glVertex2f(4.0f, 10.0f);
        glEnd();
        glRotatef(120.0f, 0.0f, 0.0f, 1.0f);
    }
    glPopMatrix();
}


///////////////////////////////////////////////////// Lower Side ///////////////////////////////////////////////////////


void drawBoatA()
{
    // Boat base
    if(isDay)
    glColor3f(0.5f, 0.2f, 0.1f); // Brown base
    else
    glColor3ub(60,58,53);// Old Wooden Boat
    glBegin(GL_QUADS);
        glVertex2f(boatA + 100, 180-100);
        glVertex2f(boatA + 300, 180-100);
        glVertex2f(boatA + 350, 200-100);
        glVertex2f(boatA + 50, 200-100);
    glEnd();

    // Boat top (cabin)
    glColor3f(0.9f, 0.9f, 0.9f); // Light grey
    glBegin(GL_QUADS);
        glVertex2f(boatA + 160, 200-100);
        glVertex2f(boatA + 240, 200-100);
        glVertex2f(boatA + 240, 230-100);
        glVertex2f(boatA + 160, 230-100);
    glEnd();
}

void drawShip()
{
    float shipX = boatB + 400; // X offset
    float shipY = 20;          // Base Y level

    // Ship Base (Hull)
    glColor3f(0.4f, 0.2f, 0.1f); // Dark brown
    glBegin(GL_POLYGON);
        glVertex2f(shipX, shipY);
        glVertex2f(shipX + 300, shipY);
        glVertex2f(shipX + 280, shipY + 40);
        glVertex2f(shipX + 20, shipY + 40);
    glEnd();

    // First Cabin (Lower deck)
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray
    glBegin(GL_QUADS);
        glVertex2f(shipX + 50, shipY + 40);
        glVertex2f(shipX + 250, shipY + 40);
        glVertex2f(shipX + 250, shipY + 80);
        glVertex2f(shipX + 50, shipY + 80);
    glEnd();

    // Second Cabin (Upper deck)
    glColor3f(0.9f, 0.9f, 0.9f); // Slightly lighter
    glBegin(GL_QUADS);
        glVertex2f(shipX + 100, shipY + 80);
        glVertex2f(shipX + 200, shipY + 80);
        glVertex2f(shipX + 200, shipY + 110);
        glVertex2f(shipX + 100, shipY + 110);
    glEnd();

    // Chimney / Funnel
    glColor3f(0.8f, 0.1f, 0.1f); // Red
    glBegin(GL_QUADS);
        glVertex2f(shipX + 135, shipY + 110);
        glVertex2f(shipX + 150, shipY + 110);
        glVertex2f(shipX + 150, shipY + 140);
        glVertex2f(shipX + 135, shipY + 140);
    glEnd();

    // Windows on 1st Cabin
    glColor3f(0.2f, 0.6f, 0.9f); // Blue windows
    for (int i = 0; i < 4; i++) {
        float wx = shipX + 60 + i * 45;
        glBegin(GL_QUADS);
            glVertex2f(wx, shipY + 50);
            glVertex2f(wx + 20, shipY + 50);
            glVertex2f(wx + 20, shipY + 65);
            glVertex2f(wx, shipY + 65);
        glEnd();
    }
}



/////////////////////////////////////////////////////
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    sky();
    sun();
    drawPlane();
    drawCloud();
    drawHill();
    drawWTower();
    drawTurbine(300,400);
    drawTurbine(380,400);
    river();
    drawGround();
    drawBoatA();
    drawShip();
    drawMetroTrain();
    bridge();
     if (isRaining)
        drawRain();
    glutSwapBuffers();
}



void idle()
{
    boatUpdate();
    trainUpdate();
    glutPostRedisplay();  // Keep updating
}


////////////////////////////////////// DISPLAY & CONTROL UNIT /////////////////////////////////////////////


void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            boatBspeed += 1.0f;
            if (boatBspeed > 3.0f)
                boatBspeed = 3.0f; // Clamp to max speed
        }
        else if (button == GLUT_RIGHT_BUTTON)
        {
            boatBspeed -= 1.0f;
            if (boatBspeed < -3.0f)
                boatBspeed = -3.0f; // Clamp to min speed
            //boatB = -400;
        }

        glutPostRedisplay();
    }
}



void specialKeysM(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            trainSpeed += 0.10f;
            if (trainSpeed > 4.0f) trainSpeed = 4.0f; // Optional: Limit max speed
            break;

        case GLUT_KEY_DOWN:
            trainSpeed -= 0.10f;
            if (trainSpeed < -2.0f) trainSpeed = -2.0f; // Prevent negative speed
            if(trainX < -1500)
            trainX =1500;
            break;
    }

    glutPostRedisplay();
}



void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
        case 'd': case 'D': // Day for All
                isDay = true;

            break;
        case 'n': case 'N': // Night for All
                isDay = false;
            break;
        case 'q' : case 'Q':
                isTrainMoving = true;
            break;
        case 'w' : case 'W':
                isTrainMoving = false;
            break;
        case 'r': case 'R': // start raining only
            isRaining = true;
            break;
        case 'h': case 'H': // stop raining only 1
            isRaining = false;
            break;
            case 27:
    exit(0);
    break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////




int main(int argc, char *argv[])
{
    srand(time(0));  // Seed for random number generator
    for (int i = 0; i < 100; i++) {
        rainDropX[i] = rand() % 1500;  // Random X position
        rainDropY[i] = rand() % 700;  // Random Y position
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1500, 700);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("3th Screen");
    cout<<" MOSA LIMA AKTER \n ID 22-47973-2 "<<endl;
    cout<<"Train Start Q || Stop W"<<endl;
    cout<<"Screen Day D || Night N"<<endl;
    cout<<"Start Rain R || Stop H"<<endl;
    cout<<"Press up to speed++ || Press down to speed-- "<<endl;
    cout<<"Left mouse button (stop ship) || Right mouse button (stop / back )"<<endl;

    initScreen();               // Initialize screen settings
    glutDisplayFunc(display);   // Set display callback
    glutIdleFunc(idle);         // Set idle function
    glutKeyboardFunc(keyboardFunc);
     glutSpecialFunc(specialKeysM);
      glutMouseFunc(mouse);
      glutTimerFunc(20, PlaneMove, 0);
     glutTimerFunc(20, MovingPart, 0);
    glutTimerFunc(16, turbineUpdate, 0);
    glutTimerFunc(100, toggle, 0);
    glutTimerFunc(1000, toggle2, 0);
    glutTimerFunc(16, Rain, 0);
    glutMainLoop();             // Enter main loop
    return 0;
}
