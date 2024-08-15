/*
 * Copyright (c) 2024 EdgeImpulse Inc.
 *
 * Generated by Edge Impulse and licensed under the applicable Edge Impulse
 * Terms of Service. Community and Professional Terms of Service
 * (https://docs.edgeimpulse.com/page/terms-of-service) or Enterprise Terms of
 * Service (https://docs.edgeimpulse.com/page/enterprise-terms-of-service),
 * according to your product plan subscription (the “License”).
 *
 * This software, documentation and other associated files (collectively referred
 * to as the “Software”) is a single SDK variation generated by the Edge Impulse
 * platform and requires an active paid Edge Impulse subscription to use this
 * Software for any purpose.
 *
 * You may NOT use this Software unless you have an active Edge Impulse subscription
 * that meets the eligibility requirements for the applicable License, subject to
 * your full and continued compliance with the terms and conditions of the License,
 * including without limitation any usage restrictions under the applicable License.
 *
 * If you do not have an active Edge Impulse product plan subscription, or if use
 * of this Software exceeds the usage limitations of your Edge Impulse product plan
 * subscription, you are not permitted to use this Software and must immediately
 * delete and erase all copies of this Software within your control or possession.
 * Edge Impulse reserves all rights and remedies available to enforce its rights.
 *
 * Unless required by applicable law or agreed to in writing, the Software is
 * distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing
 * permissions, disclaimers and limitations under the License.
 */
// Generated on: 15.08.2024 15:02:07

#include <stdio.h>
#include <stdlib.h>
#include "edge-impulse-sdk/tensorflow/lite/c/builtin_op_data.h"
#include "edge-impulse-sdk/tensorflow/lite/c/common.h"
#include "edge-impulse-sdk/tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

#if EI_CLASSIFIER_PRINT_STATE
#if defined(__cplusplus) && EI_C_LINKAGE == 1
extern "C" {
    extern void ei_printf(const char *format, ...);
}
#else
extern void ei_printf(const char *format, ...);
#endif
#endif

#if defined (__GNUC__)  /* GNU compiler */
#define ALIGN(X) __attribute__((aligned(X)))
#define DEFINE_SECTION(x) __attribute__((section(x)))
#elif defined (_MSC_VER)
#define ALIGN(X) __declspec(align(X))
#elif defined (__TASKING__) /* TASKING Compiler */
#define ALIGN(X) __align(X)
#define DEFINE_SECTION(x) __attribute__(section(x)))
#elif defined (__ARMCC_VERSION) /* Arm Compiler */
#define ALIGN(X) __ALIGNED(x)
#define DEFINE_SECTION(x) __attribute__((section(x)))
#elif defined (__ICCARM__) /* IAR Compiler */
#define ALIGN(X) __ALIGNED(x)
#define DEFINE_SECTION(x) __attribute__((section(x)))
#elif defined (__clang__) /* LLVM/Clang Compiler */
#define ALIGN(X) __ALIGNED(x)
#define DEFINE_SECTION(x) __attribute__((section(x)))
#endif

#ifndef EI_MAX_SCRATCH_BUFFER_COUNT
#ifndef CONFIG_IDF_TARGET_ESP32S3
#define EI_MAX_SCRATCH_BUFFER_COUNT 4
#else
#define EI_MAX_SCRATCH_BUFFER_COUNT 4
#endif // CONFIG_IDF_TARGET_ESP32S3
#endif // EI_MAX_SCRATCH_BUFFER_COUNT

#ifndef EI_MAX_OVERFLOW_BUFFER_COUNT
#define EI_MAX_OVERFLOW_BUFFER_COUNT 10
#endif // EI_MAX_OVERFLOW_BUFFER_COUNT

using namespace tflite;
using namespace tflite::ops;
using namespace tflite::ops::micro;

namespace {

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX) || defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
constexpr int kTensorArenaSize = 1424;
#else
constexpr int kTensorArenaSize = 400;
#endif

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC)
#if defined (EI_TENSOR_ARENA_LOCATION)
#define STRINGIZE(x) #x
#define STRINGIZE_VALUE_OF(x) STRINGIZE(x)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16) DEFINE_SECTION(STRINGIZE_VALUE_OF(EI_TENSOR_ARENA_LOCATION));
#else
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#endif
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX)
#pragma Bss(".tensor_arena")
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#pragma Bss()
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16) __attribute__((section(".tensor_arena")));
#else
#define EI_CLASSIFIER_ALLOCATION_HEAP 1
uint8_t* tensor_arena = NULL;
#endif

static uint8_t* tensor_boundary;
static uint8_t* current_location;

template <int SZ, class T> struct TfArray {
  int sz; T elem[SZ];
};

enum used_operators_e {
  OP_FULLY_CONNECTED, OP_SOFTMAX,  OP_LAST
};

