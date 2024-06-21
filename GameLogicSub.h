
#include "Map.h"
#include "Render.h"

Quad mapGrids[mapGridX*mapGridY];
Window window;
Player player;
Action action;

const int rayCap = 1366;
const double rayAngleInc = 0.04392386;//0.0625;
Line rayLines[rayCap]; 
Line vLines[rayCap];
Quad ceiling; Quad floors;

double toRadian(double angle) { return angle*M_PI/180.0; }
double fixAngle(double a)
{
    if(a>359) { a -= 360; }
    if(a<  0) { a += 360; }
    return a;
}

void buttorPress(unsigned char Key, int MousePosX, int MousePosY)
{
	switch (Key)
    {
        case 'a' : action.turnLeft  = true; break;
        case 'd' : action.turnRight = true; break;
        case 'w' : action.goFront   = true; break;
        case 's' : action.goBack    = true; break;
        case '\t': action.map       = true; break;
        case 27:   action.quit      = true; break;
    }
}

void buttorRelease(unsigned char Key, int MousePosX, int MousePosY)
{
    switch (Key)
    {
        case 'a' : action.turnLeft  = false; break;
        case 'd' : action.turnRight = false; break;
        case 'w' : action.goFront   = false; break;
        case 's' : action.goBack    = false; break;
        case '\t': action.map       = false; break;
    }
}

float frame1, frame2, hiccupFix;
void PlayerControl()
{
    frame2=glutGet(GLUT_ELAPSED_TIME); hiccupFix=frame2-frame1; frame1=glutGet(GLUT_ELAPSED_TIME);

    double turnOffset = 0.15;
    double moveOffset = 0.04;
    if (action.turnLeft)
    {
        player.angle +=  turnOffset*hiccupFix;
        player.angle  =  fixAngle(player.angle);
        player.del.x  =  cos(toRadian(player.angle));
        player.del.y  = -sin(toRadian(player.angle));
    } 	
    if (action.turnRight)
    { 
        player.angle -=  turnOffset*hiccupFix;
        player.angle  =  fixAngle(player.angle);
        player.del.x  =  cos(toRadian(player.angle));
        player.del.y  = -sin(toRadian(player.angle));
    }

    int xo = player.del.x < 0 ? -8 : 8; //x offset to check map
    int yo = player.del.y < 0 ? -8 : 8; //y offset to check map
    int ipx = (int)player.pos.x>>roundConst, ipx_add_xo = (int)(player.pos.x+xo)>>roundConst, ipx_sub_xo=(int)(player.pos.x-xo)>>roundConst; //x position and offset
    int ipy = (int)player.pos.y>>roundConst, ipy_add_yo = (int)(player.pos.y+yo)>>roundConst, ipy_sub_yo=(int)(player.pos.y-yo)>>roundConst; //y position and offset

    if (action.goFront) //move forward
    {  
        if(map[ipy*mapGridX        + ipx_add_xo]==0){ player.pos.x += player.del.x*moveOffset*hiccupFix; }
        if(map[ipy_add_yo*mapGridX + ipx       ]==0){ player.pos.y += player.del.y*moveOffset*hiccupFix; }
    }
    if(action.goBack) //move backward
    { 
    if(map[ipy*mapGridX        + ipx_sub_xo]==0){ player.pos.x -= player.del.x*moveOffset*hiccupFix; }
    if(map[ipy_sub_yo*mapGridX + ipx       ]==0){ player.pos.y -= player.del.y*moveOffset*hiccupFix; }
    }

    if(action.quit) { glutDestroyWindow(window.display); }

    glutPostRedisplay();
}

//double pos1=0;
void mouseMotion(int x, int y)
{
    /*double factor = (x)/3;

    player.angle +=  factor;
    player.angle  =  fixAngle(player.angle);
    player.del.x  =  cos(toRadian(player.angle));
    player.del.y  = -sin(toRadian(player.angle));


    if (x <= window.w/2-256) { pos1 += window.w/2-256; glutWarpPointer(window.w/2, y); }
    //if (x >= window.w/2+256) { glutWarpPointer(window.w/2, y); }
    //pos1 = x;
    std::cout  << " " << x << " " << std::endl;
    glutPostRedisplay();*/
}

