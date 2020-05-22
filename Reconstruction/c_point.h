#ifndef C_POINT_H
#define C_POINT_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>

using namespace std;

extern double fault;

class c_point
{
	float x;
	float y;
	float z;
	float value;
	int num;		//number of point in array

public:
	c_point() {x=y=z=value=num=0;}
	
	c_point(float X, float Y, float Z, float VAL=0, int N=0)
	{
		x=X; y=Y; z=Z; value=VAL; num=N;
	}

	float getX() const {return x;}
	float getY() const {return y;}
	float getZ() const {return z;}
	float getCoord(char coord)
	{
		switch(coord)
		{
		case 'X':
		case 'x': 
			return x;
		case 'Y':
		case 'y': 
			return y;
		case 'Z':
		case 'z': 
			return z;
		default:
			{
				std::cout<<"ERROR: class_point.h: getCoordByNum(): Incorrect coordinate is given"<<std::endl;
				throw "ERROR: class_point.h: getCoordByNum(): Incorrect coordinate is given";
				break;
			}
		}
	}

	float getVal() {return value;} 
	int getNum() {return num;}

	void setX(float X) {x=X;}
	void setY(float Y) {y=Y;}
	void setZ(float Z) {z=Z;}
	void setVal(float VAL) {value=VAL;}
	void setNum(int NUM) {num=NUM;}

	float calc_det(const c_point &p1, const c_point &p2) const;
	c_point get_dist_points(const c_point &p) const;

	float get_angle_OZ(const c_point &p) const;
	float get_angle_OY(const c_point &p) const;
	float get_angle_OX(const c_point &p) const;

	void rotatePoint(const c_point& p1, const c_point& p2, float angle);

	c_point& operator=(const c_point& p)
	{
		x=p.x; y=p.y; z=p.z;
		value=p.value;
		num=p.num;

		return *this;
	}
	bool operator==(const c_point& p)
		{return (x==p.x) && (y==p.y) && (z==p.z);}
	bool operator < (const c_point& p) const;
	bool operator > (const c_point& p) const;
	c_point operator+(const c_point& p) const;
	c_point operator-(const c_point& p) const;
	c_point operator/(const float del) const;
	c_point operator*(const float mn) const;
};

float c_point::calc_det(const c_point &p1, const c_point &p2) const
{
	float det=0;

	float x1=x, y1=y, z1=z;
	float x2=p1.x, y2=p1.y, z2=p1.z;
	float x3=p2.x, y3=p2.y, z3=p2.z;


	if(abs(x)+abs(x2)+abs(x3)+fault>0 && abs(x1)+abs(x2)+abs(x3)+fault<2*fault) x1=x2=x3=1;
	if(abs(y1)+abs(y2)+abs(y3)+fault>0 && abs(y1)+abs(y2)+abs(y3)+fault<2*fault) y1=y2=y3=1;
	if(abs(z1)+abs(z2)+abs(z3)+fault>0 && abs(z1)+abs(z2)+abs(z3)+fault<2*fault) z1=z2=z3=1;

	if( ((x1==x2) && (y1==y2) && (z1==z2)) || 
		((x3==x2) && (y3==y2) && (z3==z2)) ||
		((x1==x3) && (y1==y3) && (z1==z3))) 
		return det;
	
	det=x1*y2*z3 + y1*z2*x3 + z1*x2*y3 - z1*y2*x3 - y1*x2*z3 - x1*z2*y3;

	return det;
}

c_point c_point::get_dist_points(const c_point &p) const
{
	c_point res;

	res.setX(p.x - x);
	res.setY(p.y - y);
	res.setZ(p.z - z);
	res.setVal(sqrt( res.getX() * res.getX() + res.getY() * res.getY()+ res.getZ() * res.getZ() ));
	
	return res;
}

float c_point::get_angle_OZ(const c_point &p) const
{
	c_point tmp=this->get_dist_points(p);
	
	if( (abs(tmp.getX()) + abs(tmp.getY()) + fault) > 0 && (abs(tmp.getX()) + abs(tmp.getY()) +fault) < 2 * fault ) return 0;
	
	if( (abs(tmp.getY()) + abs(tmp.getZ()) + fault) > 0 && (abs(tmp.getY()) + abs(tmp.getZ()) + fault) < 2 * fault)
	{
		if(tmp.getX()>=0) return 0;
		else return M_PI;
	}

	if( (abs(tmp.getX()) + abs(tmp.getZ()) + fault) > 0 && (abs(tmp.getX()) + abs(tmp.getZ()) + fault) < 2 * fault)
	{
		if(tmp.getY()>=0) return (M_PI/2);
		else return -(M_PI/2);
	}
	
	if(tmp.getX() >= 0)
		return (atan((tmp.getY())/(tmp.getX())));
	else return (M_PI+atan((tmp.getY())/(tmp.getX())));
}

