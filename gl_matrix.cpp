void GLMatrixTranslation(f32 *Matrix, f32 x, f32 y, f32 z)
{
  Matrix[0] = 1.0f;
  Matrix[1] = 0.0f;
  Matrix[2] = 0.0f;
  Matrix[3] = 0.0f;

  Matrix[4] = 0.0f;
  Matrix[5] = 1.0f;
  Matrix[6] = 0.0f;
  Matrix[7] = 0.0f;

  Matrix[8] = 0.0f;
  Matrix[9] = 0.0f;
  Matrix[10] = 1.0f;
  Matrix[11] = 0.0f;

  Matrix[12] = x;
  Matrix[13] = y;
  Matrix[14] = z;
  Matrix[15] = 1.0f;
}

void GLMatrixRotationX(f32 *Matrix, f32 Angle)
{
  Matrix[0] = 1.0f;
  Matrix[1] = 0.0f;
  Matrix[2] = 0.0f;
  Matrix[3] = 0.0f;

  Matrix[4] = 0.0f;
  Matrix[5] = cosf(Angle);
  Matrix[6] = sinf(Angle);
  Matrix[7] = 0.0f;

  Matrix[8] = 0.0f;
  Matrix[9] = -sinf(Angle);
  Matrix[10] = cosf(Angle);
  Matrix[11] = 0.0f;

  Matrix[12] = 0.0f;
  Matrix[13] = 0.0f;
  Matrix[14] = 0.0f;
  Matrix[15] = 1.0f;
}

void GLMatrixRotationY(f32 *Matrix, f32 Angle)
{
  Matrix[0] = cosf(Angle);
  Matrix[1] = 0.0f;
  Matrix[2] = -sinf(Angle);
  Matrix[3] = 0.0f;

  Matrix[4] = 0.0f;
  Matrix[5] = 1.0f;
  Matrix[6] = 0.0f;
  Matrix[7] = 0.0f;

  Matrix[8] = sinf(Angle);
  Matrix[9] = 0.0f;
  Matrix[10] = cosf(Angle);
  Matrix[11] = 0.0f;

  Matrix[12] = 0.0f;
  Matrix[13] = 0.0f;
  Matrix[14] = 0.0f;
  Matrix[15] = 1.0f;
}

void GLMatrixRotationZ(f32 *Matrix, f32 Angle)
{
  Matrix[0] = cosf(Angle);
  Matrix[1] = sinf(Angle);
  Matrix[2] = 0.0f;
  Matrix[3] = 0.0f;

  Matrix[4] = -sinf(Angle);
  Matrix[5] = cosf(Angle);
  Matrix[6] = 0.0f;
  Matrix[7] = 0.0f;

  Matrix[8] = 0.0f;
  Matrix[9] = 0.0f;
  Matrix[10] = 1.0f;
  Matrix[11] = 0.0f;

  Matrix[12] = 0.0f;
  Matrix[13] = 0.0f;
  Matrix[14] = 0.0f;
  Matrix[15] = 1.0f;
}

void GLMatrixTranspose(f32 *Result, f32 *Matrix)
{
  Result[0] = Matrix[0];
  Result[1] = Matrix[4];
  Result[2] = Matrix[8];
  Result[3] = Matrix[12];

  Result[4] = Matrix[1];
  Result[5] = Matrix[5];
  Result[6] = Matrix[9];
  Result[7] = Matrix[13];

  Result[8] =  Matrix[2];
  Result[9] =  Matrix[6];
  Result[10] = Matrix[10];
  Result[11] = Matrix[14];

  Result[12] = Matrix[3];
  Result[13] = Matrix[7];
  Result[14] = Matrix[11];
  Result[15] = Matrix[15];
}

