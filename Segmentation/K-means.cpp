#include <math.h>
#include <time.h>
#include <algorithm>
#include "Methods.h"
#include "K-means.h"

using namespace cv;
using namespace std;

#pragma region Kernels

const char * source_distribution = "__kernel void distribution ( __global short	* data,			 \n"\
																"__global float * means,		 \n"\
																"__global unsigned int * labels, \n"\
																"unsigned int VoxelsCount,		 \n"\
																"unsigned int ClustersCount )	 \n"\

"{																	 \n"\
 "unsigned int i = get_global_id (0);								 \n"\
 "if (i<VoxelsCount)												 \n"\
 "{																	 \n"\
  "unsigned int optimal_cluster_id = 0;								 \n"\
  "float min_dist = (float)INT_MAX;									 \n"\
  "for (unsigned int j = 0; j < ClustersCount; ++j) if (means[j]>=0) \n"\
  "{																 \n"\
   "float new_dist = fabs((float)data[i]-means[j]);					 \n"\
   "if (new_dist < min_dist)										 \n"\
   "{																 \n"\
    "optimal_cluster_id = j;										 \n"\
    "min_dist = new_dist;											 \n"\
   "}																 \n"\
  "}																 \n"\
  "labels[i] = optimal_cluster_id;									 \n"\
 "}																	 \n"\
"}"; 

const char * source_conditional_distribution = "__kernel void conditional_distribution	\n"\
											   "(__global short * data,					\n"\
											    "__global float * means,				\n"\
												"__global unsigned int * labels,		\n"\
												"short min_density,						\n"\
												"short max_density,						\n"\
												"unsigned int VoxelsCount,				\n"\
												"unsigned int ClustersCount)			\n"\

"{													\n"\
 "unsigned int i = get_global_id (0);				\n"\
 "if ((i<VoxelsCount)&&								\n"\
     "(data[i]>=min_density)&&						\n"\
	 "(data[i]<=max_density))						\n"\
 "{													\n"\
  "size_t optimal_cluster_id = 0;					\n"\
  "float min_dist = (float)INT_MAX;					\n"\
  "for (size_t j = 0; j < ClustersCount; ++j)		\n"\
  "{												\n"\
   "float new_dist = fabs((float)data[i]-means[j]); \n"\
   "if (new_dist < min_dist)						\n"\
   "{												\n"\
    "optimal_cluster_id = j;						\n"\
	"min_dist = new_dist;							\n"\
   "}												\n"\
  "}												\n"\
  "labels[i] = optimal_cluster_id;					\n"\
 "}													\n"\
"}";

#pragma endregion

#pragma region Класс KMeansDensityMethod 

KMeansDensityMethod::KMeansDensityMethod(TVoxelsData *Data) : KMeansMethod <float> (Data) {}
KMeansDensityMethod::KMeansDensityMethod(TLayer layer) : KMeansMethod <float> (layer) {}
KMeansDensityMethod::KMeansDensityMethod() : KMeansMethod <float> () {}

// Вычисление центра тяжести для i-ого кластера
float KMeansDensityMethod::GetMean(size_t i) { return GetMeanDensity(InputData, Clusters[i]); }

float KMeansDensityMethod::EmptyClusterValue() { return -1.0f; }

bool KMeansDensityMethod::IsClusterNotEmpty(size_t i) { return means[i] >= 0.0f; }

float KMeansDensityMethod::GetVoxelDistance(size_t j, size_t k)
{
	return fabs((float)InputData->Density[j] - means[k]);
}

#pragma endregion 

#pragma region Класс KMeansSpatialMethod

KMeansSpatialMethod::KMeansSpatialMethod(TVoxelsData *DataValue) : KMeansMethod <Point2f> (DataValue) {}
KMeansSpatialMethod::KMeansSpatialMethod(TLayer layer) : KMeansMethod <Point2f> (layer) {}
KMeansSpatialMethod::KMeansSpatialMethod() : KMeansMethod <Point2f> () {}

Point2f KMeansSpatialMethod::GetMean(size_t i) { return GetMeanCoords_2D(InputData, Clusters[i]); }

Point2f KMeansSpatialMethod::EmptyClusterValue() { return Point2f(-1.0f, -1.0f); }

