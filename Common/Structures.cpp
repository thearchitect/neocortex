#include "Structures.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>

using namespace cv;
using namespace std;

#pragma region TLayer methods

short TLayer::GetDensity(size_t index) { return Density[index]; }
short TLayer::GetDensity(size_t x, size_t y) { return Density[ReducedIndex(x, y)]; }

size_t TLayer::ReducedIndex(size_t x, size_t y) { return x + sizeX*y; }

float TLayer::GetDistance(const Point_<size_t> &p1, const Point_<size_t> &p2) 
{ 
	return fabs((float)(Density[ReducedIndex(p1.x, p1.y)] - Density[ReducedIndex(p2.x, p2.y)])); 
}

float TLayer::GetDistance(size_t i, size_t j) {	return fabs((float)(Density[i] - Density[j])); }

#pragma endregion

#pragma region TVoxelsData methods

void TVoxelsData::Init() 
{
	sizeX = sizeY = sizeZ = TotalSize = 0;
	scaleX = scaleY = scaleZ = 0.0f;
	MinDensity = MaxDensity = 0;
	Density = NULL;	
	IsVoxelUsed = NULL;
	VoxelSegments = NULL;
}

void TVoxelsData::Clear()
{
	delete [] Density;
	delete [] IsVoxelUsed;
	delete [] VoxelSegments;

	Init();
}

bool TVoxelsData::Load(const char* pathToBinFile)
{
	 ifstream fs(pathToBinFile, std::ios::in | std::ios::binary);

	 if (!fs) return false;
	    
	 fs.read((char*)&sizeX, sizeof(int));
	 fs.read((char*)&sizeY, sizeof(int));
	 fs.read((char*)&sizeZ, sizeof(int));

	 TotalSize = sizeX*sizeY*sizeZ;

	 fs.read((char*)&scaleX, sizeof(float));
	 fs.read((char*)&scaleY, sizeof(float));
	 fs.read((char*)&scaleZ, sizeof(float));

	 Density = new short [TotalSize];

	 fs.read((char*)Density, sizeof(short) * TotalSize);

	 fs.close();

	 VoxelSegments = new TVoxelSegments [TotalSize];
	 IsVoxelUsed = NULL;

	 return true;
}

bool TVoxelsData::Load(const char* pathToBinFile, size_t StartLayer, size_t nLayers)
{
 ifstream fs(pathToBinFile, std::ios::in | std::ios::binary);

 if (!fs) return false;

 fs.read((char*)&sizeX, sizeof(int));
 fs.read((char*)&sizeY, sizeof(int));
 fs.read((char*)&sizeZ, sizeof(int));
 
 TotalSize = nLayers*sizeX*sizeY;

 fs.read((char*)&scaleX, sizeof(float));
 fs.read((char*)&scaleY, sizeof(float));
 fs.read((char*)&scaleZ, sizeof(float));
 
 for (size_t i = 0; i < StartLayer; ++i)
 {
	Density = new short [sizeX*sizeY];

	fs.read((char*)Density, sizeof(short) * sizeX * sizeY);

	delete [] Density; 
	
	Density = NULL;
 }

 Density = new short [TotalSize];
 
 fs.read((char*)Density, sizeof(short)*TotalSize);

 fs.close();
 
 return true;
}

TVoxelsData::TVoxelsData() { Init(); }
TVoxelsData::TVoxelsData(const char* pathToBinFile) { Load(pathToBinFile); }
TVoxelsData::TVoxelsData(const TLayer &layer) 
{
	sizeX = layer.sizeX; sizeY = layer.sizeY; sizeZ = 1;
    
	TotalSize = sizeX*sizeY*sizeZ;
	
    scaleX = layer.scaleX; scaleY = layer.scaleY;

	Density = layer.Density;
	VoxelSegments = new TVoxelSegments [TotalSize];
	IsVoxelUsed = NULL;
}

TVoxelsData::~TVoxelsData() { Clear(); }

TVoxelsData* TVoxelsData::GetSubData(size_t z_first, size_t z_last)
{
 TVoxelsData* result = new TVoxelsData();
 
 result->Density = Density + z_first*sizeX*sizeY;
 result->IsVoxelUsed = NULL;
 result->VoxelSegments = NULL;
 
 result->sizeX = sizeX; 
 result->sizeY = sizeY;
 result->sizeZ = z_last-z_first+1;

 TotalSize = sizeX*sizeY*sizeZ;

 result->scaleX = scaleX;
 result->scaleY = scaleY;
 result->scaleZ = scaleZ;

 result->MinDensity = MinDensity;
 result->MaxDensity = MaxDensity;
    
 return result;
}

TLayer TVoxelsData::GetLayer(size_t z) { return TLayer(Density + z*sizeX*sizeY, sizeX, sizeY, scaleX, scaleY); }

size_t TVoxelsData::ReducedIndex(size_t x, size_t y, size_t z) { return x + y*sizeX + z*sizeX*sizeY; }

short TVoxelsData::GetDensity(size_t index) { return Density[index]; }
short TVoxelsData::GetDensity(size_t x, size_t y, size_t z) { return Density[ReducedIndex(x, y, z)]; }

