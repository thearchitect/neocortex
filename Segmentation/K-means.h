#include <vector>
#include <CL/opencl.h>
#include "Structures.h"

using namespace System::ComponentModel;

#define MinGroupSize 1
#define MaxGroupSize 330

template <typename T> class KMeansMethod
{
protected:
	size_t DataSize;
	size_t NClusters;
	size_t IterationsCount;

	TVoxelsData* InputData;
	std::vector <size_t>* Clusters;
	T* means;

	float time;

	virtual T GetMean(size_t i) { return (T)0; }
	virtual T EmptyClusterValue() { return (T)(-1); }
	virtual bool IsClusterNotEmpty(size_t i) { return false; }
	virtual float GetVoxelDistance(size_t j, size_t k) { return 0.0f; }

	void Init()
	{
		InputData = NULL;
		means = NULL;
		Clusters = NULL;

		NClusters = 0;
		DataSize = 0;
		time = 0.0f;
	}

	void Clear()
	{
		Init();
		delete [] means;
		delete [] Clusters;
	}

public:
	KMeansMethod() { Init(); }

	KMeansMethod(TVoxelsData* DataValue)
	{
	 Clear(); 	
     InputData = DataValue;
     DataSize = InputData->sizeX*InputData->sizeY*InputData->sizeZ;
	}

	KMeansMethod(TLayer layer)
	{
	 Clear();
	 InputData = new TVoxelsData(layer);
	 DataSize = layer.sizeX*layer.sizeY;
	}

	~KMeansMethod() { Clear(); }	
	
	float GetExecutionTime() { return time; }

	void SetClustersNumber(size_t value) { NClusters = value; }
	void SetIterationsCount(size_t value) { IterationsCount = value; }

	virtual std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker) 
	{
	 means = new T [NClusters];
	 
	 Clusters = new vector <size_t> [NClusters];
	 
	 size_t part = DataSize/NClusters;

	 for (size_t i = 0; i < NClusters; ++i)
	 {
	  for (size_t j = part*i; j < max(DataSize*(i/(NClusters-1)), part*(i+1)); ++j)
	  Clusters[i].push_back(j);
	 }

	 clock_t timeStart = clock();

	 for (size_t iter = 1; iter <= IterationsCount; ++iter)
	 {
	  for (size_t i = 0; i < NClusters; ++i) 
	  if (Clusters[i].size()>0) 
	  {
	   means[i] = GetMean(i); 
	   Clusters[i].clear();
	  }
	  else means[i] = EmptyClusterValue();

	  for (size_t j = 0; j < DataSize; ++j)
	  {
	   size_t optimal_cluster_id = 0;

	   float min_dist = (float)UINT_MAX;

	   for (size_t k = 0; k < NClusters; ++k) if (IsClusterNotEmpty(k))
	   {
		float new_dist = GetVoxelDistance(j, k);
		if (new_dist < min_dist)
		{
		 optimal_cluster_id = k;
		 min_dist = new_dist;
		}
	   }

	   Clusters[optimal_cluster_id].push_back(j);
	  } 

	  worker->ReportProgress(100*iter/IterationsCount);
	 }
	 
	 clock_t timeFinish = clock();
	 
	 time = (timeFinish-timeStart)/(1.0f*CLOCKS_PER_SEC);

	 vector <vector <size_t> > result;
	 result.clear();
	 for (size_t i = 0; i < NClusters; ++i)
	 if (Clusters[i].size()>0) result.push_back(Clusters[i]);

	 return result;
	}
};

class KMeansDensityMethod : public KMeansMethod <float> 
{
public:
	KMeansDensityMethod(TVoxelsData* DataValue);
	KMeansDensityMethod(TLayer layer);
	KMeansDensityMethod();
	float GetMean(size_t i);
	float EmptyClusterValue();
	bool IsClusterNotEmpty(size_t i);
	virtual float GetVoxelDistance(size_t j, size_t k);
};

