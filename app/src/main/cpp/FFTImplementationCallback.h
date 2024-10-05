//
// File: FFTImplementationCallback.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 03-Oct-2024 23:06:12
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
      static void generate_twiddle_tables(double costab[524289], double sintab
        [524289]);
      static void r2br_r2dit_trig(const creal_T x[1048576], const double costab
        [524289], const double sintab[524289], creal_T y[1048576]);
      static void doHalfLengthRadix2(const double x[25000], int xoffInit,
        creal_T y[1048576], const double costab[524289], const double sintab
        [524289]);
      static void b_doHalfLengthRadix2(const double x[300000], int xoffInit,
        creal_T y[1048576], const double costab[524289], const double sintab
        [524289]);
     protected:
      static void get_bitrevIndex(int bitrevIndex[524288]);
      static void getback_radix2_fft(creal_T y[1048576], int yoff, const creal_T
        reconVar1[524288], const creal_T reconVar2[524288], const int wrapIndex
        [524288], int hnRows);
    };
  }
}

#endif

//
// File trailer for FFTImplementationCallback.h
//
// [EOF]
//