float TVoxelsData::GetDistance(size_t i, size_t j) { return fabs((float)(Density[i] - Density[j])); }
float TVoxelsData::GetDistance(const cv::Point3_<size_t> &p1, const cv::Point3_<size_t> &p2)
{
	return fabs((float)(GetDensity(p1.x, p1.y, p1.z)-GetDensity(p2.x, p2.y, p2.z)));
}

void TVoxelsData::CalcDensityVariance()
{
	cv::Mat mat(TotalSize, 1, CV_16S, Density);
	cv::Mat tmp; multiply(mat, mat, tmp);
	double ff = mean(mat)[0], fff = mean(tmp)[0];
	DensityVariance = (float)(fff-ff*ff);
}

void TVoxelsData::CalcXYVariance()
{
	float mean_x = (sizeX-1)/2.0f, mean_y = (sizeY-1)/2.0f;
	float sqr_x = (sizeX-1)*(2*sizeX-1)/6.0f, sqr_y = (sizeY-1)*(2*sizeY-1)/6.0f;
	XVariance = sqr_x - mean_x*mean_x, YVariance = sqr_y - mean_y*mean_y;
}

int TVoxelsData::FindConnectedRegions(size_t LayerIndex, int SegmentIndex, int SegmentType)
{
	int Label = -1;

	for (size_t j = 0; j < sizeY; ++j)
		for (size_t i = 0; i < sizeX; ++i)
			if (VoxelSegments[ReducedIndex(i, j, LayerIndex)].SegmentIndex_2D == SegmentIndex)
			{
				if (i && (VoxelSegments[ReducedIndex(i-1, j, LayerIndex)].ComponentIndex_2D >= 0))
				{
					VoxelSegments[ReducedIndex(i, j, LayerIndex)].ComponentIndex_2D = 
						VoxelSegments[ReducedIndex(i-1, j, LayerIndex)].ComponentIndex_2D;
				}

				else
					if (j && (VoxelSegments[ReducedIndex(i, j-1, LayerIndex)].ComponentIndex_2D >= 0))
				{
					VoxelSegments[ReducedIndex(i, j, LayerIndex)].ComponentIndex_2D = 
						VoxelSegments[ReducedIndex(i, j-1, LayerIndex)].ComponentIndex_2D;
				}

					else 
						if (i && j)
				{
					if (VoxelSegments[ReducedIndex(i-1, j-1, LayerIndex)].ComponentIndex_2D >= 0)
					VoxelSegments[ReducedIndex(i, j, LayerIndex)].ComponentIndex_2D = 
						VoxelSegments[ReducedIndex(i-1, j-1, LayerIndex)].ComponentIndex_2D;
					else
						if (VoxelSegments[ReducedIndex(i-1, j+1, LayerIndex)].ComponentIndex_2D >= 0)
					VoxelSegments[ReducedIndex(i, j, LayerIndex)].ComponentIndex_2D = 
						VoxelSegments[ReducedIndex(i-1, j+1, LayerIndex)].ComponentIndex_2D;
				}
						else
				{
					VoxelSegments[ReducedIndex(i, j, LayerIndex)].ComponentIndex_2D = (++Label);
				}
			}
	return Label+1; 
}

#pragma endregion

#pragma region TSegment methods

double TSegment::DistanceTo(const TSegment &segment, const bool* flags)
{
	cv::Mat l(7, 1, CV_32FC1), r(7, 1, CV_32FC1);

	l.at<float>(0, 0) = flags[6] ? Volume : 0; 
	l.at<float>(1, 0) = flags[3] ? MeanX : 0; l.at<float>(2, 0) = flags[3] ? MeanY : 0; 
	l.at<float>(3, 0) = flags[4] ? DevX : 0; l.at<float>(4, 0) = flags[5] ? DevY : 0; 
	l.at<float>(5, 0) = flags[1] ? MeanDensity : 0; l.at<float>(6, 0) = flags[2] ? DensityDev : 0;

	r.at<float>(0, 0) = flags[6] ? Volume : 0; 
	r.at<float>(1, 0) = flags[3] ? MeanX : 0; r.at<float>(2, 0) = flags[3] ? MeanY : 0; 
	r.at<float>(3, 0) = flags[4] ? DevX : 0; r.at<float>(4, 0) = flags[5] ? DevY : 0; 
	r.at<float>(5, 0) = flags[1] ? MeanDensity : 0; r.at<float>(6, 0) = flags[2] ? DensityDev : 0;
	
	return cv::norm(l, r);
}

bool TSegment::IsAdjacentWith(const TSegment &segment)
{
	return min(MaxDensity, segment.MaxDensity) >= max(MinDensity, segment.MinDensity);
}

#pragma endregion

#pragma region TSegmentComponent methods

TSegmentComponent::TSegmentComponent(TVoxelsData *Data, size_t LayerIndex, int SegmentIndex, int ComponentIndex)
{
	cv::Mat mat(Data->sizeY, Data->sizeX, CV_8UC1);
	for (size_t i = 0; i < Data->sizeY; ++i)
		for (size_t j = 0; j < Data->sizeX; ++j)
		{
			const TVoxelSegments voxel_segments = Data->VoxelSegments[Data->ReducedIndex(j, i, LayerIndex)];
			mat.at<uchar>(i, j) = 255*((voxel_segments.SegmentIndex_2D == SegmentIndex)&&(voxel_segments.ComponentIndex_2D == ComponentIndex));
		}
	cv::findContours(mat, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
}

#pragma endregion