bool KMeansSpatialMethod::IsClusterNotEmpty(size_t i) { return means[i].dot(-EmptyClusterValue()) >= 0.0f; }

float KMeansSpatialMethod::GetVoxelDistance(size_t j, size_t k)
{
	size_t x = j%InputData->sizeX, 
		   y = ((j-x)/InputData->sizeX)%InputData->sizeY;
	return (float)cv::norm(Vec2f((float)x, (float)y), Vec2f(means[k].x, means[k].y));
}

#pragma endregion

#pragma region Класс KMeansDensitySpatialMethod 

KMeansDensitySpatialMethod::KMeansDensitySpatialMethod(TVoxelsData *DataValue) : KMeansMethod <Point3f> (DataValue) 
{ 
	InputData->CalcDensityVariance(); 
	InputData->CalcXYVariance(); 
}

KMeansDensitySpatialMethod::KMeansDensitySpatialMethod(TLayer layer) : KMeansMethod <Point3f> (layer) 
{ 
	InputData->CalcDensityVariance(); 
	InputData->CalcXYVariance(); 
}

KMeansDensitySpatialMethod::KMeansDensitySpatialMethod() : KMeansMethod <Point3f> () {}

Point3f KMeansDensitySpatialMethod::GetMean(size_t i) { return GetMeanDensityCoords_2D(InputData, Clusters[i]); }

Point3f KMeansDensitySpatialMethod::EmptyClusterValue() { return Point3f(-1.0f, -1.0f, -1.0f); }

bool KMeansDensitySpatialMethod::IsClusterNotEmpty(size_t i) { return means[i].dot(-EmptyClusterValue()) >= 0.0f; }

float KMeansDensitySpatialMethod::GetVoxelDistance(size_t j, size_t k)
{
	size_t x = j%InputData->sizeX, 
		   y = ((j-x)/InputData->sizeX)%InputData->sizeY;
	cv::Mat point = (cv::Mat_<float>(3, 1) << (float)InputData->Density[j], (float)x, (float)y);
	cv::Mat center = (cv::Mat_<float>(3, 1) << means[k].x, means[k].y, means[k].z);
	cv::Mat Icovar = (cv::Mat_<float>(3, 3) << 1.0f/InputData->DensityVariance, 0.0f, 0.0f, 0.0f, 1.0f/InputData->XVariance, 0.0f, 0.0f, 0.0f, 1.0f/InputData->YVariance); 
	return (float)Mahalanobis(point, center, Icovar);
}

#pragma endregion

#pragma region Класс KMeansConditionalDensityMethod

KMeansConditionalDensityMethod::KMeansConditionalDensityMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder) :
KMeansConditionalMethod <float> (DataValue, LowBorder, HighBorder) {}

KMeansConditionalDensityMethod::KMeansConditionalDensityMethod(TLayer layer, short LowBorder, short HighBorder) :
KMeansConditionalMethod <float> (layer, LowBorder, HighBorder) {}

float KMeansConditionalDensityMethod::GetMean(size_t i) { return GetMeanDensity(InputData, Clusters[i]); }

float KMeansConditionalDensityMethod::EmptyClusterValue() { return -2.0f; }

bool KMeansConditionalDensityMethod::IsClusterNotEmpty(size_t i) { return means[i] >= -1.0f; }

float KMeansConditionalDensityMethod::GetVoxelDistance(size_t j, size_t k)
{
	return fabs((float)InputData->Density[VoxelsInRange.at(j)]-means[k]);
}

#pragma endregion

#pragma region Класс KMeansConditionalSpatialMethod

KMeansConditionalSpatialMethod::KMeansConditionalSpatialMethod(TVoxelsData* DataValue, short LowBorder, short HighBorder) :
KMeansConditionalMethod <Point2f> (DataValue, LowBorder, HighBorder) {}

KMeansConditionalSpatialMethod::KMeansConditionalSpatialMethod(TLayer layer, short LowBorder, short HighBorder) :
KMeansConditionalMethod <Point2f> (layer, LowBorder, HighBorder) {}

Point2f KMeansConditionalSpatialMethod::GetMean(size_t i) { return GetMeanCoords_2D(InputData, Clusters[i]); }

Point2f KMeansConditionalSpatialMethod::EmptyClusterValue() { return Point2f(-2.0f, -2.0f); }

