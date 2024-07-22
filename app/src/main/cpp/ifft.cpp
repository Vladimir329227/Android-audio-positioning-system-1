//
// File: ifft.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 22-Jul-2024 14:53:53
//

// Include Files
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const creal_T x[262144]
//                creal_T y[262144]
// Return Type  : void
//
namespace coder
{
  void ifft(const creal_T x[262144], creal_T y[262144])
  {
    static double costab[131073];
    static double sintab[131073];
    static double costab1q[65537];
    int k;
    costab1q[0] = 1.0;
    for (k = 0; k < 32768; k++) {
      costab1q[k + 1] = std::cos(2.3968449810713143E-5 * (static_cast<double>(k)
        + 1.0));
    }

    for (k = 0; k < 32767; k++) {
      costab1q[k + 32769] = std::sin(2.3968449810713143E-5 * (65536.0 - (
        static_cast<double>(k) + 32769.0)));
    }

    costab1q[65536] = 0.0;
    costab[0] = 1.0;
    sintab[0] = 0.0;
    for (k = 0; k < 65536; k++) {
      double costab_tmp;
      double sintab_tmp;
      costab_tmp = costab1q[k + 1];
      costab[k + 1] = costab_tmp;
      sintab_tmp = costab1q[65535 - k];
      sintab[k + 1] = sintab_tmp;
      costab[k + 65537] = -sintab_tmp;
      sintab[k + 65537] = costab_tmp;
    }

    internal::FFTImplementationCallback::r2br_r2dit_trig((x), (costab), (sintab),
      (y));
  }
}

//
// File trailer for ifft.cpp
//
// [EOF]
//
