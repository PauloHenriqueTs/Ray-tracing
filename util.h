#ifndef UTIL_H
#define UTIL_H

#include <math.h>
typedef struct
{
    double x;
    double y;
    double z;
} Vector;

// Create a new Vector with the given values
Vector newVector(double x, double y, double z)
{
    Vector result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

// Compute the magnitude of a vector
double mag(Vector v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
Vector normalize(Vector v)
{
    double mg = mag(v);
    return newVector(v.x / mg, v.y / mg, v.z / mg);
}

Vector minVector(Vector v)
{
    if (v.x <= v.y && v.x <= v.z)
        return newVector(1, v.y, v.z);
    else if (v.y <= v.x && v.y <= v.z)
        return newVector(v.x, 1, v.z);
    else
        return newVector(v.x, v.y, 1);
}

bool V1moreV2(Vector v1, Vector v2)
{
    if (fabs(v1.x) > fabs(v2.x) || fabs(v1.y) > fabs(v2.z) || fabs(v1.z) > fabs(v2.z))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Compute the dot product of two vectors
double dot(Vector a, Vector b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

// Scale a vector by a ant value
Vector scaleVector(double value, Vector v)
{
    return newVector(v.x * value, v.y * value, v.z * value);
}

// Compute the cross-product of two vectors
Vector cross(Vector a, Vector b)
{
    return newVector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// Compute the addition of two vectors
Vector addVector(Vector a, Vector b)
{
    return newVector(a.x + b.x, a.y + b.y, a.z + b.z);
}

// Compute a vector produced by substracting a vector from another
Vector minusVector(Vector a, Vector b)
{
    return addVector(a, scaleVector(-1, b));
}

Vector divVector(Vector a, Vector b)
{
    return newVector(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vector divScaleVector(Vector a, double b)
{
    return newVector(a.x / b, a.y / b, a.z / b);
}

Vector multScaleVector(Vector a, double b)
{

    return newVector(a.x * b, a.y * b, a.z * b);
}
Vector minusScaleVector(Vector a, double b)
{
    return newVector(a.x - b, a.y - b, a.z - b);
}

typedef struct
{
    Vector o, d;
} Ray;

Ray newRay(Vector o, Vector d)
{
    Ray ray;
    ray.o = o;
    ray.d = d;
    return ray;
}
typedef struct
{
    double r;
    Vector c;

} Sphere;

Sphere newSphere(Vector c, double r)
{
    Sphere sphere;
    sphere.c = c;
    sphere.r = r;
    return sphere;
}

Vector getNormal(Sphere sphere, Vector pi)
{
    return divScaleVector(minusVector(pi, sphere.c), sphere.r);
}

bool intersect(Sphere sphere, Ray ray, double *t)
{
    int r = sphere.r;

    Vector o = ray.o;
    Vector d = ray.d;
    Vector oc = minusVector(o, sphere.c);
    double a = dot(ray.d, ray.d);
    double b = dot(multScaleVector(ray.d, 2), oc);
    double c = (dot(oc, oc) - sphere.r * sphere.r);
    double delta = ((b * b) - (4 * a * c));
    // printf("%lf", delta);
    if (delta < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
Vector clamp255(Vector col)
{

    col.x = (col.x > 255) ? 255 : (col.x < 0) ? 0 : col.x;
    col.y = (col.y > 255) ? 255 : (col.y < 0) ? 0 : col.y;
    col.z = (col.z > 255) ? 255 : (col.z < 0) ? 0 : col.z;
    return newVector(col.x, col.y, col.z);
}

#endif
