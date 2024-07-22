//
// File: FFTImplementationCallback.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 08-Apr-2024 22:06:09
//

// Include Files
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<creal_T, 1U> &y
//                int nrowsx
//                int nRows
//                int nfft
//                const ::coder::array<creal_T, 1U> &wwc
//                const ::coder::array<double, 2U> &costab
//                const ::coder::array<double, 2U> &sintab
//                const ::coder::array<double, 2U> &costabinv
//                const ::coder::array<double, 2U> &sintabinv
// Return Type  : void
//
namespace coder
{
  namespace internal
  {
    void FFTImplementationCallback::doHalfLengthBluestein(const ::coder::array<
      double, 1U> &x, ::coder::array<creal_T, 1U> &y, int nrowsx, int nRows, int
      nfft, const ::coder::array<creal_T, 1U> &wwc, const ::coder::array<double,
      2U> &costab, const ::coder::array<double, 2U> &sintab, const ::coder::
      array<double, 2U> &costabinv, const ::coder::array<double, 2U> &sintabinv)
    {
      array<creal_T, 1U> fv;
      array<creal_T, 1U> fy;
      array<creal_T, 1U> reconVar1;
      array<creal_T, 1U> reconVar2;
      array<creal_T, 1U> ytmp;
      array<double, 2U> b_costab;
      array<double, 2U> b_sintab;
      array<double, 2U> costab1q;
      array<double, 2U> hcostabinv;
      array<double, 2U> hsintab;
      array<double, 2U> hsintabinv;
      array<int, 2U> wrapIndex;
      double e;
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      double z;
      int hnRows;
      int i;
      int iDelta2;
      int ihi;
      int ix;
      int j;
      int ju;
      int k;
      int nRowsD2;
      int nd2;
      int temp_re_tmp;
      boolean_T tst;
      hnRows = nRows / 2;
      ytmp.set_size(hnRows);
      if (hnRows > nrowsx) {
        ytmp.set_size(hnRows);
        for (iDelta2 = 0; iDelta2 < hnRows; iDelta2++) {
          ytmp[iDelta2].re = 0.0;
          ytmp[iDelta2].im = 0.0;
        }
      }

      if ((x.size(0) & 1) == 0) {
        tst = true;
        ju = x.size(0);
      } else if (x.size(0) >= nRows) {
        tst = true;
        ju = nRows;
      } else {
        tst = false;
        ju = x.size(0) - 1;
      }

      if (ju >= nRows) {
        ju = nRows;
      }

      nd2 = nRows << 1;
      e = 6.2831853071795862 / static_cast<double>(nd2);
      ihi = nd2 / 2 / 2;
      costab1q.set_size(1, (ihi + 1));
      costab1q[0] = 1.0;
      nd2 = ihi / 2 - 1;
      for (k = 0; k <= nd2; k++) {
        costab1q[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
      }

      iDelta2 = nd2 + 2;
      nd2 = ihi - 1;
      for (k = iDelta2; k <= nd2; k++) {
        costab1q[k] = std::sin(e * static_cast<double>(ihi - k));
      }

      costab1q[ihi] = 0.0;
      ihi = costab1q.size(1) - 1;
      nd2 = (costab1q.size(1) - 1) << 1;
      b_costab.set_size(1, (nd2 + 1));
      b_sintab.set_size(1, (nd2 + 1));
      b_costab[0] = 1.0;
      b_sintab[0] = 0.0;
      for (k = 0; k < ihi; k++) {
        b_costab[k + 1] = costab1q[k + 1];
        b_sintab[k + 1] = -costab1q[(ihi - k) - 1];
      }

      iDelta2 = costab1q.size(1);
      for (k = iDelta2; k <= nd2; k++) {
        b_costab[k] = -costab1q[nd2 - k];
        b_sintab[k] = -costab1q[k - ihi];
      }

      nd2 = costab.size(1) / 2;
      costab1q.set_size(1, nd2);
      hsintab.set_size(1, nd2);
      hcostabinv.set_size(1, nd2);
      hsintabinv.set_size(1, nd2);
      for (i = 0; i < nd2; i++) {
        iDelta2 = ((i + 1) << 1) - 2;
        costab1q[i] = costab[iDelta2];
        hsintab[i] = sintab[iDelta2];
        hcostabinv[i] = costabinv[iDelta2];
        hsintabinv[i] = sintabinv[iDelta2];
      }

      reconVar1.set_size(hnRows);
      reconVar2.set_size(hnRows);
      nd2 = 0;
      wrapIndex.set_size(1, hnRows);
      for (i = 0; i < hnRows; i++) {
        reconVar1[i].re = b_sintab[nd2] + 1.0;
        reconVar1[i].im = -b_costab[nd2];
        reconVar2[i].re = 1.0 - b_sintab[nd2];
        reconVar2[i].im = b_costab[nd2];
        nd2 += 2;
        if (i + 1 != 1) {
          wrapIndex[i] = (hnRows - i) + 1;
        } else {
          wrapIndex[0] = 1;
        }
      }

      nd2 = 0;
      e = static_cast<double>(ju) / 2.0;
      iDelta2 = static_cast<int>(e);
      for (ix = 0; ix < iDelta2; ix++) {
        temp_re_tmp = (hnRows + ix) - 1;
        temp_re = wwc[temp_re_tmp].re;
        temp_im = wwc[temp_re_tmp].im;
        twid_re = x[nd2];
        twid_im = x[nd2 + 1];
        ytmp[ix].re = temp_re * twid_re + temp_im * twid_im;
        ytmp[ix].im = temp_re * twid_im - temp_im * twid_re;
        nd2 += 2;
      }

      if (!tst) {
        temp_re_tmp = (hnRows + static_cast<int>(e)) - 1;
        temp_re = wwc[temp_re_tmp].re;
        temp_im = wwc[temp_re_tmp].im;
        twid_re = x[nd2];
        ytmp[static_cast<int>(static_cast<double>(ju) / 2.0)].re = temp_re *
          twid_re + temp_im * 0.0;
        ytmp[static_cast<int>(static_cast<double>(ju) / 2.0)].im = temp_re * 0.0
          - temp_im * twid_re;
        if (static_cast<int>(e) + 2 <= hnRows) {
          iDelta2 = static_cast<int>(static_cast<double>(ju) / 2.0) + 2;
          for (i = iDelta2; i <= hnRows; i++) {
            ytmp[i - 1].re = 0.0;
            ytmp[i - 1].im = 0.0;
          }
        }
      } else {
        if (static_cast<int>(e) + 1 <= hnRows) {
          iDelta2 = static_cast<int>(static_cast<double>(ju) / 2.0) + 1;
          for (i = iDelta2; i <= hnRows; i++) {
            ytmp[i - 1].re = 0.0;
            ytmp[i - 1].im = 0.0;
          }
        }
      }

      z = static_cast<double>(nfft) / 2.0;
      fy.set_size((static_cast<int>(z)));
      if (static_cast<int>(z) > ytmp.size(0)) {
        nd2 = static_cast<int>(z);
        fy.set_size((static_cast<int>(z)));
        for (iDelta2 = 0; iDelta2 < nd2; iDelta2++) {
          fy[iDelta2].re = 0.0;
          fy[iDelta2].im = 0.0;
        }
      }

      ju = ytmp.size(0);
      j = static_cast<int>(z);
      if (ju < j) {
        j = ju;
      }

      iDelta2 = static_cast<int>(z) - 2;
      nRowsD2 = static_cast<int>(z) / 2;
      k = nRowsD2 / 2;
      ix = 0;
      nd2 = 0;
      ju = 0;
      for (i = 0; i <= j - 2; i++) {
        fy[nd2] = ytmp[ix];
        ihi = static_cast<int>(z);
        tst = true;
        while (tst) {
          ihi >>= 1;
          ju ^= ihi;
          tst = ((ju & ihi) == 0);
        }

        nd2 = ju;
        ix++;
      }

      fy[nd2] = ytmp[ix];
      if (static_cast<int>(z) > 1) {
        for (i = 0; i <= iDelta2; i += 2) {
          temp_re = fy[i + 1].re;
          temp_im = fy[i + 1].im;
          e = fy[i].re;
          twid_re = fy[i].im;
          fy[i + 1].re = fy[i].re - fy[i + 1].re;
          fy[i + 1].im = fy[i].im - fy[i + 1].im;
          e += temp_re;
          twid_re += temp_im;
          fy[i].re = e;
          fy[i].im = twid_re;
        }
      }

      nd2 = 2;
      iDelta2 = 4;
      ix = ((k - 1) << 2) + 1;
      while (k > 0) {
        for (i = 0; i < ix; i += iDelta2) {
          temp_re_tmp = i + nd2;
          temp_re = fy[temp_re_tmp].re;
          temp_im = fy[temp_re_tmp].im;
          fy[temp_re_tmp].re = fy[i].re - temp_re;
          fy[temp_re_tmp].im = fy[i].im - temp_im;
          fy[i].re = fy[i].re + temp_re;
          fy[i].im = fy[i].im + temp_im;
        }

        ju = 1;
        for (j = k; j < nRowsD2; j += k) {
          twid_re = costab1q[j];
          twid_im = hsintab[j];
          i = ju;
          ihi = ju + ix;
          while (i < ihi) {
            temp_re_tmp = i + nd2;
            temp_re = twid_re * fy[temp_re_tmp].re - twid_im * fy[temp_re_tmp].
              im;
            temp_im = twid_re * fy[temp_re_tmp].im + twid_im * fy[temp_re_tmp].
              re;
            fy[temp_re_tmp].re = fy[i].re - temp_re;
            fy[temp_re_tmp].im = fy[i].im - temp_im;
            fy[i].re = fy[i].re + temp_re;
            fy[i].im = fy[i].im + temp_im;
            i += iDelta2;
          }

          ju++;
        }

        k /= 2;
        nd2 = iDelta2;
        iDelta2 += iDelta2;
        ix -= nd2;
      }

      FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (static_cast<int>(
        static_cast<double>(nfft) / 2.0)), (costab1q), (hsintab), (fv));
      nd2 = fy.size(0);
      for (iDelta2 = 0; iDelta2 < nd2; iDelta2++) {
        twid_re = fy[iDelta2].re * fv[iDelta2].im + fy[iDelta2].im * fv[iDelta2]
          .re;
        fy[iDelta2].re = fy[iDelta2].re * fv[iDelta2].re - fy[iDelta2].im *
          fv[iDelta2].im;
        fy[iDelta2].im = twid_re;
      }

      FFTImplementationCallback::r2br_r2dit_trig_impl((fy), (static_cast<int>(z)),
        (hcostabinv), (hsintabinv), (fv));
      if (fv.size(0) > 1) {
        e = 1.0 / static_cast<double>(fv.size(0));
        nd2 = fv.size(0);
        for (iDelta2 = 0; iDelta2 < nd2; iDelta2++) {
          fv[iDelta2].re = e * fv[iDelta2].re;
          fv[iDelta2].im = e * fv[iDelta2].im;
        }
      }

      nd2 = 0;
      iDelta2 = wwc.size(0);
      for (k = hnRows; k <= iDelta2; k++) {
        ytmp[nd2].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].
          im;
        ytmp[nd2].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].
          re;
        nd2++;
      }