bool KMeansConditionalSpatialMethod::IsClusterNotEmpty(size_t i) { return means[i].dot(-EmptyClusterValue()) >= -1.0f; }

float KMeansConditionalSpatialMethod::GetVoxelDistance(size_t j, size_t k)
{
	size_t x = VoxelsInRange[j]%InputData->sizeX, 
		   y = ((VoxelsInRange[j]-x)/InputData->sizeX)%InputData->sizeY;
	return (float)cv::norm(Vec2f((float)x, (float)y), Vec2f(means[k].x, means[k].y));
}

#pragma endregion

#pragma region Класс KMeansConditionalDensitySpatialMethod

KMeansConditionalDensitySpatialMethod::KMeansConditionalDensitySpatialMethod(TVoxelsData *DataValue, short LowBorder, short HighBorder) :
KMeansConditionalMethod <Point3f> (DataValue, LowBorder, HighBorder) 
{
	InputData->CalcDensityVariance();
	InputData->CalcXYVariance();
}

KMeansConditionalDensitySpatialMethod::KMeansConditionalDensitySpatialMethod(TLayer layer, short LowBorder, short HighBorder) :
KMeansConditionalMethod <Point3f> (layer, LowBorder, HighBorder)
{
	InputData->CalcDensityVariance();
	InputData->CalcXYVariance();
}

Point3f KMeansConditionalDensitySpatialMethod::GetMean(size_t i) { return GetMeanDensityCoords_2D(InputData, Clusters[i]); }

Point3f KMeansConditionalDensitySpatialMethod::EmptyClusterValue() { return Point3f(-2.0f, -2.0f, -2.0f); }

bool KMeansConditionalDensitySpatialMethod::IsClusterNotEmpty(size_t i) { return means[i].dot(-EmptyClusterValue()) >= -1.0f; }

float KMeansConditionalDensitySpatialMethod::GetVoxelDistance(size_t j, size_t k)
{
	size_t x = VoxelsInRange[j]%InputData->sizeX, 
		   y = ((VoxelsInRange[j]-x)/InputData->sizeX)%InputData->sizeY;
	cv::Mat point = (cv::Mat_<float>(3, 1) << (float)InputData->Density[VoxelsInRange.at(j)], (float)x, (float)y);
	cv::Mat center = (cv::Mat_<float>(3, 1) << means[k].x, means[k].y, means[k].z);
	cv::Mat Icovar = (cv::Mat_<float>(3, 3) << 1.0f/InputData->DensityVariance, 0.0f, 0.0f, 0.0f, 1.0f/InputData->XVariance, 0.0f, 0.0f, 0.0f, 1.0f/InputData->YVariance); 
	return (float)Mahalanobis(point, center, Icovar);
}

#pragma endregion

#pragma region Класс KMeansMaskDensityMethod

KMeansMaskDensityMethod::KMeansMaskDensityMethod(TVoxelsData *DataValue) : KMeansMaskMethod <float> (DataValue) {}
KMeansMaskDensityMethod::KMeansMaskDensityMethod(TLayer layer) : KMeansMaskMethod <float> (layer) {}

float KMeansMaskDensityMethod::GetMean(size_t i) { return GetMeanDensity(InputData, Clusters[i]); }

float KMeansMaskDensityMethod::EmptyClusterValue() { return -3.0f; }

bool KMeansMaskDensityMethod::IsClusterNotEmpty(size_t i) { return means[i] >= -2.0f; }

float KMeansMaskDensityMethod::GetVoxelDistance(size_t j, size_t k)
{
	return fabs((float)InputData->Density[VoxelsInMask.at(j)]-means[k]);
}

#pragma endregion

#pragma region Класс KMeansMaskSpatialMethod

KMeansMaskSpatialMethod::KMeansMaskSpatialMethod(TVoxelsData *DataValue) : KMeansMaskMethod <Point2f> (DataValue) {}
KMeansMaskSpatialMethod::KMeansMaskSpatialMethod(TLayer layer) : KMeansMaskMethod <Point2f> (layer) {}

Point2f KMeansMaskSpatialMethod::GetMean(size_t i) { return GetMeanCoords_2D(InputData, Clusters[i]); }