void GLMatrixMultiply(f32 *Result, f32 *Matrix1, f32 *Matrix2)
{
  Result[0]  = (Matrix1[0] * Matrix2[0]) + (Matrix1[1] * Matrix2[4]) + (Matrix1[2] * Matrix2[8]) + (Matrix1[3] * Matrix2[12]);
  Result[1]  = (Matrix1[0] * Matrix2[1]) + (Matrix1[1] * Matrix2[5]) + (Matrix1[2] * Matrix2[9]) + (Matrix1[3] * Matrix2[13]);
  Result[2]  = (Matrix1[0] * Matrix2[2]) + (Matrix1[1] * Matrix2[6]) + (Matrix1[2] * Matrix2[10]) + (Matrix1[3] * Matrix2[14]);
  Result[3]  = (Matrix1[0] * Matrix2[3]) + (Matrix1[1] * Matrix2[7]) + (Matrix1[2] * Matrix2[11]) + (Matrix1[3] * Matrix2[15]);

  Result[4]  = (Matrix1[4] * Matrix2[0]) + (Matrix1[5] * Matrix2[4]) + (Matrix1[6] * Matrix2[8]) + (Matrix1[7] * Matrix2[12]);
  Result[5]  = (Matrix1[4] * Matrix2[1]) + (Matrix1[5] * Matrix2[5]) + (Matrix1[6] * Matrix2[9]) + (Matrix1[7] * Matrix2[13]);
  Result[6]  = (Matrix1[4] * Matrix2[2]) + (Matrix1[5] * Matrix2[6]) + (Matrix1[6] * Matrix2[10]) + (Matrix1[7] * Matrix2[14]);
  Result[7]  = (Matrix1[4] * Matrix2[3]) + (Matrix1[5] * Matrix2[7]) + (Matrix1[6] * Matrix2[11]) + (Matrix1[7] * Matrix2[15]);

  Result[8]  = (Matrix1[8] * Matrix2[0]) + (Matrix1[9] * Matrix2[4]) + (Matrix1[10] * Matrix2[8]) + (Matrix1[11] * Matrix2[12]);
  Result[9]  = (Matrix1[8] * Matrix2[1]) + (Matrix1[9] * Matrix2[5]) + (Matrix1[10] * Matrix2[9]) + (Matrix1[11] * Matrix2[13]);
  Result[10] = (Matrix1[8] * Matrix2[2]) + (Matrix1[9] * Matrix2[6]) + (Matrix1[10] * Matrix2[10]) + (Matrix1[11] * Matrix2[14]);
  Result[11] = (Matrix1[8] * Matrix2[3]) + (Matrix1[9] * Matrix2[7]) + (Matrix1[10] * Matrix2[11]) + (Matrix1[11] * Matrix2[15]);

  Result[12] = (Matrix1[12] * Matrix2[0]) + (Matrix1[13] * Matrix2[4]) + (Matrix1[14] * Matrix2[8]) + (Matrix1[15] * Matrix2[12]);
  Result[13] = (Matrix1[12] * Matrix2[1]) + (Matrix1[13] * Matrix2[5]) + (Matrix1[14] * Matrix2[9]) + (Matrix1[15] * Matrix2[13]);
  Result[14] = (Matrix1[12] * Matrix2[2]) + (Matrix1[13] * Matrix2[6]) + (Matrix1[14] * Matrix2[10]) + (Matrix1[15] * Matrix2[14]);
  Result[15] = (Matrix1[12] * Matrix2[3]) + (Matrix1[13] * Matrix2[7]) + (Matrix1[14] * Matrix2[11]) + (Matrix1[15] * Matrix2[15]);
}


