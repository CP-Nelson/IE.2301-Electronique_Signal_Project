/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_processAudio_api.h
 *
 * Code generation for function 'processAudio'
 *
 */

#ifndef _CODER_PROCESSAUDIO_API_H
#define _CODER_PROCESSAUDIO_API_H

/* Include files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef typedef_struct0_T
#define typedef_struct0_T
typedef struct {
  real_T Time[44100];
  real_T Amplitude[44100];
} struct0_T;
#endif /* typedef_struct0_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void processAudio(real_T audio_data[44100], real_T Fs, struct0_T *originalAudio,
                  struct0_T *filteredAudio, real_T *Energy);

void processAudio_api(const mxArray *const prhs[2], int32_T nlhs,
                      const mxArray *plhs[3]);

void processAudio_atexit(void);

void processAudio_initialize(void);

void processAudio_terminate(void);

void processAudio_xil_shutdown(void);

void processAudio_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (_coder_processAudio_api.h) */
