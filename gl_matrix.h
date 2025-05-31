#ifndef __GL_MATRIX_H__
#define  __GL_MATRIX_H__
typedef struct {
  f32 WorldMatrix[16];
  f32 ProjectionMatrix[16];
  f32 OrthoMatrix[16];
} openGLMatrixStruct_t;
#endif
