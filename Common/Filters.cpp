#include "Filters.h"

using namespace cv;

void MatMorphologyErosion(TVoxelsData* Data, size_t z, int segment_index_2d, cv::Mat structure_element, int iterations)
{
	Mat mat(Data->sizeX, Data->sizeX, CV_8UC1);

	for (size_t i = 0; i < Data->sizeX; ++i)
		for (size_t j = 0; j < Data->sizeY; ++j)
			mat.at<uchar>(j, i) = 255*(Data->VoxelSegments[Data->ReducedIndex(i, j, z)].SegmentIndex_2D == segment_index_2d); 
		
	erode(mat, mat, structure_element, cv::Point(-1, -1), iterations);
	
	for (size_t i = 0; i < Data->sizeX; ++i)
		for (size_t j = 0; j < Data->sizeY; ++j)
		 if ((Data->VoxelSegments[Data->ReducedIndex(i, j, z)].SegmentIndex_2D == segment_index_2d))
			Data->VoxelSegments[Data->ReducedIndex(i, j, z)].SegmentIndex_2D = (mat.at<uchar>(j, i) * segment_index_2d - (255-mat.at<uchar>(j, i)))/255;
} 