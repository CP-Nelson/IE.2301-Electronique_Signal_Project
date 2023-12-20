/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FFTImplementationCallback.c
 *
 * Code generation for function 'FFTImplementationCallback'
 *
 */

/* Include files */
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static void c_FFTImplementationCallback_get(creal_T y[65536],
                                            const creal_T reconVar1[32768],
                                            const creal_T reconVar2[32768],
                                            const int wrapIndex[32768]);

/* Function Definitions */
static void c_FFTImplementationCallback_get(creal_T y[65536],
                                            const creal_T reconVar1[32768],
                                            const creal_T reconVar2[32768],
                                            const int wrapIndex[32768])
{
  double b_y_re_tmp;
  double temp1_im_tmp;
  double temp1_re_tmp_tmp;
  double y_im_tmp;
  double y_re_tmp;
  int i;
  temp1_re_tmp_tmp = y[0].re;
  temp1_im_tmp = y[0].im;
  y_re_tmp = temp1_re_tmp_tmp * reconVar1[0].re;
  y_im_tmp = temp1_re_tmp_tmp * reconVar1[0].im;
  b_y_re_tmp = temp1_re_tmp_tmp * reconVar2[0].re;
  temp1_re_tmp_tmp *= reconVar2[0].im;
  y[0].re = 0.5 * ((y_re_tmp - temp1_im_tmp * reconVar1[0].im) +
                   (b_y_re_tmp - -temp1_im_tmp * reconVar2[0].im));
  y[0].im = 0.5 * ((y_im_tmp + temp1_im_tmp * reconVar1[0].re) +
                   (temp1_re_tmp_tmp + -temp1_im_tmp * reconVar2[0].re));
  y[32768].re = 0.5 * ((b_y_re_tmp - temp1_im_tmp * reconVar2[0].im) +
                       (y_re_tmp - -temp1_im_tmp * reconVar1[0].im));
  y[32768].im = 0.5 * ((temp1_re_tmp_tmp + temp1_im_tmp * reconVar2[0].re) +
                       (y_im_tmp + -temp1_im_tmp * reconVar1[0].re));
  for (i = 0; i < 16383; i++) {
    double temp1_re_tmp;
    double temp2_im_tmp;
    double temp2_re_tmp;
    int temp2_re_tmp_tmp_tmp;
    temp1_re_tmp = y[i + 1].re;
    temp1_im_tmp = y[i + 1].im;
    temp2_re_tmp_tmp_tmp = wrapIndex[i + 1];
    temp2_re_tmp = y[temp2_re_tmp_tmp_tmp - 1].re;
    temp2_im_tmp = y[temp2_re_tmp_tmp_tmp - 1].im;
    y_re_tmp = reconVar1[i + 1].im;
    b_y_re_tmp = reconVar1[i + 1].re;
    temp1_re_tmp_tmp = reconVar2[i + 1].im;
    y_im_tmp = reconVar2[i + 1].re;
    y[i + 1].re =
        0.5 * ((temp1_re_tmp * b_y_re_tmp - temp1_im_tmp * y_re_tmp) +
               (temp2_re_tmp * y_im_tmp - -temp2_im_tmp * temp1_re_tmp_tmp));
    y[i + 1].im =
        0.5 * ((temp1_re_tmp * y_re_tmp + temp1_im_tmp * b_y_re_tmp) +
               (temp2_re_tmp * temp1_re_tmp_tmp + -temp2_im_tmp * y_im_tmp));
    y[i + 32769].re =
        0.5 * ((temp1_re_tmp * y_im_tmp - temp1_im_tmp * temp1_re_tmp_tmp) +
               (temp2_re_tmp * b_y_re_tmp - -temp2_im_tmp * y_re_tmp));
    y[i + 32769].im =
        0.5 * ((temp1_re_tmp * temp1_re_tmp_tmp + temp1_im_tmp * y_im_tmp) +
               (temp2_re_tmp * y_re_tmp + -temp2_im_tmp * b_y_re_tmp));
    temp1_re_tmp_tmp = reconVar1[temp2_re_tmp_tmp_tmp - 1].im;
    y_im_tmp = reconVar1[temp2_re_tmp_tmp_tmp - 1].re;
    y_re_tmp = reconVar2[temp2_re_tmp_tmp_tmp - 1].im;
    b_y_re_tmp = reconVar2[temp2_re_tmp_tmp_tmp - 1].re;
    y[temp2_re_tmp_tmp_tmp - 1].re =
        0.5 * ((temp2_re_tmp * y_im_tmp - temp2_im_tmp * temp1_re_tmp_tmp) +
               (temp1_re_tmp * b_y_re_tmp - -temp1_im_tmp * y_re_tmp));
    y[temp2_re_tmp_tmp_tmp - 1].im =
        0.5 * ((temp2_re_tmp * temp1_re_tmp_tmp + temp2_im_tmp * y_im_tmp) +
               (temp1_re_tmp * y_re_tmp + -temp1_im_tmp * b_y_re_tmp));
    y[temp2_re_tmp_tmp_tmp + 32767].re =
        0.5 * ((temp2_re_tmp * b_y_re_tmp - temp2_im_tmp * y_re_tmp) +
               (temp1_re_tmp * y_im_tmp - -temp1_im_tmp * temp1_re_tmp_tmp));
    y[temp2_re_tmp_tmp_tmp + 32767].im =
        0.5 * ((temp2_re_tmp * y_re_tmp + temp2_im_tmp * b_y_re_tmp) +
               (temp1_re_tmp * temp1_re_tmp_tmp + -temp1_im_tmp * y_im_tmp));
  }
  temp1_re_tmp_tmp = y[16384].re;
  temp1_im_tmp = y[16384].im;
  y_re_tmp = temp1_re_tmp_tmp * reconVar1[16384].re;
  y_im_tmp = temp1_re_tmp_tmp * reconVar1[16384].im;
  b_y_re_tmp = temp1_re_tmp_tmp * reconVar2[16384].re;
  temp1_re_tmp_tmp *= reconVar2[16384].im;
  y[16384].re = 0.5 * ((y_re_tmp - temp1_im_tmp * reconVar1[16384].im) +
                       (b_y_re_tmp - -temp1_im_tmp * reconVar2[16384].im));
  y[16384].im =
      0.5 * ((y_im_tmp + temp1_im_tmp * reconVar1[16384].re) +
             (temp1_re_tmp_tmp + -temp1_im_tmp * reconVar2[16384].re));
  y[49152].re = 0.5 * ((b_y_re_tmp - temp1_im_tmp * reconVar2[16384].im) +
                       (y_re_tmp - -temp1_im_tmp * reconVar1[16384].im));
  y[49152].im = 0.5 * ((temp1_re_tmp_tmp + temp1_im_tmp * reconVar2[16384].re) +
                       (y_im_tmp + -temp1_im_tmp * reconVar1[16384].re));
}