struct TensorInfo_t { // subset of TfLiteTensor used for initialization from constant memory
  TfLiteAllocationType allocation_type;
  TfLiteType type;
  void* data;
  TfLiteIntArray* dims;
  size_t bytes;
  TfLiteQuantization quantization;
};

typedef struct {
  TfLiteTensor tensor;
  int16_t index;
} TfLiteTensorWithIndex;

typedef struct {
  TfLiteEvalTensor tensor;
  int16_t index;
} TfLiteEvalTensorWithIndex;

TfLiteContext ctx{};
static const int MAX_TFL_TENSOR_COUNT = 4;
static TfLiteTensorWithIndex tflTensors[MAX_TFL_TENSOR_COUNT];
static const int MAX_TFL_EVAL_COUNT = 4;
static TfLiteEvalTensorWithIndex tflEvalTensors[MAX_TFL_EVAL_COUNT];
TfLiteRegistration registrations[OP_LAST];

namespace g0 {
const TfArray<2, int> tensor_dimension0 = { 2, { 1,57 } };
const TfArray<1, float> quant0_scale = { 1, { 0.12205687910318375, } };
const TfArray<1, int> quant0_zero = { 1, { -79 } };
const TfLiteAffineQuantization quant0 = { (TfLiteFloatArray*)&quant0_scale, (TfLiteIntArray*)&quant0_zero, 0 };
const ALIGN(16) int8_t tensor_data1[20*57] = { 
  -98, -79, -79, 12, -20, 11, -101, -86, -95, 19, 108, -61, -82, 107, 51, 117, 111, -35, 82, -87, 96, -108, 106, -92, -73, -73, -111, 48, -47, -44, -74, -106, 22, 106, 37, -46, -58, 83, 23, -21, 89, 109, 69, 55, -103, 32, -28, 55, -55, 18, 60, 94, -97, 98, 22, 31, 19, 
  28, 24, -7, -36, 32, 104, 68, 89, -105, 70, 55, -65, -34, -110, -76, -57, -54, -108, 74, 65, -11, -77, -84, -56, 33, -75, 22, 49, -71, -2, 87, 101, -123, -29, -118, 96, -48, 57, 94, -50, -71, 32, 36, 4, -104, -115, 24, -13, -29, -73, 65, 110, -118, -67, 98, -29, -116, 
  12, -114, -90, 59, 10, 22, -120, -34, -81, 6, -46, -35, -94, -32, 57, -107, -89, -35, 93, -102, 77, -13, -51, 34, -59, 94, 6, -68, -25, -78, -84, 83, -111, 41, -87, 32, 21, -24, -47, -79, 101, -13, 6, -15, -34, 7, 77, -37, 114, -100, 104, -10, 14, -91, 68, 54, 65, 
  -117, -32, -95, 50, 32, 35, -83, 18, 18, 103, 1, -104, 19, 53, 10, -59, -32, -26, 113, 70, -120, -75, 120, -10, -17, 110, 8, -39, 91, 22, 0, 88, 8, -98, -27, 90, 29, -24, -89, 6, 7, -22, -28, 66, -90, -75, 89, -89, 68, 73, 101, -69, -47, 108, -109, -70, 64, 
  -6, 61, -74, 68, 31, 114, -85, -40, 30, 44, 47, 11, -1, -18, -95, 2, -51, -46, 35, 20, 26, -54, -53, 20, -6, -48, 111, 56, 117, 6, 15, -56, -53, 74, -54, -38, 75, 69, -94, -55, 43, -103, -79, -25, -104, 1, 106, 98, 71, 46, 58, -101, 30, -58, 84, -18, 79, 
  60, -68, -22, -20, -3, 45, 29, 40, -2, -100, -59, -74, 110, -56, 88, 22, -61, 43, 81, 101, -59, -112, -23, -39, -81, 55, 20, -48, 65, 39, 55, 113, 6, 108, -34, 75, -12, 33, 117, -65, -4, 31, 102, 65, -34, 75, -111, 73, -19, -11, -19, 5, -39, -52, -19, 74, 32, 
  -79, 104, -18, -42, -41, 37, 37, -26, -54, 66, -98, -89, -118, -83, 105, 30, -24, 58, 33, -41, 26, -17, 110, -89, 31, 3, -58, 21, 31, -32, 54, -34, -74, -9, -42, -50, 28, 83, 10, -45, 93, 3, -106, -64, -17, -4, 88, 103, 64, 54, 43, 15, 82, -42, -112, 58, -67, 
  -38, 119, -82, -27, -106, 110, 17, -112, 93, -94, 75, -65, -87, -54, -67, -14, -3, -96, 5, -31, -36, -99, -114, -25, -19, -104, 83, 36, 43, 84, -105, 100, -107, -62, 11, 36, -119, 25, 53, 45, 11, -109, 70, -80, -80, 90, 52, 92, 25, 2, 108, 36, -56, 108, 47, 12, -1, 
  37, 46, 43, -112, 79, 55, -39, -24, 49, -95, -119, 112, 7, -47, -122, -75, 20, -22, 85, -10, -13, -34, -20, -58, -53, 104, -105, 25, 93, -4, -44, 42, -55, 45, 81, 35, -21, 12, -106, 27, 63, -99, -87, 76, -36, 3, 91, 55, -86, 99, -122, -91, 23, -85, -37, -2, -102, 
  -12, 30, 11, 52, -111, 1, -5, -39, 67, -14, 10, -32, -52, 1, 16, -46, 37, 111, 104, -101, 72, -74, -14, 95, 99, -83, -36, -68, 111, 73, -88, 41, 1, -83, -12, 108, -7, 95, -12, 83, -77, -58, 57, 73, 41, -88, 86, -6, -31, 91, -26, 124, -67, 123, 91, -109, -87, 
  -99, -99, -113, -92, 110, -38, 42, -1, 20, 85, 12, 105, 26, 104, -12, -86, -73, 76, -34, -16, -64, 7, 74, -108, -49, 41, -84, 70, 45, -97, 119, -19, -109, 1, 108, 48, -41, 17, -80, -13, -47, 3, 94, 105, 42, 80, 26, 76, -46, -106, 111, -56, -94, 5, 76, -74, 19, 
  100, 65, -5, -21, 13, 118, 31, 84, 92, 112, -26, 99, 15, -81, -72, 52, 17, 69, 92, 87, 60, -47, -4, 28, 84, -83, -25, 95, -75, 73, -105, 47, -79, -44, 86, -93, 96, 58, 96, -51, -50, -35, -119, -108, -102, -13, -119, 0, -5, 19, -29, -12, 97, 120, 115, -60, 94, 
  56, 71, 9, -59, 100, -29, 33, -56, -22, 107, -12, -57, -86, 95, 102, -122, 53, -15, -121, -13, -101, -35, 117, -11, -88, -6, -85, 37, 95, -47, 82, -37, -40, 97, -109, -75, -72, -22, -77, 122, -40, 38, 33, 103, -1, -42, 71, -51, -20, 47, -40, -48, -46, -102, 85, 70, 74, 
  13, 29, -35, 80, 16, -29, 59, -24, 37, 90, 116, 104, 58, -50, 5, 25, -70, -62, 33, 97, -116, -44, 50, -47, -118, 95, 66, 21, 104, -53, -118, 121, 35, 57, 83, 58, 107, -70, 68, -110, -37, -8, 79, -34, -69, 10, -66, -8, -2, 112, -77, -74, -13, -26, 77, 70, 23, 
  -82, -116, 123, -69, 46, -38, 65, 79, 17, -39, -95, -16, -93, -26, 19, -11, -57, -46, -43, -81, 24, 53, -80, 33, 71, 9, -83, -10, -44, 13, 25, 3, 93, 87, 105, -106, 40, 20, -99, -42, 1, -106, 71, -105, -40, 4, 82, -109, 91, 19, -82, 15, 79, 68, -9, -44, -33, 
  -75, 118, -38, 38, -33, 104, -71, -58, -16, 98, -69, 56, -47, -33, 119, -90, -9, 83, 75, 81, 28, -55, 27, -99, -54, -34, 73, 44, 12, 12, -110, -97, -104, 71, 78, -38, -30, 76, -6, 89, 100, -70, 94, -13, -47, 71, -111, 113, -42, 81, -14, 67, 30, 41, 24, 67, -13, 
  -90, 103, 71, 20, -5, -1, -13, -57, -14, 37, 4, -97, -68, -107, -78, 57, 83, 58, -100, -14, -56, -108, -54, 90, 74, 46, -26, 14, 119, 112, 9, -22, -11, 75, 29, 33, -11, -39, -94, 48, 32, 117, -68, -89, 52, 37, 61, 84, 114, 31, 106, 95, -21, 34, -30, 16, -99, 
  -53, 7, -114, -103, 106, -50, 20, 85, -69, 10, 11, 51, 25, -36, -19, -35, 5, -19, -63, 95, -109, -34, 67, -97, 106, -14, -85, 116, 70, 62, 71, 21, 21, 27, -107, -111, 108, 21, -98, 22, -93, 76, -91, 92, 114, 109, 74, 104, 13, -86, -49, 80, -55, 108, 113, -79, -12, 
  -88, -23, 106, 96, 63, 55, 7, -72, -23, -21, -93, -72, 97, -4, -44, 92, -39, -11, -90, -29, 82, -101, -43, 113, -68, -93, 97, -23, 31, 0, 75, 53, 106, 19, 60, 86, 59, -6, 19, 72, -33, -127, 26, -41, 123, 101, -82, 62, 72, 18, 19, -92, -78, -45, 54, -78, 25, 
  -31, 59, 86, 60, 28, -8, -2, -107, 102, 105, -33, 87, -12, -39, 96, 35, 24, -115, 30, -12, -41, 71, 108, -101, 78, 108, -6, 107, -110, -122, -117, -89, 117, 59, 35, 12, 92, -60, 68, -31, -89, -46, 115, 42, -72, 14, -20, 82, -57, -124, 99, 80, -41, -39, -46, -1, 96, 
};
const TfArray<2, int> tensor_dimension1 = { 2, { 20,57 } };
const TfArray<1, float> quant1_scale = { 1, { 0.0023052738979458809, } };
const TfArray<1, int> quant1_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant1 = { (TfLiteFloatArray*)&quant1_scale, (TfLiteIntArray*)&quant1_zero, 0 };
const ALIGN(16) int32_t tensor_data2[20] = { -40, 79, 63, 0, -60, 0, -5, 11, 11, -51, -23, 0, 81, 0, -88, -8, 0, 0, -71, 31, };
const TfArray<1, int> tensor_dimension2 = { 1, { 20 } };
const TfArray<1, float> quant2_scale = { 1, { 0.00028137452318333089, } };
const TfArray<1, int> quant2_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant2 = { (TfLiteFloatArray*)&quant2_scale, (TfLiteIntArray*)&quant2_zero, 0 };
const ALIGN(16) int8_t tensor_data3[10*20] = { 
  -83, 5, 39, 21, 100, -75, -40, 26, -109, -108, -33, -69, 119, 100, -29, -1, -108, 17, -30, 21, 
  -81, 18, -62, 48, 30, 11, 86, -54, -45, -89, 20, -96, -29, -38, -95, -107, -51, 81, 60, -106, 
  -87, 75, 40, -62, 83, -2, 62, -54, 108, 88, -80, -56, 33, -117, 49, -31, -28, 121, -118, -26, 
  -82, -21, -77, -101, -19, 57, 76, 94, 106, -91, 97, 48, 0, -79, -31, 120, 27, 35, 34, -85, 
  22, 11, -63, -94, -123, 106, -43, -6, -73, 124, 7, -121, -104, 45, -16, 23, 23, -111, 123, 29, 
  75, 100, -98, 11, -85, -24, 4, -28, 117, -116, -127, 117, -95, 57, -62, 97, -106, -10, -106, 87, 
  98, -33, 15, 97, 74, -34, 15, 55, 53, 107, -60, 73, -123, -11, -8, -12, 49, -26, 43, -52, 
  -68, 105, -74, -118, -25, -20, -41, -105, 101, 82, 75, 113, -27, -6, -32, -47, -71, 20, -55, 49, 
  -92, 89, 2, 57, 112, -4, 64, -120, -33, -85, 57, 91, 117, 123, -27, 55, -98, 112, 5, -3, 
  -25, 46, 36, 95, -87, 73, 96, -65, 103, -43, -24, 37, -95, -41, -91, 34, 121, 115, -41, 118, 
};
const TfArray<2, int> tensor_dimension3 = { 2, { 10,20 } };
const TfArray<1, float> quant3_scale = { 1, { 0.0034799396526068449, } };
const TfArray<1, int> quant3_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant3 = { (TfLiteFloatArray*)&quant3_scale, (TfLiteIntArray*)&quant3_zero, 0 };
const ALIGN(16) int32_t tensor_data4[10] = { 168, 0, 237, -47, 68, 0, 6, -126, -75, 216, };
const TfArray<1, int> tensor_dimension4 = { 1, { 10 } };
const TfArray<1, float> quant4_scale = { 1, { 0.00015222426736727357, } };
const TfArray<1, int> quant4_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant4 = { (TfLiteFloatArray*)&quant4_scale, (TfLiteIntArray*)&quant4_zero, 0 };
const ALIGN(16) int8_t tensor_data5[2*10] = { 
  -43, -127, -6, -112, 6, -85, 61, 76, -3, 53, 
  80, -114, -17, 104, 105, 68, 55, 0, 34, -9, 
};
const TfArray<2, int> tensor_dimension5 = { 2, { 2,10 } };
const TfArray<1, float> quant5_scale = { 1, { 0.0055145043879747391, } };
const TfArray<1, int> quant5_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant5 = { (TfLiteFloatArray*)&quant5_scale, (TfLiteIntArray*)&quant5_zero, 0 };
const ALIGN(8) int32_t tensor_data6[2] = { 245, -245, };
const TfArray<1, int> tensor_dimension6 = { 1, { 2 } };
const TfArray<1, float> quant6_scale = { 1, { 0.00012089533265680075, } };
const TfArray<1, int> quant6_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant6 = { (TfLiteFloatArray*)&quant6_scale, (TfLiteIntArray*)&quant6_zero, 0 };
const TfArray<2, int> tensor_dimension7 = { 2, { 1,20 } };
const TfArray<1, float> quant7_scale = { 1, { 0.04374336451292038, } };
const TfArray<1, int> quant7_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant7 = { (TfLiteFloatArray*)&quant7_scale, (TfLiteIntArray*)&quant7_zero, 0 };
const TfArray<2, int> tensor_dimension8 = { 2, { 1,10 } };
const TfArray<1, float> quant8_scale = { 1, { 0.021923154592514038, } };
const TfArray<1, int> quant8_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant8 = { (TfLiteFloatArray*)&quant8_scale, (TfLiteIntArray*)&quant8_zero, 0 };
const TfArray<2, int> tensor_dimension9 = { 2, { 1,2 } };
const TfArray<1, float> quant9_scale = { 1, { 0.0070637487806379795, } };
const TfArray<1, int> quant9_zero = { 1, { -53 } };
const TfLiteAffineQuantization quant9 = { (TfLiteFloatArray*)&quant9_scale, (TfLiteIntArray*)&quant9_zero, 0 };
const TfArray<2, int> tensor_dimension10 = { 2, { 1,2 } };
const TfArray<1, float> quant10_scale = { 1, { 0.00390625, } };
const TfArray<1, int> quant10_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant10 = { (TfLiteFloatArray*)&quant10_scale, (TfLiteIntArray*)&quant10_zero, 0 };
const TfLiteFullyConnectedParams opdata0 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs0 = { 3, { 0,1,2 } };
const TfArray<1, int> outputs0 = { 1, { 7 } };
const TfLiteFullyConnectedParams opdata1 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs1 = { 3, { 7,3,4 } };
const TfArray<1, int> outputs1 = { 1, { 8 } };
const TfLiteFullyConnectedParams opdata2 = { kTfLiteActNone, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs2 = { 3, { 8,5,6 } };
const TfArray<1, int> outputs2 = { 1, { 9 } };
const TfLiteSoftmaxParams opdata3 = { 1 };
const TfArray<1, int> inputs3 = { 1, { 9 } };
const TfArray<1, int> outputs3 = { 1, { 10 } };
};

TensorInfo_t tensorData[] = {
{ kTfLiteArenaRw, kTfLiteInt8, (int32_t*)(tensor_arena + 0), (TfLiteIntArray*)&g0::tensor_dimension0, 57, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant0))}, },
{ kTfLiteMmapRo, kTfLiteInt8, (int32_t*)g0::tensor_data1, (TfLiteIntArray*)&g0::tensor_dimension1, 1140, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant1))}, },
{ kTfLiteMmapRo, kTfLiteInt32, (int32_t*)g0::tensor_data2, (TfLiteIntArray*)&g0::tensor_dimension2, 80, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant2))}, },
{ kTfLiteMmapRo, kTfLiteInt8, (int32_t*)g0::tensor_data3, (TfLiteIntArray*)&g0::tensor_dimension3, 200, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant3))}, },
{ kTfLiteMmapRo, kTfLiteInt32, (int32_t*)g0::tensor_data4, (TfLiteIntArray*)&g0::tensor_dimension4, 40, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant4))}, },
{ kTfLiteMmapRo, kTfLiteInt8, (int32_t*)g0::tensor_data5, (TfLiteIntArray*)&g0::tensor_dimension5, 20, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant5))}, },
{ kTfLiteMmapRo, kTfLiteInt32, (int32_t*)g0::tensor_data6, (TfLiteIntArray*)&g0::tensor_dimension6, 8, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant6))}, },
{ kTfLiteArenaRw, kTfLiteInt8, (int32_t*)(tensor_arena + 64), (TfLiteIntArray*)&g0::tensor_dimension7, 20, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant7))}, },
{ kTfLiteArenaRw, kTfLiteInt8, (int32_t*)(tensor_arena + 0), (TfLiteIntArray*)&g0::tensor_dimension8, 10, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant8))}, },
{ kTfLiteArenaRw, kTfLiteInt8, (int32_t*)(tensor_arena + 16), (TfLiteIntArray*)&g0::tensor_dimension9, 2, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant9))}, },
{ kTfLiteArenaRw, kTfLiteInt8, (int32_t*)(tensor_arena + 0), (TfLiteIntArray*)&g0::tensor_dimension10, 2, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&g0::quant10))}, },
};

