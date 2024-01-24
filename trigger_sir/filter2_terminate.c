/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filter2_terminate.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 24-Jan-2024 01:20:42
 */

/* Include Files */
#include "filter2_terminate.h"
#include "filter2_data.h"
#include "omp.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
// extern void omp_destroy_nest_lock(omp_nest_lock_t *lock);

void filter2_terminate(void)
{
  omp_destroy_nest_lock(&filter2_nestLockGlobal);
  isInitialized_filter2 = false;
}

/*
 * File trailer for filter2_terminate.c
 *
 * [EOF]
 */
