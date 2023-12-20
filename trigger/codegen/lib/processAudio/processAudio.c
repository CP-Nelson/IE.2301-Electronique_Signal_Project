/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * processAudio.c
 *
 * Code generation for function 'processAudio'
 *
 */

/* Include files */
#include "processAudio.h"
#include "fft.h"
#include "filter.h"
#include "fir1.h"
#include "processAudio_data.h"
#include "processAudio_initialize.h"
#include "processAudio_rtwutil.h"
#include "processAudio_types.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
void processAudio(const double audio_data[44100], double Fs,
                  struct0_T *originalAudio, struct0_T *filteredAudio,
                  double *Energy)
{
  static creal_T filtered_fft_result[65536];
  double dv1[11];
  double dv[2];
  double delta1;
  int k;
  if (!isInitialized_processAudio) {
    processAudio_initialize();
  }
  /*  Calculate the length of the audio data in seconds */
  delta1 = 44100.0 / Fs;
  /*  Create a time series for plotting */
  originalAudio->Time[44099] = delta1;
  originalAudio->Time[0] = 0.0;
  if (-delta1 == 0.0) {
    delta1 /= 44099.0;
    for (k = 0; k < 44098; k++) {
      originalAudio->Time[k + 1] = (2.0 * ((double)k + 2.0) - 44101.0) * delta1;
    }
  } else if ((delta1 < 0.0) && (fabs(delta1) > 8.9884656743115785E+307)) {
    delta1 /= 44099.0;
    for (k = 0; k < 44098; k++) {
      originalAudio->Time[k + 1] = delta1 * ((double)k + 1.0);
    }
  } else {
    delta1 /= 44099.0;
    for (k = 0; k < 44098; k++) {
      originalAudio->Time[k + 1] = ((double)k + 1.0) * delta1;
    }
  }
  /*  FFT Analysis */
  /*  Number of FFT points */
  /*  Keep only the first half */
  /*  Frequency axis */
  /*  Designing Bandpass Filter */
  /*  Center frequency of the bandpass filter */
  /*  Normalize center frequency */
  delta1 = Fs / 2.0;
  dv[0] = 295.0 / delta1;
  dv[1] = 305.0 / delta1;
  /*  Bandpass filter */
  /*  Applying the Bandpass Filter */
  fir1(dv, dv1);
  filter(dv1, audio_data, filteredAudio->Amplitude);
  /*  FFT of the filtered signal */
  fft(filteredAudio->Amplitude, filtered_fft_result);
  /*  First half */
  /*  Amplitude in dB */
  /*  Calculate the energy of the filtered audio signal */
  /*  Internal function for energy calculation */
  *Energy = 0.0;
  for (k = 0; k < 32768; k++) {
    delta1 = 20.0 * log10(rt_hypotd_snf(filtered_fft_result[k].re,
                                        filtered_fft_result[k].im));
    if (delta1 > 0.0) {
      *Energy += delta1 * delta1;
      /*  Energy calculation */
    }
  }
  /*  Output structure for original and filtered audio */
  for (k = 0; k < 44100; k++) {
    originalAudio->Amplitude[k] = audio_data[k];
    filteredAudio->Time[k] = originalAudio->Time[k];
  }
}

/* End of code generation (processAudio.c) */
