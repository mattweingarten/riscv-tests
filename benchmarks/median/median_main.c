// See LICENSE for license details.

//**************************************************************************
// Median filter bencmark
//--------------------------------------------------------------------------
//
// This benchmark performs a 1D three element median filter. The
// input data (and reference data) should be generated using the
// median_gendata.pl perl script and dumped to a file named
// dataset1.h.

#include "util.h"
#include "common.h"

#include "median.h"

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset1.h"
#include "../../benchmarks/pmu_defs.h"


//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  int results_data[DATA_SIZE];

#if PREALLOCATE
  // If needed we preallocate everything in the caches
  median( DATA_SIZE, input_data, results_data );
#endif

// #ifdef PMU
//   start_counters();
// #endif

  // Do the filter
  
#ifndef PMU 
setStats(1);
#endif
  median( DATA_SIZE, input_data, results_data );
  
#ifndef PMU 
setStats(0);
#endif

// #ifdef PMU
//   end_counters();
// #endif
  // Check the results
  return verify( DATA_SIZE, results_data, verify_data );
}