void GLMatrixInverse(f32 *Result, f32 *Matrix)
{
  f32 Inverse[16];

  Inverse[0] = Matrix[5]  * Matrix[10] * Matrix[15] -
               Matrix[5]  * Matrix[11] * Matrix[14] -
               Matrix[9]  * Matrix[6]  * Matrix[15] +
               Matrix[9]  * Matrix[7]  * Matrix[14] +
               Matrix[13] * Matrix[6]  * Matrix[11] -
               Matrix[13] * Matrix[7]  * Matrix[10];

  Inverse[4] = -Matrix[4]  * Matrix[10] * Matrix[15] +
    Matrix[4]  * Matrix[11] * Matrix[14] +
    Matrix[8]  * Matrix[6]  * Matrix[15] -
    Matrix[8]  * Matrix[7]  * Matrix[14] -
    Matrix[12] * Matrix[6]  * Matrix[11] +
    Matrix[12] * Matrix[7]  * Matrix[10];

  Inverse[8] = Matrix[4]  * Matrix[9] * Matrix[15] -
    Matrix[4]  * Matrix[11] * Matrix[13] -
    Matrix[8]  * Matrix[5] * Matrix[15] +
    Matrix[8]  * Matrix[7] * Matrix[13] +
    Matrix[12] * Matrix[5] * Matrix[11] -
    Matrix[12] * Matrix[7] * Matrix[9];

  Inverse[12] = -Matrix[4]  * Matrix[9] * Matrix[14] +
    Matrix[4]  * Matrix[10] * Matrix[13] +
    Matrix[8]  * Matrix[5] * Matrix[14] -
    Matrix[8]  * Matrix[6] * Matrix[13] -
    Matrix[12] * Matrix[5] * Matrix[10] +
    Matrix[12] * Matrix[6] * Matrix[9];

  Inverse[1] = -Matrix[1]  * Matrix[10] * Matrix[15] +
    Matrix[1]  * Matrix[11] * Matrix[14] +
    Matrix[9]  * Matrix[2] * Matrix[15] -
    Matrix[9]  * Matrix[3] * Matrix[14] -
    Matrix[13] * Matrix[2] * Matrix[11] +
    Matrix[13] * Matrix[3] * Matrix[10];

  Inverse[5] = Matrix[0]  * Matrix[10] * Matrix[15] -
    Matrix[0]  * Matrix[11] * Matrix[14] -
    Matrix[8]  * Matrix[2] * Matrix[15] +
    Matrix[8]  * Matrix[3] * Matrix[14] +
    Matrix[12] * Matrix[2] * Matrix[11] -
    Matrix[12] * Matrix[3] * Matrix[10];

  Inverse[9] = -Matrix[0]  * Matrix[9] * Matrix[15] +
    Matrix[0]  * Matrix[11] * Matrix[13] +
    Matrix[8]  * Matrix[1] * Matrix[15] -
    Matrix[8]  * Matrix[3] * Matrix[13] -
    Matrix[12] * Matrix[1] * Matrix[11] +
    Matrix[12] * Matrix[3] * Matrix[9];

  Inverse[13] = Matrix[0]  * Matrix[9] * Matrix[14] -
    Matrix[0]  * Matrix[10] * Matrix[13] -
    Matrix[8]  * Matrix[1] * Matrix[14] +
    Matrix[8]  * Matrix[2] * Matrix[13] +
    Matrix[12] * Matrix[1] * Matrix[10] -
    Matrix[12] * Matrix[2] * Matrix[9];

  Inverse[2] = Matrix[1]  * Matrix[6] * Matrix[15] -
    Matrix[1]  * Matrix[7] * Matrix[14] -
    Matrix[5]  * Matrix[2] * Matrix[15] +
    Matrix[5]  * Matrix[3] * Matrix[14] +
    Matrix[13] * Matrix[2] * Matrix[7] -
    Matrix[13] * Matrix[3] * Matrix[6];

  Inverse[6] = -Matrix[0]  * Matrix[6] * Matrix[15] +
    Matrix[0]  * Matrix[7] * Matrix[14] +
    Matrix[4]  * Matrix[2] * Matrix[15] -
    Matrix[4]  * Matrix[3] * Matrix[14] -
    Matrix[12] * Matrix[2] * Matrix[7] +
    Matrix[12] * Matrix[3] * Matrix[6];

  Inverse[10] = Matrix[0]  * Matrix[5] * Matrix[15] -
    Matrix[0]  * Matrix[7] * Matrix[13] -
    Matrix[4]  * Matrix[1] * Matrix[15] +
    Matrix[4]  * Matrix[3] * Matrix[13] +
    Matrix[12] * Matrix[1] * Matrix[7] -
    Matrix[12] * Matrix[3] * Matrix[5];

  Inverse[14] = -Matrix[0]  * Matrix[5] * Matrix[14] +
    Matrix[0]  * Matrix[6] * Matrix[13] +
    Matrix[4]  * Matrix[1] * Matrix[14] -
    Matrix[4]  * Matrix[2] * Matrix[13] -
    Matrix[12] * Matrix[1] * Matrix[6] +
    Matrix[12] * Matrix[2] * Matrix[5];

  Inverse[3] = -Matrix[1] * Matrix[6] * Matrix[11] +
    Matrix[1] * Matrix[7] * Matrix[10] +
    Matrix[5] * Matrix[2] * Matrix[11] -
    Matrix[5] * Matrix[3] * Matrix[10] -
    Matrix[9] * Matrix[2] * Matrix[7] +
    Matrix[9] * Matrix[3] * Matrix[6];

  Inverse[7] = Matrix[0] * Matrix[6] * Matrix[11] -
    Matrix[0] * Matrix[7] * Matrix[10] -
    Matrix[4] * Matrix[2] * Matrix[11] +
    Matrix[4] * Matrix[3] * Matrix[10] +
    Matrix[8] * Matrix[2] * Matrix[7] -
    Matrix[8] * Matrix[3] * Matrix[6];

  Inverse[11] = -Matrix[0] * Matrix[5] * Matrix[11] +
    Matrix[0] * Matrix[7] * Matrix[9] +
    Matrix[4] * Matrix[1] * Matrix[11] -
    Matrix[4] * Matrix[3] * Matrix[9] -
    Matrix[8] * Matrix[1] * Matrix[7] +
    Matrix[8] * Matrix[3] * Matrix[5];

  Inverse[15] = Matrix[0] * Matrix[5] * Matrix[10] -
    Matrix[0] * Matrix[6] * Matrix[9] -
    Matrix[4] * Matrix[1] * Matrix[10] +
    Matrix[4] * Matrix[2] * Matrix[9] +
    Matrix[8] * Matrix[1] * Matrix[6] -
    Matrix[8] * Matrix[2] * Matrix[5];

  f32 Determinant = (Matrix[0] * Inverse[0]) + (Matrix[1] * Inverse[4]) + (Matrix[2] * Inverse[8]) + (Matrix[3] * Inverse[12]);
  // Prevent divide by zero.
  if(Determinant == 0.0f)
  {
    Determinant = 0.00001f;
  }

  Determinant = 1.0f / Determinant;

  for( s32 inverse_i = 0; inverse_i < 16; ++inverse_i )
  {
    Result[inverse_i] = Inverse[inverse_i] * Determinant;
  }
}

