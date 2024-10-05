//
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 03-Oct-2024 23:06:12
//

// Include Files
#include "FFTImplementationCallback.h"
#include <cmath>

// Function Definitions
//
// Arguments    : int bitrevIndex[524288]
// Return Type  : void
//
namespace coder
{
  namespace internal
  {
    void FFTImplementationCallback::get_bitrevIndex(int bitrevIndex[524288])
    {
      int iy;
      int ju;
      ju = 0;
      iy = 1;
      for (int b_j1 = 0; b_j1 < 524287; b_j1++) {
        boolean_T tst;
        bitrevIndex[b_j1] = iy;
        iy = 524288;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }

        iy = ju + 1;
      }

      bitrevIndex[524287] = iy;
    }

    //
    // Arguments    : creal_T y[1048576]
    //                int yoff
    //                const creal_T reconVar1[524288]
    //                const creal_T reconVar2[524288]
    //                const int wrapIndex[524288]
    //                int hnRows
    // Return Type  : void
    //
    void FFTImplementationCallback::getback_radix2_fft(creal_T y[1048576], int
      yoff, const creal_T reconVar1[524288], const creal_T reconVar2[524288],
      const int wrapIndex[524288], int hnRows)
    {
      double d;
      double d1;
      double temp1_im;
      double temp1_re;
      double temp2_im;
      double temp2_re;
      int i;
      int iterVar;
      int temp1_re_tmp;
      iterVar = hnRows / 2;
      temp2_re = y[yoff].re;
      temp1_im = y[yoff].im;
      temp2_im = y[yoff].re * reconVar1[0].im + y[yoff].im * reconVar1[0].re;
      temp1_re = -y[yoff].im;
      d = temp2_re * reconVar2[0].re;
      y[yoff].re = 0.5 * ((y[yoff].re * reconVar1[0].re - y[yoff].im *
                           reconVar1[0].im) + (d - temp1_re * reconVar2[0].im));
      d1 = temp2_re * reconVar2[0].im;
      y[yoff].im = 0.5 * (temp2_im + (d1 + temp1_re * reconVar2[0].re));
      i = yoff + hnRows;
      y[i].re = 0.5 * ((d - temp1_im * reconVar2[0].im) + (temp2_re * reconVar1
        [0].re - -temp1_im * reconVar1[0].im));
      y[i].im = 0.5 * ((d1 + temp1_im * reconVar2[0].re) + (temp2_re *
        reconVar1[0].im + -temp1_im * reconVar1[0].re));
      for (int b_i = 2; b_i <= iterVar; b_i++) {
        int b_temp2_re_tmp_tmp;
        int temp2_re_tmp_tmp;
        temp1_re_tmp = (yoff + b_i) - 1;
        temp1_re = y[temp1_re_tmp].re;
        temp1_im = y[temp1_re_tmp].im;
        temp2_re_tmp_tmp = wrapIndex[b_i - 1];
        b_temp2_re_tmp_tmp = yoff + temp2_re_tmp_tmp;
        temp2_re = y[b_temp2_re_tmp_tmp - 1].re;
        temp2_im = y[b_temp2_re_tmp_tmp - 1].im;
        y[temp1_re_tmp].re = 0.5 * ((temp1_re * reconVar1[b_i - 1].re - temp1_im
          * reconVar1[b_i - 1].im) + (temp2_re * reconVar2[b_i - 1].re -
          -temp2_im * reconVar2[b_i - 1].im));
        y[temp1_re_tmp].im = 0.5 * ((temp1_re * reconVar1[b_i - 1].im + temp1_im
          * reconVar1[b_i - 1].re) + (temp2_re * reconVar2[b_i - 1].im +
          -temp2_im * reconVar2[b_i - 1].re));
        temp1_re_tmp = (i + b_i) - 1;
        y[temp1_re_tmp].re = 0.5 * ((temp1_re * reconVar2[b_i - 1].re - temp1_im
          * reconVar2[b_i - 1].im) + (temp2_re * reconVar1[b_i - 1].re -
          -temp2_im * reconVar1[b_i - 1].im));
        y[temp1_re_tmp].im = 0.5 * ((temp1_re * reconVar2[b_i - 1].im + temp1_im
          * reconVar2[b_i - 1].re) + (temp2_re * reconVar1[b_i - 1].im +
          -temp2_im * reconVar1[b_i - 1].re));
        y[b_temp2_re_tmp_tmp - 1].re = 0.5 * ((temp2_re *
          reconVar1[temp2_re_tmp_tmp - 1].re - temp2_im *
          reconVar1[temp2_re_tmp_tmp - 1].im) + (temp1_re *
          reconVar2[temp2_re_tmp_tmp - 1].re - -temp1_im *
          reconVar2[temp2_re_tmp_tmp - 1].im));
        y[b_temp2_re_tmp_tmp - 1].im = 0.5 * ((temp2_re *
          reconVar1[temp2_re_tmp_tmp - 1].im + temp2_im *
          reconVar1[temp2_re_tmp_tmp - 1].re) + (temp1_re *
          reconVar2[temp2_re_tmp_tmp - 1].im + -temp1_im *
          reconVar2[temp2_re_tmp_tmp - 1].re));
        temp1_re_tmp = (b_temp2_re_tmp_tmp + hnRows) - 1;
        y[temp1_re_tmp].re = 0.5 * ((temp2_re * reconVar2[temp2_re_tmp_tmp - 1].
          re - temp2_im * reconVar2[temp2_re_tmp_tmp - 1].im) + (temp1_re *
          reconVar1[temp2_re_tmp_tmp - 1].re - -temp1_im *
          reconVar1[temp2_re_tmp_tmp - 1].im));
        y[temp1_re_tmp].im = 0.5 * ((temp2_re * reconVar2[temp2_re_tmp_tmp - 1].
          im + temp2_im * reconVar2[temp2_re_tmp_tmp - 1].re) + (temp1_re *
          reconVar1[temp2_re_tmp_tmp - 1].im + -temp1_im *
          reconVar1[temp2_re_tmp_tmp - 1].re));
      }

      if (iterVar != 0) {
        temp1_re_tmp = yoff + iterVar;
        temp1_re = y[temp1_re_tmp].re;
        temp1_im = y[temp1_re_tmp].im;
        d = temp1_re * reconVar2[iterVar].re;
        d1 = temp1_re * reconVar1[iterVar].re;
        y[temp1_re_tmp].re = 0.5 * ((d1 - temp1_im * reconVar1[iterVar].im) + (d
          - -temp1_im * reconVar2[iterVar].im));
        temp2_im = temp1_re * reconVar2[iterVar].im;
        temp2_re = temp1_re * reconVar1[iterVar].im;
        y[temp1_re_tmp].im = 0.5 * ((temp2_re + temp1_im * reconVar1[iterVar].re)
          + (temp2_im + -temp1_im * reconVar2[iterVar].re));
        i += iterVar;
        y[i].re = 0.5 * ((d - temp1_im * reconVar2[iterVar].im) + (d1 -
          -temp1_im * reconVar1[iterVar].im));
        y[i].im = 0.5 * ((temp2_im + temp1_im * reconVar2[iterVar].re) +
                         (temp2_re + -temp1_im * reconVar1[iterVar].re));
      }
    }

