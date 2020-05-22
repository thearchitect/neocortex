#include "Structures.h"

void MatMorphologyDilation(TVoxelsData* Data, size_t z,  int segment_index_2d, cv::Mat structure_element, int iterations = 1);
void MatMorphologyErosion(TVoxelsData* Data, size_t z, int segment_index_2d, cv::Mat structure_element, int iterations = 1);
void MatMorphologyOpening(TVoxelsData* Data, size_t z, int segment_index_2d, cv::Mat structure_element, int iterations = 1);
void MatMorphologyClosing(TVoxelsData* Data, size_t z, int segment_index_2d, cv::Mat structure_element, int iterations = 1);
