#include "Methods.h"

using namespace cv;
using namespace std;

float GetMeanDensity(TVoxelsData* Data, vector <size_t> Segment)
{
	float result = 0.0f;
	vector <size_t>::iterator iter = Segment.begin();
	vector <size_t>::iterator end = Segment.end();
	for (; iter != end; ++iter)	result += Data->Density[*iter];
	return result/Segment.size();
}

Point2f GetMeanCoords_2D(TVoxelsData* Data, vector <size_t> Segment)
{
	Point2f result(0.0f, 0.0f);
	vector <size_t>::iterator iter = Segment.begin();
	vector <size_t>::iterator end = Segment.end();
	for (; iter != end; ++iter) 
	{
		size_t x = *iter%Data->sizeX,  
			   y = ((*iter-x)/Data->sizeX)%Data->sizeY;
		result += Point2f((float)x, (float)y);
	}
		
	return (1.0f/Segment.size())*result;
}

Point3f GetMeanCoords_3D(TVoxelsData* Data, vector <size_t> Segment)
{
	Point3f result(0.0f, 0.0f, 0.0f);
	vector <size_t>::iterator iter = Segment.begin();
	vector <size_t>::iterator end = Segment.end();
	for (; iter != end; ++iter)
	{
		size_t x = *iter%Data->sizeX,
			   y = ((*iter-x)/Data->sizeX)%Data->sizeY,
			   z = (*iter-Data->sizeX*y)/(Data->sizeX*Data->sizeY); 
		result += Point3f((float)x, (float)y, (float)z);
	}

	return (1.0f/Segment.size())*result;
}

Point3f GetMeanDensityCoords_2D(TVoxelsData* Data, vector <size_t> Segment)
{
	Point3f result(0.0f, 0.0f, 0.0f);
	vector <size_t>::iterator iter = Segment.begin();
	vector <size_t>::iterator end = Segment.end();
	for (; iter != end; ++iter)
	{
		size_t x = *iter%Data->sizeX,  
			   y = ((*iter-x)/Data->sizeX)%Data->sizeY;
		result += Point3f((float)Data->Density[*iter], (float)x, (float)y);
	}

	return (1.0f/Segment.size())*result;
}

Vec4f GetMeanDensityCoords_3D(TVoxelsData* Data, vector <size_t> Segment)
{
	Vec4f result(0.0f, 0.0f, 0.0f, 0.0f);
	vector <size_t>::iterator iter = Segment.begin();
	vector <size_t>::iterator end = Segment.end();
	for (; iter != end; ++iter)
	{
		size_t x = *iter%Data->sizeX,  
			   y = ((*iter-x)/Data->sizeX)%Data->sizeY,
			   z = (*iter-x-Data->sizeX*y)/(Data->sizeX*Data->sizeY);
		result += Vec4f((float)Data->Density[*iter], (float)x, (float)y, (float)z);
	}

	return (1.0f/Segment.size())*result;
}

Point_<short> MinMaxDensityOfSegment_2D(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int SegmentType)
{
 short result_min = Data->MaxDensity, result_max = Data->MinDensity;
			  
 for (size_t i = 0; i < Data->sizeX*Data->sizeY; ++i)
 {
  bool value = SegmentType == SPATIAL ? (Data->VoxelSegments[i+LayerIndex*Data->sizeX*Data->sizeY].SpatialSegmentIndex_2D == SegmentIndex) :
									    (Data->VoxelSegments[i+LayerIndex*Data->sizeX*Data->sizeY].SegmentIndex_2D == SegmentIndex);
  if (value)
  {
	 result_min = min<short>(Data->Density[i+LayerIndex*Data->sizeX*Data->sizeY], result_min);
	 result_max = max<short>(Data->Density[i+LayerIndex*Data->sizeX*Data->sizeY], result_max);
  }
 }
 
 return Point_<short>(result_min, result_max);
}