void c_FFTImplementationCallback_doH(const double x[44100], creal_T y[65536],
                                     const double costab[32769],
                                     const double sintab[32769])
{
  static creal_T reconVar1[32768];
  static creal_T reconVar2[32768];
  static double hcostab[16384];
  static double hsintab[16384];
  static int wrapIndex[32768];
  double im;
  double re;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  int bitrevIndex[32768];
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int ihi;
  int iy;
  int ju;
  int k;
  for (i = 0; i < 16384; i++) {
    iy = ((i + 1) << 1) - 2;
    hcostab[i] = costab[iy];
    hsintab[i] = sintab[iy];
  }
  for (i = 0; i < 32768; i++) {
    re = sintab[i];
    reconVar1[i].re = re + 1.0;
    im = costab[i];
    reconVar1[i].im = -im;
    reconVar2[i].re = 1.0 - re;
    reconVar2[i].im = im;
    if (i + 1 != 1) {
      wrapIndex[i] = 32769 - i;
    } else {
      wrapIndex[0] = 1;
    }
  }
  ju = 0;
  iy = 1;
  for (ihi = 0; ihi < 32767; ihi++) {
    boolean_T tst;
    bitrevIndex[ihi] = iy;
    iy = 32768;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju + 1;
  }
  bitrevIndex[32767] = iy;
  for (i = 0; i < 22050; i++) {
    iy = i << 1;
    ju = bitrevIndex[i];
    y[ju - 1].re = x[iy];
    y[ju - 1].im = x[iy + 1];
  }
  for (i = 0; i <= 32766; i += 2) {
    re = y[i + 1].re;
    im = y[i + 1].im;
    temp_re = re;
    temp_im = im;
    twid_re = y[i].re;
    twid_im = y[i].im;
    re = twid_re - re;
    im = twid_im - im;
    y[i + 1].re = re;
    y[i + 1].im = im;
    twid_re += temp_re;
    twid_im += temp_im;
    y[i].re = twid_re;
    y[i].im = twid_im;
  }
  iDelta = 2;
  iDelta2 = 4;
  k = 8192;
  iheight = 32765;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      iy = i + iDelta;
      temp_re = y[iy].re;
      temp_im = y[iy].im;
      y[iy].re = y[i].re - temp_re;
      y[iy].im = y[i].im - temp_im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }
    iy = 1;
    for (ju = k; ju < 16384; ju += k) {
      twid_re = hcostab[ju];
      twid_im = hsintab[ju];
      i = iy;
      ihi = iy + iheight;
      while (i < ihi) {
        int temp_re_tmp_tmp;
        temp_re_tmp_tmp = i + iDelta;
        re = y[temp_re_tmp_tmp].im;
        im = y[temp_re_tmp_tmp].re;
        temp_re = twid_re * im - twid_im * re;
        temp_im = twid_re * re + twid_im * im;
        y[temp_re_tmp_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += iDelta2;
      }
      iy++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
  c_FFTImplementationCallback_get(y, reconVar1, reconVar2, wrapIndex);
}

/* End of code generation (FFTImplementationCallback.c) */
