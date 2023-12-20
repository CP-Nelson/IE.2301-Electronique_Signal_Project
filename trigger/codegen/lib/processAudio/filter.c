/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * filter.c
 *
 * Code generation for function 'filter'
 *
 */

/* Include files */
#include "filter.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
void filter(const double b[11], const double x[44100], double y[44100])
{
  int j;
  int k;
  memset(&y[0], 0, 44100U * sizeof(double));
  for (k = 0; k < 11; k++) {
    int b_k;
    b_k = k + 1;
    for (j = b_k; j < 44101; j++) {
      y[j - 1] += b[k] * x[(j - k) - 1];
    }
  }
}

/* End of code generation (filter.c) */
