#ifndef C_EDGE_H
#define C_EDGE_H

#include <math.h>
#include <iostream>
#include "c_point.h"
//#include "my_lib.h"

using namespace std;
//c_point* all_points;

c_point vectorsMultiply(const c_point& p1, const c_point& p2, const c_point& p3)
{
	c_point res;
	c_point vec1=p2-p1;
	c_point vec2=p3-p1;

	res.setX(vec1.getY()*vec2.getZ()-vec1.getZ()*vec2.getY());
	res.setY(vec1.getZ()*vec2.getX()-vec1.getX()*vec2.getZ());
	res.setZ(vec1.getX()*vec2.getY()-vec1.getY()*vec2.getX());

	float dist=sqrt(res.getX()*res.getX()+res.getY()*res.getY()+res.getZ()*res.getZ());

	res.setX(res.getX()/dist);
	res.setY(res.getY()/dist);
	res.setZ(res.getZ()/dist);

	return res;
}

float scalarMultiply(const c_point& vec1, const c_point& vec2)
{
	return (vec1.getX()*vec2.getX()+vec1.getY()*vec2.getY()+vec1.getZ()*vec2.getZ());
}

c_point calc_normal(const c_point& p1, const c_point& p2, const c_point& p3, const c_point& centerBall)
{
	// Получаем уравнение плоскости
	float A=p1.getY() * (p2.getZ() - p3.getZ()) + p2.getY() * (p3.getZ() - p1.getZ()) + p3.getY() * (p1.getZ() - p2.getZ());
	float B=p1.getZ() * (p2.getX() - p3.getX()) + p2.getZ() * (p3.getX() - p1.getX()) + p3.getZ() * (p1.getX() - p2.getX());
	float C=p1.getX() * (p2.getY() - p3.getY()) + p2.getX() * (p3.getY() - p1.getY()) + p3.getX() * (p1.getY() - p2.getY());
	float D=-p1.getX() * (p2.getY() * p3.getZ() - p3.getY() * p2.getZ()) - p2.getX() * (p3.getY() * p1.getZ() - p1.getY() * p3.getZ()) - p3.getX() * (p1.getY() * p2.getZ() - p2.getY() * p1.getZ());

	//Вектор нормали
	float x=A*(A*centerBall.getX()+B*centerBall.getY()+C*centerBall.getZ()+D)/(A*A+B*B+C*C);
	float y=B*(A*centerBall.getX()+B*centerBall.getY()+C*centerBall.getZ()+D)/(A*A+B*B+C*C);
	float z=C*(A*centerBall.getX()+B*centerBall.getY()+C*centerBall.getZ()+D)/(A*A+B*B+C*C);

	//Нормируем
	float dist=sqrt(x*x+y*y+z*z);
	x/=dist;
	y/=dist;
	z/=dist;

	return c_point(x,y,z);
}

class c_edge
{
	int f_p;			//number of first point
	int s_p;			//number of second point

	int r_p;			//number of right point
	int l_p;			//number of left point

public:
	static c_point* all_points;
	bool is_rp_exists;	
	bool is_lp_exists;	

	c_point center;

	c_edge()
	{
		f_p=s_p=r_p=l_p=-1;
		is_rp_exists=is_lp_exists=false;
		center=c_point(0,0,0,-1,-1);
	}

	c_edge(int p1, int p2);
	c_edge(int p1, int p2, int add_p, const c_point &center);

	c_point calc_center_ball(const int radius, const c_point& direction) const;
	void update(const c_edge &e);
	void add_point(int point_num);

	int getFP() const {return f_p;}
	int getSP() const {return s_p;}
	int getRP() const {return r_p;}
	int getLP() const {return l_p;}

	void setFP(int NUM) {f_p=NUM;}
	void setSP(int NUM) {s_p=NUM;}
	void setRP(int NUM) {r_p=NUM;}
	void setLP(int NUM) {l_p=NUM;}

	bool operator==(const c_edge& e) const
		{return (f_p==e.f_p) && (s_p==e.s_p);}
	bool operator<(const c_edge& e) const
	{
		if(f_p<e.f_p) return true;
		else if(f_p>e.f_p) return false;
		else
		{
			if(s_p<e.s_p) return true;
			else return false;
		}
	}
};

c_edge::c_edge(int p1, int p2)
{
	if(p1 == p2)
	{
		std::cout<<std::endl<<"ERROR: class_edge.h: c_edge::c_edge(...): p1=p2"<<std::endl
							<<"p1:"<<p1<<", p2:"<<p2<<std::endl;
		throw "ERROR: class_edge.h: c_edge::c_edge(...): p1=p2";
	}

	if(p1 < 0 || p2 < 0)
	{
		std::cout<<std::endl<<"ERROR: class_edge.h: c_edge::c_edge(...): p1<0 or p2<0"<<std::endl;
		throw "ERROR: class_edge.h: c_edge::c_edge(...): p1<0 or p2<0";
	}
	
	if(p1 > p2)			//Point with smaller number is a first point
	{
		swap<int>(p1, p2);
	}
		
	f_p=p1;
	s_p=p2;

	r_p=l_p=-1;
	is_rp_exists=is_lp_exists=false;
}

