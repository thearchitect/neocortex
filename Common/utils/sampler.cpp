#include "sampler.h"
#include <assert.h>

namespace core
{
	////////////////////////////////////////////////////
	///         BASE SAMPLER IMPLEMENTATION 
	sampler::sampler(UINT numSamples, UINT numSets) : _numSamples(numSamples), _numSets(numSets),_jump(0), _count(0)
	{
		setup_shuffled_indices();
	}

	vector2 sampler::sample_unit_square()
	{
		/// Perform random jump if the pixel is sampled completely
		if (_count % _numSamples == 0)
		{
			_jump = (rand_uint() % _numSets) * _numSamples;
		}

		/// Start returning shuffled samples
		return _samples[_jump + _shuffledIndices[_jump + _count++ % _numSamples]];
	}

	vector2 sampler::sample_unit_disk()
	{
		assert(_diskSamples.size() != 0);
			
		/// Perform random jump if the pixel is sampled completely
		if (_count % _numSamples == 0)
		{
			_jump = (rand_uint() % _numSets) * _numSamples;
		}

		/// Start returning shuffled samples
		return _diskSamples[_jump + _shuffledIndices[_jump + _count++ % _numSamples]];
	}

	vector3 sampler::sample_unit_hemisphere()
	{
		assert(_hemisphereSamples.size() != 0);
			
		/// Perform random jump if the pixel is sampled completely
		if (_count % _numSamples == 0)
		{
			_jump = (rand_uint() % _numSets) * _numSamples;
		}

		/// Start returning shuffled samples
		return _hemisphereSamples[_jump + _shuffledIndices[_jump + _count++ % _numSamples]];
	}

	void sampler::map_samples_to_unit_disk()
	{
		UINT numSamples = (UINT)_samples.size();
		_diskSamples.reserve(numSamples);

		for (UINT i = 0; i < numSamples;++i)
		{
			REAL phi, r;
			/// map samples to [-1,1]^2
			REAL a = 2 * _samples[i].x() - 1;
			REAL b = 2 * _samples[i].y() - 1;

			if (a > -b)
			{
				if (a > b)
				{
					r = a;
					phi = M_PI_4*(b/a);
				}
				else /// a <= b
				{
					r = b;
					phi = M_PI_4*(2 - a/b);
				}
			}
			else /// a <= -b
			{
				if (a < b)
				{
					r = -a;
					phi = M_PI_4*(4 + a/b); 
				}
				else /// a >= b
				{
					r = -b;
					phi = (b == 0)?(0):(M_PI_4 * (6 - a/b));
				}
			}

			_diskSamples.push_back(vector2(r*cos(phi), r*sin(phi)));
		}
	}

	void sampler::map_samples_to_unit_hemisphere( const REAL& e )
	{
		UINT numSamples = (UINT)_samples.size();
		_hemisphereSamples.reserve(numSamples);

		for (UINT i = 0; i < numSamples;++i)
		{
			REAL cos_phi  = cosf(2*M_PI*_samples[i].x());
			REAL sin_phi  = sinf(2*M_PI*_samples[i].x());
			REAL cos_theta = pow((REAL)1-_samples[i].y(), (REAL)1/(1 + e));
			REAL sin_theta = (REAL)1 - cos_theta*cos_theta;
			
			/// calculate spherical coordinates relative to u,v,w frame
			/// where w goes thru the center of a sphere and the sphere's top
			vector3 v(sin_theta*cos_phi, sin_theta*sin_phi, cos_theta);
			_hemisphereSamples.push_back(v);
		}
	}

	void sampler::setup_shuffled_indices()
	{
		/// indices array
		std::vector<UINT> indices(_numSamples);
		/// shuffled indices
		_shuffledIndices.reserve(_numSets * _numSamples);

		/// initialize
		for (UINT i = 0; i < _numSamples; ++i)
		{
			indices[i] = i;
		}

		/// fill up a shuffled indices
		for (UINT i = 0; i < _numSets; ++i)
		{
			std::random_shuffle(indices.begin(), indices.end());

			for (UINT j = 0; j < _numSamples; ++j)
				_shuffledIndices.push_back(indices[j]);
		}
	}

	////////////////////////////////////////////////////
	///         REGULAR SAMPLER IMPLEMENTATION 
	void regular_sampler::generate_samples()
	{
		UINT n = (UINT)sqrt((REAL)num_samples());
		UINT numSets = num_sets();
		for(UINT s = 0; s < numSets; ++s)
		{
			for(UINT i = 0; i < n; ++i)
				for(UINT j = 0; j < n; ++j)
				{
					vector2 v((REAL)(i + 0.5)/n, (REAL)(j + 0.5)/n);
					add_sample(v);
				}
		}
	}

