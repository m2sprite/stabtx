#include "gl_matrix.h"
#include "gl_matrix.cpp"

b32 LoadOpenGLExtensionList(void)
{
  glCreateShader = (PFNGLCREATESHADERPROC)glXGetProcAddress((unsigned char*)"glCreateShader");
  if(!glCreateShader)
  {
    return false;
  }

  glShaderSource = (PFNGLSHADERSOURCEPROC)glXGetProcAddress((unsigned char*)"glShaderSource");
  if(!glShaderSource)
  {
    return false;
  }

  glCompileShader = (PFNGLCOMPILESHADERPROC)glXGetProcAddress((unsigned char*)"glCompileShader");
  if(!glCompileShader)
  {
    return false;
  }

  glGetShaderiv = (PFNGLGETSHADERIVPROC)glXGetProcAddress((unsigned char*)"glGetShaderiv");
  if(!glGetShaderiv)
  {
    return false;
  }

  glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glXGetProcAddress((unsigned char*)"glGetShaderInfoLog");
  if(!glGetShaderInfoLog)
  {
    return false;
  }

  glCreateProgram = (PFNGLCREATEPROGRAMPROC)glXGetProcAddress((unsigned char*)"glCreateProgram");
  if(!glCreateProgram)
  {
    return false;
  }

  glAttachShader = (PFNGLATTACHSHADERPROC)glXGetProcAddress((unsigned char*)"glAttachShader");
  if(!glAttachShader)
  {
    return false;
  }

  glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glXGetProcAddress((unsigned char*)"glBindAttribLocation");
  if(!glBindAttribLocation)
  {
    return false;
  }

  glLinkProgram = (PFNGLLINKPROGRAMPROC)glXGetProcAddress((unsigned char*)"glLinkProgram");
  if(!glLinkProgram)
  {
    return false;
  }

  glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glXGetProcAddress((unsigned char*)"glGetProgramiv");
  if(!glGetProgramiv)
  {
    return false;
  }

  glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glXGetProcAddress((unsigned char*)"glGetProgramInfoLog");
  if(!glGetProgramInfoLog)
  {
    return false;
  }

  glDetachShader = (PFNGLDETACHSHADERPROC)glXGetProcAddress((unsigned char*)"glDetachShader");
  if(!glDetachShader)
  {
    return false;
  }

  glDeleteShader = (PFNGLDELETESHADERPROC)glXGetProcAddress((unsigned char*)"glDeleteShader");
  if(!glDeleteShader) {
    return false;
  }

  glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glXGetProcAddress((unsigned char*)"glDeleteProgram");
  if(!glDeleteProgram) {
    return false;
  }

  glUseProgram = (PFNGLUSEPROGRAMPROC)glXGetProcAddress((unsigned char*)"glUseProgram");
  if(!glUseProgram)
  {
    return false;
  }

  glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glXGetProcAddress((unsigned char*)"glGetUniformLocation");
  if(!glGetUniformLocation)
  {
    return false;
  }

  glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glXGetProcAddress((unsigned char*)"glUniformMatrix4fv");
  if(!glUniformMatrix4fv)
  {
    return false;
  }

  glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glXGetProcAddress((unsigned char*)"glGenVertexArrays");
  if(!glGenVertexArrays)
  {
    return false;
  }

  glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glXGetProcAddress((unsigned char*)"glBindVertexArray");
  if(!glBindVertexArray)
  {
    return false;
  }

  glGenBuffers = (PFNGLGENBUFFERSPROC)glXGetProcAddress((unsigned char*)"glGenBuffers");
  if(!glGenBuffers)
  {
    return false;
  }

  glBindBuffer = (PFNGLBINDBUFFERPROC)glXGetProcAddress((unsigned char*)"glBindBuffer");
  if(!glBindBuffer)
  {
    return false;
  }

  glBufferData = (PFNGLBUFFERDATAPROC)glXGetProcAddress((unsigned char*)"glBufferData");
  if(!glBufferData)
  {
    return false;
  }

  glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glXGetProcAddress((unsigned char*)"glEnableVertexAttribArray");
  if(!glEnableVertexAttribArray)
  {
    return false;
  }

  glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glXGetProcAddress((unsigned char*)"glVertexAttribPointer");
  if(!glVertexAttribPointer)
  {
    return false;
  }

  glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glXGetProcAddress((unsigned char*)"glDeleteBuffers");
  if(!glDeleteBuffers)
  {
    return false;
  }

  glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glXGetProcAddress((unsigned char*)"glDeleteVertexArrays");
  if(!glDeleteVertexArrays)
  {
    return false;
  }

  glUniform1i = (PFNGLUNIFORM1IPROC)glXGetProcAddress((unsigned char*)"glUniform1i");
  if(!glUniform1i)
  {
    return false;
  }

  /*
  glActiveTexture = (PFNGLACTIVETEXTUREPROC)glXGetProcAddress((unsigned char*)"glActiveTexture");
  if(!glActiveTexture)
  {
    return false;
  }
  */

  glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glXGetProcAddress((unsigned char*)"glGenerateMipmap");
  if(!glGenerateMipmap)
  {
    return false;
  }

  glUniform2fv = (PFNGLUNIFORM2FVPROC)glXGetProcAddress((unsigned char*)"glUniform2fv");
  if(!glUniform2fv)
  {
    return false;
  }

  glUniform3fv = (PFNGLUNIFORM3FVPROC)glXGetProcAddress((unsigned char*)"glUniform3fv");
  if(!glUniform3fv)
  {
    return false;
  }

  glUniform4fv = (PFNGLUNIFORM4FVPROC)glXGetProcAddress((unsigned char*)"glUniform4fv");
  if(!glUniform4fv)
  {
    return false;
  }

  glMapBuffer = (PFNGLMAPBUFFERPROC)glXGetProcAddress((unsigned char*)"glMapBuffer");
  if(!glMapBuffer)
  {
    return false;
  }

  glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)glXGetProcAddress((unsigned char*)"glUnmapBuffer");
  if(!glUnmapBuffer)
  {
    return false;
  }

  glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((unsigned char*)"glXSwapIntervalEXT");
  if(!glXSwapIntervalEXT)
  {
    return false;
  }

  glUniform1f = (PFNGLUNIFORM1FPROC)glXGetProcAddress((unsigned char*)"glUniform1f");
  if(!glUniform1f)
  {
    return false;
  }

  glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char*)"glGenFramebuffers");
  if(!glGenFramebuffers)
  {
    return false;
  }

  glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char*)"glDeleteFramebuffers");
  if(!glDeleteFramebuffers)
  {
    return false;
  }

  glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glXGetProcAddress((unsigned char*)"glBindFramebuffer");
  if(!glBindFramebuffer)
  {
    return false;
  }

  glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)glXGetProcAddress((unsigned char*)"glFramebufferTexture2D");
  if(!glFramebufferTexture2D)
  {
    return false;
  }

  glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)glXGetProcAddress((unsigned char*)"glGenRenderbuffers");
  if(!glGenRenderbuffers)
  {
    return false;
  }

  glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)glXGetProcAddress((unsigned char*)"glBindRenderbuffer");
  if(!glBindRenderbuffer)
  {
    return false;
  }

  glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)glXGetProcAddress((unsigned char*)"glRenderbufferStorage");
  if(!glRenderbufferStorage)
  {
    return false;
  }

  glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glXGetProcAddress((unsigned char*)"glFramebufferRenderbuffer");
  if(!glFramebufferRenderbuffer)
  {
    return false;
  }

  glDrawBuffers = (PFNGLDRAWBUFFERSARBPROC)glXGetProcAddress((unsigned char*)"glDrawBuffers");
  if(!glDrawBuffers)
  {
    return false;
  }

  glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)glXGetProcAddress((unsigned char*)"glDeleteRenderbuffers");
  if(!glDeleteRenderbuffers)
  {
    return false;
  }

  glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)glXGetProcAddress((unsigned char*)"glBlendFuncSeparate");
  if(!glBlendFuncSeparate)
  {
    return false;
  }

  return(true);
}

