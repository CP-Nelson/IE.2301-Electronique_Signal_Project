/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: firls.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 24-Jan-2024 01:20:42
 */

#ifndef FIRLS_H
#define FIRLS_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int eFirls(const double freq[6], double h_data[], int h_size[2],
           double a_data[]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for firls.h
 *
 * [EOF]
 */