Point2f KMeansMaskSpatialMethod::EmptyClusterValue() { return Point2f(-3.0f, -3.0f); }

bool KMeansMaskSpatialMethod::IsClusterNotEmpty(size_t i) {	return means[i].dot(-EmptyClusterValue()) >= -2.0f; }

float KMeansMaskSpatialMethod::GetVoxelDistance(size_t j, size_t k) 
{
	size_t x = VoxelsInMask[j]%InputData->sizeX, 
		   y = ((VoxelsInMask[j]-x)/InputData->sizeX)%InputData->sizeY;
	return (float)cv::norm(Vec2f((float)x, (float)y), Vec2f(means[k].x, means[k].y));
}

#pragma endregion

#pragma region Класс KMeansMaskDensitySpatialMethod

KMeansMaskDensitySpatialMethod::KMeansMaskDensitySpatialMethod(TVoxelsData *DataValue) : KMeansMaskMethod <Point3f> (DataValue) 
{
	InputData->CalcDensityVariance();
	InputData->CalcXYVariance();
}
KMeansMaskDensitySpatialMethod::KMeansMaskDensitySpatialMethod(TLayer layer) : KMeansMaskMethod <Point3f> (layer)
{
	InputData->CalcDensityVariance();
	InputData->CalcXYVariance();
}

Point3f KMeansMaskDensitySpatialMethod::GetMean(size_t i) { return GetMeanDensityCoords_2D(InputData, Clusters[i]); }

Point3f KMeansMaskDensitySpatialMethod::EmptyClusterValue() { return Point3f(-3.0f, -3.0f, -3.0f); }

bool KMeansMaskDensitySpatialMethod::IsClusterNotEmpty(size_t i) { return means[i].dot(-EmptyClusterValue()) >= -2.0f; }

float KMeansMaskDensitySpatialMethod::GetVoxelDistance(size_t j, size_t k)
{
	size_t x = VoxelsInMask[j]%InputData->sizeX, 
		   y = ((VoxelsInMask[j]-x)/InputData->sizeX)%InputData->sizeY;
	cv::Mat point = (cv::Mat_<float>(3, 1) << (float)InputData->Density[VoxelsInMask.at(j)], (float)x, (float)y);
	cv::Mat center = (cv::Mat_<float>(3, 1) << means[k].x, means[k].y, means[k].z);
	cv::Mat Icovar = (cv::Mat_<float>(3, 3) << 1.0f/InputData->DensityVariance, 0.0f, 0.0f, 0.0f, 1.0f/InputData->XVariance, 0.0f, 0.0f, 0.0f, 1.0f/InputData->YVariance); 
	return (float)Mahalanobis(point, center, Icovar);
}

#pragma endregion

#pragma region Класс KMeansOpenCLDensityMethod

KMeansOpenCLDensityMethod::KMeansOpenCLDensityMethod(TVoxelsData *DataValue) : KMeansOpenCLMethod <float> (DataValue) {}
KMeansOpenCLDensityMethod::KMeansOpenCLDensityMethod(TLayer layer) : KMeansOpenCLMethod <float> (layer) {}

float KMeansOpenCLDensityMethod::GetMean(size_t i) { return GetMeanDensity(InputData, Clusters[i]); }

