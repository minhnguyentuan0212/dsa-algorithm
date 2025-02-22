#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>
#include <sstream>
using namespace std;

#define EPSILON (1E-8)

#include "geom/Vector3D.h"
class Point3D {
private:
    float x, y, z; 
public:
    friend ostream &operator<<( ostream &os, const Point3D& point);
    
    Point3D(float x=0.0f, float y=0.0f, float z=0.0f);
    Point3D(const Point3D& point);
    virtual ~Point3D();
    
    void setX(float z);
    float getX() const;
    void setY(float z);
    float getY() const;
    void setZ(float z);
    float getZ() const;
    
    bool operator==(Point3D rhs);
    Vector3D operator-(Point3D other);
    Point3D operator+(Vector3D dir);
    operator float(); 
    
    
    float radius();
    void println();
    
    //static section  
    static bool equals(Point3D& lhs, Point3D& rhs); 
    static bool equals(Point3D*& lhs, Point3D*& rhs); 
    static string toString(Point3D& point);
    static string toString(Point3D*& point);
    
    static float distance(Point3D& lhs, Point3D& rhs);
    static float distance(Point3D*& lhs, Point3D*& rhs);

    static Point3D* genPoints(  int size, 
                                float minValue=0, float maxValue=1, 
                                bool manualSeed=false, int seedValue=0);
    static Point3D* genPointsNormal(  int size, 
                                float *mu, //array 3 items
                                float *sigma, //array 3 items
                                bool manualSeed=false, int seedValue=0);
    static void println(Point3D* head, int size);  
};

#endif /* POINT3D_H */