#ifndef TF_LITE_STATIC_MEMORY
TfLiteNode tflNodes[4] = {
{ (TfLiteIntArray*)&g0::inputs0, (TfLiteIntArray*)&g0::outputs0, (TfLiteIntArray*)&g0::inputs0, nullptr, nullptr, const_cast<void*>(static_cast<const void*>(&g0::opdata0)), nullptr, 0, },
{ (TfLiteIntArray*)&g0::inputs1, (TfLiteIntArray*)&g0::outputs1, (TfLiteIntArray*)&g0::inputs1, nullptr, nullptr, const_cast<void*>(static_cast<const void*>(&g0::opdata1)), nullptr, 0, },
{ (TfLiteIntArray*)&g0::inputs2, (TfLiteIntArray*)&g0::outputs2, (TfLiteIntArray*)&g0::inputs2, nullptr, nullptr, const_cast<void*>(static_cast<const void*>(&g0::opdata2)), nullptr, 0, },
{ (TfLiteIntArray*)&g0::inputs3, (TfLiteIntArray*)&g0::outputs3, (TfLiteIntArray*)&g0::inputs3, nullptr, nullptr, const_cast<void*>(static_cast<const void*>(&g0::opdata3)), nullptr, 0, },
};
#else
TfLiteNode tflNodes[4] = {
{ (TfLiteIntArray*)&g0::inputs0, (TfLiteIntArray*)&g0::outputs0, (TfLiteIntArray*)&g0::inputs0, nullptr, const_cast<void*>(static_cast<const void*>(&g0::opdata0)), nullptr, 0, },
{ (TfLiteIntArray*)&g0::inputs1, (TfLiteIntArray*)&g0::outputs1, (TfLiteIntArray*)&g0::inputs1, nullptr, const_cast<void*>(static_cast<const void*>(&g0::opdata1)), nullptr, 0, },
{ (TfLiteIntArray*)&g0::inputs2, (TfLiteIntArray*)&g0::outputs2, (TfLiteIntArray*)&g0::inputs2, nullptr, const_cast<void*>(static_cast<const void*>(&g0::opdata2)), nullptr, 0, },
{ (TfLiteIntArray*)&g0::inputs3, (TfLiteIntArray*)&g0::outputs3, (TfLiteIntArray*)&g0::inputs3, nullptr, const_cast<void*>(static_cast<const void*>(&g0::opdata3)), nullptr, 0, },
};
#endif

