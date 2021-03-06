#include "Cone.h"
#include <math.h>

/**
* Cylinder's intersection method.  The input is a ray.
*/
float Cone::intersect(glm::vec3 p0, glm::vec3 dir)
{
    float rOnH = (radius / height)*(radius / height);
    float a = dir.x*dir.x + dir.z*dir.z - rOnH*dir.y*dir.y;
    float diffx = p0.x - center.x;
    float diffy = -p0.y + center.y + height;
    float diffz = p0.z - center.z;
    float b = dir.x*(diffx) + dir.y*rOnH*diffy + dir.z*(diffz);
    float c = diffx*diffx + diffz*diffz - rOnH*(diffy*diffy);
    float delta = b*b - a*c;      // sqrt part of t value

    if(fabs(delta) < 0.001) return -1.0;    //fabs returns the absolute value
    if(delta < 0.0) return -1.0;

    float t1 = (-b - sqrt(delta))/a;
    float t2 = (-b + sqrt(delta))/a;

    glm::vec3 hit1 = p0 + t1*dir;
    glm::vec3 hit2 = p0 + t2*dir;

    if(fabs(t1) < 0.001 )
    {
        if (t2 > 0) return t2;
        else t1 = -1.0;
    }
    if(fabs(t2) < 0.001 ) t2 = -1.0;

    if (hit1.y > (center.y + height)) {
       t1 = -1.0;
    }

    return (t1 < t2)? t1: t2;
}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the sphere.
*/
glm::vec3 Cone::normal(glm::vec3 p)
{
    double theta = atan(radius/height);
    double alpha = atan((p.x-center.x)/(p.z-center.z));
    glm::vec3 n = glm::vec3(sin(alpha)*cos(theta), sin(theta), cos(alpha)*cos(theta));

    return n;
}