vector <vector <size_t> > KMeansOpenCLDensityMethod::GetClusters(BackgroundWorker^ worker)
{
	InitOpenCL();

	// Создаем программный объект из исходного кода (определен выше)
	size_t srclen [] = { strlen ( source_distribution ) };

	cl_program program = clCreateProgramWithSource (context						/* context */,
		1								/* count */	 ,
		&source_distribution			/* strings */,
		srclen							/* lengths */,
		NULL							/* errcode_ret */ );

	// Создаем исполняемый файл программы для выбранного устройства (GPU)
	clBuildProgram (program /* program */,
		1		 /* num_devices */,
		&device /* device_list */,
		NULL	 /* options */,
		NULL    /* pfn_notify */,
		NULL    /* user_data */ );


	// Создаем объект ядра для перераспределения вокселов между кластерами
	cl_kernel kernel = clCreateKernel ( program		/* program */,
		"distribution"	/* kernel_name */,
		NULL			/* errcode_ret */ );

	// Создаем объект памяти в виде буфера для передачи ядру входного массива
	cl_mem input_data = clCreateBuffer (context					  /* context */,
		CL_MEM_READ_ONLY		      /* flags */,
		sizeof (short) * DataSize	  /* size */,
		NULL					      /* host_ptr */,
		NULL					      /* errcode_ret */ );

	cl_mem input_means = clCreateBuffer (context, 
		CL_MEM_READ_ONLY, 
		sizeof (float) * NClusters, 
		NULL, 
		NULL);	// буфер для передачи центров тяжести

	cl_mem output_labels = clCreateBuffer (context, 
		CL_MEM_WRITE_ONLY, 
		sizeof (unsigned int) * DataSize, 
		NULL, 
		NULL); // буфер для передачи меток кластеров

	// Задание аргументов ядра
	clSetKernelArg (kernel				/* kernel		*/,
		0					/* arg_index	*/,
		sizeof ( cl_mem )	/* arg_size		*/,
		&input_data		/* arg_value	*/ );

	clSetKernelArg (kernel				/* kernel		*/,
		1					/* arg_index	*/,
		sizeof ( cl_mem )	/* arg_size		*/,
		&input_means		/* arg_value	*/ );

	clSetKernelArg (kernel				/* kernel		*/,
		2					/* arg_index	*/,
		sizeof ( cl_mem )	/* arg_size		*/,
		&output_labels		/* arg_value	*/ );

	clSetKernelArg (kernel, 3, sizeof (unsigned int), &DataSize);

	clSetKernelArg (kernel, 4, sizeof (unsigned int), &NClusters);

	size_t group; // максимальный размер группы работ

	CalcWorkGroupSize(kernel, group);

	size_t part = DataSize/NClusters;

	means = new float [NClusters];

	Labels = new size_t [DataSize];

	Clusters = new vector <size_t> [NClusters];

	for (size_t i = 0; i < NClusters; ++i)
	{
		for (size_t j = part*i; j < max(DataSize*(i/(NClusters-1)), part*(i+1)); ++j)
			Clusters[i].push_back(j);
	}

	clock_t timeStart = clock();

	for (size_t iter = 1; iter <= IterationsCount; ++iter)
	{
		// Вычисление центров тяжести кластеров
		for (size_t i = 0; i < NClusters; ++i)
			if (Clusters[i].size()>0) 
			{
				means[i] = GetMean(i); 
				Clusters[i].clear();
			}  
			else means[i] = -1.0f;

			// Помещаем в очередь команду записи входного массива в объект памяти
			clEnqueueWriteBuffer (queue						/* command_queue */,
				input_data					/* buffer */,
				CL_TRUE						/* blocking_write */,
				0							/* offset */,
				sizeof ( short ) * DataSize	/* cb */,
				InputData->Density				/* ptr */,
				0							/* num_events_in_wait_list */,
				NULL						/* event_wait_list */,
				NULL						/* event */ );

			clEnqueueWriteBuffer (queue, input_means, CL_TRUE, 0, sizeof (float) * NClusters, means, 0, NULL, NULL);

			clEnqueueWriteBuffer (queue, output_labels, CL_TRUE, 0, sizeof (unsigned int) * DataSize, Labels, 0, NULL, NULL);

			// Выполнение ядра над всем множеством входных данных
			clEnqueueNDRangeKernel (queue		/* command_queue */,
				kernel	/* kernel */,
				1			/* work_dim */,
				NULL		/* global_work_offset */,
				&DataSize	/* global_work_size */,
				&group	/* local_work_size */,
				0			/* num_events_in_wait_list */,
				NULL		/* event_wait_list */,
				NULL		/* event */ );

			clFinish ( queue ); // Ожидаем завершения всех команд в очереди

			// Загрузка результатов вычислений с устройства
			clEnqueueReadBuffer (queue								 /* command_queue */,
				output_labels						 /* buffer */,
				CL_TRUE								 /* blocking_read */,
				0									 /* offset */,
				sizeof (unsigned int) * DataSize		 /* cb */,
				Labels								 /* ptr */,
				0									 /* num_events_in_wait_list */,
				NULL									 /* event_wait_list */,
				NULL									 /* event */ );

			// формирование новых кластеров
			for (size_t i = 0; i < DataSize; ++i) Clusters[Labels[i]].push_back(i);

			worker->ReportProgress(100*iter/IterationsCount);
	}

	clock_t timeFinish = clock();

	time = (timeFinish-timeStart)/(1.0f*CLOCKS_PER_SEC);

	//printf("\n");

	// освобождение занятых ресурсов 
	clReleaseMemObject ( input_data );
	clReleaseMemObject ( input_means );
	clReleaseMemObject ( output_labels );
	clReleaseProgram ( program );
	clReleaseKernel ( kernel );
	clReleaseCommandQueue ( queue );
	clReleaseContext ( context );

	vector <vector <size_t> > result; result.clear();
	for (size_t i = 0; i < NClusters; ++i)
		if (Clusters[i].size()>0) result.push_back(Clusters[i]);

	return result;
}	

