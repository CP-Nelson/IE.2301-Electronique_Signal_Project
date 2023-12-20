/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * processAudio_terminate.c
 *
 * Code generation for function 'processAudio_terminate'
 *
 */

/* Include files */
#include "processAudio_terminate.h"
#include "processAudio_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void processAudio_terminate(void)
{
  omp_destroy_nest_lock(&processAudio_nestLockGlobal);
  isInitialized_processAudio = false;
}

/* End of code generation (processAudio_terminate.c) */
