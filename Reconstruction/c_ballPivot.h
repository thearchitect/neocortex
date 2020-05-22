#ifndef C_BALLPIVOT_H
#define C_BALLPIVOT_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include <queue>
#include <vector>
#include <list>
#include <set>

#include "glut.h"
#include "struct.h"
#include "c_point.h"
#include "c_edge.h"
#include "c_object.h"

#include "Structures.h"

using namespace std;

c_point* c_edge::all_points;

class ballPivot
{
 public:
	GLfloat MIN_DENSITY;
	GLfloat MAX_DENSITY;
	GLfloat razm_x, razm_y, razm_z;
	int COUNT_OF_POINTS_X, COUNT_OF_POINTS_Y, COUNT_OF_POINTS_Z;
	int COUNT_OF_ALL_POINTS, COUNT_OF_ALL_SHOWED_POINTS;
	int STEP_X, STEP_Y, STEP_Z;
	int radius;
	c_point camera_pos;
	float angle;
	short ***data3ar;

	_data_size data_size;
	_scale scale;
	c_point *t_points;

	c_point* all_points;
	
	list <c_edge> edges;
	list <c_object> objects;
	set <c_edge> all_edges;
	set <c_point> s_points;
	queue <t_triangle> triangles;
	t_triangle *triangles_res;
	int TRIANGLES_COUNT;

	void DrawTriangle(int &p1, int &p2, int &p3);

	int getLeftPos(c_point *points, int first, int last, float val, char coord);
	int getRightPos(c_point *points, int first, int last, float val, char coord);
	void getPointsSection(c_point *points, int first, int last, c_point coords, int dist, list<c_point> &result, char coord);

	void searchOfObjects(c_point* points, int len, int radius, list<c_object> &objects);	


	void postProcessing(c_point* points, int len);


	void drawAxises();

	int neighbor_point_to_i(c_point &point, unsigned char var, int act);


	int diag_point_to_i(c_point &point, int actX, int actY, int actZ);

	bool IsBorder(int i, c_point *t_points, float MIN_DENSITY);

	bool SelectPoints(int x, int y, int z, int min_dens, int max_dens);


	void RenderScene(void);


	void calc_showed_points(c_point *t_points, int count, float min_dens);

	void ManageKeys(unsigned char key, int x, int y);


	void SetupRC(void);

	void ChangeSize(GLsizei w, GLsizei h);


	bool if_edge_is_full(c_edge &edge, bool update);


	int if_point_on_ball(c_edge &edge, c_point &center, list <c_point> &points);
	int find_point(c_edge &edge, c_point *points, c_point &endCenterPos);

	void ball_pivot(c_point *points, c_edge seed=c_edge(0, 1));

	void get_triangles();


	void init_data(char * file);

public:
	ballPivot();
	ballPivot(char *file);																																								// чтение исходных данных из bin-файла
	ballPivot(TVoxelsData *InputData, int MeshStep_X, int MeshStep_Y, int MeshStep_Z, GLfloat MinVoxelDensity, GLfloat MaxVoxelDensity);												// из сохранённого набора данных
	ballPivot(TVoxelsData *InputData, vector <cv::Point2i> *SnakePoints, int MeshStep_X = 1, int MeshStep_Y = 1, int MeshStep_Z = 1);
	ballPivot(TVoxelsData *InputData, int SegmentIndex, int MeshStep_X, int MeshStep_Y, int MeshStep_Z, GLfloat MinVoxelDensity, GLfloat MaxVoxelDensity);								// из 3D-сегмента	
	ballPivot(TVoxelsData *InputData, vector <TPath> *paths, size_t LayerIndex, size_t PathIndex, int MeshStep_X, int MeshStep_Y, int MeshStep_Z, GLfloat MinVoxelDensity, GLfloat MaxVoxelDensity);							// из цепочки 2D-сегментов
	~ballPivot();
	void buildMesh();
	void renderMesh();
};

struct TVolumeSegment			// объёмный реконструируемый сегмент
{
 ballPivot object;				// объект для построения сетки
 TColor color;					// цвет сегмента
 bool visible;					// атрибут видимости

 size_t LayerRoot;
 size_t SegmentRoot;

 // Конструктор по умолчанию
 TVolumeSegment() { object = ballPivot(); }
};

void ballPivot::DrawTriangle(int &p1, int &p2, int &p3)
{
	int HalfCountX=data_size.x/(2*STEP_X);
	int HalfCountY=data_size.y/(2*STEP_Y);
	int HalfCountZ=data_size.z/(2*STEP_Z);
	//HalfCountZ=HalfCountY=HalfCountX=0;
	//double N=0.05;
	//double RazmX_By_N=razm_x*COUNT_OF_ALL_SHOWED_POINTS/3*N;
	//double RazmY_By_N=razm_y*COUNT_OF_ALL_SHOWED_POINTS/3*N;
	//double RazmZ_By_N=razm_z*COUNT_OF_ALL_SHOWED_POINTS/3*N;

	glBegin(GL_TRIANGLES);

	//glVertex3f((p1.getX()-HalfCountX)*RazmX_By_N, (p1.getY()-HalfCountY)*RazmY_By_N, (p1.getZ()-HalfCountZ)*RazmZ_By_N);
	//glVertex3f((p2.getX()-HalfCountX)*RazmX_By_N, (p2.getY()-HalfCountY)*RazmY_By_N, (p2.getZ()-HalfCountZ)*RazmZ_By_N);
	//glVertex3f((p3.getX()-HalfCountX)*RazmX_By_N, (p3.getY()-HalfCountY)*RazmY_By_N, (p3.getZ()-HalfCountZ)*RazmZ_By_N);
	glVertex3f((all_points[p1].getX()-HalfCountX)*scale.x, (all_points[p1].getY()-HalfCountY)*scale.y, (all_points[p1].getZ()-HalfCountZ)*scale.z);
	glVertex3f((all_points[p2].getX()-HalfCountX)*scale.x, (all_points[p2].getY()-HalfCountY)*scale.y, (all_points[p2].getZ()-HalfCountZ)*scale.z);
	glVertex3f((all_points[p3].getX()-HalfCountX)*scale.x, (all_points[p3].getY()-HalfCountY)*scale.y, (all_points[p3].getZ()-HalfCountZ)*scale.z);
	
	glEnd();
}

int ballPivot::getLeftPos(c_point *points, int first, int last, float val, char coord)
{
	if(val <= points[first].getCoord(coord)) return first;
	if(val > points[last].getCoord(coord)) return -1;

	while(first<last)
	{
		int mid=(first+last)/2;
		if(val<=points[mid].getCoord(coord)) last=mid;
		else first=mid+1;
	}
	
	return first;
}

int ballPivot::getRightPos(c_point *points, int first, int last, float val, char coord)
{
	if(val >= points[last].getCoord(coord)) return last;
	if(val < points[first].getCoord(coord)) return -1;

	while(first<last)
	{
		int mid=(first+last)/2;
		if(val<points[mid].getCoord(coord)) last=mid;
		else first=mid+1;
	}
	
	if (val<points[first].getCoord(coord)) return first-1;
	return first;
}