	////////////////////////////////////////////////////
	///			RANDOM SAMPLER IMPLEMENTATION 
	void random_sampler::generate_samples()
	{
		UINT n = num_samples();
		UINT numSets = num_sets();
		for(UINT s = 0; s < numSets; ++s)
		{
			for(UINT i = 0; i < n; ++i)
			{
				vector2 v(rand_float(), rand_float());
				add_sample(v);
			}
		}
	}

	////////////////////////////////////////////////////
	///			JITTERED SAMPLER IMPLEMENTATION 
	void jittered_sampler::generate_samples()
	{
		UINT n = (UINT)sqrt((REAL)num_samples());
		UINT numSets = num_sets();
		for(UINT s = 0; s < numSets; ++s)
		{
			for(UINT i = 0; i < n; ++i)
				for(UINT j = 0; j < n; ++j)
				{
					vector2 v((REAL)(i + rand_float()) /n, (REAL)(j + rand_float())/n);
					add_sample(v);
				}
		}
	}

	////////////////////////////////////////////////////
	///			N-ROOKS SAMPLER IMPLEMENTATION 
	void nrooks_sampler::generate_samples()
	{
		UINT n = num_samples();
		UINT numSets = num_sets();
		for(UINT s = 0; s < numSets; ++s)
		{
			for(UINT i = 0; i < n; ++i)
			{
				vector2 v((REAL)(i + rand_float())/n, (REAL)(i + rand_float())/n);
				add_sample(v);
			}
		}

		shuffle();
	}

	void nrooks_sampler::shuffle()
	{
		UINT n = num_samples();
		UINT numSets = num_sets();
		for(UINT i = 0; i  < numSets; ++i)
		{
			/// shuffle x coordinate
			for (UINT j = 0; j < n - 1; ++j)
			{
				UINT offset = rand_uint() % n;
				if (offset == j) continue;
				UINT target = i * n + offset;
				UINT source = i * n + j;

				REAL temp = get_sample(target).x();
				get_sample(target).x() = get_sample(source).x();
				get_sample(source).x() = temp;
			}

			/// shuffle y coordinate
			for (UINT j = 0; j < n - 1; ++j)
			{
				UINT offset = rand_uint() % n;
				if (offset == j) continue;
				UINT target = i * n + offset;
				UINT source = i * n + j;

				REAL temp = get_sample(target).y();
				get_sample(target).y() = get_sample(source).y();
				get_sample(source).y() = temp;
			}
		}
	}

	////////////////////////////////////////////////////
	///			HAMMERSLEY SAMPLER IMPLEMENTATION 
	void hammersley_sampler::generate_samples()
	{
		UINT n = num_samples();
		UINT numSets = num_sets();
		for(UINT s = 0; s < numSets; ++s)
		{
			for(UINT i = 0; i < n; ++i)
			{
				vector2 v((REAL)i/n, phi(i));
				add_sample(v);
			}
		}
	}

	REAL hammersley_sampler::phi( UINT n )
	{
		UINT temp = n;
		REAL base = 0.5;
		REAL res = 0;

		while(temp)
		{
			res += base * (temp & 1);
			temp >>= 1;
			base *= 0.5;
		}

		return res;
	}

	////////////////////////////////////////////////////
	///	   MULTI-JITTERED SAMPLER IMPLEMENTATION 
	void multijittered_sampler::generate_samples()
	{
		// subgrid size
		UINT subGridSize = num_samples();
		// grid size
		UINT gridSize = (UINT)sqrt((REAL)subGridSize);
		// sub-cells per cell
		UINT subCellsPerCell = (UINT)subGridSize/gridSize;
		// subgrid cell size
		REAL subCellSize = (REAL)1/subGridSize;
		// Num sets 
		UINT numSets = num_sets();

		for (UINT i = 0; i < numSets; ++i)
		{
			for (UINT yj = 0; yj < gridSize; ++yj)
			{
				for (UINT xj = 0; xj < gridSize; ++xj)
				{
					vector2 v((xj*subCellsPerCell + yj + rand_float())*subCellSize, (yj * subCellsPerCell + xj + rand_float())*subCellSize);
					add_sample(v);
				}
			}
		}

		shuffle();
	}
}
