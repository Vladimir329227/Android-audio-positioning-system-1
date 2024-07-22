//
// File: CORRX.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2024 14:53:53
//

// Include Files
#include "CORRX.h"
#include "FFTImplementationCallback.h"
#include "ifft.h"
#include <cstring>

// Function Definitions
//
// Arguments    : const short input1[10000]
//                const short input2[96000]
//                double output[191999]
// Return Type  : void
//
void CORRX(const short input1[10000], const short input2[96000], double output
           [191999])
{
  static creal_T dcv[262144];
  static creal_T dcv1[262144];
  static double c1[262144];
  static double b_costab[131073];
  static double b_sintab[131073];
  static double costab[131073];
  static double sintab[131073];
  static double b_input2[96000];
  double b_input1[10000];
  int i;
  coder::internal::FFTImplementationCallback::generate_twiddle_tables((costab),
    (sintab));
  coder::internal::FFTImplementationCallback::generate_twiddle_tables((b_costab),
    (b_sintab));
  std::memset(&dcv[0], 0, 262144U * sizeof(creal_T));
  for (i = 0; i < 10000; i++) {
    b_input1[i] = input1[i];
  }

  coder::internal::FFTImplementationCallback::doHalfLengthRadix2((b_input1), (0),
    (dcv), (costab), (sintab));
  std::memset(&dcv1[0], 0, 262144U * sizeof(creal_T));
  for (i = 0; i < 96000; i++) {
    b_input2[i] = input2[i];
  }

  coder::internal::FFTImplementationCallback::b_doHalfLengthRadix2((b_input2),
    (0), (dcv1), (b_costab), (b_sintab));
  for (i = 0; i < 262144; i++) {
    double d;
    double d1;
    double im;
    double re;
    re = dcv1[i].re;
    im = -dcv1[i].im;
    d = dcv[i].re;
    d1 = dcv[i].im;
    dcv1[i].re = d * re - d1 * im;
    dcv1[i].im = d * im + d1 * re;
  }

  coder::ifft(dcv1, dcv);
  for (i = 0; i < 262144; i++) {
    c1[i] = dcv[i].re;
  }

  std::memcpy(&output[0], &c1[166145], 95999U * sizeof(double));
  std::memcpy(&output[95999], &c1[0], 96000U * sizeof(double));
}

//
// File trailer for CORRX.cpp
//
// [EOF]
//