void ballPivot::getPointsSection(c_point *points, int first, int last, c_point coords, int dist, list<c_point> &result, char coord='x')
{
	int f=getLeftPos(points, first, last, coords.getCoord(coord)-dist, coord);
	int l=getRightPos(points, first, last, coords.getCoord(coord)+dist, coord);

	if(f!=-1 && l!=-1)
	{
		if(coord!='z')
			while(f<=l)
			{
				int sub_l=getRightPos(points, f, l, points[f].getCoord(coord), coord);
				getPointsSection(points, f, sub_l, coords, dist, result, (char)(coord+1));
				f=sub_l+1;
			}
		else
			for(int i=f; i<=l; i++)
				result.push_back(points[i]);
	}
}

void ballPivot::searchOfObjects(c_point* points, int len, int radius, list<c_object> &objects)
{
	/*cout<<endl<<"Sorting points...";
	set<c_point> pnts;
	for(int j=0; j<len; j++)
	{
		points[j]=points[j]*5;
		pnts.insert(points[j]);
	}

	int i=0;
	c_point nullPoint;
	for (set<c_point>::iterator iter=pnts.begin(); iter!=pnts.end(); iter++)
	{
		iter->setNum(i); 
		points[i]=*iter;
//		cout<<i<<"   "<<"("<<points[i].getX()<<","<<points[i].getY()<<","<<points[i].getZ()<<")"<<endl;
		i++;
	}
	cout<<"Done"<<endl;

	cout<<"Searching of objects...";
	while(pnts.size())
	{
		list<c_point> my_points;
		list<c_object>::iterator last_obj=objects.end();
		c_point point=*pnts.begin();
		getPointsSection(points, 0, len-1, point, radius, my_points);

		// Variables for recovery of iterator when object erased
		list<c_object>::iterator last=objects.begin();
		bool ifIterWasFirst=false;
		for(list<c_object>::iterator iter=objects.begin(); iter!=objects.end(); iter++)
		{
			if(iter->hasPoints(my_points))
			{
				if(ifIterWasFirst){iter--; ifIterWasFirst=false;}
				if(last_obj!=objects.end())
				{
					if(iter==objects.begin()) ifIterWasFirst=true;
					last_obj->merge(*iter);
					objects.erase(iter);
					if(ifIterWasFirst)iter=objects.begin();
					else iter=last;
				}
				else
				{
					last=iter;
					iter->addPoints(my_points);
					last_obj=iter;
				}
			}
		}
		
		// If no such objects
		if(last_obj==objects.end())
		{
			c_object obj;
			obj.addPoints(my_points);
			objects.push_back(obj);
		}

		for(list<c_point>::iterator iter=my_points.begin(); iter != my_points.end(); iter++)
		{
			c_point p=*iter;
			set<c_point>::iterator ip;
			ip=pnts.find(p);
			if(ip!=pnts.end())
				pnts.erase(ip);
		}
	}

	// Variables for recovery of iterator when object erased
	list<c_object>::iterator iter = objects.begin();
	list<c_object>::iterator last = objects.end();
	bool ifIterWasFirst=false;
	for(; iter!=last; iter++)
	{
		iter->ready();
		if(ifIterWasFirst){iter--; ifIterWasFirst=false;}
		if(iter->getEdge().getFP()==-1)
		{
			if(iter==objects.begin()) ifIterWasFirst=true;
			objects.erase(iter);
			if(ifIterWasFirst)iter=objects.begin();
			else iter=last;
		}
		else
		{
			last=iter;
		}
	}

	cout<<"Done"<<endl;
	cout<<objects.size()<<" objects found"<<endl; */

	cout<<endl<<"Sorting points...";
	set<c_point> pnts;
	for(int j=0; j<len; j++)
	{
		points[j]=points[j]*5;
		pnts.insert(points[j]);
	}

	int i=0;
	c_point nullPoint;
	for (set<c_point>::iterator iter=pnts.begin(); iter!=pnts.end(); iter++)
	{
		iter->setNum(i); 
		points[i]=*iter;
//		cout<<i<<"   "<<"("<<points[i].getX()<<","<<points[i].getY()<<","<<points[i].getZ()<<")"<<endl;
		i++;
	}
	cout<<"Done"<<endl;

	cout<<"Searching of objects...";
	while(pnts.size())
	{
		list<c_point> my_points;
		list<c_object>::iterator last_obj=objects.end();
		c_point point=*pnts.begin();
		getPointsSection(points, 0, len-1, point, radius, my_points);

		// Variables for recovery of iterator when object erased
		list<c_object>::iterator last=objects.begin();
		bool ifIterWasFirst=false;
		for(list<c_object>::iterator iter=objects.begin(); iter!=objects.end(); iter++)
		{
			if(iter->hasPoints(my_points))
			{
				if(ifIterWasFirst){iter--; ifIterWasFirst=false;}
				if(last_obj!=objects.end())
				{
					if(iter==objects.begin()) ifIterWasFirst=true;
					last_obj->merge(*iter);
					objects.erase(iter);
					if(ifIterWasFirst)iter=objects.begin();
					else iter=last;
				}
				else
				{
					last=iter;
					iter->addPoints(my_points);
					last_obj=iter;
				}
			}
		}
		
		// If no such objects
		if(last_obj==objects.end())
		{
			c_object obj;
			obj.addPoints(my_points);
			objects.push_back(obj);
		}

		for(list<c_point>::iterator iter=my_points.begin(); iter != my_points.end(); iter++)
		{
			c_point p=*iter;
			set<c_point>::iterator ip;
			ip=pnts.find(p);
			if(ip!=pnts.end())
				pnts.erase(ip);
		}
	}

	// Variables for recovery of iterator when object erased
	list<c_object>::iterator last=objects.begin();
	bool ifIterWasFirst=false;
	for(list<c_object>::iterator iter=objects.begin(); iter!=objects.end(); iter++)
	{
		iter->ready();
		if(ifIterWasFirst)
		{
			iter--; ifIterWasFirst=false;
		}
		if(iter->getEdge().getFP()==-1)
		{
			if(iter==objects.begin()) ifIterWasFirst=true;
			objects.erase(iter);
			if(ifIterWasFirst)iter=objects.begin();
			else iter=last;
			if(iter==objects.end()) break;
		}
		else
		{
			last=iter;
		}
	}

	cout<<"Done"<<endl;
	cout<<objects.size()<<" objects found"<<endl;
}

void ballPivot::postProcessing(c_point* points, int len)
{
	for(int j=0; j<len; j++)
		points[j]=points[j]/5;

}

void ballPivot::drawAxises()
{
	glColor4f(1,0,0,0.1f);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(10000000,0,0);
	glEnd();

	glColor4f(0,1,0,0.1f);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(0,10000000,0);
	glEnd();

	glColor4f(0,0,1,0.1f);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(0,0,10000000);
	glEnd();
}

int ballPivot::neighbor_point_to_i(c_point &point, unsigned char var, int act)
{
	int x=point.getX();
	int y=point.getY();
	int z=point.getZ();

	switch (var)
	{
	case 'x':
			return (x+act)*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z + y*COUNT_OF_POINTS_Z + z;
	case 'y':
			return x*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z + (y+act)*COUNT_OF_POINTS_Z + z;
	case 'z':
			return x*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z + y*COUNT_OF_POINTS_Z + z+act;
	default :
			throw "ERROR: main.cpp: neighbor_point_to_i(): incorrect coordinate";
	}
}