class KMeansSpatialMethod : public KMeansMethod <cv::Point2f>
{
public:
	KMeansSpatialMethod(TVoxelsData* DataValue);
	KMeansSpatialMethod(TLayer layer);
	KMeansSpatialMethod();
	cv::Point2f GetMean(size_t i);
	cv::Point2f EmptyClusterValue();
	bool IsClusterNotEmpty(size_t i);
	float GetVoxelDistance(size_t j, size_t k);
};

class KMeansDensitySpatialMethod : public KMeansMethod <cv::Point3f>
{
public:
	KMeansDensitySpatialMethod(TVoxelsData* DataValue);
	KMeansDensitySpatialMethod(TLayer layer);
	KMeansDensitySpatialMethod();
	cv::Point3f GetMean(size_t i);
	cv::Point3f EmptyClusterValue();
	bool IsClusterNotEmpty(size_t i);
	float GetVoxelDistance(size_t j, size_t k);
};

template <typename T> class KMeansConditionalMethod : public KMeansMethod <T>
{
protected:
		short MinDensityRange, MaxDensityRange;			// границы диапазона
		std::vector <size_t> VoxelsInRange;				// вектор индексов вокселов с плотностью из диапазона

public:
		//  онструкторы
		KMeansConditionalMethod():KMeansMethod <T>() {}

		KMeansConditionalMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder): 
						            KMeansMethod <T> (DataValue)
		{
		 SetRangesOfDensity(LowBorder, HighBorder);
		}
		
		KMeansConditionalMethod(TLayer layer, short LowBorder, short HighBorder):
		KMeansMethod <T> (layer)
		{
		 SetRangesOfDensity(LowBorder, HighBorder);
		}
	    
		void SetRangesOfDensity(short left, short right)	// установить диапазон значений плотности
		{
			MinDensityRange = left;
			MaxDensityRange = right;
		}

		// ”словна€ кластеризаци€ методом k-средних 
		virtual std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker) 
		{
			VoxelsInRange.clear();

			for (size_t i = 0; i < DataSize; ++i)
				if ((InputData->Density[i]>=MinDensityRange)&&
					(InputData->Density[i]<=MaxDensityRange))
					VoxelsInRange.push_back(i);

			size_t ConditionalDataSize = VoxelsInRange.size();

			size_t part = ConditionalDataSize/NClusters;

			means = new T [NClusters];

			Clusters = new vector <size_t> [NClusters];

			for (size_t i = 0; i < NClusters; ++i)
			{
				for (size_t j = part*i; j < max(ConditionalDataSize*(i/(NClusters-1)), part*(i+1)); ++j)
					Clusters[i].push_back(VoxelsInRange.at(j));
			}

			clock_t timeStart = clock();

			for (size_t iter = 1; iter <= IterationsCount; ++iter)
			{
				for (size_t i = 0; i < NClusters; ++i)
					if (Clusters[i].size()>0) 
					{
						means[i] = GetMean(i); 
						Clusters[i].clear();
					}
					else means[i] = EmptyClusterValue();

					for (size_t j = 0; j < ConditionalDataSize; ++j)
					{
						size_t optimal_cluster_id = 0;

						float min_dist = (float)UINT_MAX;

						for (size_t k = 0; k < NClusters; ++k) if (IsClusterNotEmpty(k)) 
						{
							float new_dist = GetVoxelDistance(j, k);
							if (new_dist < min_dist)
							{
								optimal_cluster_id = k; 
								min_dist = new_dist;
							}
						}

						Clusters[optimal_cluster_id].push_back(VoxelsInRange.at(j));
					}

					worker->ReportProgress(100*iter/IterationsCount);
			}

			clock_t timeFinish = clock();

			time = (timeFinish-timeStart)/(1.0f*CLOCKS_PER_SEC);

			vector <vector <size_t> > result; result.clear();
			for (size_t i = 0; i < NClusters; ++i) 
				if (Clusters[i].size()>0) result.push_back(Clusters[i]);

			return result;
		}
};

class KMeansConditionalDensityMethod : public KMeansConditionalMethod <float>
{
public:
	KMeansConditionalDensityMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder);
	KMeansConditionalDensityMethod(TLayer layer, short LowBorder, short HighBorder);
	KMeansConditionalDensityMethod();
	float GetMean(size_t i);
	float EmptyClusterValue();
	bool IsClusterNotEmpty(size_t i);
	float GetVoxelDistance(size_t j, size_t k);
};

