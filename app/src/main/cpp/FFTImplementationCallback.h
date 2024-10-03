//
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2024 14:53:53
//
#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder
{
  namespace internal
  {
    class FFTImplementationCallback
    {
     public:
      static void generate_twiddle_tables(double costab[131073], double sintab
        [131073]);
      static void r2br_r2dit_trig(const creal_T x[262144], const double costab
        [131073], const double sintab[131073], creal_T y[262144]);
      static void doHalfLengthRadix2(const double x[10000], int xoffInit,
        creal_T y[262144], const double costab[131073], const double sintab
        [131073]);
      static void b_doHalfLengthRadix2(const double x[96000], int xoffInit,
        creal_T y[262144], const double costab[131073], const double sintab
        [131073]);
     protected:
      static void get_bitrevIndex(int bitrevIndex[131072]);
      static void getback_radix2_fft(creal_T y[262144], int yoff, const creal_T
        reconVar1[131072], const creal_T reconVar2[131072], const int wrapIndex
        [131072], int hnRows);
    };
  }
}

#endif

//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