int ballPivot::diag_point_to_i(c_point &point, int actX, int actY, int actZ)
{
	int x=point.getX();
	int y=point.getY();
	int z=point.getZ();

	return (x+actX)*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z + (y+actY)*COUNT_OF_POINTS_Z + z+actZ;
}

bool ballPivot::IsBorder(int i, c_point *t_points, float MIN_DENSITY)
{
	if(t_points[i].getVal()<MIN_DENSITY) return false;
	else return true;
 }

bool ballPivot::SelectPoints(int x, int y, int z, int min_dens, int max_dens)
{
	if(data3ar[x][y][z]<=max_dens && data3ar[x][y][z]>=min_dens)
		return true;
	return false;
}

void ballPivot::RenderScene(void)
{
	int HalfCountX=COUNT_OF_POINTS_X/2;
	int HalfCountY=COUNT_OF_POINTS_Y/2;
	int HalfCountZ=COUNT_OF_POINTS_Z/2;

	int N=10;
	int RazmX_By_N=razm_x*N;
	int RazmY_By_N=razm_y*N;
	int RazmZ_By_N=razm_z*N;

	glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();

	glColor4f(1,1,1,0.1f);
//glBegin(GL_POINTS);
//	for(int i=0; i<COUNT_OF_ALL_SHOWED_POINTS; i++)
//			glVertex3f((all_points[i].getX()-HalfCountX)*RazmX_By_N,(all_points[i].getY()-HalfCountY)*RazmY_By_N,(all_points[i].getZ()-HalfCountZ)*RazmZ_By_N);
//glEnd();

	for(int i=0; i<TRIANGLES_COUNT; i++)
		DrawTriangle(triangles_res[i].point1, triangles_res[i].point2, triangles_res[i].point3);

	drawAxises();
    glPopMatrix();
    glutSwapBuffers();
}

void ballPivot::calc_showed_points(c_point *t_points, int count, float min_dens)
{
	COUNT_OF_ALL_SHOWED_POINTS=0;
	for(int i=0; i<count; i++)
		if(IsBorder(i, t_points, min_dens))
			COUNT_OF_ALL_SHOWED_POINTS++;

	all_points = new c_point[COUNT_OF_ALL_SHOWED_POINTS];
	c_edge::all_points=all_points;
	int count_of_showed_tmp=0;
	for(int i=0; i<count; i++)
		if(IsBorder(i, t_points, min_dens))
		{
			all_points[count_of_showed_tmp]=t_points[i];
			count_of_showed_tmp++;
		}
}

void ballPivot::ManageKeys(unsigned char key, int x, int y)
{
	switch ( key )
	{
		case (unsigned char)233:	//й
		case 'q':
		{
		   // матрица поворота
		   camera_pos=c_point(camera_pos.getX(), camera_pos.getY()*cos(angle)+camera_pos.getZ()*sin(angle), -camera_pos.getY()*sin(angle)+camera_pos.getZ()*cos(angle));
		   glRotatef(5.0f,1.0,0.0,0.0);
		   glutPostRedisplay();
		   break;
		}

		case (unsigned char)244:	//ф
		case 'a':
		{
		   // матрица поворота
		   camera_pos=c_point(camera_pos.getX(), camera_pos.getY()*cos(-angle)+camera_pos.getZ()*sin(-angle), -camera_pos.getY()*sin(-angle)+camera_pos.getZ()*cos(-angle));
		   glRotatef(-5.0f,1.0,0.0,0.0);
		   glutPostRedisplay();
		   break;
		}

		case (unsigned char)246:	//ц
		case 'w':
		{
		   // матрица поворота
		   camera_pos=c_point(camera_pos.getX()*cos(angle)-camera_pos.getZ()*sin(angle), camera_pos.getY(), camera_pos.getX()*sin(angle)+camera_pos.getZ()*cos(angle));
		   glRotatef(5.0f,0.0,1.0,0.0);
		   glutPostRedisplay();
		   break;
		}

		case (unsigned char)251:	//ы
		case 's':
		{
		   // матрица поворота
		   camera_pos=c_point(camera_pos.getX()*cos(-angle)-camera_pos.getZ()*sin(-angle), camera_pos.getY(), camera_pos.getX()*sin(-angle)+camera_pos.getZ()*cos(-angle));
		   glRotatef(-5.0f,0.0,1.0,0.0);
		   glutPostRedisplay();
		   break;
		}

		case (unsigned char)243:	//у
		case 'e':
		{
		   // матрица поворота
		   camera_pos=c_point(camera_pos.getX()*cos(angle)+camera_pos.getY()*sin(angle), -camera_pos.getX()*sin(angle)+camera_pos.getY()*cos(angle), camera_pos.getZ());
		   glRotatef(5.0f,0.0,0.0,1.0);
		   glutPostRedisplay();
		   break;
		}

		case (unsigned char)226:	//в
		case 'd':
		{
		   // матрица поворота
		   camera_pos=c_point(camera_pos.getX()*cos(-angle)+camera_pos.getY()*sin(-angle), -camera_pos.getX()*sin(-angle)+camera_pos.getY()*cos(-angle), camera_pos.getZ());
		   glRotatef(-5.0f,0.0,0.0,1.0);
		   glutPostRedisplay();
		   break;
		}

		case (unsigned char)234:	//к
		case 'r':
		{
		   glTranslatef(camera_pos.getX(), camera_pos.getY(), camera_pos.getZ());
		   glutPostRedisplay();
		   break;
		}

		case (unsigned char)224:	//а
		case 'f':
		{
		   glTranslatef(-camera_pos.getX(), -camera_pos.getY(), -camera_pos.getZ());
		   glutPostRedisplay();
		   break;
		}

	}
}

void ballPivot::SetupRC(void)
{
     glClearColor(0.0f,0.0f,0.0f,1.0f);
     glColor3f(0.0f, 1.0f, 0.0f); 
}