used_operators_e used_ops[] =
{OP_FULLY_CONNECTED, OP_FULLY_CONNECTED, OP_FULLY_CONNECTED, OP_SOFTMAX, };


// Indices into tflTensors and tflNodes for subgraphs
const size_t tflTensors_subgraph_index[] = {0, 11, };
const size_t tflNodes_subgraph_index[] = {0, 4, };

// Input/output tensors
static const int in_tensor_indices[] = {
  0, 
};

static const int out_tensor_indices[] = {
  10, 
};


size_t current_subgraph_index = 0;

static void init_tflite_tensor(size_t i, TfLiteTensor *tensor) {
  tensor->type = tensorData[i].type;
  tensor->is_variable = false;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  tensor->allocation_type = tensorData[i].allocation_type;
#else
  tensor->allocation_type = (tensor_arena <= tensorData[i].data && tensorData[i].data < tensor_arena + kTensorArenaSize) ? kTfLiteArenaRw : kTfLiteMmapRo;
#endif
  tensor->bytes = tensorData[i].bytes;
  tensor->dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  if(tensor->allocation_type == kTfLiteArenaRw){
    uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

    tensor->data.data =  start;
  }
  else {
      tensor->data.data = tensorData[i].data;
  }
#else
  tensor->data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
  tensor->quantization = tensorData[i].quantization;
  if (tensor->quantization.type == kTfLiteAffineQuantization) {
    TfLiteAffineQuantization const* quant = ((TfLiteAffineQuantization const*)(tensorData[i].quantization.params));
    tensor->params.scale = quant->scale->data[0];
    tensor->params.zero_point = quant->zero_point->data[0];
  }

}

