/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: energycalcul.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 20-Dec-2023 16:29:58
 */

/* Include Files */
#include "energycalcul.h"

/* Function Definitions */
/*
 * Arguments    : double timeLeft
 *                double timeRight
 *                const double amp[2]
 * Return Type  : double
 */
double energycalcul(double timeLeft, double timeRight, const double amp[2])
{
  double energ;
  int b_i;
  int i;
  energ = 0.0;
  i = (int)(timeRight + (1.0 - timeLeft));
  for (b_i = 0; b_i < i; b_i++) {
    double d;
    d = amp[(int)(timeLeft + (double)b_i) - 1];
    if (d > 0.0) {
      energ += d * d;
    }
  }
  return energ;
}

/*
 * File trailer for energycalcul.c
 *
 * [EOF]
 */