class KMeansConditionalSpatialMethod : public KMeansConditionalMethod <cv::Point2f>
{
public:
	KMeansConditionalSpatialMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder);
	KMeansConditionalSpatialMethod(TLayer layer, short LowBorder, short HighBorder);
	KMeansConditionalSpatialMethod();
	cv::Point2f GetMean(size_t i);
	cv::Point2f EmptyClusterValue();
	bool IsClusterNotEmpty(size_t i);
	float GetVoxelDistance(size_t j, size_t k);
};

class KMeansConditionalDensitySpatialMethod : public KMeansConditionalMethod <cv::Point3f>
{
public:
	KMeansConditionalDensitySpatialMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder);
	KMeansConditionalDensitySpatialMethod(TLayer layer, short LowBorder, short HighBorder);
	KMeansConditionalDensitySpatialMethod();
	cv::Point3f GetMean(size_t i);
	cv::Point3f EmptyClusterValue();
	bool IsClusterNotEmpty(size_t i);
	float GetVoxelDistance(size_t j, size_t k);
};

template <typename T> class KMeansMaskMethod : public KMeansMethod <T>
{
protected:
	std::vector <size_t> VoxelsInMask;

public:
	KMeansMaskMethod(TVoxelsData* DataValue) : KMeansMethod <T> (DataValue) {}
	KMeansMaskMethod(TLayer layer) : KMeansMethod <T> (layer) {}
	KMeansMaskMethod() : KMeansMethod <T> () {}
	virtual std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker) 
	{
		VoxelsInMask.clear();

		for (size_t i = 0; i < DataSize; ++i)
			if (InputData->IsVoxelUsed[i]) VoxelsInMask.push_back(i);

		size_t MaskDataSize = VoxelsInMask.size();

		size_t part = MaskDataSize/NClusters;

		means = new T [NClusters];

		Clusters = new vector <size_t> [NClusters];

		for (size_t i = 0; i < NClusters; ++i)
		{
			for (size_t j = part*i; j < max(MaskDataSize*(i/(NClusters-1)), part*(i+1)); ++j)
				Clusters[i].push_back(VoxelsInMask.at(j));
		}

		clock_t timeStart = clock();

		for (size_t iter = 1; iter <= IterationsCount; ++iter)
		{
			for (size_t i = 0; i < NClusters; ++i)
				if (Clusters[i].size()>0) 
				{
					means[i] = GetMean(i); 
					Clusters[i].clear();
				}
				else means[i] = EmptyClusterValue();

				for (size_t j = 0; j < MaskDataSize; ++j)
				{
					size_t optimal_cluster_id = 0;

					float min_dist = (float)UINT_MAX;

					for (size_t k = 0; k < NClusters; ++k) if (IsClusterNotEmpty(k)) 
					{
						float new_dist = GetVoxelDistance(j, k);
						if (new_dist < min_dist)
						{
							optimal_cluster_id = k; 
							min_dist = new_dist;
						}
					}

					Clusters[optimal_cluster_id].push_back(VoxelsInMask.at(j));
				}

				worker->ReportProgress(100*iter/IterationsCount);
		}

		clock_t timeFinish = clock();

		time = (timeFinish-timeStart)/(1.0f*CLOCKS_PER_SEC);

		vector <vector <size_t> > result; result.clear();
		for (size_t i = 0; i < NClusters; ++i) 
			if (Clusters[i].size()>0) result.push_back(Clusters[i]);

		return result;
	}
};

class KMeansMaskDensityMethod : public KMeansMaskMethod <float>
{
public:
	KMeansMaskDensityMethod(TVoxelsData* DataValue);
	KMeansMaskDensityMethod(TLayer layer);
	KMeansMaskDensityMethod();
	float GetMean(size_t i);
	float EmptyClusterValue();
	bool IsClusterNotEmpty(size_t i);
	float GetVoxelDistance(size_t j, size_t k);
};

