// See LICENSE for license details.

//**************************************************************************
// Memcpy benchmark
//--------------------------------------------------------------------------
//
// This benchmark tests the memcpy implementation in syscalls.c.
// The input data (and reference data) should be generated using
// the memcpy_gendata.pl perl script and dumped to a file named
// dataset1.h.

#include <string.h>
#include "util.h"
#include "../../benchmarks/pmu_defs.h"
// #define BARE

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset1.h"

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  int results_data[DATA_SIZE];

#if PREALLOCATE
  // If needed we preallocate everything in the caches
  memcpy(results_data, input_data, sizeof(int) * DATA_SIZE);
#endif
#ifdef PMU
  start_counters();
#endif
  // Do the riscv-linux memcpy
  
#ifndef PMU 
setStats(1);
#endif
  memcpy(results_data, input_data, sizeof(int) * DATA_SIZE); //, DATA_SIZE * sizeof(int));
  
#ifndef PMU 
setStats(0);
#endif
#ifdef PMU
  end_counters();
#endif
  // Check the results
  return verify( DATA_SIZE, results_data, input_data );
}