#pragma endregion

#pragma region Класс KMeansConditionalOpenCLDensityMethod

KMeansConditionalOpenCLDensityMethod::KMeansConditionalOpenCLDensityMethod(TVoxelsData *DataValue, short LowBorder, short HighBorder) : KMeansConditionalOpenCLMethod <float>(DataValue, LowBorder, HighBorder) {}
KMeansConditionalOpenCLDensityMethod::KMeansConditionalOpenCLDensityMethod(TLayer layer, short LowBorder, short HighBorder) : KMeansConditionalOpenCLMethod <float>(layer, LowBorder, HighBorder) {}

float KMeansConditionalOpenCLDensityMethod::GetMean(size_t i) {	return GetMeanDensity(InputData, Clusters[i]); }

vector <vector <size_t> > KMeansConditionalOpenCLDensityMethod::GetClusters(BackgroundWorker^ worker)
{
 VoxelsInRange.clear();

 for (size_t i = 0; i < DataSize; ++i)
 if ((InputData->Density[i]>=MinDensityRange)&&
	 (InputData->Density[i]<=MaxDensityRange))
 VoxelsInRange.push_back(i);

 size_t ConditionalDataSize = VoxelsInRange.size();

 size_t part = ConditionalDataSize/NClusters;

 means = new float [NClusters];

 Labels = new size_t [DataSize];

 Clusters = new vector <size_t> [NClusters];

 for (size_t i = 0; i < NClusters; ++i)
 {
  for (size_t j = part*i; j < max(ConditionalDataSize*(i/(NClusters-1)), part*(i+1)); ++j)
  Clusters[i].push_back(VoxelsInRange.at(j));
 }

 InitOpenCL();

 // Создаем программный объект из исходного кода (определен выше)
 size_t srclen [] = { strlen ( source_conditional_distribution ) };

 cl_program program = clCreateProgramWithSource (context							/* context */,
   											     1									/* count */	 ,
												 &source_conditional_distribution	/* strings */,
												 srclen								/* lengths */,
												 NULL								/* errcode_ret */ );

 // Создаем исполняемый файл программы для выбранного устройства (GPU)
 clBuildProgram (program  /* program	 */,
    			 1		  /* num_devices */,
				 &device  /* device_list */,
				 NULL	  /* options     */,
				 NULL     /* pfn_notify  */,
                 NULL     /* user_data   */ );

  // Создаем объект ядра для перераспределения вокселов между кластерами
  cl_kernel kernel = clCreateKernel (program					/* program */,
									 "conditional_distribution"	/* kernel_name */,
									 NULL						/* errcode_ret */ );

  // Создаем объект памяти в виде буфера для передачи ядру входного массива
  cl_mem input_data = clCreateBuffer (context					  /* context */,
									  CL_MEM_READ_ONLY		      /* flags */,
								      sizeof (short) * DataSize	  /* size */,
								      NULL					      /* host_ptr */,
								      NULL					      /* errcode_ret */ );
  
  cl_mem input_means = clCreateBuffer (context, 
									   CL_MEM_READ_ONLY, 
									   sizeof (float) * NClusters, 
									   NULL, 
									   NULL);	// буфер для передачи центров тяжести

  cl_mem output_labels = clCreateBuffer (context, 
										 CL_MEM_WRITE_ONLY, 
										 sizeof (unsigned int) * DataSize, 
										 NULL, 
										 NULL); // буфер для передачи меток кластеров
 
  // Задание аргументов ядра
  clSetKernelArg (kernel			/* kernel		*/,
				  0					/* arg_index	*/,
				  sizeof ( cl_mem )	/* arg_size		*/,
				  &input_data		/* arg_value	*/ );
 
  clSetKernelArg (kernel			/* kernel		*/,
				  1					/* arg_index	*/,
				  sizeof ( cl_mem )	/* arg_size		*/,
				  &input_means		/* arg_value	*/ );

 clSetKernelArg (kernel			/* kernel		*/,
				  2					/* arg_index	*/,
				  sizeof ( cl_mem ) /* arg_size		*/,
				  &output_labels	/* arg_value	*/ );

 clSetKernelArg (kernel, 3, sizeof (short), &MinDensityRange);

 clSetKernelArg (kernel, 4, sizeof (short), &MaxDensityRange);

 clSetKernelArg (kernel, 5, sizeof (unsigned int), &DataSize);

 clSetKernelArg (kernel, 6, sizeof (unsigned int), &NClusters);

 size_t group; // максимальный размер группы работ

 CalcWorkGroupSize(kernel, group);

 clock_t timeStart = clock();
 
 for (size_t iter = 1; iter <= IterationsCount; ++iter)
 {
  for (size_t i = 0; i < NClusters; ++i)
  if (Clusters[i].size()>0) 
  {
   means[i] = GetMean(i); 
   Clusters[i].clear();
  }
  else means[i] = -1.0f;

  // Помещаем в очередь команду записи входного массива в объект памяти
  clEnqueueWriteBuffer (queue							/* command_queue */,
					     input_data						/* buffer */,
					     CL_TRUE						/* blocking_write */,
					     0								/* offset */,
					     sizeof ( short ) * DataSize	/* cb */,
						 InputData->Density				/* ptr */,
					     0								/* num_events_in_wait_list */,
					     NULL							/* event_wait_list */,
					     NULL							/* event */ );

  clEnqueueWriteBuffer (queue, input_means, CL_TRUE, 0, sizeof (float) * NClusters, means, 0, NULL, NULL);
  
  clEnqueueWriteBuffer (queue, output_labels, CL_TRUE, 0, sizeof (unsigned int) * DataSize, Labels, 0, NULL, NULL);
 
  // Выполнение ядра над всем множеством входных данных
  clEnqueueNDRangeKernel (queue		/* command_queue */,
   						  kernel	/* kernel */,
						  1			/* work_dim */,
						  NULL		/* global_work_offset */,
						  &DataSize	/* global_work_size */,
						  &group	/* local_work_size */,
						  0			/* num_events_in_wait_list */,
						  NULL		/* event_wait_list */,
						  NULL		/* event */ );

  clFinish ( queue ); // Ожидаем завершения всех команд в очереди

  // Загрузка результатов вычислений с устройства
  clEnqueueReadBuffer (queue								 /* command_queue */,
					   output_labels						 /* buffer */,
					   CL_TRUE								 /* blocking_read */,
					   0									 /* offset */,
					   sizeof (unsigned int) * DataSize		 /* cb */,
					   Labels								 /* ptr */,
					   0									 /* num_events_in_wait_list */,
					   NULL									 /* event_wait_list */,
					   NULL									 /* event */ );

  for (size_t i = 0; i < DataSize; ++i)
  if ((InputData->Density[i]>=MinDensityRange)&&
      (InputData->Density[i]<=MaxDensityRange))
  Clusters[Labels[i]].push_back(i);

  worker->ReportProgress(100*iter/IterationsCount);
 }

 clock_t timeFinish = clock();

 time = (timeFinish-timeStart)/(1.0f*CLOCKS_PER_SEC);
 
 // освобождение занятых ресурсов 
 clReleaseMemObject ( input_data );
 clReleaseMemObject ( input_means );
 clReleaseMemObject ( output_labels );
 clReleaseProgram ( program );
 clReleaseKernel ( kernel );
 clReleaseCommandQueue ( queue );
 clReleaseContext ( context );

 vector <vector <size_t> > result; result.clear();
 for (size_t i = 0; i<NClusters; ++i)
 if (Clusters[i].size()>0) result.push_back(Clusters[i]);

 return result;
}

#pragma endregion