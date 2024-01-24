/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: firls.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 24-Jan-2024 01:20:42
 */

/* Include Files */
#include "firls.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double freq[6]
 *                double h_data[]
 *                int h_size[2]
 *                double a_data[]
 * Return Type  : int
 */
int eFirls(const double freq[6], double h_data[], int h_size[2],
           double a_data[])
{
  static const double wt[3] = {0.031622776601683791, 0.23979392774838984, 0.01};
  static const signed char A[6] = {0, 0, 1, 1, 0, 0};
  double G_data[676];
  double b0_data[26];
  double b_data[26];
  double d;
  double k1;
  double k2;
  double k3;
  double k4;
  double max_freq;
  double min_freq;
  int G_data_tmp;
  int a_size;
  int b_k;
  int i;
  int i1Map;
  int i2Map;
  int idx;
  int ii;
  int jp1j;
  int k;
  int nn;
  int s;
  boolean_T b;
  boolean_T exitg1;
  b = !rtIsNaN(freq[0]);
  if (b) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 7)) {
      if (!rtIsNaN(freq[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    max_freq = freq[0];
  } else {
    max_freq = freq[idx - 1];
    i = idx + 1;
    for (k = i; k < 7; k++) {
      d = freq[k - 1];
      if (max_freq < d) {
        max_freq = d;
      }
    }
  }
  if (b) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 7)) {
      if (!rtIsNaN(freq[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    min_freq = freq[0];
  } else {
    min_freq = freq[idx - 1];
    i = idx + 1;
    for (k = i; k < 7; k++) {
      d = freq[k - 1];
      if (min_freq > d) {
        min_freq = d;
      }
    }
  }
  if ((!(max_freq > 1.0)) && (!(min_freq < 0.0))) {
    double F[6];
    double b0;
    int yk;
    signed char k_data[26];
    signed char m_s_tmp;
    for (i = 0; i < 6; i++) {
      F[i] = freq[i] / 2.0;
    }
    memset(&G_data[0], 0, 676U * sizeof(double));
    b0 = 0.0;
    for (i = 0; i < 25; i++) {
      k_data[i] = (signed char)(i + 1);
      b_data[i] = 0.0;
    }
    for (s = 0; s < 3; s++) {
      double sinc1A_data[51];
      double sinc2A_data[51];
      double sinc3A_data[51];
      double sinc4A_data[51];
      double a;
      double b0_tmp;
      double b1;
      double b1_tmp;
      double b_a;
      double b_m_s_tmp;
      double m_s;
      idx = (s << 1) + 1;
      m_s_tmp = A[idx - 1];
      b_m_s_tmp = F[idx - 1];
      d = F[idx];
      min_freq = d - b_m_s_tmp;
      m_s = (double)(A[idx] - m_s_tmp) / min_freq;
      b1_tmp = m_s * b_m_s_tmp;
      b1 = (double)m_s_tmp - b1_tmp;
      max_freq = wt[(int)(((double)idx + 1.0) / 2.0) - 1];
      b0_tmp = max_freq * max_freq;
      b0 += (b1 * min_freq + m_s / 2.0 * (d * d - b_m_s_tmp * b_m_s_tmp)) *
            b0_tmp;
      a = m_s / 39.478417604357432;
      b_a = d * (m_s * d + b1);
      max_freq = b_m_s_tmp * (b1_tmp + b1);
      for (k = 0; k < 25; k++) {
        m_s_tmp = k_data[k];
        m_s = 6.2831853071795862 * (double)m_s_tmp;
        b1_tmp = cos(m_s * d);
        m_s = cos(m_s * b_m_s_tmp);
        min_freq = b_data[k] +
                   a * (b1_tmp - m_s) / (double)(m_s_tmp * m_s_tmp) * b0_tmp;
        b1_tmp = 2.0 * (double)m_s_tmp;
        m_s = b1_tmp * d;
        if (fabs(m_s) < 1.0020841800044864E-292) {
          m_s = 1.0;
        } else {
          m_s *= 3.1415926535897931;
          m_s = sin(m_s) / m_s;
        }
        b1_tmp *= b_m_s_tmp;
        if (fabs(b1_tmp) < 1.0020841800044864E-292) {
          b1_tmp = 1.0;
        } else {
          b1_tmp *= 3.1415926535897931;
          b1_tmp = sin(b1_tmp) / b1_tmp;
        }
        min_freq += (b_a * m_s - max_freq * b1_tmp) * b0_tmp;
        b_data[k] = min_freq;
      }
      m_s = 0.25 * b0_tmp;
      min_freq = 2.0 * d;
      max_freq = 2.0 * b_m_s_tmp;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(k4, k3,    \
                                                                    k2, k1)

      for (ii = 0; ii < 51; ii++) {
        k1 = min_freq * (((double)ii + 1.0) - 1.0);
        k2 = max_freq * (((double)ii + 1.0) - 1.0);
        k3 = min_freq * (((double)ii + 1.0) - 26.0);
        k4 = max_freq * (((double)ii + 1.0) - 26.0);
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
    i2Map, i1Map, nn, G_data_tmp)

      for (ii = 0; ii < 26; ii++) {
        for (nn = 0; nn < 26; nn++) {
          i1Map = (nn + ii) + 1;
          i2Map = (nn - ii) + 26;
          G_data_tmp = nn + 26 * ii;
          G_data[G_data_tmp] +=
              m_s *
              (min_freq * (sinc1A_data[i1Map - 1] + sinc3A_data[i2Map - 1]) -
               max_freq * (sinc2A_data[i1Map - 1] + sinc4A_data[i2Map - 1]));
        }
      }
    }
    b0_data[0] = b0;
    memcpy(&b0_data[1], &b_data[0], 25U * sizeof(double));
    memcpy(&b_data[0], &b0_data[0], 26U * sizeof(double));
    k_data[0] = 1;
    yk = 1;
    for (k = 0; k < 25; k++) {
      int b_tmp;
      int mmj_tmp;
      yk++;
      k_data[k + 1] = (signed char)yk;
      mmj_tmp = 24 - k;
      b_tmp = k * 27;
      jp1j = b_tmp + 2;
      idx = 26 - k;
      s = 0;
      max_freq = fabs(G_data[b_tmp]);
      for (b_k = 2; b_k <= idx; b_k++) {
        min_freq = fabs(G_data[(b_tmp + b_k) - 1]);
        if (min_freq > max_freq) {
          s = b_k - 1;
          max_freq = min_freq;
        }
      }
      if (G_data[b_tmp + s] != 0.0) {
        if (s != 0) {
          idx = k + s;
          k_data[k] = (signed char)(idx + 1);
          for (b_k = 0; b_k < 26; b_k++) {
            s = k + b_k * 26;
            max_freq = G_data[s];
            i = idx + b_k * 26;
            G_data[s] = G_data[i];
            G_data[i] = max_freq;
          }
        }
        i = (b_tmp - k) + 26;
        for (s = jp1j; s <= i; s++) {
          G_data[s - 1] /= G_data[b_tmp];
        }
      }
      idx = b_tmp;
      for (s = 0; s <= mmj_tmp; s++) {
        max_freq = G_data[(b_tmp + s * 26) + 26];
        if (max_freq != 0.0) {
          i = idx + 28;
          b_k = (idx - k) + 52;
          for (jp1j = i; jp1j <= b_k; jp1j++) {
            G_data[jp1j - 1] += G_data[((b_tmp + jp1j) - idx) - 27] * -max_freq;
          }
        }
        idx += 26;
      }
      m_s_tmp = k_data[k];
      if (m_s_tmp != k + 1) {
        max_freq = b_data[k];
        b_data[k] = b_data[m_s_tmp - 1];
        b_data[m_s_tmp - 1] = max_freq;
      }
    }
    for (k = 0; k < 26; k++) {
      idx = 26 * k;
      if (b_data[k] != 0.0) {
        i = k + 2;
        for (s = i; s < 27; s++) {
          b_data[s - 1] -= b_data[k] * G_data[(s + idx) - 1];
        }
      }
    }
    for (k = 25; k >= 0; k--) {
      idx = 26 * k;
      d = b_data[k];
      if (d != 0.0) {
        d /= G_data[k + idx];
        b_data[k] = d;
        for (s = 0; s < k; s++) {
          b_data[s] -= b_data[k] * G_data[s + idx];
        }
      }
    }
    h_size[0] = 1;
    h_size[1] = 51;
    h_data[25] = b_data[0];
    for (i = 0; i < 25; i++) {
      h_data[i] = b_data[25 - i] / 2.0;
      h_data[i + 26] = b_data[i + 1] / 2.0;
    }
    a_size = 1;
    a_data[0] = 1.0;
  }
  return a_size;
}

/*
 * File trailer for firls.c
 *
 * [EOF]
 */
