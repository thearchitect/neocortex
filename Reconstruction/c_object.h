#ifndef C_OBJECT_H
#define C_OBJECT_H

#include <set>
#include <list>
#include "c_edge.h"
#include "c_point.h"

class c_object
{
private:
	c_edge seed;
	set <int> points;
public:
	~c_object(){points.clear();}
	bool hasPoints(list<c_point> &pnts);
	bool hasPoint(c_point &point);
	void merge(c_object &obj);
	void addPoint(c_point &point);
	void addPoints(list<c_point> &pnts);
	c_edge getEdge() {return seed;}
	void ready();
};

bool c_object::hasPoints(list<c_point> &pnts)
{
	for(list<c_point>::iterator iter=pnts.begin(); iter!=pnts.end(); iter++)
		if(points.find(iter->getNum())!=points.end()) return true;
	return false;
}

bool c_object::hasPoint(c_point &point)
{
	if(points.find(point.getNum())!=points.end())
		return true;
	else
		return false;
}

void c_object::addPoint(c_point &point)
{
	points.insert(point.getNum());
}

void c_object::addPoints(list<c_point> &pnts)
{
	for(list<c_point>::iterator iter=pnts.begin(); iter!=pnts.end(); iter++)
		points.insert(iter->getNum());
}

void c_object::merge(c_object &obj)
{
	points.insert(obj.points.begin(), obj.points.end());
}

void c_object::ready()
{
	if(points.size()>1)
	{
		set<int>::iterator i=points.begin();
		seed.setFP(*i);
		i++;
		seed.setSP(*i);
	}
	points.clear();
}

#endif C_OBJECT_H