double CastRay(double rayAngle, double& disV, double& disH, int count)
{
    int dof, dofCap = mapGridX, round = roundConst;
    double rayDisX, rayDisY, Tan, xo, yo;
    int mx,my, mapGrid; 
    double vDistX, vDistY;
    double hDistX, hDistY; 

    //---------------------------Vertical---------------------------
    dof=0;
    Tan=tan(toRadian(rayAngle));

         if(cos(toRadian(rayAngle))> 0.001) { vDistX = (((int)player.pos.x>>round)<<round) + mapGridPixels; vDistY = (player.pos.x-vDistX)*Tan+player.pos.y; xo =  mapGridPixels; yo = -xo*Tan; } //looking right
    else if(cos(toRadian(rayAngle))<-0.001) { vDistX = (((int)player.pos.x>>round)<<round) -        0.0001; vDistY = (player.pos.x-vDistX)*Tan+player.pos.y; xo = -mapGridPixels; yo = -xo*Tan; } //looking left
    else { vDistX = player.pos.x; vDistY = player.pos.y; dof = dofCap; }                                                   //looking up or down. no hit  

    while(dof < dofCap) 
    { 
        mx = (int)(vDistX)>>round; my=(int)(vDistY)>>round; mapGrid=my*mapGridX+mx;                     
        if(mapGrid>0 && mapGrid<mapGridX*mapGridY && map[mapGrid]==1)
        {
            dof  = dofCap;
            disV = cos(toRadian(rayAngle)) * (vDistX-player.pos.x) - sin(toRadian(rayAngle)) * (vDistY-player.pos.y);
        } //hit         
        else{ vDistX += xo; vDistY += yo; dof += 1;}                                               //check next horizontal
    }
    
    //---------------------------Horizontal---------------------------
    dof=0;
    Tan=1.0/Tan;

         if(sin(toRadian(rayAngle))> 0.001) { rayDisY = (((int)player.pos.y>>round)<<round) -        0.0001; rayDisX = (player.pos.y-rayDisY)*Tan+player.pos.x; yo = -mapGridPixels; xo = -yo*Tan; } //looking up 
    else if(sin(toRadian(rayAngle))<-0.001) { rayDisY = (((int)player.pos.y>>round)<<round) + mapGridPixels; rayDisX = (player.pos.y-rayDisY)*Tan+player.pos.x; yo =  mapGridPixels; xo = -yo*Tan; } //looking down
    else{ rayDisX=player.pos.x; rayDisY=player.pos.y; dof=dofCap; } //looking straight left or right
    
    while(dof < dofCap) 
    { 
        mx = (int)(rayDisX)>>round; my=(int)(rayDisY)>>round; mapGrid=my*mapGridX+mx;                          
        if(mapGrid>0 && mapGrid < mapGridX*mapGridY && map[mapGrid]==1)
        {
            dof  = dofCap;
            disH = cos(toRadian(rayAngle)) * (rayDisX-player.pos.x) - sin(toRadian(rayAngle)) * (rayDisY-player.pos.y);
        } //hit         
        else{ rayDisX += xo; rayDisY += yo; dof += 1;} //check next horizontal
    }

    if(disV < disH)
    {
        rayDisX = vDistX; rayDisY = vDistY; disH=disV;
        rayLines[count].r = 0.90; rayLines[count].g = 0.85, rayLines[count].b = 0.15;
    } //vertical hit first
    else { rayLines[count].r = 0.5; rayLines[count].g = 0.5, rayLines[count].b = 0.0; }
    rayLines[count].a = 0.05;
    
    double xRayLineoff = window.w/2 - (mapGridPixels*mapGridX)/2;
    double yRayLineoff = window.h/2 - (mapGridPixels*mapGridX)/2;

    rayLines[count].width = 1;
    rayLines[count].start = player.pos; rayLines[count].start += Vec2(xRayLineoff, yRayLineoff);
    rayLines[count].end   = { rayDisX+xRayLineoff, rayDisY+yRayLineoff };
    
    return disH;    
}