class KMeansMaskSpatialMethod : public KMeansMaskMethod <cv::Point2f>
{
public:
	KMeansMaskSpatialMethod(TVoxelsData* DataValue);
	KMeansMaskSpatialMethod(TLayer layer);
	KMeansMaskSpatialMethod();
	cv::Point2f GetMean(size_t i);
	cv::Point2f EmptyClusterValue();
	bool IsClusterNotEmpty(size_t i);
	float GetVoxelDistance(size_t j, size_t k);
};

class KMeansMaskDensitySpatialMethod : public KMeansMaskMethod <cv::Point3f>
{
public:
	KMeansMaskDensitySpatialMethod(TVoxelsData* DataValue);
	KMeansMaskDensitySpatialMethod(TLayer layer);
	KMeansMaskDensitySpatialMethod();
	cv::Point3f GetMean(size_t i);
	cv::Point3f EmptyClusterValue();
	bool IsClusterNotEmpty(size_t i);
	float GetVoxelDistance(size_t j, size_t k);
};

template <typename T> class KMeansOpenCLMethod : public KMeansMethod <T>						// метод k-средних на GPU (OpenCL)
{
 protected: 
		   size_t* Labels;											// метки кластеров 
		   cl_device_id device;										// устройство исполнени€
		   cl_context context;										// контекст устройства
		   cl_command_queue queue;									// очередь команд

           void InitOpenCL()										// »нициализаци€ контекста OpenCL
			{
			 cl_uint numPlatforms = 0;

			 clGetPlatformIDs(0,            /* number of entries */
							  NULL,         /* платформы */
							  &numPlatforms /* число платформ */);

			 cl_platform_id platform = NULL;

			 if (numPlatforms > 0)
			 {
			  cl_platform_id * platforms = new cl_platform_id [numPlatforms];

			  clGetPlatformIDs(numPlatforms, 
							   platforms, 
							   NULL);

			  platform = platforms[0];

			  delete [] platforms;
			 }

			 // —оздаЄм свойства контекста дл€ заданной платформы 
			 cl_context_properties properties [3] = { CL_CONTEXT_PLATFORM, (cl_context_properties) platform, 0 };

			 context = clCreateContextFromType((NULL == platform) ? NULL : properties, 
												CL_DEVICE_TYPE_GPU, 
												NULL, 
												NULL, 
												NULL);

			 size_t Size = 0;

			 clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL, &Size);

			 device = NULL;

			 if (Size > 0)
			 {
			  cl_device_id * devices = ( cl_device_id * ) alloca ( Size );

			  clGetContextInfo (context				/* context */,
								CL_CONTEXT_DEVICES	/* param_name */,
								Size				/* param_value_size */,
								devices				/* param_value */,
								NULL				/* param_value__size_ret */ );

			  device = devices [0];
			 }

			 // —оздаем очередь команд дл€ заданного контекста и выбранного устройства
			 queue = clCreateCommandQueue (context  /* context */,
   										   device	/* device */,
										   0		/* properties */,
										   NULL		/* errcode_ret */ );
			}

		   void CalcWorkGroupSize(cl_kernel kernel, size_t &group)	// ¬ычисление размера рабочей группы
		   {
			 // ќпредел€ем размер рабочей группы автоматически
			 clGetKernelWorkGroupInfo(kernel, device, CL_KERNEL_WORK_GROUP_SIZE, sizeof ( size_t ), &group, NULL);

			 // ѕерва€ корректировка
			 while (group*(DataSize/group)<DataSize) group--;

			 // ¬тора€ корректировка
			 if (group < min<size_t>(MinGroupSize, DataSize)) do group++; 
			 while ((group*(DataSize/group)<DataSize)||(group < min<size_t>(MinGroupSize, DataSize)));

			 // “реть€ корректировка
			 else if (group > MaxGroupSize) do group--; 
			 while ((group*(DataSize/group)<DataSize)||(group>MaxGroupSize));
			}
 public:
		// онструкторы 
		KMeansOpenCLMethod() : KMeansMethod <T> () {}

		KMeansOpenCLMethod(TVoxelsData* DataValue) : KMeansMethod <T> (DataValue)
		{
		 Labels = NULL;
		 delete [] Labels; 
		}
		
		KMeansOpenCLMethod(TLayer layer) : KMeansMethod <T> (layer)
		{
		 Labels = NULL;
		 delete [] Labels; 
		}
	
		// ластеризаци€ методом k-средних с использованием OpenCL
		virtual std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker) { return std::vector <std::vector <size_t> >(0); } 
		
};

