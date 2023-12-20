/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * powcal.c
 *
 * Code generation for function 'powcal'
 *
 */

/* Include files */
#include "powcal.h"

/* Function Definitions */
double powcal(double timeLeft, double timeRight, const double amp[2])
{
  double b_pow;
  int b_i;
  int i;
  b_pow = 0.0;
  i = (int)(timeRight + (1.0 - timeLeft));
  for (b_i = 0; b_i < i; b_i++) {
    double a;
    a = amp[(int)(timeLeft + (double)b_i) - 1];
    b_pow += a * a;
  }
  return b_pow;
}

/* End of code generation (powcal.c) */
