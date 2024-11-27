// See LICENSE for license details.

//**************************************************************************
// Memcpy benchmark
//--------------------------------------------------------------------------
//
// This benchmark tests a vectorized memcpy implementation.
// The input data (and reference data) should be generated using
// the memcpy_gendata.pl perl script and dumped to a file named
// dataset1.h.

#include <string.h>
#include "util.h"
#include "../../benchmarks/pmu_defs.h"

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset1.h"

//--------------------------------------------------------------------------
// Main

void *vec_memcpy(void*, const void*, size_t);

int main( int argc, char* argv[] )
{
  int results_data[DATA_SIZE];

#if PREALLOCATE
  // If needed we preallocate everything in the caches
  vec_memcpy(results_data, input_data, sizeof(int) * DATA_SIZE);
#endif

  // Do the riscv-linux memcpy
#ifdef PMU
  start_counters();
#endif
  
#ifndef PMU 
setStats(1);
#endif
  vec_memcpy(results_data, input_data, sizeof(int) * DATA_SIZE); //, DATA_SIZE * sizeof(int));
  
#ifndef PMU 
setStats(0);
#endif
#ifdef PMU
  end_counters();
#endif
  // Check the results
  return verify( DATA_SIZE, results_data, input_data );
}