static void init_tflite_eval_tensor(int i, TfLiteEvalTensor *tensor) {

  tensor->type = tensorData[i].type;

  tensor->dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
  auto allocation_type = tensorData[i].allocation_type;
  if(allocation_type == kTfLiteArenaRw) {
    uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

    tensor->data.data =  start;
  }
  else {
    tensor->data.data = tensorData[i].data;
  }
#else
  tensor->data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
}

static void* overflow_buffers[EI_MAX_OVERFLOW_BUFFER_COUNT];
static size_t overflow_buffers_ix = 0;
static void * AllocatePersistentBufferImpl(struct TfLiteContext* ctx,
                                       size_t bytes) {
  void *ptr;
  uint32_t align_bytes = (bytes % 16) ? 16 - (bytes % 16) : 0;

  if (current_location - (bytes + align_bytes) < tensor_boundary) {
    if (overflow_buffers_ix > EI_MAX_OVERFLOW_BUFFER_COUNT - 1) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d, does not fit in tensor arena and reached EI_MAX_OVERFLOW_BUFFER_COUNT\n",
        (int)bytes);
      return NULL;
    }

    // OK, this will look super weird, but.... we have CMSIS-NN buffers which
    // we cannot calculate beforehand easily.
    ptr = ei_calloc(bytes, 1);
    if (ptr == NULL) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d\n", (int)bytes);
      return NULL;
    }
    overflow_buffers[overflow_buffers_ix++] = ptr;
    return ptr;
  }

  current_location -= bytes;

  // align to the left aligned boundary of 16 bytes
  current_location -= 15; // for alignment
  current_location += 16 - ((uintptr_t)(current_location) & 15);

  ptr = current_location;
  memset(ptr, 0, bytes);

  return ptr;
}

