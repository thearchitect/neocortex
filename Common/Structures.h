#pragma once

#include <vector>
#include "opencv/cv.h"

#define IsVolumeUsing true
#define IsMeanXYUsing true
#define IsDevXYUsing true
#define IsMeanDensityUsing true
#define IsDevDensityUsing true

struct TLayer  // слой данных (двумерное изображение)
{ 
 short *Density;
 size_t sizeX, sizeY;  // ширина и высота слоя
 float scaleX, scaleY; // размеры слоя по осям

 // Конструкторы
 TLayer() : Density(0), sizeX(0), sizeY(0), scaleX(0), scaleY(0) {};
 TLayer(short*_density, size_t _sizeX, size_t _sizeY, float _scaleX, float _scaleY): 
 Density(_density), sizeX(_sizeX), sizeY(_sizeY), scaleX(_scaleX), scaleY(_scaleY) {};

 size_t ReducedIndex(size_t x, size_t y);	// приведённый индекс воксела в наборе данных

 // Методы доступа к данным в наборе
 short GetDensity(size_t index);
 short GetDensity(size_t x, size_t y);

 // методы, вычисляющие абсолютную разницу между вокселами
 float GetDistance(const cv::Point_<size_t> &p1, const cv::Point_<size_t> &p2);
 float GetDistance(size_t i, size_t j);
};

struct TVoxelSegments					
{
 int SegmentIndex_2D, SegmentIndex_3D;					// индексы сегментов, которым принадлежит воксел
 int SpatialSegmentIndex_2D, SpatialSegmentIndex_3D;	// индексы пространственных кластеров, которым принадлежит воксел
 int ComponentIndex_2D;									// индекс компоненты связности, входящей в сегмент, которому принадлежит воксел

 // Конструктор по умолчанию
 TVoxelSegments(): SegmentIndex_2D(-1), SegmentIndex_3D(-1), 
				   SpatialSegmentIndex_2D(-1), SpatialSegmentIndex_3D(-1),
				   ComponentIndex_2D(-1) {}
};

struct TColor 
{
 float R, G, B, A;						// параметры цвета
 TColor():R(0), G(0), B(0), A(0) {};
 TColor(float value_R, float value_G, float value_B, float value_A): 
        R(value_R), G(value_G), B(value_B), A(value_A) {};
 TColor(float value_R, float value_G, float value_B): R(value_R), G(value_G), B(value_B) {};
};

struct TPath						// путь (цепочка) из сегментов
{
 size_t root;						// корень цепочки
 std::vector <size_t> forward;		// передний фрагмент цепочки
 std::vector <size_t> backward;		// задний фрагмент цепочки

 // Конструктор по умолчанию
 TPath():root(0) { forward.clear(); backward.clear(); }
};

class TVoxelsData 
{
 public:
		short *Density;					// плотность вокселов
		bool *IsVoxelUsed;				// маска используемых вокселов
		TVoxelSegments *VoxelSegments;	// сегменты, которым принадлежат вокселы
		
		size_t sizeX, sizeY, sizeZ;		// размеры вдоль координатных осей
		float scaleX, scaleY, scaleZ;	// масштабы вдоль координатных осей

		size_t TotalSize;				// размер всего набора вокселов

		short MinDensity, MaxDensity;	// минимальное и максимальное значение плотности

		float DensityVariance;			// дисперсия плотности
		float XVariance, YVariance;		// дисперсии по координатам

		// Конструкторы и деструктор
		TVoxelsData();
		TVoxelsData(const char *pathToBinFile);
		TVoxelsData(const TLayer &layer);
		~TVoxelsData();

		void Init();	// инициализация всех полей значениями по умолчанию
		void Clear();	// освобождение всех ресурсов, занятых данными

		// Методы загрузки данных из файла
		bool Load(const char *pathToBinFile);
		bool Load(const char *pathToBinFile, size_t z_start, size_t nLayers);

		// Методы получения подмножества исходных данных 
		TVoxelsData* GetSubData(size_t z_first, size_t z_last);
		TLayer GetLayer(size_t z); 
		
		size_t ReducedIndex(size_t x, size_t y, size_t z);	// приведённый индекс воксела в наборе данных

		// Методы доступа к данным в наборе
		short GetDensity(size_t index);
		short GetDensity(size_t x, size_t y, size_t z);
		
		// Методы, вычисляющие абсолютную разницу между вокселами
		float GetDistance(const cv::Point3_<size_t> &p1, const cv::Point3_<size_t> &p2);
		float GetDistance(size_t i, size_t j);

		// Методы, вычисляющие дисперсию плотности и координат вокселов
		void CalcDensityVariance();
		void CalcXYVariance();

		// Поиск связных областей
		int FindConnectedRegions(size_t LayerIndex, int SegmentIndex, int SegmentType);
};

struct TSegment					// сегмент из вокселов
{
 short MinDensity;				// минимальное значение плотности 
 short MaxDensity;				// максимальное значение плотности

 short* Histogram;				// гистограмма значений плотности
 
 TColor Color;					// цвет сегмента
 bool Visible;					// атрибут видимости вокселов, входящих в сегмент

 TColor tmpColor;				// импортированный цвет сегмента
 bool tmpVisible;				// импортированный атрибут видимости

 float MeanX, MeanY;			// геометрический центр сегмента
 float DevX, DevY;				// среднеквадратическое отклонение вдоль координатных осей
 float MeanDensity;				// среднее значение плотности
 float DensityDev;				// разброс вокселов сегмента по плотности
 float Volume;					// объём сегмента (с учётом размеров воксела вдоль осей)

 std::vector <TSegment>* NextLevelSegments;	// сегменты следующего уровня иерархии
 
 // Конструктор сегмента по умолчанию
 TSegment(): MinDensity(0), MaxDensity(0), Histogram(0), NextLevelSegments(0),
	         Color(TColor(0.0f, 0.0f, 0.0f, 0.0f)), Visible(false), 
			 tmpColor(TColor(0.0f, 0.0f, 0.0f, 0.0f)), tmpVisible(false) {}

 double DistanceTo(const TSegment &segment, const bool* flags = NULL);

 bool IsAdjacentWith(const TSegment &segment);
};

struct TSegmentParent			// атрибуты корневого сегмента в цепочке соответствий
{
	size_t LayerRoot;			// индекс слоя
	size_t SegmentRoot;			// индекс сегмента

	// Конструкторы
	TSegmentParent() : LayerRoot(0), SegmentRoot(0) {}
	TSegmentParent(size_t layer_index, size_t segment_index) : LayerRoot(layer_index), SegmentRoot(segment_index) {}
};

struct TSegmentComponent	// компонента связности сегментов
{
private:
	std::vector <std::vector <cv::Point_<size_t> > > contours;	// контуры
	std::vector <cv::Vec4i> hierarchy;							// иерархия
public:
	TSegmentComponent(TVoxelsData* Data, size_t LayerIndex, int SegmentIndex, int ComponentIndex);
};

typedef std::vector <TSegmentComponent> TSegmentGraph;		// графовая модель представления сегмента


