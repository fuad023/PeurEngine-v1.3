#pragma once

#include <iostream>
#include <math.h> // sin() cos() sqrt()
#define M_PI 3.14159265358979323846

class Vec2
{
public:

    double x = 0.0;
    double y = 0.0;

    Vec2();
    Vec2(double n);
    Vec2(double xin, double yin);
    Vec2(const Vec2& rhs);                    // copy constuctor
    
    Vec2 operator =  (const Vec2& rhs);       // same as the copy constructor above
    Vec2 operator +  (const Vec2& rhs) const; ////////////////////////////////////////////////////////////////////
    Vec2 operator -  (const Vec2& rhs) const; // Example: c = a + b, here a and b will remain intact,           //
    Vec2 operator *  (const Vec2& rhs) const; // only c will be manipulated.                                    //
    Vec2 operator /  (const Vec2& rhs) const; // jar upor operation kora hoy tar value manipulation hoy na      //
    Vec2 operator *  (double val) const;      // rather notun vector create hoy                                 //
    Vec2 operator /  (double val) const;      // jeta assignment operator diye onno Vec2 ke manipulate kore hoy //
    //                                        //                                                                //
    bool operator == (const Vec2& rhs) const; // till here [code 101]                                           //
    bool operator != (const Vec2& rhs) const; ////////////////////////////////////////////////////////////////////

    void operator += (const Vec2& rhs);       ////////////////////////////////////////////////////////////////////
    void operator -= (const Vec2& rhs);       // left side manipulate hoy                                       //
    void operator *= (const Vec2& rhs);       // right side intact thake                                        //
    void operator /= (const Vec2& rhs);       //                                                                //
    void operator *= (double val);            // till here                                                      //
    void operator /= (double val);            ////////////////////////////////////////////////////////////////////
    void print       ()                const;

    double dist       (const Vec2& rhs) const;
    double distSq     (const Vec2& rhs) const;
    double length     ()                const;
    Vec2   normalize  ();                     // look code 101 above || modified from 'jar upor perform kora hoto she e maniputale hoto' [code: double len = Vec2::length(); x /= len; y /= len; return *this; ]
    Vec2&  add        (double val);           // somewhat like the above + operator
    Vec2&  scale      (double val);           // somewhat like the above * operator
    Vec2&  assign     (const Vec2& rhs);
    Vec2&  abs        ();
    Vec2&  unit       (double degree);        // uses sin() cos() methods which are slow
    Vec2&  unit       (Vec2 velDir);          // makes the Vec2(1, 1) keeping the (+) (-) signs [ekhane parameter Vec2 reference hobe na]
    Vec2&  diagonalFix();                     // for same apmlitude in both axes for only at 45 degree vector
};