Point_<short> MinMaxDensityOfSegment_3D(TVoxelsData* Data, size_t StartLayerIndex, int SegmentIndex, int SegmentType)
{
 short result_min = Data->MaxDensity, result_max = Data->MinDensity; 

 for (size_t i = 0; i < Data->TotalSize - StartLayerIndex*Data->sizeX*Data->sizeY; ++i)
 {
  bool value = SegmentType == SPATIAL ? (Data->VoxelSegments[i+StartLayerIndex*Data->sizeX*Data->sizeY].SpatialSegmentIndex_3D == SegmentIndex) :
									    (Data->VoxelSegments[i+StartLayerIndex*Data->sizeX*Data->sizeY].SegmentIndex_3D == SegmentIndex);
  if (value)
  {
	 result_min = min<short>(Data->Density[i+StartLayerIndex*Data->sizeX*Data->sizeY], result_min);
	 result_max = max<short>(Data->Density[i+StartLayerIndex*Data->sizeX*Data->sizeY], result_max);
  }
 }
 
 return Point_<short>(result_min, result_max);
}

Point2f DensityMeanDevOfSegment_2D(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int SegmentType)
{
	float sqr = 0.0f, mean = 0.0f; int N = 0;
	for (size_t i = 0; i < Data->sizeX*Data->sizeY; ++i)
	{
		bool value = SegmentType == SPATIAL ? (Data->VoxelSegments[i+LayerIndex*Data->sizeX*Data->sizeY].SpatialSegmentIndex_2D == SegmentIndex) :
											  (Data->VoxelSegments[i+LayerIndex*Data->sizeX*Data->sizeY].SegmentIndex_2D == SegmentIndex);
		if (value)
		{
		   short density = Data->Density[i+LayerIndex*Data->sizeX*Data->sizeY];
		   sqr += density*density; mean += density;
		   N++;
		}
	}
	
	return Point2f(mean/N, sqrt(sqr/N-(mean/N)*(mean/N)));
}

Vec4f MeanDevXYOfSegment_2D(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int SegmentType)
{
	float sqr_x = 0.0f, sqr_y = 0.0f, mean_x = 0.0f, mean_y = 0.0f; int N = 0;

	for (size_t i = 0; i < Data->sizeX; ++i)
	for (size_t j = 0; j < Data->sizeY; ++j)
	{
		bool value = SegmentType == SPATIAL ? (Data->VoxelSegments[Data->ReducedIndex(i, j, LayerIndex)].SpatialSegmentIndex_2D == SegmentIndex) :
											  (Data->VoxelSegments[Data->ReducedIndex(i, j, LayerIndex)].SegmentIndex_2D == SegmentIndex);
			
		if (value)
		{
		   sqr_x += i*i; sqr_y += j*j;
		   mean_x += i; mean_y += j; 
		   N++;
		}
	}
	
	return Vec4f(mean_x/N, mean_y/N, sqrt(sqr_x/N-(mean_x/N)*(mean_x/N)), sqrt(sqr_y/N-(mean_y/N)*(mean_y/N)));
}

void SegmentsSort(const TVoxelsData* Data, vector <TSegment>& Segments, size_t LayerIndex, int left, int right)
{
	int middle, a;

	int i = left, j = right;
	middle = (left+right)/2;
	a = Segments.at(middle).MinDensity;

	do
	{
		while (Segments.at(i).MinDensity < a) i++;
		while (a < Segments.at(j).MinDensity) j--;

		if (i<=j)
		{
			swap(Segments.at(i), Segments.at(j));
			for (size_t index = 0; index < Data->TotalSize/Data->sizeZ; ++index)
			{
				size_t reduced_index = index+LayerIndex*Data->sizeX*Data->sizeY;

					if (Data->VoxelSegments[reduced_index].SegmentIndex_2D == i)
						Data->VoxelSegments[reduced_index].SegmentIndex_2D = j;
					else if (Data->VoxelSegments[reduced_index].SegmentIndex_2D == j)
						Data->VoxelSegments[reduced_index].SegmentIndex_2D = i;
			}
			i++; j--;
		}
	}
	while (i <= j);

	if (left < j) SegmentsSort(Data, Segments, LayerIndex, left, j);
	if (i < right) SegmentsSort(Data, Segments, LayerIndex, i, right);
} 

System::String^ GetStringOfColor(TColor Color)
{
  return L"Color[R = "+((unsigned char)(Color.R*255)).ToString()+L", "+
	           L"G = "+((unsigned char)(Color.G*255)).ToString()+L", "+
			   L"B = "+((unsigned char)(Color.B*255)).ToString()+L"]";
}