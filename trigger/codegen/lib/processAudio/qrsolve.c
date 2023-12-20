/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * qrsolve.c
 *
 * Code generation for function 'qrsolve'
 *
 */

/* Include files */
#include "qrsolve.h"
#include "processAudio_rtwutil.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static int div_nde_s32_floor(int numerator);

/* Function Definitions */
static int div_nde_s32_floor(int numerator)
{
  int i;
  if ((numerator < 0) && (numerator % 6 != 0)) {
    i = -1;
  } else {
    i = 0;
  }
  return numerator / 6 + i;
}

int qrsolve(const double A_data[], const int A_size[2], const double B_data[],
            double Y_data[])
{
  double b_A_data[30];
  double b_B_data[6];
  double tau_data[5];
  double work_data[5];
  double smax;
  int A_size_idx_1;
  int Y_size;
  int b_i;
  int b_k;
  int i;
  int iy;
  int k;
  int kend;
  int n;
  int pvt;
  signed char jpvt_data[5];
  A_size_idx_1 = A_size[1];
  iy = 6 * A_size[1];
  if (iy - 1 >= 0) {
    memcpy(&b_A_data[0], &A_data[0], (unsigned int)iy * sizeof(double));
  }
  n = A_size[1];
  iy = A_size[1];
  if (iy - 1 >= 0) {
    memset(&tau_data[0], 0, (unsigned int)iy * sizeof(double));
  }
  if (A_size[1] == 0) {
    for (k = 0; k < n; k++) {
      jpvt_data[k] = (signed char)(k + 1);
    }
  } else {
    double vn1_data[5];
    double vn2_data[5];
    double absxk;
    double scale;
    double t;
    iy = A_size[1];
    for (k = 0; k < iy; k++) {
      jpvt_data[k] = (signed char)(k + 1);
      work_data[k] = 0.0;
      vn1_data[k] = 0.0;
      vn2_data[k] = 0.0;
      pvt = k * 6;
      smax = 0.0;
      scale = 3.3121686421112381E-170;
      kend = pvt + 6;
      for (b_k = pvt + 1; b_k <= kend; b_k++) {
        absxk = fabs(A_data[b_k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          smax = smax * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          smax += t * t;
        }
      }
      absxk = scale * sqrt(smax);
      vn1_data[k] = absxk;
      vn2_data[k] = absxk;
    }
    for (i = 0; i < n; i++) {
      int ii;
      int ip1;
      int nmi;
      ip1 = i + 2;
      ii = i * 6 + i;
      nmi = n - i;
      if (nmi < 1) {
        iy = -1;
      } else {
        iy = 0;
        if (nmi > 1) {
          smax = fabs(vn1_data[i]);
          for (k = 2; k <= nmi; k++) {
            scale = fabs(vn1_data[(i + k) - 1]);
            if (scale > smax) {
              iy = k - 1;
              smax = scale;
            }
          }
        }
      }
      pvt = i + iy;
      if (pvt != i) {
        kend = pvt * 6;
        iy = i * 6;
        for (k = 0; k < 6; k++) {
          b_k = kend + k;
          smax = b_A_data[b_k];
          b_i = iy + k;
          b_A_data[b_k] = b_A_data[b_i];
          b_A_data[b_i] = smax;
        }
        iy = jpvt_data[pvt];
        jpvt_data[pvt] = jpvt_data[i];
        jpvt_data[i] = (signed char)iy;
        vn1_data[pvt] = vn1_data[i];
        vn2_data[pvt] = vn2_data[i];
      }
      t = b_A_data[ii];
      pvt = ii + 2;
      tau_data[i] = 0.0;
      smax = xnrm2(5 - i, b_A_data, ii + 2);
      if (smax != 0.0) {
        absxk = b_A_data[ii];
        scale = rt_hypotd_snf(absxk, smax);
        if (absxk >= 0.0) {
          scale = -scale;
        }
        if (fabs(scale) < 1.0020841800044864E-292) {
          kend = 0;
          b_i = (ii - i) + 6;
          do {
            kend++;
            for (k = pvt; k <= b_i; k++) {
              b_A_data[k - 1] *= 9.9792015476736E+291;
            }
            scale *= 9.9792015476736E+291;
            t *= 9.9792015476736E+291;
          } while ((fabs(scale) < 1.0020841800044864E-292) && (kend < 20));
          scale = rt_hypotd_snf(t, xnrm2(5 - i, b_A_data, ii + 2));
          if (t >= 0.0) {
            scale = -scale;
          }
          tau_data[i] = (scale - t) / scale;
          smax = 1.0 / (t - scale);
          for (k = pvt; k <= b_i; k++) {
            b_A_data[k - 1] *= smax;
          }
          for (k = 0; k < kend; k++) {
            scale *= 1.0020841800044864E-292;
          }
          t = scale;
        } else {
          tau_data[i] = (scale - absxk) / scale;
          smax = 1.0 / (absxk - scale);
          b_i = (ii - i) + 6;
          for (k = pvt; k <= b_i; k++) {
            b_A_data[k - 1] *= smax;
          }
          t = scale;
        }
      }
      b_A_data[ii] = t;
      if (i + 1 < n) {
        int lastv;
        b_A_data[ii] = 1.0;
        k = ii + 7;
        if (tau_data[i] != 0.0) {
          boolean_T exitg2;
          lastv = 6 - i;
          kend = (ii - i) + 5;
          while ((lastv > 0) && (b_A_data[kend] == 0.0)) {
            lastv--;
            kend--;
          }
          nmi -= 2;
          exitg2 = false;
          while ((!exitg2) && (nmi + 1 > 0)) {
            int exitg1;
            kend = (ii + nmi * 6) + 6;
            b_k = kend;
            do {
              exitg1 = 0;
              if (b_k + 1 <= kend + lastv) {
                if (b_A_data[b_k] != 0.0) {
                  exitg1 = 1;
                } else {
                  b_k++;
                }
              } else {
                nmi--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);
            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = 0;
          nmi = -1;
        }
        if (lastv > 0) {
          if (nmi + 1 != 0) {
            if (nmi >= 0) {
              memset(&work_data[0], 0,
                     (unsigned int)(nmi + 1) * sizeof(double));
            }
            b_i = (ii + 6 * nmi) + 7;
            for (iy = k; iy <= b_i; iy += 6) {
              smax = 0.0;
              pvt = (iy + lastv) - 1;
              for (b_k = iy; b_k <= pvt; b_k++) {
                smax += b_A_data[b_k - 1] * b_A_data[(ii + b_k) - iy];
              }
              kend = div_nde_s32_floor((iy - ii) - 7);
              work_data[kend] += smax;
            }
          }
          if (!(-tau_data[i] == 0.0)) {
            kend = ii;
            for (k = 0; k <= nmi; k++) {
              absxk = work_data[k];
              if (absxk != 0.0) {
                smax = absxk * -tau_data[i];
                b_i = kend + 7;
                pvt = lastv + kend;
                for (b_k = b_i; b_k <= pvt + 6; b_k++) {
                  b_A_data[b_k - 1] += b_A_data[((ii + b_k) - kend) - 7] * smax;
                }
              }
              kend += 6;
            }
          }
        }
        b_A_data[ii] = t;
      }
      for (k = ip1; k <= n; k++) {
        iy = i + (k - 1) * 6;
        absxk = vn1_data[k - 1];
        if (absxk != 0.0) {
          smax = fabs(b_A_data[iy]) / absxk;
          smax = 1.0 - smax * smax;
          if (smax < 0.0) {
            smax = 0.0;
          }
          scale = absxk / vn2_data[k - 1];
          scale = smax * (scale * scale);
          if (scale <= 1.4901161193847656E-8) {
            absxk = xnrm2(5 - i, b_A_data, iy + 2);
            vn1_data[k - 1] = absxk;
            vn2_data[k - 1] = absxk;
          } else {
            vn1_data[k - 1] = absxk * sqrt(smax);
          }
        }
      }
    }
  }
  pvt = 0;
  if (A_size[1] > 0) {
    smax = 1.3322676295501878E-14 * fabs(b_A_data[0]);
    while ((pvt < A_size_idx_1) && (!(fabs(b_A_data[pvt + 6 * pvt]) <= smax))) {
      pvt++;
    }
  }
  for (b_i = 0; b_i < 6; b_i++) {
    b_B_data[b_i] = B_data[b_i];
  }
  Y_size = A_size[1];
  for (k = 0; k < A_size_idx_1; k++) {
    Y_data[k] = 0.0;
    if (tau_data[k] != 0.0) {
      smax = b_B_data[k];
      b_i = k + 2;
      for (i = b_i; i < 7; i++) {
        smax += b_A_data[(i + 6 * k) - 1] * b_B_data[i - 1];
      }
      smax *= tau_data[k];
      if (smax != 0.0) {
        b_B_data[k] -= smax;
        for (i = b_i; i < 7; i++) {
          b_B_data[i - 1] -= b_A_data[(i + 6 * k) - 1] * smax;
        }
      }
    }
  }
  for (i = 0; i < pvt; i++) {
    Y_data[jpvt_data[i] - 1] = b_B_data[i];
  }
  for (k = pvt; k >= 1; k--) {
    iy = jpvt_data[k - 1] - 1;
    kend = 6 * (k - 1);
    Y_data[jpvt_data[k - 1] - 1] = Y_data[iy] / b_A_data[(k + kend) - 1];
    for (i = 0; i <= k - 2; i++) {
      b_k = jpvt_data[i] - 1;
      Y_data[b_k] -= Y_data[iy] * b_A_data[i + kend];
    }
  }
  return Y_size;
}

/* End of code generation (qrsolve.c) */