    //
    // Arguments    : const double x[300000]
    //                int xoffInit
    //                creal_T y[1048576]
    //                const double costab[524289]
    //                const double sintab[524289]
    // Return Type  : void
    //
    void FFTImplementationCallback::b_doHalfLengthRadix2(const double x[300000],
      int xoffInit, creal_T y[1048576], const double costab[524289], const
      double sintab[524289])
    {
      static creal_T reconVar1[524288];
      static creal_T reconVar2[524288];
      static double hcostab[262144];
      static double hsintab[262144];
      static int bitrevIndex[524288];
      static int wrapIndex[524288];
      double temp_im;
      double temp_re;
      int i;
      int iDelta2;
      int iheight;
      int ix;
      int j;
      int k;
      for (i = 0; i < 262144; i++) {
        ix = ((i + 1) << 1) - 2;
        hcostab[i] = costab[ix];
        hsintab[i] = sintab[ix];
      }

      for (i = 0; i < 524288; i++) {
        temp_re = sintab[i];
        reconVar1[i].re = temp_re + 1.0;
        temp_im = costab[i];
        reconVar1[i].im = -temp_im;
        reconVar2[i].re = 1.0 - temp_re;
        reconVar2[i].im = temp_im;
        if (i + 1 != 1) {
          wrapIndex[i] = 524289 - i;
        } else {
          wrapIndex[0] = 1;
        }
      }

      FFTImplementationCallback::get_bitrevIndex((bitrevIndex));
      ix = xoffInit;
      for (i = 0; i < 150000; i++) {
        iDelta2 = bitrevIndex[i];
        y[iDelta2 - 1].re = x[ix];
        y[iDelta2 - 1].im = x[ix + 1];
        ix += 2;
      }

      for (i = 0; i <= 524286; i += 2) {
        temp_re = y[i + 1].re;
        temp_im = y[i + 1].im;
        y[i + 1].re = y[i].re - y[i + 1].re;
        y[i + 1].im = y[i].im - y[i + 1].im;
        y[i].re += temp_re;
        y[i].im += temp_im;
      }

      ix = 2;
      iDelta2 = 4;
      k = 131072;
      iheight = 524285;
      while (k > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += iDelta2) {
          temp_re_tmp = i + ix;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = k; j < 262144; j += k) {
          double twid_im;
          double twid_re;
          int ihi;
          twid_re = hcostab[j];
          twid_im = hsintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + ix;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += iDelta2;
          }

          istart++;
        }

