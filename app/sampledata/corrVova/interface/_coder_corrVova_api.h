/*
 * File: _coder_corrVova_api.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 08-Apr-2024 22:06:09
 */

#ifndef _CODER_CORRVOVA_API_H
#define _CODER_CORRVOVA_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void corrVova(emxArray_real_T *input1, emxArray_real_T *input2,
                emxArray_real_T *output);
  void corrVova_api(const mxArray * const prhs[2], const mxArray *plhs[1]);
  void corrVova_atexit(void);
  void corrVova_initialize(void);
  void corrVova_terminate(void);
  void corrVova_xil_shutdown(void);
  void corrVova_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for _coder_corrVova_api.h
 *
 * [EOF]
 */
