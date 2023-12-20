/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_powcal_api.h
 *
 * Code generation for function 'powcal'
 *
 */

#ifndef _CODER_POWCAL_API_H
#define _CODER_POWCAL_API_H

/* Include files */
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
real_T powcal(real_T timeLeft, real_T timeRight, real_T amp[2]);

void powcal_api(const mxArray *const prhs[3], const mxArray **plhs);

void powcal_atexit(void);

void powcal_initialize(void);

void powcal_terminate(void);

void powcal_xil_shutdown(void);

void powcal_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_powcal_api.h) */