void GLBuildIdentityMatrix(f32 *Matrix)
{
  Matrix[0] = 1.0f;
  Matrix[1] = 0.0f;
  Matrix[2] = 0.0f;
  Matrix[3] = 0.0f;

  Matrix[4] = 0.0f;
  Matrix[5] = 1.0f;
  Matrix[6] = 0.0f;
  Matrix[7] = 0.0f;

  Matrix[8] = 0.0f;
  Matrix[9] = 0.0f;
  Matrix[10] = 1.0f;
  Matrix[11] = 0.0f;

  Matrix[12] = 0.0f;
  Matrix[13] = 0.0f;
  Matrix[14] = 0.0f;
  Matrix[15] = 1.0f;
}

void GLBuildPerspectiveFovMatrix(f32 *Matrix,
                                 f32 FieldOfView,
                                 f32 ScreenAspect,
                                 f32 ScreenNear,
                                 f32 ScreenDepth
                                 )
{
  Matrix[0] = 1.0f / (ScreenAspect * tan(FieldOfView * 0.5f));
  Matrix[1] = 0.0f;
  Matrix[2] = 0.0f;
  Matrix[3] = 0.0f;

  Matrix[4] = 0.0f;
  Matrix[5] = 1.0f / tan(FieldOfView * 0.5f);
  Matrix[6] = 0.0f;
  Matrix[7] = 0.0f;

  Matrix[8] = 0.0f;
  Matrix[9] = 0.0f;
  Matrix[10] = ScreenDepth/(ScreenDepth - ScreenNear);
  Matrix[11] = 1.0f;

  Matrix[12] = 0.0f;
  Matrix[13] = 0.0f;
  Matrix[14] = (-ScreenNear * ScreenDepth)/(ScreenDepth - ScreenNear);
  Matrix[15] = 0.0f;
}

void GLBuildOrthoMatrix(f32 *Matrix, f32 ScreenWidth, f32 ScreenHeight, f32 ScreenNear, f32 ScreenDepth )
{
  Matrix[0] = 2.0f/ ScreenWidth;
  Matrix[1] = 0.0f;
  Matrix[2] = 0.0f;
  Matrix[3] = 0.0f;

  Matrix[4] = 0.0f;
  Matrix[5] = 2.0f / ScreenHeight;
  Matrix[6] = 0.0f;
  Matrix[7] = 0.0f;

  Matrix[8] = 0.0f;
  Matrix[9] = 0.0f;
  Matrix[10] = 1.0f / (ScreenDepth - ScreenNear);
  Matrix[11] = 0.0f;

  Matrix[12] = 0.0f;
  Matrix[13] = 0.0f;
  Matrix[14] = ScreenNear / (ScreenNear - ScreenDepth);
  Matrix[15] = 1.0f;
}

void GLPrintMatrix16( f32 *Matrix, const char *Name )
{
  printf("----%s \n", Name);
  for(size_t i = 0; i < 16; i+=4 )
  {
    printf( "%f %f %f %f \n", Matrix[i], Matrix[i+1], Matrix[i+2], Matrix[i+3] );
  }
}