c_edge::c_edge(int p1, int p2, int add_p, const c_point &center)	//They are numbers of points
{
	if(p1 == p2)
	{
		std::cout<<std::endl<<"ERROR: class_edge.h: c_edge::c_edge(...): p1=p2"<<std::endl
							<<"p1:"<<p1<<", p2:"<<p2<<", p3:"<<add_p<<std::endl;
		throw "ERROR: class_edge.h: c_edge::c_edge(...): p1=p2";
	}

	if(p1 < 0 || p2 < 0)
	{
		std::cout<<std::endl<<"ERROR: class_edge.h: c_edge::c_edge(...): p1<0 or p2<0"<<std::endl;
		throw "ERROR: class_edge.h: c_edge::c_edge(...): p1<0 or p2<0";
	}
	
	if(p1 > p2)			//Point with smaller number is a first point
	{
		swap(p1, p2);
	}
		
	f_p=p1;
	s_p=p2;

	r_p=l_p=-1;
	is_rp_exists=is_lp_exists=false;
	
	c_point normal=calc_normal(all_points[p1], all_points[p2], all_points[add_p], center);
	c_point vecMult=vectorsMultiply(all_points[p1], all_points[p2], all_points[add_p]);
	if(scalarMultiply(normal, vecMult)>0)
	{
		l_p=add_p;
		is_lp_exists=true; 
	} else if (scalarMultiply(normal, vecMult)<0)
	{
		r_p=add_p;
		is_rp_exists=true;
	} else {
		std::cout<<std::endl<<"ERROR: class_edge.h: c_edge::c_edge(...): scalarMultiply(normal, vecMult)=0"<<std::endl;
		std::cout<<p1<<":"<<all_points[p1].getX()<<","<<all_points[p1].getY()<<","<<all_points[p1].getZ()
			<<" "<<p2<<":"<<all_points[p2].getX()<<","<<all_points[p2].getY()<<","<<all_points[p2].getZ()
			<<" "<<add_p<<":"<<all_points[add_p].getX()<<","<<all_points[add_p].getY()<<","<<all_points[add_p].getZ()<<std::endl;
		throw "ERROR: class_edge.h: c_edge::c_edge(...): scalarMultiply(normal, vecMult)=0";
	}
	this->center=center;
}

c_point c_edge::calc_center_ball(const int radius, const c_point& direction) const
{
	c_point center, middle, normal, point, proection;
	
	middle=(all_points[s_p]+all_points[f_p])/2;
	normal=all_points[s_p]-all_points[f_p];

	// уравнение плоскости
	float A=normal.getX();
	float B=normal.getY();
	float C=normal.getZ();
	float D=-(A*middle.getX() + B*middle.getY() + C*middle.getZ());

	// проекция точки на плоскость
	point=middle+direction;
	float t=-(A*point.getX() + B*point.getY() + C*point.getZ() + D) / (A*A + B*B + C*C);

	//float x=point.getX()+t*A;
	//float y=point.getY()+t*B;
	//float z=point.getZ()+t*C;
	proection=point+normal*t;

	float h=sqrt(normal.getX()*normal.getX() + normal.getY()*normal.getY() + normal.getZ()*normal.getZ())/2;
	float dist=cos(asin(h/radius))*radius;
	// уравнение прямой
	t=dist/sqrt((proection-middle).getX()*(proection-middle).getX() + (proection-middle).getY()*(proection-middle).getY() + (proection-middle).getZ()*(proection-middle).getZ());

	center=middle+(proection-middle)*t;
	return center;
}

void c_edge::update(const c_edge &e)
{
	if (e.is_rp_exists)
	{
		is_rp_exists=e.is_rp_exists;
		r_p=e.r_p;
	}
	if (e.is_lp_exists)
	{
		is_lp_exists=e.is_lp_exists;
		l_p=e.l_p;
	}
}

void c_edge::add_point(int point_num)
{
	if(is_rp_exists && is_lp_exists)
	{
		std::cout<<std::endl<<"ERROR: class_edge.h: c_edge::add_point(...): edge is full"<<std::endl;
		throw "ERROR: class_edge.h: c_edge::add_point(...): edge is full";

	}

	if(is_rp_exists)
	{
		l_p=point_num;
		is_lp_exists=true;
	} 
	else
	{
		r_p=point_num;
		is_rp_exists=true;
	}
}

#endif C_EDGE_H