/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filter2.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 24-Jan-2024 01:20:42
 */

/* Include Files */
#include "filter2.h"
#include "filter2_data.h"
#include "filter2_initialize.h"
#include "firls.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double Fs
 *                const double audio_data[1000]
 * Return Type  : double
 */
double filter2(double Fs, const double audio_data[1000])
{
  double filtered_output[1000];
  double b_data[51];
  double a_data[26];
  double dv[6];
  double Energy;
  int b_size[2];
  int a_size;
  int j;
  (void)Fs;
  if (!isInitialized_filter2) {
    filter2_initialize();
  }
  /*  Order */
  /*  First Stopband Frequency */
  /*  First Passband Frequency */
  /*  Second Passband Frequency */
  /*  Second Stopband Frequency */
  /*  First Stopband Weight */
  /*  Passband Weight */
  /*  Second Stopband Weight */
  /*  Calculate the coefficients using the FIRLS function. */
  dv[0] = 0.0;
  dv[1] = 0.4;
  dv[2] = 0.5;
  dv[3] = 0.7;
  dv[4] = 0.8;
  dv[5] = 1.0;
  eFirls(dv, b_data, b_size, a_data);
  memset(&filtered_output[0], 0, 1000U * sizeof(double));
  for (a_size = 0; a_size < 51; a_size++) {
    int k;
    k = a_size + 1;
    for (j = k; j < 1001; j++) {
      filtered_output[j - 1] += b_data[a_size] * audio_data[(j - a_size) - 1];
    }
  }
  Energy = 0.0;
  for (a_size = 0; a_size < 1000; a_size++) {
    double d;
    d = filtered_output[a_size];
    if (d > 0.0) {
      Energy += d * d;
    }
  }
  return Energy;
}

/*
 * File trailer for filter2.c
 *
 * [EOF]
 */
