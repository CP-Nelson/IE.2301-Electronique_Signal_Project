/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * firls.h
 *
 * Code generation for function 'firls'
 *
 */

#ifndef FIRLS_H
#define FIRLS_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
int eFirls(const double freq[6], const double amp[6], double h_data[],
           int h_size[2], double a_data[]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (firls.h) */