float c_point::get_angle_OY(const c_point &p) const
{
	c_point tmp=c_point(this->get_dist_points(p));
	
	if( (abs(tmp.getX()) + abs(tmp.getZ()) + fault) > 0 && (abs(tmp.getX()) + abs(tmp.getZ()) +fault) < 2 * fault ) return 0;
	
	if( (abs(tmp.getY()) + abs(tmp.getZ()) + fault) > 0 && (abs(tmp.getY()) + abs(tmp.getZ()) + fault) < 2 * fault)
	{
		if(tmp.getX()>=0) return 0;
		else return M_PI;
	}

	if( (abs(tmp.getX()) + abs(tmp.getY()) + fault) > 0 && (abs(tmp.getX()) + abs(tmp.getY()) + fault) < 2 * fault)
	{
		if(tmp.getZ()>=0) return -(M_PI/2);
		else return (M_PI/2);
	}
	
	if(tmp.getX() >= 0)
		return -(atan((tmp.getZ())/(tmp.getX())));
	else return (M_PI-atan((tmp.getZ())/(tmp.getX())));
}

float c_point::get_angle_OX(const c_point &p) const
{
	c_point tmp=c_point(this->get_dist_points(p));
	
	if( (abs(tmp.getY()) + abs(tmp.getZ()) + fault) > 0 && (abs(tmp.getY()) + abs(tmp.getZ()) +fault) < 2 * fault ) return 0;
	
	if( (abs(tmp.getX()) + abs(tmp.getZ()) + fault) > 0 && (abs(tmp.getX()) + abs(tmp.getZ()) + fault) < 2 * fault)
	{
		if(tmp.getY()>=0) return 0;
		else return M_PI;
	}

	if( (abs(tmp.getX()) + abs(tmp.getY()) + fault) > 0 && (abs(tmp.getX()) + abs(tmp.getY()) + fault) < 2 * fault)
	{
		if(tmp.getZ()>=0) return 0;
		else return M_PI;
	}
	
	if(tmp.getY() >= 0)
		return (atan((tmp.getZ())/(tmp.getY())));
	else return (M_PI+atan((tmp.getZ())/(tmp.getY())));
}

bool c_point::operator < (const c_point& p) const
{
	if(x<p.x) return true;
	else if(x>p.x) return false;
	else
	{
		if(y<p.y) return true;
		else if(y>p.y) return false;
		else
		{
			if(z<p.z) return true;
			else return false;
		}
	}
}

bool c_point::operator > (const c_point& p) const
{
	if(x>p.x) return true;
	else if(x<p.x) return false;
	else
	{
		if(y>p.y) return true;
		else if(y<p.y) return false;
		else
		{
			if(z>p.z) return true;
			else return false;
		}
	}
}

void c_point::rotatePoint(const c_point& p1, const c_point& p2, float angle) // поворот вокруг прямой (р2-р1) на angle градусов
{
	float modP2P1=sqrt( (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y) + (p2.z-p1.z)*(p2.z-p1.z) );	// Длина вектора (р2-р1)

	float X=(p2.x-p1.x)/modP2P1;	//Нормируем направляющий вектор
	float Y=(p2.y-p1.y)/modP2P1;
	float Z=(p2.z-p1.z)/modP2P1;

	float x0=x-p1.x, y0=y-p1.y, z0=z-p1.z;			//Сохраняем старое значение и сдвигаем к (0,0,0)

	float a=(angle*M_PI)/180;		//Переводим градусы в радианы

	//Матрица поворота
	x = (cos(a)+(1-cos(a))*X*X)    *x0 + ((1-cos(a))*X*Y-sin(a)*Z)  *y0 + ((1-cos(a))*X*Z+sin(a)*Y)  *z0;
	y = ((1-cos(a))*Y*X+sin(a)*Z)  *x0 + (cos(a)+(1-cos(a))*Y*Y)    *y0 + ((1-cos(a))*Y*Z-sin(a)*X)  *z0;
	z = ((1-cos(a))*Z*X-sin(a)*Y)  *x0 + ((1-cos(a))*Z*Y+sin(a)*X)  *y0 + (cos(a)+(1-cos(a))*Z*Z)    *z0;

	x+=p1.x; y+=p1.y; z+=p1.z;		//Сдвигаем на начальное расстояние
}

c_point c_point::operator+(const c_point& p) const
{
	c_point res;

	res.x=x+p.x;
	res.y=y+p.y;
	res.z=z+p.z;
	res.value=value;
	res.num=num;

	return res;
}

c_point c_point::operator-(const c_point& p) const
{
	c_point res;

	res.x=x-p.x;
	res.y=y-p.y;
	res.z=z-p.z;
	res.value=value;
	res.num=num;

	return res;
}

c_point c_point::operator/(const float del) const
{
	c_point res;

	res.x=x/del;
	res.y=y/del;
	res.z=z/del;
	res.value=value;
	res.num=num;

	return res;
}

c_point c_point::operator*(const float mn) const
{
	c_point res;

	res.x=x*mn;
	res.y=y*mn;
	res.z=z*mn;
	res.value=value;
	res.num=num;

	return res;
}

#endif C_POINT_H