typedef struct {
  size_t bytes;
  void *ptr;
} scratch_buffer_t;

static scratch_buffer_t scratch_buffers[EI_MAX_SCRATCH_BUFFER_COUNT];
static size_t scratch_buffers_ix = 0;

static TfLiteStatus RequestScratchBufferInArenaImpl(struct TfLiteContext* ctx, size_t bytes,
                                                int* buffer_idx) {
  if (scratch_buffers_ix > EI_MAX_SCRATCH_BUFFER_COUNT - 1) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d, reached EI_MAX_SCRATCH_BUFFER_COUNT\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffer_t b;
  b.bytes = bytes;

  b.ptr = AllocatePersistentBufferImpl(ctx, b.bytes);
  if (!b.ptr) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffers[scratch_buffers_ix] = b;
  *buffer_idx = scratch_buffers_ix;

  scratch_buffers_ix++;

  return kTfLiteOk;
}

static void* GetScratchBufferImpl(struct TfLiteContext* ctx, int buffer_idx) {
  if (buffer_idx > (int)scratch_buffers_ix) {
    return NULL;
  }
  return scratch_buffers[buffer_idx].ptr;
}

static const uint16_t TENSOR_IX_UNUSED = 0x7FFF;

static void ResetTensors() {
  for (size_t ix = 0; ix < MAX_TFL_TENSOR_COUNT; ix++) {
    tflTensors[ix].index = TENSOR_IX_UNUSED;
  }
  for (size_t ix = 0; ix < MAX_TFL_EVAL_COUNT; ix++) {
    tflEvalTensors[ix].index = TENSOR_IX_UNUSED;
  }
}

