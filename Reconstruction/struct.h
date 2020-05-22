#ifndef STRUCT_H
#define STRUCT_H

#include "c_point.h"
#include "c_edge.h"
#include <set>

extern const float PI;
extern double fault=0.00001;

struct _data_size
{
    int x;
    int y;
    int z;
};

struct _scale
{
    float x;
    float y;
    float z;
};

struct t_triangle
{
	int point1;
	int point2;
	int point3;
};

struct _object
{
	c_edge seed;
	set <int> points;
};
#endif STRUCT_H