        k /= 2;
        ix = iDelta2;
        iDelta2 += iDelta2;
        iheight -= ix;
      }

      FFTImplementationCallback::getback_radix2_fft((y), (0), (reconVar1),
        (reconVar2), (wrapIndex), (524288));
    }

    //
    // Arguments    : const double x[25000]
    //                int xoffInit
    //                creal_T y[1048576]
    //                const double costab[524289]
    //                const double sintab[524289]
    // Return Type  : void
    //
    void FFTImplementationCallback::doHalfLengthRadix2(const double x[25000],
      int xoffInit, creal_T y[1048576], const double costab[524289], const
      double sintab[524289])
    {
      static creal_T reconVar1[524288];
      static creal_T reconVar2[524288];
      static double hcostab[262144];
      static double hsintab[262144];
      static int bitrevIndex[524288];
      static int wrapIndex[524288];
      double temp_im;
      double temp_re;
      int i;
      int iDelta2;
      int iheight;
      int ix;
      int j;
      int k;
      for (i = 0; i < 262144; i++) {
        ix = ((i + 1) << 1) - 2;
        hcostab[i] = costab[ix];
        hsintab[i] = sintab[ix];
      }

      for (i = 0; i < 524288; i++) {
        temp_re = sintab[i];
        reconVar1[i].re = temp_re + 1.0;
        temp_im = costab[i];
        reconVar1[i].im = -temp_im;
        reconVar2[i].re = 1.0 - temp_re;
        reconVar2[i].im = temp_im;
        if (i + 1 != 1) {
          wrapIndex[i] = 524289 - i;
        } else {
          wrapIndex[0] = 1;
        }
      }

      FFTImplementationCallback::get_bitrevIndex((bitrevIndex));
      ix = xoffInit;
      for (i = 0; i < 12500; i++) {
        iDelta2 = bitrevIndex[i];
        y[iDelta2 - 1].re = x[ix];
        y[iDelta2 - 1].im = x[ix + 1];
        ix += 2;
      }

      for (i = 0; i <= 524286; i += 2) {
        temp_re = y[i + 1].re;
        temp_im = y[i + 1].im;
        y[i + 1].re = y[i].re - y[i + 1].re;
        y[i + 1].im = y[i].im - y[i + 1].im;
        y[i].re += temp_re;
        y[i].im += temp_im;
      }

      ix = 2;
      iDelta2 = 4;
      k = 131072;
      iheight = 524285;
      while (k > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += iDelta2) {
          temp_re_tmp = i + ix;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = k; j < 262144; j += k) {
          double twid_im;
          double twid_re;
          int ihi;
          twid_re = hcostab[j];
          twid_im = hsintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + ix;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += iDelta2;
          }

          istart++;
        }

        k /= 2;
        ix = iDelta2;
        iDelta2 += iDelta2;
        iheight -= ix;
      }

      FFTImplementationCallback::getback_radix2_fft((y), (0), (reconVar1),
        (reconVar2), (wrapIndex), (524288));
    }

    //
    // Arguments    : double costab[524289]
    //                double sintab[524289]
    // Return Type  : void
    //
    void FFTImplementationCallback::generate_twiddle_tables(double costab[524289],
      double sintab[524289])
    {
      static double costab1q[262145];
      int k;
      costab1q[0] = 1.0;
      for (k = 0; k < 131072; k++) {
        costab1q[k + 1] = std::cos(5.9921124526782858E-6 * (static_cast<double>
          (k) + 1.0));
      }

      for (k = 0; k < 131071; k++) {
        costab1q[k + 131073] = std::sin(5.9921124526782858E-6 * (262144.0 - (
          static_cast<double>(k) + 131073.0)));
      }

      costab1q[262144] = 0.0;
      costab[0] = 1.0;
      sintab[0] = 0.0;
      for (k = 0; k < 262144; k++) {
        double costab_tmp;
        double sintab_tmp;
        costab_tmp = costab1q[k + 1];
        costab[k + 1] = costab_tmp;
        sintab_tmp = -costab1q[262143 - k];
        sintab[k + 1] = sintab_tmp;
        costab[k + 262145] = sintab_tmp;
        sintab[k + 262145] = -costab_tmp;
      }
    }

    //
    // Arguments    : const creal_T x[1048576]
    //                const double costab[524289]
    //                const double sintab[524289]
    //                creal_T y[1048576]
    // Return Type  : void
    //
    void FFTImplementationCallback::r2br_r2dit_trig(const creal_T x[1048576],
      const double costab[524289], const double sintab[524289], creal_T y
      [1048576])
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iheight;
      int ix;
      int iy;
      int j;
      int ju;
      ix = 0;
      iy = 0;
      ju = 0;
      for (i = 0; i < 1048575; i++) {
        boolean_T tst;
        y[iy] = x[ix];
        iy = 1048576;
        tst = true;
        while (tst) {
          iy >>= 1;
          ju ^= iy;
          tst = ((ju & iy) == 0);
        }

        iy = ju;
        ix++;
      }

      y[iy] = x[ix];
      for (i = 0; i <= 1048574; i += 2) {
        double im;
        double re;
        twid_re = y[i + 1].re;
        temp_re = twid_re;
        twid_im = y[i + 1].im;
        temp_im = twid_im;
        re = y[i].re;
        im = y[i].im;
        twid_re = re - twid_re;
        y[i + 1].re = twid_re;
        twid_im = im - twid_im;
        y[i + 1].im = twid_im;
        y[i].re = re + temp_re;
        y[i].im = im + temp_im;
      }

      iy = 2;
      ix = 4;
      ju = 262144;
      iheight = 1048573;
      while (ju > 0) {
        int istart;
        int temp_re_tmp;
        for (i = 0; i < iheight; i += ix) {
          temp_re_tmp = i + iy;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re += temp_re;
          y[i].im += temp_im;
        }

        istart = 1;
        for (j = ju; j < 524288; j += ju) {
          int ihi;
          twid_re = costab[j];
          twid_im = sintab[j];
          i = istart;
          ihi = istart + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iy;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re += temp_re;
            y[i].im += temp_im;
            i += ix;
          }

          istart++;
        }

        ju /= 2;
        iy = ix;
        ix += ix;
        iheight -= iy;
      }

      for (iy = 0; iy < 1048576; iy++) {
        y[iy].re *= 9.5367431640625E-7;
        y[iy].im *= 9.5367431640625E-7;
      }
    }
  }
}

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