class KMeansOpenCLDensityMethod : public KMeansOpenCLMethod <float>
{
public:
	KMeansOpenCLDensityMethod(TVoxelsData* DataValue);
	KMeansOpenCLDensityMethod(TLayer layer);
	float GetMean(size_t i);
	std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);
};

class KMeansOpenCLSpatialMethod : public KMeansOpenCLMethod <cv::Point2f>
{
public:
	KMeansOpenCLSpatialMethod(TVoxelsData* DataValue);
	KMeansOpenCLSpatialMethod(TLayer layer);
	std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);
};

class KMeansOpenCLDensitySpatialMethod : public KMeansOpenCLMethod <cv::Point3f>
{
public:
	KMeansOpenCLDensitySpatialMethod(TVoxelsData* DataValue);
	KMeansOpenCLDensitySpatialMethod(TLayer layer);
	std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);
};

template <typename T> class KMeansConditionalOpenCLMethod: public KMeansOpenCLMethod <T>  // кластеризаци€ методом k-средних в заданном диапазоне на OpenCL
{
 protected: 
		 short MinDensityRange, MaxDensityRange;				 // границы диапазона
		 std::vector <size_t> VoxelsInRange;					 // вектор индексов вокселов с плотностью из диапазона 
	 
 public:
	    //  онструкторы
		KMeansConditionalOpenCLMethod() : KMeansOpenCLMethod <T> () {}

	    KMeansConditionalOpenCLMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder): 
										  KMeansOpenCLMethod <T> (DataValue)
		{
		 SetRangesOfDensity(LowBorder, HighBorder);
		}

	    KMeansConditionalOpenCLMethod(TLayer layer, short LowBorder, short HighBorder): 
										  KMeansOpenCLMethod(layer)
		{
		 SetRangesOfDensity(LowBorder, HighBorder);
		}

		void SetRangesOfDensity(short left, short right)	// установить диапазон значений плотности
		{
		 MinDensityRange = left;
		 MaxDensityRange = right;
		}		 

		// ”словна€ кластеризаци€ методом k-средних на OpenCL
		virtual std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker) { return std::vector <std::vector <size_t> >(0); }		
};

class KMeansConditionalOpenCLDensityMethod : public KMeansConditionalOpenCLMethod <float>
{
public:
	KMeansConditionalOpenCLDensityMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder);
	KMeansConditionalOpenCLDensityMethod(TLayer layer, short LowBorder, short HighBorder);
	float GetMean(size_t i);
	std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);
};

class KMeansConditionalOpenCLSpatialMethod : public KMeansConditionalOpenCLMethod <cv::Point2f>
{
public:
	KMeansConditionalOpenCLSpatialMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder);
	KMeansConditionalOpenCLSpatialMethod(TLayer layer, short LowBorder, short HighBorder);
	std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);
};

class KMeansConditionalOpenCLDensitySpatialMethod : public KMeansConditionalOpenCLMethod <cv::Point3f>
{
public:
	KMeansConditionalOpenCLDensitySpatialMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder);
	KMeansConditionalOpenCLDensitySpatialMethod(TLayer layer, short LowBorder, short HighBorder);
	std::vector <std::vector <size_t> > GetClusters(BackgroundWorker^ worker);
};

template <typename T> class KMeansMaskOpenCLMethod : public KMeansMaskMethod <T>
{
	
};

class KMeansMaskOpenCLDensityMethod : public KMeansMaskOpenCLMethod <float>
{

};

class KMeansMaskOpenCLSpatialMethod : public KMeansMaskOpenCLMethod <cv::Point2f>
{

};

class KMeansMaskOpenCLDensitySpatialMethod : public KMeansMaskOpenCLMethod <cv::Point3f>
{

};

