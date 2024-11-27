// See LICENSE for license details.

//**************************************************************************
// SGEMM benchmark
//--------------------------------------------------------------------------
//
// This benchmark tests a vectorized sgemm implementation.

#include <string.h>
#include "util.h"
#include "../../benchmarks/pmu_defs.h"

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset1.h"

//--------------------------------------------------------------------------
// Main

void *vec_sgemm_nn (size_t, size_t, size_t, const float*, size_t, const float*, size_t, float*, size_t);

int main( int argc, char* argv[] )
{
  float results_data[ARRAY_SIZE] = {0};

#if PREALLOCATE
  // If needed we preallocate everything in the caches
  vec_sgemm_nn(DIM_SIZE, DIM_SIZE, DIM_SIZE, input1_data, DIM_SIZE, input2_data, DIM_SIZE, results_data, DIM_SIZE);
  memset(results_data, 0, sizeof(results_data));
#endif

  // Do the sgemm
  
#ifndef PMU 
setStats(1);
#endif
#ifdef PMU
  start_counters();
#endif
  vec_sgemm_nn(DIM_SIZE, DIM_SIZE, DIM_SIZE, input1_data, DIM_SIZE, input2_data, DIM_SIZE, results_data, DIM_SIZE);
  
#ifndef PMU 
setStats(0);
#endif
#ifdef PMU
  end_counters();
#endif
  // Check the results
  return verifyFloat( ARRAY_SIZE, results_data, verify_data );
}
