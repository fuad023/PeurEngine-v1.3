
#include "GameLogicSub.h"

void Map2D()
{
    int x, y; double xOffset, yOffset;
    for(y=0; y<mapGridY; ++y)
    {
        for(x=0; x<mapGridX; ++x)
        {
            int i = y*mapGridX+x;

            if(map[i] == 1) { mapGrids[i].r = 0.3; mapGrids[i].g = 0.3; mapGrids[i].b = 0.3; }
            else            { mapGrids[i].r = 0; mapGrids[i].g = 0; mapGrids[i].b = 0; } 
            mapGrids[i].a = 0.67;

            xOffset = x*mapGridPixels; yOffset = y*mapGridPixels;
            double xo = window.w/2 - (mapGridPixels*mapGridX)/2;
            double yo = window.h/2 - (mapGridPixels*mapGridX)/2;
            
            mapGrids[i].topL    = { 0            +xOffset +0.5 +xo, 0            +yOffset+0.5 +yo };
            mapGrids[i].topR    = { 0            +xOffset +0.5 +xo, mapGridPixels+yOffset-0.5 +yo };
            mapGrids[i].bottomR = { mapGridPixels+xOffset -0.5 +xo, mapGridPixels+yOffset-0.5 +yo };
            mapGrids[i].bottomL = { mapGridPixels+xOffset -0.5 +xo, 0            +yOffset+0.5 +yo };
        }
    } 
}

void Player2D()
{
    player.point.r = 1; player.point.g = 0; player.point.b = 0; player.point.a = 0.34;
    player.line.r  = 1; player.line.g  = 0; player.line.b  = 0; player.line.a  = 0.34;
    player.point.size = 6; player.line.width = 4;

    double xo = window.w/2 - (mapGridPixels*mapGridX)/2;
    double yo = window.h/2 - (mapGridPixels*mapGridX)/2;
    player.point.pos = player.pos; player.point.pos += Vec2(xo, yo);

    player.line.start = player.pos; player.line.end = player.pos + player.del*10;
    player.line.start += Vec2(xo, yo); player.line.end += Vec2(xo, yo);
}

void Rays3D()
{
    double rayAngle, disV, disH;;
    rayAngle = fixAngle(player.angle+30); //ray set back 30 degrees

    for(int rayCount = 0; rayCount < rayCap; ++rayCount)
    {
        double disH = CastRay(rayAngle, disV = 100000, disH = 100000, rayCount);
                
        //---------------------------3D-walls---------------------------
        int columnAngle = fixAngle(player.angle-rayAngle); disH=disH*cos(toRadian(columnAngle)); //fix fisheye 
        int lineH = (mapGridPixels*window.h*1.36) / (disH); if(lineH > window.h) { lineH = window.h;} //line height and limit i.e. 320
        int lineOff = window.h/2 - (lineH>>1); //line offset: certers the line in the game-view: fullwindow
        
        vLines[rayCount].r = rayLines[rayCount].r; vLines[rayCount].g = rayLines[rayCount].g; vLines[rayCount].b = rayLines[rayCount].b;
        vLines[rayCount].width = 1;
        rayLines[rayCount].r = 0.67; rayLines[rayCount].g = 0.67; rayLines[rayCount].b = 0.67;
        
        vLines[rayCount].start = { (double)rayCount, (double)lineOff };
        vLines[rayCount].end   = { (double)rayCount, (double)lineOff+lineH };
        //-------------------------------------------------------------------
        
        rayAngle=fixAngle(rayAngle-rayAngleInc); //go to next ray
    }

}