static TfLiteTensor* GetTensorImpl(const struct TfLiteContext* context,
                               int tensor_idx) {

  tensor_idx = tflTensors_subgraph_index[current_subgraph_index] + tensor_idx;

  for (size_t ix = 0; ix < MAX_TFL_TENSOR_COUNT; ix++) {
    // already used? OK!
    if (tflTensors[ix].index == tensor_idx) {
      return &tflTensors[ix].tensor;
    }
    // passed all the ones we've used, so end of the list?
    if (tflTensors[ix].index == TENSOR_IX_UNUSED) {
      // init the tensor
      init_tflite_tensor(tensor_idx, &tflTensors[ix].tensor);
      tflTensors[ix].index = tensor_idx;
      return &tflTensors[ix].tensor;
    }
  }

  ei_printf("ERR: GetTensor called beyond MAX_TFL_TENSOR_COUNT (%d)\n", MAX_TFL_TENSOR_COUNT);
  return nullptr;
}

static TfLiteEvalTensor* GetEvalTensorImpl(const struct TfLiteContext* context,
                                       int tensor_idx) {

  tensor_idx = tflTensors_subgraph_index[current_subgraph_index] + tensor_idx;

  for (size_t ix = 0; ix < MAX_TFL_EVAL_COUNT; ix++) {
    // already used? OK!
    if (tflEvalTensors[ix].index == tensor_idx) {
      return &tflEvalTensors[ix].tensor;
    }
    // passed all the ones we've used, so end of the list?
    if (tflEvalTensors[ix].index == TENSOR_IX_UNUSED) {
      // init the tensor
      init_tflite_eval_tensor(tensor_idx, &tflEvalTensors[ix].tensor);
      tflEvalTensors[ix].index = tensor_idx;
      return &tflEvalTensors[ix].tensor;
    }
  }

  ei_printf("ERR: GetTensor called beyond MAX_TFL_EVAL_COUNT (%d)\n", (int)MAX_TFL_EVAL_COUNT);
  return nullptr;
}

class EonMicroContext : public MicroContext {
 public:
 
  EonMicroContext(): MicroContext(nullptr, nullptr, nullptr) { }

  void* AllocatePersistentBuffer(size_t bytes) {
    return AllocatePersistentBufferImpl(nullptr, bytes);
  }

  TfLiteStatus RequestScratchBufferInArena(size_t bytes,
                                           int* buffer_index) {
  return RequestScratchBufferInArenaImpl(nullptr, bytes, buffer_index);
  }

  void* GetScratchBuffer(int buffer_index) {
    return GetScratchBufferImpl(nullptr, buffer_index);
  }
 
  TfLiteTensor* AllocateTempTfLiteTensor(int tensor_index) {
    return GetTensorImpl(nullptr, tensor_index);
  }

  void DeallocateTempTfLiteTensor(TfLiteTensor* tensor) {
    return;
  }