void ballPivot::ChangeSize(GLsizei w, GLsizei h)
{
     GLfloat aspectRatio;
     if(h==0) h=1;
     glViewport(0,0,w,h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     aspectRatio=(GLfloat)w/(GLfloat)h;
     gluPerspective(40.0, (GLfloat) w/(GLfloat) h, .0, 20.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
	 gluLookAt(0,0,500,0,0,0,0,1,0);

	 camera_pos.setX(0);
	 camera_pos.setY(0);
	 camera_pos.setZ(-10);
}

bool ballPivot::if_edge_is_full(c_edge &edge, bool update=false)
{
	bool edge_is_full=false;
	bool edge_already_exist=false;

	set <c_edge>::iterator iter=all_edges.find(edge);
	if(iter!=all_edges.end())
	{
		edge_already_exist=true;
		if(update) 
		{
			//iter->update(edge);
			c_edge tmp_edge;
			tmp_edge=(*iter);
			tmp_edge.update(edge);
			all_edges.erase(iter);
			all_edges.insert(tmp_edge);
			iter=all_edges.find(edge);
		}
		if(iter->is_lp_exists && iter->is_rp_exists)
			edge_is_full=true;
	}
	else
	{
		if(update) all_edges.insert(edge);
	}
	
	return edge_is_full;
}

int ballPivot::if_point_on_ball(c_edge &edge, c_point &center, list <c_point> &points)
{
	int point_num=-1, point_num_res=-1;
	double x=0, y=0, z=0;
	double dist=99999999, dist_tmp=99999999;
	
	c_point &point1=all_points[edge.getFP()];
	c_point &point2=all_points[edge.getSP()];

	for(list <c_point>::iterator point_iter=points.begin(); point_iter!=points.end(); point_iter++)
	{
		if ((*point_iter==point1) || (*point_iter==point2)) continue;
		
		// Если расстояние между точкой и центром сферы равно радиусу то точка лежит на поверхности сферы
		// если оно меньше чем радиус то точка внутри
		float cur_dist=point_iter->get_dist_points(center).getVal();
		
		float flt=0.01;
		if (cur_dist<radius-flt) return -2;
		if ((cur_dist<radius+flt)&&(cur_dist>radius-flt))
		{
			point_num=point_iter->getNum();

			float scalar=scalarMultiply(calc_normal(all_points[edge.getFP()], all_points[edge.getSP()], all_points[point_num], center),
										vectorsMultiply(all_points[edge.getFP()], all_points[edge.getSP()], all_points[point_num]));
			if(scalar>0)		//левая точка
			{
				if(edge.is_lp_exists) continue;
			}
			else if(scalar<0)	//правая точка
			{
				if(edge.is_rp_exists) continue;
			}

			c_edge e1(edge.getFP(), point_num);
			c_edge e2(edge.getSP(), point_num);
			if(if_edge_is_full(e1) || if_edge_is_full(e2)) continue;

			dist_tmp=all_points[edge.getFP()].get_dist_points(*point_iter).getVal();
			if(dist_tmp<dist)
			{
				dist=dist_tmp;
				point_num_res=point_num;
			}
		}
	}

	return point_num_res;
}

int ballPivot::find_point(c_edge &edge, c_point *points, c_point &endCenterPos)
{
	float a=0;			//Угол поворота
	int point_num=-1;
	int direct=1;		//Направление поворота шара. 1-по часовой
	c_point center, null_center;

	if(edge.is_lp_exists && edge.is_rp_exists) return -1;
	if(edge.is_rp_exists) direct=-1; 
	
	list <c_point> my_points;

	getPointsSection(points, 0, COUNT_OF_ALL_SHOWED_POINTS-1, all_points[edge.getFP()], 2*radius, my_points);	//Находим точки в пределах 2*Радиус от текущего ребра

	int multiplier=1000000;							// for more correct result
	int grad=180, step=45*multiplier; 
	int first=0, last=0, mid=0;
	bool point_inside=false;

	if(edge.is_lp_exists || edge.is_rp_exists) center=edge.center;
	else center=edge.calc_center_ball(radius, c_point(-1, 0, 0));

	//сохраняем начальное положение центра
	null_center=center;

	for(int i=0; i<grad*multiplier; i+=step)		//поворот на grad градусов
	{						
		center=null_center;
		//Поворот вокруг edge
		center.rotatePoint(points[edge.getFP()], points[edge.getSP()], ((float)(direct*i))/multiplier);

		point_num=if_point_on_ball(edge, center, my_points);
		if (point_num>=0) break;					// точка на сфере
		if (point_num!=-2) continue;				// сфера пуста
		else point_inside=true;						// точка внутри

		first=i-step; last=i; mid=(first+last)/2;
		while(first<last)
		{
			center=null_center;
			//Поворот вокруг edge
			center.rotatePoint(points[edge.getFP()], points[edge.getSP()], ((float)(direct*mid))/multiplier);

			point_num=if_point_on_ball(edge, center, my_points);
			if (point_num>=0) break;				// точка на сфере
			if (point_num==-2) last=mid;			// точка внутри
			else first=mid+1;
			mid=(first+last)/2;
			if(first<0 && abs(first-last)==1)
				last=first;
		}

		if (point_inside) break;
	}

	//Сохраняем текущее положение центра
	if (point_num>=0) endCenterPos=center;

	return point_num;
}

void ballPivot::ball_pivot(c_point *points, c_edge seed)
{
	c_edge seed_edge;
	c_edge cur_edge;
	c_edge new_edge;

	c_point center;
	int point_num=-1;

	seed_edge=seed;
	edges.push_back(seed_edge);
	all_edges.insert(seed_edge);

	t_triangle triangle;
	bool edge_already_exists=false;
	bool edge_is_full=false;

	while(edges.size())
	{
	cur_edge=edges.front();
		point_num=find_point(cur_edge, points, center);
		
		//if(point_num==-2) 
		//{
		//	//cout<<"ERROR: main.cpp: ball_pivot(): point_num==-2"<<endl<<
		//	//	"edge:"<<cur_edge.getFP()<<","<<cur_edge.getSP()<<"  Left:"<<cur_edge.getLP()<<"  Right:"<<cur_edge.getRP()<<endl;

		//	//throw "ERROR: main.cpp: ball_pivot(): point_num==-2";
		//}

		if(point_num>=0)
		{
			//edge 1
			new_edge=c_edge(cur_edge.getFP(), point_num, cur_edge.getSP(), center);

			edge_is_full=if_edge_is_full(new_edge, true);

			for(list <c_edge>::iterator iter=edges.begin(); iter!=edges.end(); iter++)
				if(*iter==new_edge)
				{
					iter->update(new_edge);
					edge_already_exists=true;
					if(edge_is_full) edges.erase(iter);
					break;
				}
			if(!edge_already_exists && !edge_is_full) edges.push_back(new_edge);
			edge_already_exists=false;
			edge_is_full=false;

			//edge 2
			new_edge=c_edge(cur_edge.getSP(), point_num, cur_edge.getFP(), center);

			edge_is_full=if_edge_is_full(new_edge, true);

			for(list <c_edge>::iterator iter=edges.begin(); iter!=edges.end(); iter++)
				if(*iter==new_edge)
				{
					iter->update(new_edge);
					edge_already_exists=true;
					if(edge_is_full) edges.erase(iter);
					break;
				}
			if(!edge_already_exists && !edge_is_full) edges.push_back(new_edge);
			edge_already_exists=false;
			edge_is_full=false;

			// save cur_edge
			cur_edge.add_point(point_num);
			if_edge_is_full(cur_edge, true);

			//save triangle
			triangle.point1=cur_edge.getFP();
			triangle.point2=cur_edge.getSP();
			triangle.point3=point_num;
			triangles.push(triangle);
		}

		edges.pop_front();
	}
}

void ballPivot::get_triangles()
{
	TRIANGLES_COUNT=triangles.size();
	cout<<TRIANGLES_COUNT<<endl;
	triangles_res=new t_triangle[triangles.size()];
	int i=0;
	
	while (triangles.size())
	{
		triangles_res[i]=triangles.front();
		triangles.pop();
		i++;
	}
}

void ballPivot::init_data(char * file)
{
	radius=8;
	std::ifstream fs(file,std::ios::in | std::ios::binary);
	short *data1ar;
	fs.read((char*)&data_size.x,sizeof(int));
	fs.read((char*)&data_size.y,sizeof(int));
	fs.read((char*)&data_size.z,sizeof(int));

	fs.read((char*)&scale.x,sizeof(float));
	fs.read((char*)&scale.y,sizeof(float));
	fs.read((char*)&scale.z,sizeof(float));
	data1ar = new short [data_size.x*data_size.y*data_size.z];
	data3ar = new short **[data_size.x];
	for( int i = 0; i < data_size.x; i++ )
	{
		data3ar[i] = new short *[data_size.y];
		for( int j = 0; j < data_size.y; j++)
		{
			data3ar[i][j] = new short[data_size.z];
		}
	}

	fs.read((char*)data1ar,sizeof( short ) * data_size.x * data_size.y * data_size.z);
	for(int x=0; x<data_size.x; x++)
		for(int y=0; y<data_size.y; y++)
			for(int z=0; z<data_size.z; z++)
				data3ar[x][y][z] = data1ar[z*data_size.y*data_size.x+y*data_size.x+x];

	COUNT_OF_POINTS_X=data_size.x/STEP_X;
	COUNT_OF_POINTS_Y=data_size.y/STEP_Y;
	COUNT_OF_POINTS_Z=data_size.z/STEP_Z;
	
	razm_x=scale.x;
	razm_y=scale.y;
	razm_z=scale.z;

	COUNT_OF_ALL_POINTS=COUNT_OF_POINTS_X*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z;
	t_points=new c_point[COUNT_OF_ALL_POINTS];

	for(int i=0; i<COUNT_OF_POINTS_X; i++)
	{
		for(int j=0; j<COUNT_OF_POINTS_Y; j++)
		{
			for(int k=0; k<COUNT_OF_POINTS_Z; k++)
			{
				
				t_points[i*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z + j*COUNT_OF_POINTS_Z + k].setX(i);
				t_points[i*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z + j*COUNT_OF_POINTS_Z + k].setY(j);
				t_points[i*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z + j*COUNT_OF_POINTS_Z + k].setZ(k);
				t_points[i*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z + j*COUNT_OF_POINTS_Z + k].setVal(data3ar[i*STEP_X][j*STEP_Y][k*STEP_Z]);
			}
		}
	}

	fs.close();
	delete []data1ar;
	for( int i = 0; i < data_size.x; i++ )
	{
		for( int j = 0; j < data_size.y; j++)
			delete []data3ar[i][j];
		delete []data3ar[i];
	}
	delete []data3ar;
}

ballPivot::ballPivot() {}

ballPivot::ballPivot(char *file)
{
	MIN_DENSITY = 1000;
	razm_x=1; razm_y=1; razm_z=1;
	COUNT_OF_POINTS_X=0; COUNT_OF_POINTS_Y=0; COUNT_OF_POINTS_Z=0;
	COUNT_OF_ALL_POINTS=0; COUNT_OF_ALL_SHOWED_POINTS=0;
	STEP_X=STEP_Y=STEP_Z=5;
	radius=0;
	camera_pos=c_point(0,0,-10);
	angle=5.0f*M_PI/180;
	TRIANGLES_COUNT=0;

	init_data(file);
	
	std::cout<<"Count of all points:"<<std::endl;
	std::cout<<data_size.x * data_size.y * data_size.z<<std::endl;
	std::cout<<"Sizes:"<<std::endl;
	std::cout<<"x:"<<data_size.x<<std::endl;
	std::cout<<"y:"<<data_size.y<<std::endl;
	std::cout<<"z:"<<data_size.z<<std::endl;
	std::cout<<"Sizes of voxel"<<std::endl;
	std::cout<<"x:"<<scale.x<<std::endl;
	std::cout<<"y:"<<scale.y<<std::endl;
	std::cout<<"z:"<<scale.z<<std::endl;

	calc_showed_points(t_points, COUNT_OF_ALL_POINTS, MIN_DENSITY);
	cout<<endl<<COUNT_OF_ALL_SHOWED_POINTS<<endl;
}

ballPivot::ballPivot(TVoxelsData* InputData, int MeshStep_X, int MeshStep_Y, int MeshStep_Z, GLfloat MinVoxelDensity, GLfloat MaxVoxelDensity)
{
 MIN_DENSITY = MinVoxelDensity;
 MAX_DENSITY = MaxVoxelDensity;
 STEP_X = MeshStep_X; STEP_Y = MeshStep_Y; STEP_Z = MeshStep_Z;
 razm_x=InputData->scaleX; razm_y=InputData->scaleY; razm_z=InputData->scaleZ;
 scale.x=razm_x; scale.y=razm_y; scale.z=razm_z;
 COUNT_OF_POINTS_X=InputData->sizeX/STEP_X; COUNT_OF_POINTS_Y=InputData->sizeY/STEP_Y; COUNT_OF_POINTS_Z=InputData->sizeZ/STEP_Z;
 data_size.x=InputData->sizeX; data_size.y=InputData->sizeY; data_size.z=InputData->sizeZ;
 COUNT_OF_ALL_POINTS=COUNT_OF_POINTS_X*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z; 
 COUNT_OF_ALL_SHOWED_POINTS=0;
 radius=8;
 camera_pos=c_point(0,0,-10);
 angle=5.0f*M_PI/180;
 TRIANGLES_COUNT=0;

 // Подсчитываем количество видимых вокселов
 for (size_t i = 0; i < InputData->sizeX; i+=STEP_X)
 for (size_t j = 0; j < InputData->sizeY; j+=STEP_Y)
 for (size_t k = 0; k < InputData->sizeZ; k+=STEP_Z)
	 if((InputData->Density[InputData->ReducedIndex(i, j, k)]>=MIN_DENSITY) && 
	 (InputData->Density[InputData->ReducedIndex(i, j, k)]<=MAX_DENSITY))
		 COUNT_OF_ALL_SHOWED_POINTS++;

 delete [] all_points;
 all_points = new c_point [COUNT_OF_ALL_SHOWED_POINTS];
 c_edge::all_points=all_points;

 // Инициализируем значения всех видимых вокселов
 int num=0;
 for (size_t i = 0; i < InputData->sizeX; i+=STEP_X)
 for (size_t j = 0; j < InputData->sizeY; j+=STEP_Y)
 for (size_t k = 0; k < InputData->sizeZ; k+=STEP_Z)
 if((InputData->Density[InputData->ReducedIndex(i, j, k)]>=MIN_DENSITY) && 
	(InputData->Density[InputData->ReducedIndex(i, j, k)]<=MAX_DENSITY))
	 {
	  all_points[num].setX(i/STEP_X);
	  all_points[num].setY(j/STEP_Y);
	  all_points[num].setZ(k/STEP_Z);
	  all_points[num].setVal(InputData->Density[InputData->ReducedIndex(i, j, k)]);
	  num++;
	 }
}

ballPivot::ballPivot(TVoxelsData *InputData, vector<cv::Point2i> *SnakePoints, int MeshStep_X, int MeshStep_Y, int MeshStep_Z)
{
	MIN_DENSITY = (GLfloat)InputData->MinDensity;
	MAX_DENSITY = (GLfloat)InputData->MaxDensity;
	STEP_X = MeshStep_X; STEP_Y = MeshStep_Y; STEP_Z = MeshStep_Z;
	razm_x=InputData->scaleX; razm_y=InputData->scaleY; razm_z=InputData->scaleZ;
	scale.x=razm_x; scale.y=razm_y; scale.z=razm_z;
	COUNT_OF_POINTS_X = COUNT_OF_POINTS_Y = COUNT_OF_POINTS_Z = 0;
	COUNT_OF_ALL_POINTS = 0;
	COUNT_OF_ALL_SHOWED_POINTS=0;

	bool *IS_USED_X, *IS_USED_Y, *IS_USED_Z;

	IS_USED_X = new bool [InputData->sizeX]; for (size_t i = 0; i < InputData->sizeX; ++i) IS_USED_X[i] = false;
	IS_USED_Y = new bool [InputData->sizeY]; for (size_t j = 0; j < InputData->sizeY; ++j) IS_USED_Y[j] = false;
	IS_USED_Z = new bool [InputData->sizeZ]; for (size_t k = 0; k < InputData->sizeZ; ++k) IS_USED_Z[k] = false;

	vector <size_t> Index_X, Index_Y, Index_Z;
	Index_X.clear(); Index_Y.clear(); Index_Z.clear();

	for (size_t z = 0; z < InputData->sizeZ; ++z)
	{
		vector <cv::Point2i>::iterator iter = SnakePoints[z].begin();
		vector <cv::Point2i>::iterator _end = SnakePoints[z].end();

		for (; iter != _end; ++iter)
		{
			int i = (*iter).x, j = (*iter).y;
			if (!IS_USED_X[i]) {COUNT_OF_POINTS_X++; Index_X.push_back(i); IS_USED_X[i] = true;}
			if (!IS_USED_Y[j]) {COUNT_OF_POINTS_Y++; Index_Y.push_back(j); IS_USED_Y[j] = true;}
		}

		if (SnakePoints[z].size()) {COUNT_OF_POINTS_Z++; Index_Z.push_back(z); IS_USED_Z[z] = true;}

		COUNT_OF_ALL_SHOWED_POINTS += SnakePoints[z].size();
	}

	COUNT_OF_POINTS_X = COUNT_OF_POINTS_Y = COUNT_OF_ALL_SHOWED_POINTS;
	COUNT_OF_POINTS_Z = InputData->sizeZ;

	COUNT_OF_ALL_POINTS = COUNT_OF_ALL_SHOWED_POINTS;

	COUNT_OF_POINTS_X /= STEP_X; COUNT_OF_POINTS_Y /= STEP_Y; COUNT_OF_POINTS_Z /= STEP_Z;
	data_size.x=STEP_X*COUNT_OF_POINTS_X; data_size.y=STEP_Y*COUNT_OF_POINTS_Y; data_size.z=STEP_Z*COUNT_OF_POINTS_Z;
	radius=20;
	camera_pos=c_point(0,0,-10);
	angle=5.0f*M_PI/180;
	TRIANGLES_COUNT=0;

	all_points = new c_point [COUNT_OF_ALL_SHOWED_POINTS];
	c_edge::all_points=all_points;

	int num=0;

	for (size_t k = 0; k < InputData->sizeZ; ++k)
	{
		vector <cv::Point2i>::iterator iter = SnakePoints[k].begin();
		vector <cv::Point2i>::iterator _end = SnakePoints[k].end();

		for (; iter != _end; ++iter)
		{
			int i = (*iter).x, j = (*iter).y;
			
					all_points[num].setX(i);
					all_points[num].setY(j);
					all_points[num].setZ(k);
					all_points[num].setVal((float)InputData->GetDensity(i, j, k));
					num++;
		}
	}

				delete [] IS_USED_X; delete [] IS_USED_Y; delete [] IS_USED_Z;
}

ballPivot::ballPivot(TVoxelsData *InputData, vector <TPath> *paths, size_t LayerIndex, size_t PathIndex, int MeshStep_X, int MeshStep_Y, int MeshStep_Z, GLfloat MinVoxelDensity, GLfloat MaxVoxelDensity)
{
 MIN_DENSITY = MinVoxelDensity;
 MAX_DENSITY = MaxVoxelDensity;
 STEP_X = MeshStep_X; STEP_Y = MeshStep_Y; STEP_Z = MeshStep_Z;
 razm_x=InputData->scaleX; razm_y=InputData->scaleY; razm_z=InputData->scaleZ;
 scale.x=razm_x; scale.y=razm_y; scale.z=razm_z;
 data_size.x=InputData->sizeX; data_size.y=InputData->sizeY; data_size.z=InputData->sizeZ;
 COUNT_OF_POINTS_X=InputData->sizeX/STEP_X; COUNT_OF_POINTS_Y=InputData->sizeY/STEP_Y; COUNT_OF_POINTS_Z=InputData->sizeZ/STEP_Z;
 //COUNT_OF_POINTS_X = COUNT_OF_POINTS_Y = COUNT_OF_POINTS_Z = 0;
 COUNT_OF_ALL_POINTS = COUNT_OF_POINTS_X*COUNT_OF_POINTS_Y*COUNT_OF_POINTS_Z;
 COUNT_OF_ALL_SHOWED_POINTS=0;
 radius=8;
 camera_pos=c_point(0,0,-10);
 angle=5.0f*M_PI/180;
 TRIANGLES_COUNT=0;

 bool *IS_USED_X, *IS_USED_Y, *IS_USED_Z;

 IS_USED_X = new bool [InputData->sizeX]; for (size_t i = 0; i < InputData->sizeX; ++i) IS_USED_X[i] = false;
 IS_USED_Y = new bool [InputData->sizeY]; for (size_t j = 0; j < InputData->sizeY; ++j) IS_USED_Y[j] = false;
 IS_USED_Z = new bool [InputData->sizeZ]; for (size_t k = 0; k < InputData->sizeZ; ++k) IS_USED_Z[k] = false;

 vector <size_t> Index_X, Index_Y, Index_Z;
 Index_X.clear(); Index_Y.clear(); Index_Z.clear();

 size_t z = LayerIndex-1; 
 
 if (z > -1)
 {
	 vector <size_t>::iterator iter = paths[LayerIndex].at(PathIndex).backward.begin();
	 vector <size_t>::iterator _end = paths[LayerIndex].at(PathIndex).backward.end();
	 for (; iter != _end; iter += STEP_Z, z -= STEP_Z)
	 {
		 for (size_t i = 0; i < InputData->sizeX; i += STEP_X)
			 for (size_t j = 0; j < InputData->sizeY; j += STEP_Y)
				 if ((InputData->VoxelSegments[InputData->ReducedIndex(i, j, z)].SegmentIndex_2D == *iter) &&
					 (InputData->Density[InputData->ReducedIndex(i, j, z)] >= MIN_DENSITY) &&
					 (InputData->Density[InputData->ReducedIndex(i, j, z)] <= MAX_DENSITY))
				 {
					/* if (!IS_USED_X[i]) {COUNT_OF_POINTS_X++; Index_X.push_back(i); IS_USED_X[i] = true;}
					 if (!IS_USED_Y[j]) {COUNT_OF_POINTS_Y++; Index_Y.push_back(j); IS_USED_Y[j] = true;}
					 if (!IS_USED_Z[z]) {COUNT_OF_POINTS_Z++; Index_Z.push_back(z); IS_USED_Z[z] = true;}
					 */

					 COUNT_OF_ALL_SHOWED_POINTS++;
				 }
	 }

 }

 for (size_t i = 0; i < InputData->sizeX; i += STEP_X)
 for (size_t j = 0; j < InputData->sizeY; j += STEP_Y)
 if (InputData->VoxelSegments[InputData->ReducedIndex(i, j, LayerIndex)].SegmentIndex_2D == paths[LayerIndex].at(PathIndex).root)
 {
  /* if (!IS_USED_X[i]) {COUNT_OF_POINTS_X++; Index_X.push_back(i); IS_USED_X[i] = true;}
  if (!IS_USED_Y[j]) {COUNT_OF_POINTS_Y++; Index_Y.push_back(j); IS_USED_Y[j] = true;}
  if (!IS_USED_Z[LayerIndex]) {COUNT_OF_POINTS_Z++; Index_Z.push_back(LayerIndex); IS_USED_Z[LayerIndex] = true;} */
	 COUNT_OF_ALL_SHOWED_POINTS++;
 }

 z = LayerIndex+1; 

 if (z < InputData->sizeZ)
 {
	 vector <size_t>::iterator iter = paths[LayerIndex].at(PathIndex).forward.begin();
	 vector <size_t>::iterator _end = paths[LayerIndex].at(PathIndex).forward.end();
	 for (; iter != _end; iter += STEP_Z, z += STEP_Z)
	 {
		 for (size_t i = 0; i < InputData->sizeX; i += STEP_X)
			 for (size_t j = 0; j < InputData->sizeY; j += STEP_Y)
				 if ((InputData->VoxelSegments[InputData->ReducedIndex(i, j, z)].SegmentIndex_2D == *iter) &&
					 (InputData->Density[InputData->ReducedIndex(i, j, z)] >= MIN_DENSITY) &&
					 (InputData->Density[InputData->ReducedIndex(i, j, z)] <= MAX_DENSITY))
				 {
					/* if (!IS_USED_X[i]) {COUNT_OF_POINTS_X++; Index_X.push_back(i); IS_USED_X[i] = true;}
					 if (!IS_USED_Y[j]) {COUNT_OF_POINTS_Y++; Index_Y.push_back(j); IS_USED_Y[j] = true;}
					 if (!IS_USED_Z[z]) {COUNT_OF_POINTS_Z++; Index_Z.push_back(z); IS_USED_Z[z] = true;} */
					 COUNT_OF_ALL_SHOWED_POINTS++;
				 }
	 }
	
 }

 // for (int k = 1; k <= paths[LayerIndex].at(PathIndex).backward.size(); ++k)
 /* for (int i = 0; i < COUNT_OF_POINTS_X; ++i)
 for (int j = 0; j < COUNT_OF_POINTS_Y; ++j)
 for (int k = 0; k < COUNT_OF_POINTS_Z; ++k)
 {
	 if ((Index_Z.at(STEP_Z*k)>=LayerIndex-paths[LayerIndex].at(PathIndex).backward.size())&&
		 (Index_Z.at(STEP_Z*k)<LayerIndex))
 if ((InputData->VoxelSegments[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)].SegmentIndex_2D == paths[LayerIndex].at(PathIndex).backward.at(LayerIndex-Index_Z.at(STEP_Z*k)-1)) &&
	 (InputData->Density[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]>=MIN_DENSITY) &&
	 (InputData->Density[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]<=MAX_DENSITY))
 COUNT_OF_ALL_SHOWED_POINTS++; 
 }

 for (int i = 0; i < COUNT_OF_POINTS_X; ++i)
 for (int j = 0; j < COUNT_OF_POINTS_Y; ++j)
 if ((InputData->VoxelSegments[LayerIndex*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)].SegmentIndex_2D == paths[LayerIndex].at(PathIndex).root) &&
	 (InputData->Density[LayerIndex*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]>=MIN_DENSITY) &&
	 (InputData->Density[LayerIndex*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]<=MAX_DENSITY))
 COUNT_OF_ALL_SHOWED_POINTS++; 

 for (int i = 0; i < COUNT_OF_POINTS_X; ++i)
 for (int j = 0; j < COUNT_OF_POINTS_Y; ++j)
 for (int k = 0; k < COUNT_OF_POINTS_Z; ++k)
 {
	 if ((Index_Z.at(STEP_Z*k)>LayerIndex)&&
		 (Index_Z.at(STEP_Z*k)<=LayerIndex+paths[LayerIndex].at(PathIndex).forward.size()))
 if ((InputData->VoxelSegments[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)].SegmentIndex_2D == paths[LayerIndex].at(PathIndex).forward.at(Index_Z.at(STEP_Z*k)-LayerIndex-1)) &&
	 (InputData->Density[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]>=MIN_DENSITY) &&
	 (InputData->Density[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]<=MAX_DENSITY))
 COUNT_OF_ALL_SHOWED_POINTS++; 
 } */

 // delete [] all_points;
 all_points = new c_point [COUNT_OF_ALL_SHOWED_POINTS];
 c_edge::all_points=all_points;

 int num=0;
 
 z = LayerIndex-1; 
 
 if (z > -1)
 {
	 vector <size_t>::iterator iter = paths[LayerIndex].at(PathIndex).backward.begin();
	 vector <size_t>::iterator _end = paths[LayerIndex].at(PathIndex).backward.end();
	 for (; iter != _end; iter++, --z)
	 {
		  for (size_t k = 0; k < InputData->sizeZ; k += STEP_Z) if (k == z)
		  {
			for (size_t i = 0; i < InputData->sizeX; i += STEP_X)
			 for (size_t j = 0; j < InputData->sizeY; j += STEP_Y)
				
				 if ((InputData->VoxelSegments[InputData->ReducedIndex(i, j, z)].SegmentIndex_2D == *iter) &&
					 (InputData->Density[InputData->ReducedIndex(i, j, z)] >= MIN_DENSITY) &&
					 (InputData->Density[InputData->ReducedIndex(i, j, z)] <= MAX_DENSITY))
				 

			 {
			  all_points[num].setX(i/STEP_X);
			  all_points[num].setY(j/STEP_Y);
			  all_points[num].setZ(k/STEP_Z);
			  all_points[num].setVal(InputData->Density[InputData->ReducedIndex(i, j, z)]);
			  num++;
			 }
		  }
	 }
 }

 for (size_t k = 0; k < InputData->sizeZ; k += STEP_Z) if (k == LayerIndex)
 {
	 for (size_t i = 0; i < InputData->sizeX; i += STEP_X)
	 for (size_t j = 0; j < InputData->sizeY; j += STEP_Y)
	 if ((InputData->VoxelSegments[InputData->ReducedIndex(i, j, LayerIndex)].SegmentIndex_2D == paths[LayerIndex].at(PathIndex).root) &&
		 (InputData->Density[InputData->ReducedIndex(i, j, LayerIndex)]>=MIN_DENSITY) &&
		 (InputData->Density[InputData->ReducedIndex(i, j, LayerIndex)]<=MAX_DENSITY))
	 {
	  all_points[num].setX(i/STEP_X);
	  all_points[num].setY(j/STEP_Y);
	  all_points[num].setZ(LayerIndex/STEP_Z);
	  all_points[num].setVal(InputData->Density[InputData->ReducedIndex(i, j, LayerIndex)]);
	  num++;
	 }
 }

 z = LayerIndex + 1;

 if (z < InputData->sizeZ)
 {
	 vector <size_t>::iterator iter = paths[LayerIndex].at(PathIndex).forward.begin();
	 vector <size_t>::iterator _end = paths[LayerIndex].at(PathIndex).forward.end();
	 for (; iter != _end; ++iter, ++z)
	 {
		for (size_t k = 0; k < InputData->sizeZ; k += STEP_Z) if (k == z)
		{
			for (size_t i = 0; i < InputData->sizeX; i += STEP_X)
				 for (size_t j = 0; j < InputData->sizeY; j += STEP_Y)
					
					 if ((InputData->VoxelSegments[InputData->ReducedIndex(i, j, z)].SegmentIndex_2D == *iter) &&
						 (InputData->Density[InputData->ReducedIndex(i, j, z)] >= MIN_DENSITY) &&
						 (InputData->Density[InputData->ReducedIndex(i, j, z)] <= MAX_DENSITY))
				{
				  all_points[num].setX(i/STEP_X);
				  all_points[num].setY(j/STEP_Y);
				  all_points[num].setZ(k/STEP_Z);
				  all_points[num].setVal(InputData->Density[InputData->ReducedIndex(i, j, z)]);
				  num++;
				}
		}
	 }
 }

 delete [] IS_USED_X; delete [] IS_USED_Y; delete [] IS_USED_Z;
}

ballPivot::ballPivot(TVoxelsData *InputData, int SegmentIndex, int MeshStep_X, int MeshStep_Y, int MeshStep_Z, GLfloat MinVoxelDensity, GLfloat MaxVoxelDensity)
{
 MIN_DENSITY = MinVoxelDensity;
 MAX_DENSITY = MaxVoxelDensity;
 STEP_X = MeshStep_X; STEP_Y = MeshStep_Y; STEP_Z = MeshStep_Z;
 razm_x=InputData->scaleX; razm_y=InputData->scaleY; razm_z=InputData->scaleZ;
 scale.x=razm_x; scale.y=razm_y; scale.z=razm_z;
 COUNT_OF_POINTS_X = COUNT_OF_POINTS_Y = COUNT_OF_POINTS_Z = 0;
 COUNT_OF_ALL_POINTS = 0;
 COUNT_OF_ALL_SHOWED_POINTS=0;

 bool *IS_USED_X, *IS_USED_Y, *IS_USED_Z;

 IS_USED_X = new bool [InputData->sizeX]; for (size_t i = 0; i < InputData->sizeX; ++i) IS_USED_X[i] = false;
 IS_USED_Y = new bool [InputData->sizeY]; for (size_t j = 0; j < InputData->sizeY; ++j) IS_USED_Y[j] = false;
 IS_USED_Z = new bool [InputData->sizeZ]; for (size_t k = 0; k < InputData->sizeZ; ++k) IS_USED_Z[k] = false;

 vector <size_t> Index_X, Index_Y, Index_Z;
 Index_X.clear(); Index_Y.clear(); Index_Z.clear();

 for (size_t i = 0; i < InputData->sizeX; ++i)
 for (size_t j = 0; j < InputData->sizeY; ++j)
 for (size_t k = 0; k < InputData->sizeZ; ++k)
 if (InputData->VoxelSegments[k*InputData->sizeX*InputData->sizeY+j*InputData->sizeX+i].SegmentIndex_3D == SegmentIndex) 
 {
  //COUNT_OF_ALL_POINTS++;
  if (!IS_USED_X[i]) {COUNT_OF_POINTS_X++; Index_X.push_back(i); IS_USED_X[i] = true;}
  if (!IS_USED_Y[j]) {COUNT_OF_POINTS_Y++; Index_Y.push_back(j); IS_USED_Y[j] = true;}
  if (!IS_USED_Z[k]) {COUNT_OF_POINTS_Z++; Index_Z.push_back(k); IS_USED_Z[k] = true;}
 }

 COUNT_OF_POINTS_X /= STEP_X; COUNT_OF_POINTS_Y /= STEP_Y; COUNT_OF_POINTS_Z /= STEP_Z;
 data_size.x=STEP_X*COUNT_OF_POINTS_X; data_size.y=STEP_Y*COUNT_OF_POINTS_Y; data_size.z=STEP_Z*COUNT_OF_POINTS_Z;
 radius=8;
 camera_pos=c_point(0,0,-10);
 angle=5.0f*M_PI/180;
 TRIANGLES_COUNT=0;

  for (int i = 0; i < COUNT_OF_POINTS_X; ++i)
	 for (int j = 0; j < COUNT_OF_POINTS_Y; ++j)
		 for (int k = 0; k < COUNT_OF_POINTS_Z; ++k)
			 if ((InputData->VoxelSegments[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)].SegmentIndex_3D == SegmentIndex) &&
				 (InputData->Density[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]>=MIN_DENSITY) &&
				 (InputData->Density[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]<=MAX_DENSITY))
					 COUNT_OF_ALL_SHOWED_POINTS++; 

 // delete [] all_points;
 all_points = new c_point [COUNT_OF_ALL_SHOWED_POINTS];
 c_edge::all_points=all_points;

 int num=0;
 for (int i = 0; i < COUNT_OF_POINTS_X; ++i)
 for (int j = 0; j < COUNT_OF_POINTS_Y; ++j)
 for (int k = 0; k < COUNT_OF_POINTS_Z; ++k)
 if ((InputData->VoxelSegments[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)].SegmentIndex_3D == SegmentIndex) &&
	 (InputData->Density[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]>=MIN_DENSITY) &&
	 (InputData->Density[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]<=MAX_DENSITY))
	 {
	  all_points[num].setX(i);
	  all_points[num].setY(j);
	  all_points[num].setZ(k);
	  all_points[num].setVal(InputData->Density[Index_Z.at(STEP_Z*k)*InputData->sizeX*InputData->sizeY+Index_Y.at(STEP_Y*j)*InputData->sizeX+Index_X.at(STEP_X*i)]);
	  num++;
	 }
	
 delete [] IS_USED_X; delete [] IS_USED_Y; delete [] IS_USED_Z;
}