void TurnZBufferOn(void)
{
  glEnable(GL_DEPTH_TEST);
}

void TurnZBufferOff(void)
{
  glDisable(GL_DEPTH_TEST);
}

b32 InitializeOpenGL( Display *MainVideoDisplay,/* Window win, */s32 ScreenWidth, s32 ScreenHeight, f32 ScreenNear, f32 ScreenDepth, b32 Vsync,  f32 WorldMatrix[16], f32 ProjectionMatrix[16], f32 OrthoMatrix[16] )
{
  if(!LoadOpenGLExtensionList())
  {
    LogFatal(ERROR, "Failed to Load OpenGL functions");
  }

  glClearDepth(1.0f);
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CW);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  GLXDrawable Drawable = glXGetCurrentDrawable();

  if(Vsync)
  {
    glXSwapIntervalEXT( MainVideoDisplay, Drawable, 1);
  }
  else
  {
    glXSwapIntervalEXT( MainVideoDisplay, Drawable, 0);
  }

  GLBuildIdentityMatrix( WorldMatrix );
  f32 FieldOfView = 3.14159265358979323846f / 4.0f;
  f32 ScreenAspect = (f32)ScreenWidth/(f32)ScreenHeight;

  GLBuildPerspectiveFovMatrix( ProjectionMatrix, FieldOfView, ScreenAspect, ScreenNear, ScreenDepth );
  GLBuildOrthoMatrix( OrthoMatrix, (f32)ScreenHeight, (f32)ScreenHeight, ScreenNear, ScreenDepth);

  return true;
}

