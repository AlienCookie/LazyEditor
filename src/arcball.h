#ifndef ARCBALL_H
#define ARCBALL_H

#include <cmath> // for sqrt

typedef float vec_float;

class vec // simple 3D vector class
{
  public:
    vec_float x,y,z;

    vec() {}
    vec( vec_float xx, vec_float yy, vec_float zz )
    { x=xx; y=yy; z=zz; }

    inline vec operator + (vec t) // addition
    { return vec(x+t.x,y+t.y,z+t.z); }
    inline vec operator - (vec t) // subtraction
    { return vec(x-t.x,y-t.y,z-t.z); }
    inline vec operator * (vec_float t) // dot product
    { return vec(x*t,y*t,z*t); }
    inline vec_float operator * (vec t) // scalar product
    { return x*t.x + y*t.y + z*t.z; }
    inline vec operator ^ (vec t) // cross product
    { return vec( y*t.z-z*t.y, t.x*z-x*t.z, x*t.y-y*t.x ); }

    inline vec_float length() // pythagorean length
    { return sqrt(x*x + y*y + z*z); }
    inline vec unit() // normalized to a length of 1
    { vec_float l = length();
      if (l == 0.0) return vec(0.0,0.0,0.0);
      return vec(x/l,y/l,z/l); }
    inline bool zero() // returns true if a zero vector
    { return x==0 && y==0 && z==0; }
    inline bool equals(vec t) // returns true if exactly equal
    { return x==t.x && y==t.y && z==t.z; }
};

#endif
