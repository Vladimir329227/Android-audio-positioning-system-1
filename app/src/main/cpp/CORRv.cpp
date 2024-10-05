//
// File: CORRv.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 03-Oct-2024 23:06:12
//

// Include Files
#include "CORRv.h"
#include "FFTImplementationCallback.h"
#include "ifft.h"
#include <cstring>

// Function Definitions
//
// Arguments    : const short input1[25000]
//                const short input2[300000]
//                double output[599999]
// Return Type  : void
//
void CORRv(const short input1[25000], const short input2[300000], double output
           [599999])
{
  static creal_T dcv[1048576];
  static creal_T dcv1[1048576];
  static double c1[1048576];
  static double b_costab[524289];
  static double b_sintab[524289];
  static double costab[524289];
  static double sintab[524289];
  static double b_input2[300000];
  static double b_input1[25000];
  int i;
  coder::internal::FFTImplementationCallback::generate_twiddle_tables((costab),
    (sintab));
  coder::internal::FFTImplementationCallback::generate_twiddle_tables((b_costab),
    (b_sintab));
  std::memset(&dcv[0], 0, 1048576U * sizeof(creal_T));
  for (i = 0; i < 25000; i++) {
    b_input1[i] = input1[i];
  }

  coder::internal::FFTImplementationCallback::doHalfLengthRadix2((b_input1), (0),
    (dcv), (costab), (sintab));
  std::memset(&dcv1[0], 0, 1048576U * sizeof(creal_T));
  for (i = 0; i < 300000; i++) {
    b_input2[i] = input2[i];
  }

  coder::internal::FFTImplementationCallback::b_doHalfLengthRadix2((b_input2),
    (0), (dcv1), (b_costab), (b_sintab));
  for (i = 0; i < 1048576; i++) {
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
  for (i = 0; i < 1048576; i++) {
    c1[i] = dcv[i].re;
  }

  std::memcpy(&output[0], &c1[748577], 299999U * sizeof(double));
  std::memcpy(&output[299999], &c1[0], 300000U * sizeof(double));
}

//
// File trailer for CORRv.cpp
//
// [EOF]
//
