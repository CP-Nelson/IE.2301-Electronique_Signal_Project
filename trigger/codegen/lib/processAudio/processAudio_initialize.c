/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * processAudio_initialize.c
 *
 * Code generation for function 'processAudio_initialize'
 *
 */

/* Include files */
#include "processAudio_initialize.h"
#include "processAudio_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
void processAudio_initialize(void)
{
  omp_init_nest_lock(&processAudio_nestLockGlobal);
  isInitialized_processAudio = true;
}

/* End of code generation (processAudio_initialize.c) */
