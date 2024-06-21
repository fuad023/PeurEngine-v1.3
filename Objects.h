#include "Vec2.h"

typedef struct
{
    Vec2 topL    = {0.0, 0.0}; Vec2 topR    = {0.0, 0.0};
    Vec2 bottomL = {0.0, 0.0}; Vec2 bottomR = {0.0, 0.0};
    double r=1, g=1, b=1, a=1;

} Quad; 

typedef struct
{
    Vec2 start = {0.0, 0.0}; Vec2 end = {0.0, 0.0};
    double r=1, g=1, b=1, a=1, width;

} Line; 

typedef struct 
{
    Vec2 pos = {0.0, 0.0};
    double r=1, g=1, b=1, a=1, size;

} Point;



typedef struct
{
    int display;
    int w = 1366, h = 760;

} Window; 

typedef struct
{
    Vec2 pos = {0.0, 0.0};
    Vec2 del = {0.0, 0.0};
    double angle = 0.0;

    Point point;
    Line line;

} Player; 

typedef struct
{
	bool goFront, goBack, turnLeft, turnRight;
    bool map, quit;

} Action; 


