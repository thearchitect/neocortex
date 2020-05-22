#pragma once

#include "Structures.h"

enum SEGMENT_TYPE {DENSITY, SPATIAL, CONNECTED};

System::String^ GetStringOfColor(TColor Color);																				// получить строковое представление цвета

float GetMeanDensity(TVoxelsData* Data, std::vector <size_t> Segment);
cv::Point2f GetMeanCoords_2D(TVoxelsData* Data, std::vector <size_t> Segment);
cv::Point3f GetMeanCoords_3D(TVoxelsData* Data, std::vector <size_t> Segment);
cv::Point3f GetMeanDensityCoords_2D(TVoxelsData* Data, std::vector <size_t> Segment);
cv::Vec4f GetMeanDensityCoords_3D(TVoxelsData* Data, std::vector <size_t> Segment);

cv::Point_<short> MinMaxDensityOfSegment_2D(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int SegmentType);		// минимальное и максимальное значения плотности 2D-сегмента
cv::Point_<short> MinMaxDensityOfSegment_3D(TVoxelsData* Data, size_t StartLayerIndex, int SegmentIndex, int SegmentType);	// минимальное и максимальное значения плотности 3D-сегмента
cv::Point2f DensityMeanDevOfSegment_2D(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int SegmentType);			// мат. ожидание и дисперсия плотности вокселов в 2D-сегменте
cv::Vec4f MeanDevXYOfSegment_2D(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int SegmentType);					// мат. ожидание и дисперсия координат вокселов в 2D-сегменте

void SegmentsSort(const TVoxelsData* Data, std::vector <TSegment>& Segments, size_t LayerIndex, int left, int right);		// сортировка сегментов по возрастанию диапазонов значений плотности
