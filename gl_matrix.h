#ifndef __HTABTX_GL_MATRIX_H__
#define __HTABTX_GL_MATRIX_H__
void GLMatrixTranslation(f32 *Matrix, f32 x, f32 y, f32 z);
void GLMatrixRotationX(f32 *Matrix, f32 Angle);
void GLMatrixRotationY(f32 *Matrix, f32 Angle);
void GLMatrixRotationZ(f32 *Matrix, f32 Angle);
void GLMatrixTranspose(f32 *Result, f32 *Matrix);
void GLMatrixMultiply(f32 *Result, f32 *Matrix1, f32 *Matrix2);
void GLMatrixInverse(f32 *Result, f32 *Matrix);
void GLBuildIdentityMatrix(f32 *Matrix);
void GLBuildPerspectiveFovMatrix(f32 *Matrix, f32 FieldOfView, f32 ScreenAspect, f32 ScreenNear, f32 ScreenDepth);
void GLBuildOrthoMatrix(f32 *Matrix, f32 ScreenWidth, f32 ScreenHeight, f32 ScreenNear, f32 ScreenDepth );
#endif
