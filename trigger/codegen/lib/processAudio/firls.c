/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * firls.c
 *
 * Code generation for function 'firls'
 *
 */

/* Include files */
#include "firls.h"
#include "qrsolve.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
int eFirls(const double freq[6], const double amp[6], double h_data[],
           int h_size[2], double a_data[])
{
  double G_data[36];
  double max_freq[6];
  double min_freq[6];
  double k1;
  double k2;
  double k3;
  double k4;
  int G_size[2];
  int G_data_tmp;
  int a_size;
  int b_i;
  int b_k;
  int i;
  int i1Map;
  int i2;
  int i2Map;
  int ii;
  int jA;
  int k;
  int nn;
  int tmpStorageLen;
  for (i = 0; i < 6; i++) {
    max_freq[i] = freq[i];
    min_freq[i] = freq[i];
  }
  if ((!(max_freq[0] > 1.0)) && (!(min_freq[0] < 0.0))) {
    double sinc1A_data[11];
    double sinc2A_data[11];
    double sinc3A_data[11];
    double sinc4A_data[11];
    double b_y1[5];
    double b0;
    double d;
    double tmp2;
    double work;
    signed char k_data[6];
    signed char i1;
    boolean_T exitg1;
    boolean_T fullband;
    for (i = 0; i < 6; i++) {
      max_freq[i] = freq[i] / 2.0;
    }
    work = 0.0;
    for (jA = 0; jA < 5; jA++) {
      tmp2 = work;
      work = max_freq[jA + 1];
      b_y1[jA] = work - tmp2;
    }
    fullband = true;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 2)) {
      if (b_y1[(i << 1) + 1] != 0.0) {
        fullband = false;
        exitg1 = true;
      } else {
        i++;
      }
    }
    fullband = !fullband;
    if (fullband) {
      G_size[0] = 6;
      G_size[1] = 6;
      memset(&G_data[0], 0, 36U * sizeof(double));
      tmpStorageLen = 10;
    } else {
      G_size[0] = 0;
      G_size[1] = 0;
      tmpStorageLen = -1;
    }
    b0 = 0.0;
    for (b_i = 0; b_i < 5; b_i++) {
      k_data[b_i] = (signed char)(b_i + 1);
      a_data[b_i] = 0.0;
    }
    for (i = 0; i < 3; i++) {
      double a;
      double b1;
      double b1_tmp;
      double b_a;
      double d1;
      double m_s_tmp_tmp;
      jA = i << 1;
      m_s_tmp_tmp = max_freq[jA + 1];
      d = max_freq[jA];
      work = m_s_tmp_tmp - d;
      d1 = amp[jA];
      tmp2 = (amp[jA + 1] - d1) / work;
      b1_tmp = tmp2 * d;
      b1 = d1 - b1_tmp;
      b0 += b1 * work + tmp2 / 2.0 * (m_s_tmp_tmp * m_s_tmp_tmp - d * d);
      a = tmp2 / 39.478417604357432;
      b_a = m_s_tmp_tmp * (tmp2 * m_s_tmp_tmp + b1);
      work = d * (b1_tmp + b1);
      for (k = 0; k < 5; k++) {
        i1 = k_data[k];
        d1 = 6.2831853071795862 * (double)i1;
        tmp2 = a_data[k] +
               a * (cos(d1 * m_s_tmp_tmp) - cos(d1 * d)) / (double)(i1 * i1);
        d1 = 2.0 * (double)i1;
        b1 = d1 * m_s_tmp_tmp;
        if (fabs(b1) < 1.0020841800044864E-292) {
          b1 = 1.0;
        } else {
          b1 *= 3.1415926535897931;
          b1 = sin(b1) / b1;
        }
        d1 *= d;
        if (fabs(d1) < 1.0020841800044864E-292) {
          d1 = 1.0;
        } else {
          d1 *= 3.1415926535897931;
          d1 = sin(d1) / d1;
        }
        tmp2 += b_a * b1 - work * d1;
        a_data[k] = tmp2;
      }
      if (fullband) {
        tmp2 = 2.0 * m_s_tmp_tmp;
        work = 2.0 * d;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k4, k3,    \
                                                                    k2, k1)

        for (ii = 0; ii <= tmpStorageLen; ii++) {
          k1 = tmp2 * (((double)ii + 1.0) - 1.0);
          k2 = work * (((double)ii + 1.0) - 1.0);
          k3 = tmp2 * (((double)ii + 1.0) - 6.0);
          k4 = work * (((double)ii + 1.0) - 6.0);
          if (fabs(k1) < 1.0020841800044864E-292) {
            sinc1A_data[ii] = 1.0;
          } else {
            k1 *= 3.1415926535897931;
            sinc1A_data[ii] = sin(k1) / k1;
          }
          if (fabs(k2) < 1.0020841800044864E-292) {
            sinc2A_data[ii] = 1.0;
          } else {
            k1 = 3.1415926535897931 * k2;
            sinc2A_data[ii] = sin(k1) / k1;
          }
          if (fabs(k3) < 1.0020841800044864E-292) {
            sinc3A_data[ii] = 1.0;
          } else {
            k1 = 3.1415926535897931 * k3;
            sinc3A_data[ii] = sin(k1) / k1;
          }
          if (fabs(k4) < 1.0020841800044864E-292) {
            sinc4A_data[ii] = 1.0;
          } else {
            k1 = 3.1415926535897931 * k4;
            sinc4A_data[ii] = sin(k1) / k1;
          }
        }
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    i2Map, i1Map, i2, nn, G_data_tmp)

        for (ii = 0; ii < 6; ii++) {
          i2 = G_size[0];
          for (nn = 0; nn < 6; nn++) {
            i1Map = (nn + ii) + 1;
            i2Map = (nn - ii) + 6;
            G_data_tmp = nn + i2 * ii;
            G_data[G_data_tmp] +=
                0.25 *
                (tmp2 * (sinc1A_data[i1Map - 1] + sinc3A_data[i2Map - 1]) -
                 work * (sinc2A_data[i1Map - 1] + sinc4A_data[i2Map - 1]));
          }
        }
      }
    }
    max_freq[0] = b0;
    for (b_i = 0; b_i < 5; b_i++) {
      max_freq[b_i + 1] = a_data[b_i];
    }
    for (b_i = 0; b_i < 6; b_i++) {
      a_data[b_i] = max_freq[b_i];
    }
    if (fullband) {
      if (G_size[1] == 0) {
      } else if (G_size[1] == 6) {
        int yk;
        k_data[0] = 1;
        yk = 1;
        for (k = 0; k < 5; k++) {
          int b_tmp;
          int mmj_tmp;
          yk++;
          k_data[k + 1] = (signed char)yk;
          mmj_tmp = 4 - k;
          b_tmp = k * 7;
          tmpStorageLen = b_tmp + 2;
          jA = 6 - k;
          i = 0;
          work = fabs(G_data[b_tmp]);
          for (b_k = 2; b_k <= jA; b_k++) {
            tmp2 = fabs(G_data[(b_tmp + b_k) - 1]);
            if (tmp2 > work) {
              i = b_k - 1;
              work = tmp2;
            }
          }
          if (G_data[b_tmp + i] != 0.0) {
            if (i != 0) {
              jA = k + i;
              k_data[k] = (signed char)(jA + 1);
              for (b_k = 0; b_k < 6; b_k++) {
                i = k + b_k * 6;
                work = G_data[i];
                b_i = jA + b_k * 6;
                G_data[i] = G_data[b_i];
                G_data[b_i] = work;
              }
            }
            b_i = (b_tmp - k) + 6;
            for (i = tmpStorageLen; i <= b_i; i++) {
              G_data[i - 1] /= G_data[b_tmp];
            }
          }
          jA = b_tmp;
          for (i = 0; i <= mmj_tmp; i++) {
            work = G_data[(b_tmp + i * 6) + 6];
            if (work != 0.0) {
              b_i = jA + 8;
              b_k = (jA - k) + 12;
              for (tmpStorageLen = b_i; tmpStorageLen <= b_k; tmpStorageLen++) {
                G_data[tmpStorageLen - 1] +=
                    G_data[((b_tmp + tmpStorageLen) - jA) - 7] * -work;
              }
            }
            jA += 6;
          }
          i1 = k_data[k];
          if (i1 != k + 1) {
            work = a_data[k];
            a_data[k] = a_data[i1 - 1];
            a_data[i1 - 1] = work;
          }
        }
        for (k = 0; k < 6; k++) {
          jA = 6 * k;
          if (a_data[k] != 0.0) {
            b_i = k + 2;
            for (i = b_i; i < 7; i++) {
              a_data[i - 1] -= a_data[k] * G_data[(i + jA) - 1];
            }
          }
        }
        for (k = 5; k >= 0; k--) {
          jA = 6 * k;
          d = a_data[k];
          if (d != 0.0) {
            d /= G_data[k + jA];
            a_data[k] = d;
            for (i = 0; i < k; i++) {
              a_data[i] -= a_data[k] * G_data[i + jA];
            }
          }
        }
      } else {
        for (b_i = 0; b_i < 6; b_i++) {
          max_freq[b_i] = a_data[b_i];
        }
        qrsolve(G_data, G_size, max_freq, a_data);
      }
    } else {
      for (b_i = 0; b_i < 6; b_i++) {
        a_data[b_i] *= 4.0;
      }
      a_data[0] /= 2.0;
    }
    h_size[0] = 1;
    h_size[1] = 11;
    h_data[5] = a_data[0];
    for (b_i = 0; b_i < 5; b_i++) {
      h_data[b_i] = a_data[5 - b_i] / 2.0;
      h_data[b_i + 6] = a_data[b_i + 1] / 2.0;
    }
    a_size = 1;
    a_data[0] = 1.0;
  }
  return a_size;
}

/* End of code generation (firls.c) */
