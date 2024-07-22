//
// File: corrVova.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 08-Apr-2024 22:06:09
//

// Include Files
#include "corrVova.h"
#include "FFTImplementationCallback.h"
#include "fft.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <math.h>

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

//
// Arguments    : const coder::array<double, 1U> &input1
//                const coder::array<double, 1U> &input2
//                coder::array<double, 1U> &output
// Return Type  : void
//
void corrVova(const coder::array<double, 1U> &input1, const coder::array<double,
              1U> &input2, coder::array<double, 1U> &output)
{
  coder::array<creal_T, 1U> X;
  coder::array<creal_T, 1U> Y;
  coder::array<creal_T, 1U> b_Y;
  coder::array<creal_T, 1U> wwc;
  coder::array<creal_T, 1U> y;
  coder::array<double, 2U> costab;
  coder::array<double, 2U> costab1q;
  coder::array<double, 2U> sintab;
  coder::array<double, 2U> sintabinv;
  coder::array<double, 1U> b_c1;
  coder::array<double, 1U> c1;
  double Sn;
  double c0;
  double m2;
  int N2blue;
  int ceilLog2;
  int i;
  int m;
  int mxl;
  int n;
  int rt;
  int u1;
  rt = input1.size(0);
  u1 = input2.size(0);
  if (rt > u1) {
    u1 = rt;
  }

  rt = input1.size(0);
  m = input2.size(0);
  if (rt > m) {
    m = rt;
  }

  rt = u1 - 1;
  mxl = m - 1;
  if (rt < mxl) {
    mxl = rt;
  }

  c0 = frexp(std::abs(2.0 * static_cast<double>(m) - 1.0), &ceilLog2);
  if (c0 == 0.5) {
    ceilLog2--;
  }

  m2 = rt_powd_snf(2.0, static_cast<double>(ceilLog2));
  rt = input1.size(0);
  m = input2.size(0);
  if (rt > m) {
    m = rt;
  }

  rt = input1.size(0);
  n = input2.size(0);
  if (rt < n) {
    n = rt;
  }

  c0 = 2.0 * static_cast<double>(n) - 1.0;
  if (mxl <= n - 1) {
    Sn = static_cast<double>(mxl) * ((c0 - static_cast<double>(mxl)) - 1.0);
    if (mxl <= m - n) {
      c0 = (c0 + static_cast<double>(mxl) * c0) + Sn;
    } else {
      c0 = ((c0 + static_cast<double>(m - n) * c0) + (static_cast<double>(mxl) -
             static_cast<double>(m - n)) * (((static_cast<double>(m) -
               static_cast<double>(mxl)) + static_cast<double>(n)) - 2.0)) + Sn;
    }
  } else if (mxl <= m - 1) {
    Sn = (static_cast<double>(n) - 1.0) * (static_cast<double>(n) - 1.0);
    if (mxl <= m - n) {
      c0 = (c0 + static_cast<double>(mxl) * c0) + Sn;
    } else {
      c0 = ((c0 + static_cast<double>(m - n) * c0) + (static_cast<double>(mxl) -
             static_cast<double>(m - n)) * ((static_cast<double>(m - mxl) +
              static_cast<double>(n)) - 2.0)) + Sn;
    }
  } else {
    c0 = 2.0 * static_cast<double>(m) * static_cast<double>(n) - (static_cast<
      double>(static_cast<unsigned int>(m) + n) - 1.0);
  }

  if (c0 < m2 * (15.0 * static_cast<double>(ceilLog2) + 6.0)) {
    int k;
    int nInt2;
    m = input1.size(0);
    n = input2.size(0);
    rt = input1.size(0);
    ceilLog2 = input2.size(0);
    if (rt > ceilLog2) {
      ceilLog2 = rt;
    }

    nInt2 = ceilLog2 - 1;
    if (mxl < nInt2) {
      nInt2 = mxl;
    }

    c0 = 2.0 * static_cast<double>(nInt2) + 1.0;
    c1.set_size((static_cast<int>(c0)));
    rt = static_cast<int>(c0);
    for (i = 0; i < rt; i++) {
      c1[i] = 0.0;
    }

    for (k = 0; k <= nInt2; k++) {
      ceilLog2 = m - k;
      if (ceilLog2 >= n) {
        ceilLog2 = n;
      }

      c0 = 0.0;
      for (rt = 0; rt < ceilLog2; rt++) {
        c0 += input2[rt] * input1[k + rt];
      }

      c1[nInt2 + k] = c0;
    }

    for (k = 0; k < nInt2; k++) {
      ceilLog2 = (n - k) - 1;
      if (m < ceilLog2) {
        ceilLog2 = m;
      }

      c0 = 0.0;
      for (rt = 0; rt < ceilLog2; rt++) {
        c0 += input2[(k + rt) + 1] * input1[rt];
      }

      c1[(nInt2 - k) - 1] = c0;
    }
  } else {
    double im;
    int nfft;
    coder::fft(input1, m2, X);
    coder::fft(input2, m2, Y);
    rt = X.size(0);
    for (i = 0; i < rt; i++) {
      c0 = Y[i].re;
      Sn = -Y[i].im;
      im = X[i].re * Sn + X[i].im * c0;
      X[i].re = X[i].re * c0 - X[i].im * Sn;
      X[i].im = im;
    }

    nfft = X.size(0);
    if (X.size(0) == 0) {
      y.set_size(X.size(0));
      rt = X.size(0);
      for (i = 0; i < rt; i++) {
        y[i].re = 0.0;
        y[i].im = 0.0;
      }
    } else {
      int k;
      boolean_T useRadix2;
      useRadix2 = ((X.size(0) & (X.size(0) - 1)) == 0);
      coder::internal::FFTImplementationCallback::get_algo_sizes((X.size(0)),
        (useRadix2), (&N2blue), (&ceilLog2));
      c0 = 6.2831853071795862 / static_cast<double>(ceilLog2);
      n = ceilLog2 / 2 / 2;
      costab1q.set_size(1, (n + 1));
      costab1q[0] = 1.0;
      ceilLog2 = n / 2 - 1;
      for (k = 0; k <= ceilLog2; k++) {
        costab1q[k + 1] = std::cos(c0 * (static_cast<double>(k) + 1.0));
      }

      i = ceilLog2 + 2;
      ceilLog2 = n - 1;
      for (k = i; k <= ceilLog2; k++) {
        costab1q[k] = std::sin(c0 * static_cast<double>(n - k));
      }

      costab1q[n] = 0.0;
      if (!useRadix2) {
        n = costab1q.size(1) - 1;
        ceilLog2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (ceilLog2 + 1));
        sintab.set_size(1, (ceilLog2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        sintabinv.set_size(1, (ceilLog2 + 1));
        for (k = 0; k < n; k++) {
          sintabinv[k + 1] = costab1q[(n - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= ceilLog2; k++) {
          sintabinv[k] = costab1q[k - n];
        }

        for (k = 0; k < n; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = -costab1q[(n - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= ceilLog2; k++) {
          costab[k] = -costab1q[ceilLog2 - k];
          sintab[k] = -costab1q[k - n];
        }
      } else {
        n = costab1q.size(1) - 1;
        ceilLog2 = (costab1q.size(1) - 1) << 1;
        costab.set_size(1, (ceilLog2 + 1));
        sintab.set_size(1, (ceilLog2 + 1));
        costab[0] = 1.0;
        sintab[0] = 0.0;
        for (k = 0; k < n; k++) {
          costab[k + 1] = costab1q[k + 1];
          sintab[k + 1] = costab1q[(n - k) - 1];
        }

        i = costab1q.size(1);
        for (k = i; k <= ceilLog2; k++) {
          costab[k] = -costab1q[ceilLog2 - k];
          sintab[k] = costab1q[k - n];
        }

        sintabinv.set_size(1, 0);
      }

      if (useRadix2) {
        coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((X),
          (X.size(0)), (costab), (sintab), (y));
        if (y.size(0) > 1) {
          c0 = 1.0 / static_cast<double>(y.size(0));
          rt = y.size(0);
          for (i = 0; i < rt; i++) {
            y[i].re = c0 * y[i].re;
            y[i].im = c0 * y[i].im;
          }
        }
      } else {
        double nt_re;
        int nInt2;
        ceilLog2 = (X.size(0) + X.size(0)) - 1;
        wwc.set_size(ceilLog2);
        n = X.size(0);
        rt = 0;
        wwc[X.size(0) - 1].re = 1.0;
        wwc[X.size(0) - 1].im = 0.0;
        nInt2 = X.size(0) << 1;
        i = X.size(0);
        for (k = 0; k <= i - 2; k++) {
          m = ((k + 1) << 1) - 1;
          if (nInt2 - rt <= m) {
            rt += m - nInt2;
          } else {
            rt += m;
          }

          c0 = 3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
            (nfft);
          if (c0 == 0.0) {
            nt_re = 1.0;
            c0 = 0.0;
          } else {
            nt_re = std::cos(c0);
            c0 = std::sin(c0);
          }

          wwc[n - 2].re = nt_re;
          wwc[n - 2].im = -c0;
          n--;
        }

        n = 0;
        i = ceilLog2 - 1;
        for (k = i; k >= nfft; k--) {
          wwc[k] = wwc[n];
          n++;
        }

        y.set_size(X.size(0));
        ceilLog2 = X.size(0);
        rt = 0;
        for (k = 0; k < ceilLog2; k++) {
          nInt2 = (nfft + k) - 1;
          nt_re = wwc[nInt2].re;
          c0 = wwc[nInt2].im;
          y[k].re = nt_re * X[rt].re + c0 * X[rt].im;
          y[k].im = nt_re * X[rt].im - c0 * X[rt].re;
          rt++;
        }

        i = X.size(0) + 1;
        for (k = i; k <= nfft; k++) {
          y[k - 1].re = 0.0;
          y[k - 1].im = 0.0;
        }

        coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((y),
          (N2blue), (costab), (sintab), (Y));
        coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((wwc),
          (N2blue), (costab), (sintab), (b_Y));
        b_Y.set_size(Y.size(0));
        rt = Y.size(0);
        for (i = 0; i < rt; i++) {
          im = Y[i].re * b_Y[i].im + Y[i].im * b_Y[i].re;
          b_Y[i].re = Y[i].re * b_Y[i].re - Y[i].im * b_Y[i].im;
          b_Y[i].im = im;
        }

        coder::internal::FFTImplementationCallback::r2br_r2dit_trig_impl((b_Y),
          (N2blue), (costab), (sintabinv), (Y));
        if (Y.size(0) > 1) {
          c0 = 1.0 / static_cast<double>(Y.size(0));
          rt = Y.size(0);
          for (i = 0; i < rt; i++) {
            Y[i].re = c0 * Y[i].re;
            Y[i].im = c0 * Y[i].im;
          }
        }

        n = 0;
        nt_re = X.size(0);
        i = X.size(0);
        ceilLog2 = wwc.size(0);
        for (k = i; k <= ceilLog2; k++) {
          y[n].re = wwc[k - 1].re * Y[k - 1].re + wwc[k - 1].im * Y[k - 1].im;
          y[n].im = wwc[k - 1].re * Y[k - 1].im - wwc[k - 1].im * Y[k - 1].re;
          c0 = y[n].re;
          Sn = y[n].im;
          if (Sn == 0.0) {
            c0 /= nt_re;
            im = 0.0;
          } else if (c0 == 0.0) {
            c0 = 0.0;
            im = Sn / nt_re;
          } else {
            c0 /= nt_re;
            im = Sn / nt_re;
          }

          y[n].re = c0;
          y[n].im = im;
          n++;
        }
      }
    }

    b_c1.set_size(y.size(0));
    rt = y.size(0);
    for (i = 0; i < rt; i++) {
      b_c1[i] = y[i].re;
    }

    if (mxl < 1) {
      costab1q.set_size(1, 0);
    } else {
      rt = mxl - 1;
      costab1q.set_size(1, mxl);
      for (i = 0; i <= rt; i++) {
        costab1q[i] = static_cast<double>(i) + 1.0;
      }
    }

    if (1 > mxl + 1) {
      rt = -1;
    } else {
      rt = mxl;
    }

    m2 -= static_cast<double>(mxl);
    c1.set_size(((costab1q.size(1) + rt) + 1));
    ceilLog2 = costab1q.size(1);
    for (i = 0; i < ceilLog2; i++) {
      c1[i] = b_c1[static_cast<int>(m2 + costab1q[i]) - 1];
    }

    for (i = 0; i <= rt; i++) {
      c1[i + costab1q.size(1)] = b_c1[i];
    }
  }

  rt = static_cast<int>(2.0 * (static_cast<double>(u1) - 1.0) + 1.0);
  output.set_size(rt);
  for (i = 0; i < rt; i++) {
    output[i] = 0.0;
  }

  rt = c1.size(0);
  for (i = 0; i < rt; i++) {
    output[i] = c1[i];
  }
}

//
// File trailer for corrVova.cpp
//
// [EOF]
//
