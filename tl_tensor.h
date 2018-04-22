#ifndef _TL_TENSOR_H_
#define _TL_TENSOR_H_

#include "tl_util.h"

typedef struct tl_tensor tl_tensor;
struct tl_tensor {
     tl_dtype  dtype;
     int       len;
     int       ndim;
     int      *dims;
     void     *data;
};

#ifdef __cplusplus
extern "C" {
#endif

int isTensorValid(const Tensor *tensor);
int isShapeEqual(const Tensor *t1, const Tensor *t2);
int isHostMem(const void *ptr);
int isDeviceMem(const void *ptr);
void *cloneMem(const void *src, size_t size, CloneKind kind);
Tensor *cloneTensor(const Tensor *src, CloneKind kind);
void *repeatMem(void *data, size_t size, int times, CloneKind kind);
int computeLength(int ndim, const int *dims);
Tensor *createTensor(uint8_t *data, int ndim, const int *dims);
Tensor *mallocTensor(int ndim, const int* dims, const MallocKind mkind);
void freeTensor(Tensor *t, int do_free_data);

void fprintTensor(FILE *stream, const Tensor *tensor, const char *fmt);
void printTensor(const Tensor *tensor, const char *fmt);
void fprintDeviceTensor(FILE *stream, const Tensor *d_tensor, const char *fmt);
void printDeviceTensor(const Tensor *d_tensor, const char *fmt);
void saveTensor(const char *file_name, const Tensor *tensor, const char *fmt);
void saveDeviceTensor(const char *file_name, const Tensor *d_tensor, const char *fmt);

Tensor *createSlicedTensor(const Tensor *src, int dim, int start, int len);
Tensor *sliceTensor(const Tensor *src, Tensor *dst, int dim, int start, int len);
/* Tensor *creatSlicedTensorCuda(const Tensor *src, int dim, int start, int len); */
/* void *sliceTensorCuda(const Tensor *src, Tensor *dst, int dim, int start, int len); */
Tensor *reshapeTensor(const Tensor *src, int newNdim, const int *newDims);
Tensor *createReducedTensor(const Tensor *src, int dim);
void *reduceArgMax(const Tensor *src, Tensor *dst, Tensor *arg, int dim);
Tensor *multiplyElement(const Tensor *src1, const Tensor *src2, Tensor *dst);
Tensor *transposeTensor(const Tensor *src, Tensor *dst, int *axes, int **workspace);
Tensor *transformBboxSQD(const Tensor *delta, const Tensor *anchor, Tensor *res, float width, float height, float img_width, float img_height, int x_shift, int y_shift);
void tensorIndexSort(Tensor *src, int *idx);
void pickElements(uint8_t *src, uint8_t *dst, int stride, int *idx, int len);
float computeIou(float *bbox0, float *bbox1);

#ifdef __cplusplus
}
#endif

#endif  /* _TL_TENSOR_H_ */
