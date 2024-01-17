/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_energycalcul_api.h
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 20-Dec-2023 16:29:58
 */

#ifndef _CODER_ENERGYCALCUL_API_H
#define _CODER_ENERGYCALCUL_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
real_T energycalcul(real_T timeLeft, real_T timeRight, real_T amp[2]);

void energycalcul_api(const mxArray *const prhs[3], const mxArray **plhs);

void energycalcul_atexit(void);

void energycalcul_initialize(void);

void energycalcul_terminate(void);

void energycalcul_xil_shutdown(void);

void energycalcul_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_energycalcul_api.h
 *
 * [EOF]
 */