  bool IsAllTempTfLiteTensorDeallocated() {
    return true;
  }

  TfLiteEvalTensor* GetEvalTensor(int tensor_index) {
    return GetEvalTensorImpl(nullptr, tensor_index);
  }

};


} // namespace

TfLiteStatus tflite_learn_7_init( void*(*alloc_fnc)(size_t,size_t) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  tensor_arena = (uint8_t*) alloc_fnc(16, kTensorArenaSize);
  if (!tensor_arena) {
    ei_printf("ERR: failed to allocate tensor arena\n");
    return kTfLiteError;
  }
#else
  memset(tensor_arena, 0, kTensorArenaSize);
#endif
  tensor_boundary = tensor_arena;
  current_location = tensor_arena + kTensorArenaSize;

  EonMicroContext micro_context_;
  
  // Set microcontext as the context ptr
  ctx.impl_ = static_cast<void*>(&micro_context_);
  // Setup tflitecontext functions
  ctx.AllocatePersistentBuffer = &AllocatePersistentBufferImpl;
  ctx.RequestScratchBufferInArena = &RequestScratchBufferInArenaImpl;
  ctx.GetScratchBuffer = &GetScratchBufferImpl;
  ctx.GetTensor = &GetTensorImpl;
  ctx.GetEvalTensor = &GetEvalTensorImpl;
  ctx.ReportError = &MicroContextReportOpError;

  ctx.tensors_size = 11;
  for (size_t i = 0; i < 11; ++i) {
    TfLiteTensor tensor;
    init_tflite_tensor(i, &tensor);
    if (tensor.allocation_type == kTfLiteArenaRw) {
      auto data_end_ptr = (uint8_t*)tensor.data.data + tensorData[i].bytes;
      if (data_end_ptr > tensor_boundary) {
        tensor_boundary = data_end_ptr;
      }
    }
  }

  if (tensor_boundary > current_location /* end of arena size */) {
    ei_printf("ERR: tensor arena is too small, does not fit model - even without scratch buffers\n");
    return kTfLiteError;
  }

  registrations[OP_FULLY_CONNECTED] = Register_FULLY_CONNECTED();
  registrations[OP_SOFTMAX] = Register_SOFTMAX();

  for (size_t g = 0; g < 1; ++g) {
    current_subgraph_index = g;
    for(size_t i = tflNodes_subgraph_index[g]; i < tflNodes_subgraph_index[g+1]; ++i) {
      if (registrations[used_ops[i]].init) {
        tflNodes[i].user_data = registrations[used_ops[i]].init(&ctx, (const char*)tflNodes[i].builtin_data, 0);
      }
    }
  }
  current_subgraph_index = 0;

  for(size_t g = 0; g < 1; ++g) {
    current_subgraph_index = g;
    for(size_t i = tflNodes_subgraph_index[g]; i < tflNodes_subgraph_index[g+1]; ++i) {
      if (registrations[used_ops[i]].prepare) {
        ResetTensors();
        TfLiteStatus status = registrations[used_ops[i]].prepare(&ctx, &tflNodes[i]);
        if (status != kTfLiteOk) {
          return status;
        }
      }
    }
  }
  current_subgraph_index = 0;

  return kTfLiteOk;
}

TfLiteStatus tflite_learn_7_input(int index, TfLiteTensor *tensor) {
  init_tflite_tensor(in_tensor_indices[index], tensor);
  return kTfLiteOk;
}

TfLiteStatus tflite_learn_7_output(int index, TfLiteTensor *tensor) {
  init_tflite_tensor(out_tensor_indices[index], tensor);
  return kTfLiteOk;
}

TfLiteStatus tflite_learn_7_invoke() {
  for (size_t i = 0; i < 4; ++i) {
    ResetTensors();

    TfLiteStatus status = registrations[used_ops[i]].invoke(&ctx, &tflNodes[i]);

#if EI_CLASSIFIER_PRINT_STATE
    ei_printf("layer %lu\n", i);
    ei_printf("    inputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].inputs->size; ix++) {
      auto d = tensorData[tflNodes[i].inputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");

    ei_printf("    outputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].outputs->size; ix++) {
      auto d = tensorData[tflNodes[i].outputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");
#endif // EI_CLASSIFIER_PRINT_STATE

    if (status != kTfLiteOk) {
      return status;
    }
  }
  return kTfLiteOk;
}

TfLiteStatus tflite_learn_7_reset( void (*free_fnc)(void* ptr) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  free_fnc(tensor_arena);
#endif

  // scratch buffers are allocated within the arena, so just reset the counter so memory can be reused
  scratch_buffers_ix = 0;

  // overflow buffers are on the heap, so free them first
  for (size_t ix = 0; ix < overflow_buffers_ix; ix++) {
    ei_free(overflow_buffers[ix]);
  }
  overflow_buffers_ix = 0;
  return kTfLiteOk;
}
