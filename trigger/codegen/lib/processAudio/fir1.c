/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fir1.c
 *
 * Code generation for function 'fir1'
 *
 */

/* Include files */
#include "fir1.h"
#include "firls.h"
#include "processAudio_rtwutil.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <float.h>
#include <math.h>

/* Type Definitions */
#ifndef struct_emxArray_char_T_1x8
#define struct_emxArray_char_T_1x8
struct emxArray_char_T_1x8 {
  char data[8];
  int size[2];
};
#endif /* struct_emxArray_char_T_1x8 */
#ifndef typedef_emxArray_char_T_1x8
#define typedef_emxArray_char_T_1x8
typedef struct emxArray_char_T_1x8 emxArray_char_T_1x8;
#endif /* typedef_emxArray_char_T_1x8 */

#ifndef typedef_rtString
#define typedef_rtString
typedef struct {
  emxArray_char_T_1x8 Value;
} rtString;
#endif /* typedef_rtString */

/* Function Declarations */
static double rt_remd_snf(double u0, double u1);

/* Function Definitions */
static double rt_remd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = rtNaN;
  } else if (rtIsInf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    double q;
    q = fabs(u0 / u1);
    if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }
  return y;
}

void fir1(const double varargin_2[2], double b[11])
{
  static const double wind[11] = {
      0.080000000000000016, 0.16785218258752421, 0.39785218258752419,
      0.68214781741247577,  0.91214781741247575, 1.0,
      0.91214781741247575,  0.68214781741247577, 0.39785218258752419,
      0.16785218258752421,  0.080000000000000016};
  static const char b_b[8] = {'B', 'A', 'N', 'D', 'P', 'A', 'S', 'S'};
  static const char cv1[8] = {'B', 'A', 'N', 'D', 'P', 'A', 'S', 'S'};
  static const char cv2[7] = {'N', 'O', 'S', 'C', 'A', 'L', 'E'};
  static const char cv[5] = {'S', 'C', 'A', 'L', 'E'};
  static const char cv3[4] = {'D', 'C', '-', '0'};
  static const char cv4[4] = {'H', 'I', 'G', 'H'};
  rtString rv[6];
  rtString r;
  rtString r1;
  rtString r2;
  rtString r3;
  rtString r4;
  rtString strOption;
  double hh_data[11];
  double a_data[6];
  double freq[6];
  double magnitude[6];
  int exitg2;
  int idx;
  int j;
  int kstr;
  int scale_Value_size_idx_1;
  int scaling;
  char scale_Value_data[8];
  boolean_T exitg1;
  boolean_T result;
  scaling = 1;
  scale_Value_size_idx_1 = 5;
  for (idx = 0; idx < 5; idx++) {
    scale_Value_data[idx] = cv[idx];
  }
  strOption.Value.size[0] = 1;
  strOption.Value.size[1] = 8;
  for (idx = 0; idx < 8; idx++) {
    strOption.Value.data[idx] = b_b[idx];
  }
  r.Value.size[0] = 1;
  r.Value.size[1] = 3;
  r.Value.data[0] = 'L';
  r.Value.data[1] = 'O';
  r.Value.data[2] = 'W';
  r1.Value.size[0] = 1;
  r1.Value.size[1] = 4;
  r2.Value.size[0] = 1;
  r2.Value.size[1] = 4;
  r3.Value.size[0] = 1;
  r3.Value.size[1] = 4;
  r4.Value.size[0] = 1;
  r4.Value.size[1] = 4;
  r1.Value.data[0] = 'H';
  r2.Value.data[0] = 'S';
  r3.Value.data[0] = 'D';
  r4.Value.data[0] = 'D';
  r1.Value.data[1] = 'I';
  r2.Value.data[1] = 'T';
  r3.Value.data[1] = 'C';
  r4.Value.data[1] = 'C';
  r1.Value.data[2] = 'G';
  r2.Value.data[2] = 'O';
  r3.Value.data[2] = '-';
  r4.Value.data[2] = '-';
  r1.Value.data[3] = 'H';
  r2.Value.data[3] = 'P';
  r3.Value.data[3] = '0';
  r4.Value.data[3] = '1';
  rv[0] = r;
  rv[1] = r1;
  rv[2] = strOption;
  rv[3] = r2;
  rv[4] = r3;
  rv[5] = r4;
  idx = -1;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 6)) {
    result = false;
    if (rv[j].Value.size[1] == 8) {
      kstr = 0;
      do {
        exitg2 = 0;
        if (kstr < 8) {
          if (rv[j].Value.data[kstr] != cv1[kstr]) {
            exitg2 = 1;
          } else {
            kstr++;
          }
        } else {
          result = true;
          exitg2 = 1;
        }
      } while (exitg2 == 0);
    }
    if (result) {
      idx = 1;
      exitg1 = true;
    } else {
      j++;
    }
  }
  switch (idx) {
  case 0:
    scale_Value_size_idx_1 = 8;
    for (idx = 0; idx < 8; idx++) {
      scale_Value_data[idx] = strOption.Value.data[idx];
    }
    break;
  case 1:
    break;
  }
  result = false;
  if (scale_Value_size_idx_1 == 7) {
    kstr = 0;
    do {
      exitg2 = 0;
      if (kstr < 7) {
        if (scale_Value_data[kstr] != cv2[kstr]) {
          exitg2 = 1;
        } else {
          kstr++;
        }
      } else {
        result = true;
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
  if (result) {
    scaling = 0;
  }
  result = false;
  kstr = 0;
  do {
    exitg2 = 0;
    if (kstr < 8) {
      if (strOption.Value.data[kstr] != cv1[kstr]) {
        exitg2 = 1;
      } else {
        kstr++;
      }
    } else {
      result = true;
      exitg2 = 1;
    }
  } while (exitg2 == 0);
  if (result) {
    strOption.Value.size[1] = 4;
    strOption.Value.data[0] = 'D';
    strOption.Value.data[1] = 'C';
    strOption.Value.data[2] = '-';
    strOption.Value.data[3] = '0';
  }
  freq[0] = 0.0;
  freq[1] = varargin_2[0];
  freq[2] = varargin_2[0];
  freq[3] = varargin_2[1];
  freq[4] = varargin_2[1];
  freq[5] = 1.0;
  result = false;
  if (strOption.Value.size[1] == 4) {
    kstr = 0;
    do {
      exitg2 = 0;
      if (kstr < 4) {
        if (strOption.Value.data[kstr] != cv3[kstr]) {
          exitg2 = 1;
        } else {
          kstr++;
        }
      } else {
        result = true;
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
  if (!result) {
    result = false;
    if (strOption.Value.size[1] == 4) {
      kstr = 0;
      do {
        exitg2 = 0;
        if (kstr < 4) {
          if (strOption.Value.data[kstr] != cv4[kstr]) {
            exitg2 = 1;
          } else {
            kstr++;
          }
        } else {
          result = true;
          exitg2 = 1;
        }
      } while (exitg2 == 0);
    }
    if (!result) {
      result = true;
    } else {
      result = false;
    }
  } else {
    result = false;
  }
  idx = -1;
  for (j = 0; j < 3; j++) {
    kstr = (signed char)rt_remd_snf((double)j + (double)result, 2.0);
    magnitude[idx + 1] = kstr;
    magnitude[idx + 2] = kstr;
    idx += 2;
  }
  int hh_size[2];
  eFirls(freq, magnitude, hh_data, hh_size, a_data);
  for (idx = 0; idx < 11; idx++) {
    b[idx] = hh_data[idx] * wind[idx];
  }
  if (scaling != 0) {
    if (result) {
      double f0;
      f0 = b[0];
      for (j = 0; j < 10; j++) {
        f0 += b[j + 1];
      }
      for (idx = 0; idx < 11; idx++) {
        b[idx] /= f0;
      }
    } else {
      double f0;
      double y_im;
      double y_re;
      if (varargin_2[1] == 1.0) {
        f0 = 1.0;
      } else {
        f0 = (varargin_2[0] + varargin_2[1]) / 2.0;
      }
      f0 /= 2.0;
      y_re = 0.0;
      y_im = 0.0;
      for (j = 0; j < 11; j++) {
        double b_re;
        double im;
        double re;
        im = f0 * (-6.2831853071795862 * (double)j);
        if (f0 * -0.0 == 0.0) {
          re = cos(im);
          im = sin(im);
        } else if (im == 0.0) {
          re = rtNaN;
          im = 0.0;
        } else {
          re = rtNaN;
          im = rtNaN;
        }
        b_re = b[j];
        y_re += re * b_re - im * 0.0;
        y_im += re * 0.0 + im * b_re;
      }
      f0 = rt_hypotd_snf(y_re, y_im);
      for (idx = 0; idx < 11; idx++) {
        b[idx] /= f0;
      }
    }
  }
}

/* End of code generation (fir1.c) */
