
#include "GameLogic.h"
#include <iostream>

void GameLogic()
{
    PlayerControl();

    Map2D();
    Player2D();

    Rays3D();
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Render(ceiling); Render(floors);
    for(Line& line: vLines)    { Render(line); } //View3D

    if(action.map)
    {  
        for(Quad& quad: mapGrids)  { Render(quad); } //Grid2D
        for(Line& line: rayLines)  { Render(line); } //Ray2D
        Render(player.point); Render(player.line);   //Player2D 
    }

    glutSwapBuffers();
}

void GameLoop()
{
    GameLogic();
    Render();
}

void bgCeilingFllor()
{
    ceiling.topL = Vec2(0, 0); ceiling.topR = Vec2(window.w, 0);
    ceiling.bottomL = Vec2(0, window.h/2); ceiling.bottomR = Vec2(window.w, window.h/2);
    ceiling.r = 0.45, ceiling.g = 0.40; ceiling.b = 0.20;

    floors.topL = Vec2(0, window.h/2 +1); floors.topR = Vec2(window.w, window.h/2 +1);
    floors.bottomL = Vec2(0, window.h); floors.bottomR = Vec2(window.w, window.h);
    floors.r = 0.70, floors.g = 0.65; floors.b = 0.3;
}

void init()
{
    player.pos = Vec2( mapGridPixels*8 + mapGridPixels/2, mapGridPixels*22 - mapGridPixels/2 );
    player.del = Vec2( cos(toRadian(player.angle)), -sin(toRadian(player.angle)) );

    bgCeilingFllor();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutWarpPointer(window.w/2, window.h/2);
    glutSetCursor(GLUT_CURSOR_NONE);
}

void resizeWindow(int w,int h)                                                        //screen window rescaled, snap back
{
    glutReshapeWindow(window.w, window.h);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window.w, window.h);
    glutInitWindowPosition( (glutGet(GLUT_SCREEN_WIDTH)-window.w)/2, (glutGet(GLUT_SCREEN_HEIGHT)-window.h)/2 );
    window.display = glutCreateWindow("Peur");

    init();
    glClearColor(0.3, 0.3, 0.3, 0.3);
    gluOrtho2D(0, window.w, window.h, 0);

    glutDisplayFunc(GameLoop);
    glutFullScreen();
    //glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(buttorPress);
    glutKeyboardUpFunc(buttorRelease);
    //glutPassiveMotionFunc(mouseMotion);
    
    glutMainLoop();
}