void ballPivot::buildMesh()
{

	LARGE_INTEGER before, after, freq;
    QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&before);
	// sortArrOfPoints(all_points, COUNT_OF_ALL_SHOWED_POINTS);
	searchOfObjects(all_points, COUNT_OF_ALL_SHOWED_POINTS, radius, objects);	
	QueryPerformanceCounter(&after);
	double cpu_time = (after.QuadPart - before.QuadPart) / double(freq.QuadPart);
	cout<<cpu_time;

cout<<" sorted"<<endl;

//---------

    QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&before);

	int obj_pos=0;
	for(list<c_object>::iterator iter=objects.begin(); iter!=objects.end(); iter++)
	{
		obj_pos++;
		ball_pivot(all_points, iter->getEdge());
		cout<<"Object "<<obj_pos<<" processed"<<endl;
	}
	postProcessing(all_points, COUNT_OF_ALL_SHOWED_POINTS);
	get_triangles();
	
	QueryPerformanceCounter(&after);
    cpu_time = (after.QuadPart - before.QuadPart) / double(freq.QuadPart);
	cout<<cpu_time;
}

//void ballPivot::renderMesh()
//{
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(500,500);
//	glutCreateWindow("Simple");
//	   
//	SetupRC();
//	glutDisplayFunc(RenderScene);
//	glutReshapeFunc(&ballPivot::ChangeSize);
//	glutKeyboardFunc(&ballPivot::ManageKeys);
//	   
//	glutMainLoop();
//}

ballPivot::~ballPivot()
{
	/* delete []t_points;
	delete []all_points;
	delete []triangles_res; */
}

#endif C_BALLPIVOT_H