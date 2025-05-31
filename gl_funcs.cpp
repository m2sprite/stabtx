b32 LoadOpenGLExtensionList(openGLFnPtr_t *OpenGLFunctions)
{
  OpenGLFunctions->glCreateShader = (PFNGLCREATESHADERPROC)glXGetProcAddress((unsigned char*)"glCreateShader");
  if(!OpenGLFunctions->glCreateShader)
  {
    return false;
  }

  OpenGLFunctions->glShaderSource = (PFNGLSHADERSOURCEPROC)glXGetProcAddress((unsigned char*)"glShaderSource");
  if(!OpenGLFunctions->glShaderSource)
  {
    return false;
  }

  OpenGLFunctions->glCompileShader = (PFNGLCOMPILESHADERPROC)glXGetProcAddress((unsigned char*)"glCompileShader");
  if(!OpenGLFunctions->glCompileShader)
  {
    return false;
  }

  OpenGLFunctions->glGetShaderiv = (PFNGLGETSHADERIVPROC)glXGetProcAddress((unsigned char*)"glGetShaderiv");
  if(!OpenGLFunctions->glGetShaderiv)
  {
    return false;
  }

  OpenGLFunctions->glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glXGetProcAddress((unsigned char*)"glGetShaderInfoLog");
  if(!OpenGLFunctions->glGetShaderInfoLog)
  {
    return false;
  }

  OpenGLFunctions->glCreateProgram = (PFNGLCREATEPROGRAMPROC)glXGetProcAddress((unsigned char*)"glCreateProgram");
  if(!OpenGLFunctions->glCreateProgram)
  {
    return false;
  }

  OpenGLFunctions->glAttachShader = (PFNGLATTACHSHADERPROC)glXGetProcAddress((unsigned char*)"glAttachShader");
  if(!OpenGLFunctions->glAttachShader)
  {
    return false;
  }

  OpenGLFunctions->glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glXGetProcAddress((unsigned char*)"glBindAttribLocation");
  if(!OpenGLFunctions->glBindAttribLocation)
  {
    return false;
  }

  OpenGLFunctions->glLinkProgram = (PFNGLLINKPROGRAMPROC)glXGetProcAddress((unsigned char*)"glLinkProgram");
  if(!OpenGLFunctions->glLinkProgram)
  {
    return false;
  }

  OpenGLFunctions->glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glXGetProcAddress((unsigned char*)"glGetProgramiv");
  if(!OpenGLFunctions->glGetProgramiv)
  {
    return false;
  }

  OpenGLFunctions->glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glXGetProcAddress((unsigned char*)"glGetProgramInfoLog");
  if(!OpenGLFunctions->glGetProgramInfoLog)
  {
    return false;
  }

  OpenGLFunctions->glDetachShader = (PFNGLDETACHSHADERPROC)glXGetProcAddress((unsigned char*)"glDetachShader");
  if(!OpenGLFunctions->glDetachShader)
  {
    return false;
  }

  OpenGLFunctions->glDeleteShader = (PFNGLDELETESHADERPROC)glXGetProcAddress((unsigned char*)"glDeleteShader");
  if(!OpenGLFunctions->glDeleteShader)
  {
    return false;
  }

  OpenGLFunctions->glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glXGetProcAddress((unsigned char*)"glDeleteProgram");
  if(!OpenGLFunctions->glDeleteProgram)
  {
    return false;
  }

  OpenGLFunctions->glUseProgram = (PFNGLUSEPROGRAMPROC)glXGetProcAddress((unsigned char*)"glUseProgram");
  if(!OpenGLFunctions->glUseProgram)
  {
    return false;
  }

  OpenGLFunctions->glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glXGetProcAddress((unsigned char*)"glGetUniformLocation");
  if(!OpenGLFunctions->glGetUniformLocation)
  {
    return false;
  }

  OpenGLFunctions->glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glXGetProcAddress((unsigned char*)"glUniformMatrix4fv");
  if(!OpenGLFunctions->glUniformMatrix4fv)
  {
    return false;
  }

  OpenGLFunctions->glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glXGetProcAddress((unsigned char*)"glGenVertexArrays");
  if(!OpenGLFunctions->glGenVertexArrays)
  {
    return false;
  }

  OpenGLFunctions->glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glXGetProcAddress((unsigned char*)"glBindVertexArray");
  if(!OpenGLFunctions->glBindVertexArray)
  {
    return false;
  }

  OpenGLFunctions->glGenBuffers = (PFNGLGENBUFFERSPROC)glXGetProcAddress((unsigned char*)"glGenBuffers");
  if(!OpenGLFunctions->glGenBuffers)
  {
    return false;
  }

  OpenGLFunctions->glBindBuffer = (PFNGLBINDBUFFERPROC)glXGetProcAddress((unsigned char*)"glBindBuffer");
  if(!OpenGLFunctions->glBindBuffer)
  {
    return false;
  }

  OpenGLFunctions->glBufferData = (PFNGLBUFFERDATAPROC)glXGetProcAddress((unsigned char*)"glBufferData");
  if(!OpenGLFunctions->glBufferData)
  {
    return false;
  }

  OpenGLFunctions->glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glXGetProcAddress((unsigned char*)"glEnableVertexAttribArray");
  if(!OpenGLFunctions->glEnableVertexAttribArray)
  {
    return false;
  }

  OpenGLFunctions->glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glXGetProcAddress((unsigned char*)"glVertexAttribPointer");
  if(!OpenGLFunctions->glVertexAttribPointer)
  {
    return false;
  }

  OpenGLFunctions->glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glXGetProcAddress((unsigned char*)"glDeleteBuffers");
  if(!OpenGLFunctions->glDeleteBuffers)
  {
    return false;
  }

  OpenGLFunctions->glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glXGetProcAddress((unsigned char*)"glDeleteVertexArrays");
  if(!OpenGLFunctions->glDeleteVertexArrays)
  {
    return false;
  }

  OpenGLFunctions->glUniform1i = (PFNGLUNIFORM1IPROC)glXGetProcAddress((unsigned char*)"glUniform1i");
  if(!OpenGLFunctions->glUniform1i)
  {
    return false;
  }

  OpenGLFunctions->glActiveTexture = (PFNGLACTIVETEXTUREPROC)glXGetProcAddress((unsigned char*)"glActiveTexture");
  if(!OpenGLFunctions->glActiveTexture)
  {
    return false;
  }

  OpenGLFunctions->glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glXGetProcAddress((unsigned char*)"glGenerateMipmap");
  if(!OpenGLFunctions->glGenerateMipmap)
  {
    return false;
  }

  OpenGLFunctions->glUniform2fv = (PFNGLUNIFORM2FVPROC)glXGetProcAddress((unsigned char*)"glUniform2fv");
  if(!OpenGLFunctions->glUniform2fv)
  {
    return false;
  }

  OpenGLFunctions->glUniform3fv = (PFNGLUNIFORM3FVPROC)glXGetProcAddress((unsigned char*)"glUniform3fv");
  if(!OpenGLFunctions->glUniform3fv)
  {
    return false;
  }

  OpenGLFunctions->glUniform4fv = (PFNGLUNIFORM4FVPROC)glXGetProcAddress((unsigned char*)"glUniform4fv");
  if(!OpenGLFunctions->glUniform4fv)
  {
    return false;
  }

  OpenGLFunctions->glMapBuffer = (PFNGLMAPBUFFERPROC)glXGetProcAddress((unsigned char*)"glMapBuffer");
  if(!OpenGLFunctions->glMapBuffer)
  {
    return false;
  }

  OpenGLFunctions->glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)glXGetProcAddress((unsigned char*)"glUnmapBuffer");
  if(!OpenGLFunctions->glUnmapBuffer)
  {
    return false;
  }

  OpenGLFunctions->glXSwapIntervalEXT = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddress((unsigned char*)"glXSwapIntervalEXT");
  if(!OpenGLFunctions->glXSwapIntervalEXT)
  {
    return false;
  }

  OpenGLFunctions->glUniform1f = (PFNGLUNIFORM1FPROC)glXGetProcAddress((unsigned char*)"glUniform1f");
  if(!OpenGLFunctions->glUniform1f)
  {
    return false;
  }

  OpenGLFunctions->glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char*)"glGenFramebuffers");
  if(!OpenGLFunctions->glGenFramebuffers)
  {
    return false;
  }

  OpenGLFunctions->glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glXGetProcAddress((unsigned char*)"glDeleteFramebuffers");
  if(!OpenGLFunctions->glDeleteFramebuffers)
  {
    return false;
  }

  OpenGLFunctions->glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glXGetProcAddress((unsigned char*)"glBindFramebuffer");
  if(!OpenGLFunctions->glBindFramebuffer)
  {
    return false;
  }

  OpenGLFunctions->glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)glXGetProcAddress((unsigned char*)"glFramebufferTexture2D");
  if(!OpenGLFunctions->glFramebufferTexture2D)
  {
    return false;
  }

  OpenGLFunctions->glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)glXGetProcAddress((unsigned char*)"glGenRenderbuffers");
  if(!OpenGLFunctions->glGenRenderbuffers)
  {
    return false;
  }

  OpenGLFunctions->glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)glXGetProcAddress((unsigned char*)"glBindRenderbuffer");
  if(!OpenGLFunctions->glBindRenderbuffer)
  {
    return false;
  }

  OpenGLFunctions->glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)glXGetProcAddress((unsigned char*)"glRenderbufferStorage");
  if(!OpenGLFunctions->glRenderbufferStorage)
  {
    return false;
  }

  OpenGLFunctions->glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glXGetProcAddress((unsigned char*)"glFramebufferRenderbuffer");
  if(!OpenGLFunctions->glFramebufferRenderbuffer)
  {
    return false;
  }

  OpenGLFunctions->glDrawBuffers = (PFNGLDRAWBUFFERSARBPROC)glXGetProcAddress((unsigned char*)"glDrawBuffers");
  if(!OpenGLFunctions->glDrawBuffers)
  {
    return false;
  }

  OpenGLFunctions->glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)glXGetProcAddress((unsigned char*)"glDeleteRenderbuffers");
  if(!OpenGLFunctions->glDeleteRenderbuffers)
  {
    return false;
  }

  OpenGLFunctions->glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)glXGetProcAddress((unsigned char*)"glBlendFuncSeparate");
  if(!OpenGLFunctions->glBlendFuncSeparate)
  {
    return false;
  }

  return(true);
}
