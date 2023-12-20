/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * processAudio.h
 *
 * Code generation for function 'processAudio'
 *
 */

#ifndef PROCESSAUDIO_H
#define PROCESSAUDIO_H

/* Include files */
#include "processAudio_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void processAudio(const double audio_data[44100], double Fs,
                         struct0_T *originalAudio, struct0_T *filteredAudio,
                         double *Energy);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (processAudio.h) */