      for (i = 0; i < hnRows; i++) {
        iDelta2 = wrapIndex[i];
        e = ytmp[iDelta2 - 1].re;
        twid_re = -ytmp[iDelta2 - 1].im;
        y[i].re = 0.5 * ((ytmp[i].re * reconVar1[i].re - ytmp[i].im *
                          reconVar1[i].im) + (e * reconVar2[i].re - twid_re *
          reconVar2[i].im));
        y[i].im = 0.5 * ((ytmp[i].re * reconVar1[i].im + ytmp[i].im *
                          reconVar1[i].re) + (e * reconVar2[i].im + twid_re *
          reconVar2[i].re));
        iDelta2 = hnRows + i;
        y[iDelta2].re = 0.5 * ((ytmp[i].re * reconVar2[i].re - ytmp[i].im *
          reconVar2[i].im) + (e * reconVar1[i].re - twid_re * reconVar1[i].im));
        y[iDelta2].im = 0.5 * ((ytmp[i].re * reconVar2[i].im + ytmp[i].im *
          reconVar2[i].re) + (e * reconVar1[i].im + twid_re * reconVar1[i].re));
      }
    }

    //
    // Arguments    : const ::coder::array<double, 1U> &x
    //                ::coder::array<creal_T, 1U> &y
    //                int unsigned_nRows
    //                const ::coder::array<double, 2U> &costab
    //                const ::coder::array<double, 2U> &sintab
    // Return Type  : void
    //
    void FFTImplementationCallback::doHalfLengthRadix2(const ::coder::array<
      double, 1U> &x, ::coder::array<creal_T, 1U> &y, int unsigned_nRows, const ::
      coder::array<double, 2U> &costab, const ::coder::array<double, 2U> &sintab)
    {
      array<creal_T, 1U> reconVar1;
      array<creal_T, 1U> reconVar2;
      array<double, 2U> hcostab;
      array<double, 2U> hsintab;
      array<int, 2U> wrapIndex;
      array<int, 1U> bitrevIndex;
      double temp2_im;
      double temp2_re;
      double temp_im;
      double temp_re;
      double y_im;
      double y_im_tmp;
      double z;
      int hszCostab;
      int i;
      int ihi;
      int istart;
      int iy;
      int ju;
      int k;
      int nRows;
      int nRowsD2;
      int nRowsM2;
      boolean_T tst;
      nRows = unsigned_nRows / 2;
      ihi = y.size(0);
      if (ihi >= nRows) {
        ihi = nRows;
      }

      nRowsM2 = nRows - 2;
      nRowsD2 = nRows / 2;
      k = nRowsD2 / 2;
      hszCostab = costab.size(1) / 2;
      hcostab.set_size(1, hszCostab);
      hsintab.set_size(1, hszCostab);
      for (i = 0; i < hszCostab; i++) {
        iy = ((i + 1) << 1) - 2;
        hcostab[i] = costab[iy];
        hsintab[i] = sintab[iy];
      }

      reconVar1.set_size(nRows);
      reconVar2.set_size(nRows);
      wrapIndex.set_size(1, nRows);
      for (i = 0; i < nRows; i++) {
        temp2_im = sintab[i];
        temp2_re = costab[i];
        reconVar1[i].re = temp2_im + 1.0;
        reconVar1[i].im = -temp2_re;
        reconVar2[i].re = 1.0 - temp2_im;
        reconVar2[i].im = temp2_re;
        if (i + 1 != 1) {
          wrapIndex[i] = (nRows - i) + 1;
        } else {
          wrapIndex[0] = 1;
        }
      }

      z = static_cast<double>(unsigned_nRows) / 2.0;
      ju = 0;
      iy = 1;
      bitrevIndex.set_size((static_cast<int>(z)));
      hszCostab = static_cast<int>(z);
      for (istart = 0; istart < hszCostab; istart++) {
        bitrevIndex[istart] = 0;
      }

      for (istart = 0; istart <= ihi - 2; istart++) {
        bitrevIndex[istart] = iy;
        hszCostab = static_cast<int>(z);
        tst = true;
        while (tst) {
          hszCostab >>= 1;
          ju ^= hszCostab;
          tst = ((ju & hszCostab) == 0);
        }

        iy = ju + 1;
      }

      bitrevIndex[ihi - 1] = iy;
      if ((x.size(0) & 1) == 0) {
        tst = true;
        ihi = x.size(0);
      } else if (x.size(0) >= unsigned_nRows) {
        tst = true;
        ihi = unsigned_nRows;
      } else {
        tst = false;
        ihi = x.size(0) - 1;
      }

      hszCostab = 0;
      if (ihi >= unsigned_nRows) {
        ihi = unsigned_nRows;
      }

      temp2_im = static_cast<double>(ihi) / 2.0;
      istart = static_cast<int>(temp2_im);
      for (i = 0; i < istart; i++) {
        y[bitrevIndex[i] - 1].re = x[hszCostab];
        y[bitrevIndex[i] - 1].im = x[hszCostab + 1];
        hszCostab += 2;
      }

      if (!tst) {
        istart = bitrevIndex[static_cast<int>(temp2_im)] - 1;
        y[istart].re = x[hszCostab];
        y[istart].im = 0.0;
      }

      if (nRows > 1) {
        for (i = 0; i <= nRowsM2; i += 2) {
          temp_re = y[i + 1].re;
          temp_im = y[i + 1].im;
          y[i + 1].re = y[i].re - y[i + 1].re;
          y[i + 1].im = y[i].im - y[i + 1].im;
          y[i].re = y[i].re + temp_re;
          y[i].im = y[i].im + temp_im;
        }
      }

      hszCostab = 2;
      iy = 4;
      ju = ((k - 1) << 2) + 1;
      while (k > 0) {
        for (i = 0; i < ju; i += iy) {
          nRowsM2 = i + hszCostab;
          temp_re = y[nRowsM2].re;
          temp_im = y[nRowsM2].im;
          y[nRowsM2].re = y[i].re - temp_re;
          y[nRowsM2].im = y[i].im - temp_im;
          y[i].re = y[i].re + temp_re;
          y[i].im = y[i].im + temp_im;
        }

        istart = 1;
        for (nRows = k; nRows < nRowsD2; nRows += k) {
          temp2_re = hcostab[nRows];
          temp2_im = hsintab[nRows];
          i = istart;
          ihi = istart + ju;
          while (i < ihi) {
            nRowsM2 = i + hszCostab;
            temp_re = temp2_re * y[nRowsM2].re - temp2_im * y[nRowsM2].im;
            temp_im = temp2_re * y[nRowsM2].im + temp2_im * y[nRowsM2].re;
            y[nRowsM2].re = y[i].re - temp_re;
            y[nRowsM2].im = y[i].im - temp_im;
            y[i].re = y[i].re + temp_re;
            y[i].im = y[i].im + temp_im;
            i += iy;
          }

          istart++;
        }

        k /= 2;
        hszCostab = iy;
        iy += iy;
        ju -= hszCostab;
      }

      hszCostab = static_cast<int>(z) / 2;
      temp_re = y[0].re;
      temp_im = y[0].im;
      y_im = y[0].re * reconVar1[0].im + y[0].im * reconVar1[0].re;
      temp2_re = y[0].re;
      temp2_im = -y[0].im;
      y[0].re = 0.5 * ((y[0].re * reconVar1[0].re - y[0].im * reconVar1[0].im) +
                       (temp2_re * reconVar2[0].re - temp2_im * reconVar2[0].im));
      y[0].im = 0.5 * (y_im + (temp2_re * reconVar2[0].im + temp2_im *
        reconVar2[0].re));
      y[static_cast<int>(z)].re = 0.5 * ((temp_re * reconVar2[0].re - temp_im *
        reconVar2[0].im) + (temp_re * reconVar1[0].re - -temp_im * reconVar1[0].
                            im));
      y[static_cast<int>(z)].im = 0.5 * ((temp_re * reconVar2[0].im + temp_im *
        reconVar2[0].re) + (temp_re * reconVar1[0].im + -temp_im * reconVar1[0].
                            re));
      for (i = 2; i <= hszCostab; i++) {
        temp_re = y[i - 1].re;
        temp_im = y[i - 1].im;
        istart = wrapIndex[i - 1];
        temp2_re = y[istart - 1].re;
        temp2_im = y[istart - 1].im;
        y_im = y[i - 1].re * reconVar1[i - 1].im + y[i - 1].im * reconVar1[i - 1]
          .re;
        y_im_tmp = -y[istart - 1].im;
        y[i - 1].re = 0.5 * ((y[i - 1].re * reconVar1[i - 1].re - y[i - 1].im *
                              reconVar1[i - 1].im) + (temp2_re * reconVar2[i - 1]
          .re - y_im_tmp * reconVar2[i - 1].im));
        y[i - 1].im = 0.5 * (y_im + (temp2_re * reconVar2[i - 1].im + y_im_tmp *
          reconVar2[i - 1].re));
        iy = (static_cast<int>(z) + i) - 1;
        y[iy].re = 0.5 * ((temp_re * reconVar2[i - 1].re - temp_im * reconVar2[i
                           - 1].im) + (temp2_re * reconVar1[i - 1].re -
          -temp2_im * reconVar1[i - 1].im));
        y[iy].im = 0.5 * ((temp_re * reconVar2[i - 1].im + temp_im * reconVar2[i
                           - 1].re) + (temp2_re * reconVar1[i - 1].im +
          -temp2_im * reconVar1[i - 1].re));
        y[istart - 1].re = 0.5 * ((temp2_re * reconVar1[istart - 1].re -
          temp2_im * reconVar1[istart - 1].im) + (temp_re * reconVar2[istart - 1]
          .re - -temp_im * reconVar2[istart - 1].im));
        y[istart - 1].im = 0.5 * ((temp2_re * reconVar1[istart - 1].im +
          temp2_im * reconVar1[istart - 1].re) + (temp_re * reconVar2[istart - 1]
          .im + -temp_im * reconVar2[istart - 1].re));
        iy = (istart + static_cast<int>(z)) - 1;
        y[iy].re = 0.5 * ((temp2_re * reconVar2[istart - 1].re - temp2_im *
                           reconVar2[istart - 1].im) + (temp_re *
          reconVar1[istart - 1].re - -temp_im * reconVar1[istart - 1].im));
        y[iy].im = 0.5 * ((temp2_re * reconVar2[istart - 1].im + temp2_im *
                           reconVar2[istart - 1].re) + (temp_re *
          reconVar1[istart - 1].im + -temp_im * reconVar1[istart - 1].re));
      }

      if (hszCostab != 0) {
        temp2_im = y[hszCostab].re;
        temp_im = y[hszCostab].im;
        y_im = y[hszCostab].re * reconVar1[hszCostab].im + y[hszCostab].im *
          reconVar1[hszCostab].re;
        y_im_tmp = -y[hszCostab].im;
        y[hszCostab].re = 0.5 * ((y[hszCostab].re * reconVar1[hszCostab].re -
          y[hszCostab].im * reconVar1[hszCostab].im) + (temp2_im *
          reconVar2[hszCostab].re - y_im_tmp * reconVar2[hszCostab].im));
        y[hszCostab].im = 0.5 * (y_im + (temp2_im * reconVar2[hszCostab].im +
          y_im_tmp * reconVar2[hszCostab].re));
        istart = static_cast<int>(z) + hszCostab;
        y[istart].re = 0.5 * ((temp2_im * reconVar2[hszCostab].re - temp_im *
          reconVar2[hszCostab].im) + (temp2_im * reconVar1[hszCostab].re -
          -temp_im * reconVar1[hszCostab].im));
        y[istart].im = 0.5 * ((temp2_im * reconVar2[hszCostab].im + temp_im *
          reconVar2[hszCostab].re) + (temp2_im * reconVar1[hszCostab].im +
          -temp_im * reconVar1[hszCostab].re));
      }
    }

    //
    // Arguments    : const ::coder::array<double, 1U> &x
    //                int n2blue
    //                int nfft
    //                const ::coder::array<double, 2U> &costab
    //                const ::coder::array<double, 2U> &sintab
    //                const ::coder::array<double, 2U> &sintabinv
    //                ::coder::array<creal_T, 1U> &y
    // Return Type  : void
    //
    void FFTImplementationCallback::dobluesteinfft(const ::coder::array<double,
      1U> &x, int n2blue, int nfft, const ::coder::array<double, 2U> &costab,
      const ::coder::array<double, 2U> &sintab, const ::coder::array<double, 2U>
      &sintabinv, ::coder::array<creal_T, 1U> &y)
    {
      array<creal_T, 1U> b_fv;
      array<creal_T, 1U> fv;
      array<creal_T, 1U> wwc;
      double nt_re;
      int idx;
      int k;
      int nInt2;
      int nInt2m1;
      int rt;
      if ((nfft != 1) && ((nfft & 1) == 0)) {
        int nRows;
        nRows = nfft / 2;
        nInt2m1 = (nRows + nRows) - 1;
        wwc.set_size(nInt2m1);
        idx = nRows;
        rt = 0;
        wwc[nRows - 1].re = 1.0;
        wwc[nRows - 1].im = 0.0;
        nInt2 = nRows << 1;
        for (k = 0; k <= nRows - 2; k++) {
          double nt_im;
          int b_y;
          b_y = ((k + 1) << 1) - 1;
          if (nInt2 - rt <= b_y) {
            rt += b_y - nInt2;
          } else {
            rt += b_y;
          }

          nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
            double>(nRows);
          if (nt_im == 0.0) {
            nt_re = 1.0;
            nt_im = 0.0;
          } else {
            nt_re = std::cos(nt_im);
            nt_im = std::sin(nt_im);
          }

          wwc[idx - 2].re = nt_re;
          wwc[idx - 2].im = -nt_im;
          idx--;
        }

        idx = 0;
        rt = nInt2m1 - 1;
        for (k = rt; k >= nRows; k--) {
          wwc[k] = wwc[idx];
          idx++;
        }
      } else {
        nInt2m1 = (nfft + nfft) - 1;
        wwc.set_size(nInt2m1);
        idx = nfft;
        rt = 0;
        wwc[nfft - 1].re = 1.0;
        wwc[nfft - 1].im = 0.0;
        nInt2 = nfft << 1;
        for (k = 0; k <= nfft - 2; k++) {
          double nt_im;
          int b_y;
          b_y = ((k + 1) << 1) - 1;
          if (nInt2 - rt <= b_y) {
            rt += b_y - nInt2;
          } else {
            rt += b_y;
          }

          nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<
            double>(nfft);
          if (nt_im == 0.0) {
            nt_re = 1.0;
            nt_im = 0.0;
          } else {
            nt_re = std::cos(nt_im);
            nt_im = std::sin(nt_im);
          }

          wwc[idx - 2].re = nt_re;
          wwc[idx - 2].im = -nt_im;
          idx--;
        }

        idx = 0;
        rt = nInt2m1 - 1;
        for (k = rt; k >= nfft; k--) {
          wwc[k] = wwc[idx];
          idx++;
        }
      }

      y.set_size(nfft);
      if (nfft > x.size(0)) {
        y.set_size(nfft);
        for (rt = 0; rt < nfft; rt++) {
          y[rt].re = 0.0;
          y[rt].im = 0.0;
        }
      }

      if ((n2blue != 1) && ((nfft & 1) == 0)) {
        FFTImplementationCallback::doHalfLengthBluestein((x), (y), (x.size(0)),
          (nfft), (n2blue), (wwc), (costab), (sintab), (costab), (sintabinv));
      } else {
        nInt2m1 = x.size(0);
        if (nfft < nInt2m1) {
          nInt2m1 = nfft;
        }

        rt = 0;
        for (k = 0; k < nInt2m1; k++) {
          nInt2 = (nfft + k) - 1;
          y[k].re = wwc[nInt2].re * x[rt];
          y[k].im = wwc[nInt2].im * -x[rt];
          rt++;
        }

        rt = nInt2m1 + 1;
        for (k = rt; k <= nfft; k++) {
          y[k - 1].re = 0.0;
          y[k - 1].im = 0.0;
        }

        FFTImplementationCallback::r2br_r2dit_trig_impl((y), (n2blue), (costab),
          (sintab), (fv));
        FFTImplementationCallback::r2br_r2dit_trig_impl((wwc), (n2blue), (costab),
          (sintab), (b_fv));
        b_fv.set_size(fv.size(0));
        nInt2m1 = fv.size(0);
        for (rt = 0; rt < nInt2m1; rt++) {
          nt_re = fv[rt].re * b_fv[rt].im + fv[rt].im * b_fv[rt].re;
          b_fv[rt].re = fv[rt].re * b_fv[rt].re - fv[rt].im * b_fv[rt].im;
          b_fv[rt].im = nt_re;
        }

        FFTImplementationCallback::r2br_r2dit_trig_impl((b_fv), (n2blue),
          (costab), (sintabinv), (fv));
        if (fv.size(0) > 1) {
          nt_re = 1.0 / static_cast<double>(fv.size(0));
          nInt2m1 = fv.size(0);
          for (rt = 0; rt < nInt2m1; rt++) {
            fv[rt].re = nt_re * fv[rt].re;
            fv[rt].im = nt_re * fv[rt].im;
          }
        }

        idx = 0;
        rt = wwc.size(0);
        for (k = nfft; k <= rt; k++) {
          y[idx].re = wwc[k - 1].re * fv[k - 1].re + wwc[k - 1].im * fv[k - 1].
            im;
          y[idx].im = wwc[k - 1].re * fv[k - 1].im - wwc[k - 1].im * fv[k - 1].
            re;
          idx++;
        }
      }
    }

    //
    // Arguments    : int nfft
    //                boolean_T useRadix2
    //                int *n2blue
    //                int *nRows
    // Return Type  : void
    //
    void FFTImplementationCallback::get_algo_sizes(int nfft, boolean_T useRadix2,
      int *n2blue, int *nRows)
    {
      *n2blue = 1;
      if (useRadix2) {
        *nRows = nfft;
      } else {
        if (nfft > 0) {
          int n;
          int pmax;
          n = (nfft + nfft) - 1;
          pmax = 31;
          if (n <= 1) {
            pmax = 0;
          } else {
            int pmin;
            boolean_T exitg1;
            pmin = 0;
            exitg1 = false;
            while ((!exitg1) && (pmax - pmin > 1)) {
              int k;
              int pow2p;
              k = (pmin + pmax) >> 1;
              pow2p = 1 << k;
              if (pow2p == n) {
                pmax = k;
                exitg1 = true;
              } else if (pow2p > n) {
                pmax = k;
              } else {
                pmin = k;
              }
            }
          }

          *n2blue = 1 << pmax;
        }

        *nRows = *n2blue;
      }
    }

    //
    // Arguments    : const ::coder::array<creal_T, 1U> &x
    //                int unsigned_nRows
    //                const ::coder::array<double, 2U> &costab
    //                const ::coder::array<double, 2U> &sintab
    //                ::coder::array<creal_T, 1U> &y
    // Return Type  : void
    //
    void FFTImplementationCallback::r2br_r2dit_trig_impl(const ::coder::array<
      creal_T, 1U> &x, int unsigned_nRows, const ::coder::array<double, 2U>
      &costab, const ::coder::array<double, 2U> &sintab, ::coder::array<creal_T,
      1U> &y)
    {
      double temp_im;
      double temp_re;
      double twid_im;
      double twid_re;
      int i;
      int iDelta2;
      int iheight;
      int ix;
      int iy;
      int ju;
      int k;
      int nRowsD2;
      y.set_size(unsigned_nRows);
      if (unsigned_nRows > x.size(0)) {
        y.set_size(unsigned_nRows);
        for (iy = 0; iy < unsigned_nRows; iy++) {
          y[iy].re = 0.0;
          y[iy].im = 0.0;
        }
      }

      iDelta2 = x.size(0);
      if (iDelta2 >= unsigned_nRows) {
        iDelta2 = unsigned_nRows;
      }

      iheight = unsigned_nRows - 2;
      nRowsD2 = unsigned_nRows / 2;
      k = nRowsD2 / 2;
      ix = 0;
      iy = 0;
      ju = 0;
      for (i = 0; i <= iDelta2 - 2; i++) {
        boolean_T tst;
        y[iy] = x[ix];
        iy = unsigned_nRows;
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
      if (unsigned_nRows > 1) {
        for (i = 0; i <= iheight; i += 2) {
          temp_re = y[i + 1].re;
          temp_im = y[i + 1].im;
          twid_re = y[i].re;
          twid_im = y[i].im;
          y[i + 1].re = y[i].re - y[i + 1].re;
          y[i + 1].im = y[i].im - y[i + 1].im;
          twid_re += temp_re;
          twid_im += temp_im;
          y[i].re = twid_re;
          y[i].im = twid_im;
        }
      }

      iy = 2;
      iDelta2 = 4;
      iheight = ((k - 1) << 2) + 1;
      while (k > 0) {
        int temp_re_tmp;
        for (i = 0; i < iheight; i += iDelta2) {
          temp_re_tmp = i + iy;
          temp_re = y[temp_re_tmp].re;
          temp_im = y[temp_re_tmp].im;
          y[temp_re_tmp].re = y[i].re - temp_re;
          y[temp_re_tmp].im = y[i].im - temp_im;
          y[i].re = y[i].re + temp_re;
          y[i].im = y[i].im + temp_im;
        }

        ix = 1;
        for (ju = k; ju < nRowsD2; ju += k) {
          int ihi;
          twid_re = costab[ju];
          twid_im = sintab[ju];
          i = ix;
          ihi = ix + iheight;
          while (i < ihi) {
            temp_re_tmp = i + iy;
            temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
            temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
            y[temp_re_tmp].re = y[i].re - temp_re;
            y[temp_re_tmp].im = y[i].im - temp_im;
            y[i].re = y[i].re + temp_re;
            y[i].im = y[i].im + temp_im;
            i += iDelta2;
          }

          ix++;
        }

        k /= 2;
        iy = iDelta2;
        iDelta2 += iDelta2;
        iheight -= iy;
      }
    }
  }
}

//
// File trailer for FFTImplementationCallback.cpp
//
// [EOF]
//
