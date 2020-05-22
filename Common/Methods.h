#pragma once

#include "Structures.h"

enum SEGMENT_TYPE {DENSITY, SPATIAL, CONNECTED};

System::String^ GetStringOfColor(TColor Color);																				// �������� ��������� ������������� �����

float GetMeanDensity(TVoxelsData* Data, std::vector <size_t> Segment);
cv::Point2f GetMeanCoords_2D(TVoxelsData* Data, std::vector <size_t> Segment);
cv::Point3f GetMeanCoords_3D(TVoxelsData* Data, std::vector <size_t> Segment);
cv::Point3f GetMeanDensityCoords_2D(TVoxelsData* Data, std::vector <size_t> Segment);
cv::Vec4f GetMeanDensityCoords_3D(TVoxelsData* Data, std::vector <size_t> Segment);

cv::Point_<short> MinMaxDensityOfSegment_2D(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int SegmentType);		// ����������� � ������������ �������� ��������� 2D-��������
cv::Point_<short> MinMaxDensityOfSegment_3D(TVoxelsData* Data, size_t StartLayerIndex, int SegmentIndex, int SegmentType);	// ����������� � ������������ �������� ��������� 3D-��������
cv::Point2f DensityMeanDevOfSegment_2D(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int SegmentType);			// ���. �������� � ��������� ��������� �������� � 2D-��������
cv::Vec4f MeanDevXYOfSegment_2D(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int SegmentType);					// ���. �������� � ��������� ��������� �������� � 2D-��������

void SegmentsSort(const TVoxelsData* Data, std::vector <TSegment>& Segments, size_t LayerIndex, int left, int right);		// ���������� ��������� �� ����������� ���������� �������� ���������
