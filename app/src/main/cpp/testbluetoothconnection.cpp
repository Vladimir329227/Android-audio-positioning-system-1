// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("testbluetoothconnection");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("testbluetoothconnection")
//      }
//    }

#include <jni.h>
#include <iostream>
#include <list>
#include "main.h"
#include "corrVova.h"
#include "corrVova_terminate.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

extern "C"
JNIEXPORT jdoubleArray JNICALL
Java_com_example_testbluetoothconnection_MainActivity_argInit_1real_1T(JNIEnv *env, jclass clazz, jdoubleArray input1, jdoubleArray input2, jint razmer1, jint razmer2) {
    coder::array<double, 1U> input1_tmp;
    coder::array<double, 1U> input2_tmp;
    coder::array<double, 1U> output;
    /*double* inp1 = new double[razmer1];
    double* inp2 = new double[razmer2];
    input1_tmp.set_size(razmer1);
    input2_tmp.set_size(razmer2);
    (*env).GetDoubleArrayRegion(input1,0,razmer1, inp1);
    (*env).GetDoubleArrayRegion(input2,0,razmer2, inp2);
    

    for (int i=0;i<razmer1;i++)
        input1_tmp[i] = inp1[i];
    for (int i=0;i<razmer2;i++)
        input2_tmp[i] = inp2[i];
*/

    input1_tmp.set_size(4);
    input2_tmp.set_size(3);

    input1_tmp[0] = 1.0;
    input1_tmp[1] = 2.0;
    input1_tmp[2] = 3.0;
    input1_tmp[3] = 5.0;

    input2_tmp[0] = 1.0;
    input2_tmp[1] = 4.0;
    input2_tmp[2] = 7.0;

    corrVova(input1_tmp, input2_tmp, output);
    std::list<double> test_list;

    int t=0;
    for(auto i: output)
        t++;

    jdoubleArray numbers = (*env).NewDoubleArray(t);

    (*env).SetDoubleArrayRegion(  numbers, 0, t, (const jdouble*) output.data());

    /*int t2=0;
    for(double i: output)
    {
        outCArray[t2] = i;
        t2++;
    }

    (*env).SetDoubleArrayRegion( numbers, 0, 7, outCArray);*/
    return numbers;

}