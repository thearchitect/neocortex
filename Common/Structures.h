#pragma once

#include <vector>
#include "opencv/cv.h"

#define IsVolumeUsing true
#define IsMeanXYUsing true
#define IsDevXYUsing true
#define IsMeanDensityUsing true
#define IsDevDensityUsing true

struct TLayer  // ���� ������ (��������� �����������)
{ 
 short *Density;
 size_t sizeX, sizeY;  // ������ � ������ ����
 float scaleX, scaleY; // ������� ���� �� ����

 // ������������
 TLayer() : Density(0), sizeX(0), sizeY(0), scaleX(0), scaleY(0) {};
 TLayer(short*_density, size_t _sizeX, size_t _sizeY, float _scaleX, float _scaleY): 
 Density(_density), sizeX(_sizeX), sizeY(_sizeY), scaleX(_scaleX), scaleY(_scaleY) {};

 size_t ReducedIndex(size_t x, size_t y);	// ���������� ������ ������� � ������ ������

 // ������ ������� � ������ � ������
 short GetDensity(size_t index);
 short GetDensity(size_t x, size_t y);

 // ������, ����������� ���������� ������� ����� ���������
 float GetDistance(const cv::Point_<size_t> &p1, const cv::Point_<size_t> &p2);
 float GetDistance(size_t i, size_t j);
};

struct TVoxelSegments					
{
 int SegmentIndex_2D, SegmentIndex_3D;					// ������� ���������, ������� ����������� ������
 int SpatialSegmentIndex_2D, SpatialSegmentIndex_3D;	// ������� ���������������� ���������, ������� ����������� ������
 int ComponentIndex_2D;									// ������ ���������� ���������, �������� � �������, �������� ����������� ������

 // ����������� �� ���������
 TVoxelSegments(): SegmentIndex_2D(-1), SegmentIndex_3D(-1), 
				   SpatialSegmentIndex_2D(-1), SpatialSegmentIndex_3D(-1),
				   ComponentIndex_2D(-1) {}
};

struct TColor 
{
 float R, G, B, A;						// ��������� �����
 TColor():R(0), G(0), B(0), A(0) {};
 TColor(float value_R, float value_G, float value_B, float value_A): 
        R(value_R), G(value_G), B(value_B), A(value_A) {};
 TColor(float value_R, float value_G, float value_B): R(value_R), G(value_G), B(value_B) {};
};

struct TPath						// ���� (�������) �� ���������
{
 size_t root;						// ������ �������
 std::vector <size_t> forward;		// �������� �������� �������
 std::vector <size_t> backward;		// ������ �������� �������

 // ����������� �� ���������
 TPath():root(0) { forward.clear(); backward.clear(); }
};

class TVoxelsData 
{
 public:
		short *Density;					// ��������� ��������
		bool *IsVoxelUsed;				// ����� ������������ ��������
		TVoxelSegments *VoxelSegments;	// ��������, ������� ����������� �������
		
		size_t sizeX, sizeY, sizeZ;		// ������� ����� ������������ ����
		float scaleX, scaleY, scaleZ;	// �������� ����� ������������ ����

		size_t TotalSize;				// ������ ����� ������ ��������

		short MinDensity, MaxDensity;	// ����������� � ������������ �������� ���������

		float DensityVariance;			// ��������� ���������
		float XVariance, YVariance;		// ��������� �� �����������

		// ������������ � ����������
		TVoxelsData();
		TVoxelsData(const char *pathToBinFile);
		TVoxelsData(const TLayer &layer);
		~TVoxelsData();

		void Init();	// ������������� ���� ����� ���������� �� ���������
		void Clear();	// ������������ ���� ��������, ������� �������

		// ������ �������� ������ �� �����
		bool Load(const char *pathToBinFile);
		bool Load(const char *pathToBinFile, size_t z_start, size_t nLayers);

		// ������ ��������� ������������ �������� ������ 
		TVoxelsData* GetSubData(size_t z_first, size_t z_last);
		TLayer GetLayer(size_t z); 
		
		size_t ReducedIndex(size_t x, size_t y, size_t z);	// ���������� ������ ������� � ������ ������

		// ������ ������� � ������ � ������
		short GetDensity(size_t index);
		short GetDensity(size_t x, size_t y, size_t z);
		
		// ������, ����������� ���������� ������� ����� ���������
		float GetDistance(const cv::Point3_<size_t> &p1, const cv::Point3_<size_t> &p2);
		float GetDistance(size_t i, size_t j);

		// ������, ����������� ��������� ��������� � ��������� ��������
		void CalcDensityVariance();
		void CalcXYVariance();

		// ����� ������� ��������
		int FindConnectedRegions(size_t LayerIndex, int SegmentIndex, int SegmentType);
};

struct TSegment					// ������� �� ��������
{
 short MinDensity;				// ����������� �������� ��������� 
 short MaxDensity;				// ������������ �������� ���������

 short* Histogram;				// ����������� �������� ���������
 
 TColor Color;					// ���� ��������
 bool Visible;					// ������� ��������� ��������, �������� � �������

 TColor tmpColor;				// ��������������� ���� ��������
 bool tmpVisible;				// ��������������� ������� ���������

 float MeanX, MeanY;			// �������������� ����� ��������
 float DevX, DevY;				// �������������������� ���������� ����� ������������ ����
 float MeanDensity;				// ������� �������� ���������
 float DensityDev;				// ������� �������� �������� �� ���������
 float Volume;					// ����� �������� (� ������ �������� ������� ����� ����)

 std::vector <TSegment>* NextLevelSegments;	// �������� ���������� ������ ��������
 
 // ����������� �������� �� ���������
 TSegment(): MinDensity(0), MaxDensity(0), Histogram(0), NextLevelSegments(0),
	         Color(TColor(0.0f, 0.0f, 0.0f, 0.0f)), Visible(false), 
			 tmpColor(TColor(0.0f, 0.0f, 0.0f, 0.0f)), tmpVisible(false) {}

 double DistanceTo(const TSegment &segment, const bool* flags = NULL);

 bool IsAdjacentWith(const TSegment &segment);
};

struct TSegmentParent			// �������� ��������� �������� � ������� ������������
{
	size_t LayerRoot;			// ������ ����
	size_t SegmentRoot;			// ������ ��������

	// ������������
	TSegmentParent() : LayerRoot(0), SegmentRoot(0) {}
	TSegmentParent(size_t layer_index, size_t segment_index) : LayerRoot(layer_index), SegmentRoot(segment_index) {}
};

struct TSegmentComponent	// ���������� ��������� ���������
{
private:
	std::vector <std::vector <cv::Point_<size_t> > > contours;	// �������
	std::vector <cv::Vec4i> hierarchy;							// ��������
public:
	TSegmentComponent(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int ComponentIndex);
};

typedef std::vector <TSegmentComponent> TSegmentGraph;		// �������� ������ ������������� ��������


