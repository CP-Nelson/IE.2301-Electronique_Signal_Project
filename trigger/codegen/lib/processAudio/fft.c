/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fft.c
 *
 * Code generation for function 'fft'
 *
 */

/* Include files */
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void fft(const double x[44100], creal_T y[65536])
{
  static double costab[32769];
  static double sintab[32769];
  static double costab1q[16385];
  int k;
  costab1q[0] = 1.0;
  for (k = 0; k < 8192; k++) {
    costab1q[k + 1] = cos(9.5873799242852573E-5 * ((double)k + 1.0));
  }
  for (k = 0; k < 8191; k++) {
    costab1q[k + 8193] =
        sin(9.5873799242852573E-5 * (16384.0 - ((double)k + 8193.0)));
  }
  costab1q[16384] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
  for (k = 0; k < 16384; k++) {
    double costab_tmp;
    double sintab_tmp;
    costab_tmp = costab1q[k + 1];
    costab[k + 1] = costab_tmp;
    sintab_tmp = -costab1q[16383 - k];
    sintab[k + 1] = sintab_tmp;
    costab[k + 16385] = sintab_tmp;
    sintab[k + 16385] = -costab_tmp;
  }
  memset(&y[0], 0, 65536U * sizeof(creal_T));
  c_FFTImplementationCallback_doH(x, y, costab, sintab);
}

/* End of code generation (fft.c) */
