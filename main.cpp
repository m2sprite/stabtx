#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "htabtx_types.h"
#include "htabtx_log.h"
#include "gl.h"
#include "gl.cpp"

#define KEY_SUPPORT_COUNT 1
global b32 FULL_SCREEN = false;
global b32 VSYNC_ENABLED = true;

global s32 KEY_ESCAPE = 0;

global f32 SCREEN_NEAR = 0.3f;
global f32 SCREEN_DEPTH = 1000.0f;

#define TEMP_SHADER_ERROR_MESSAGES_SIZE 10240
global char TempGLErrorMessagesHere[TEMP_SHADER_ERROR_MESSAGES_SIZE];

struct vertex_t {
  f32 x;
  f32 y;
  f32 z;
  f32 r;
  f32 g;
  f32 b;
};

void PrintVertex( vertex_t Vertex )
{
  printf( " x %f y %f z %f \n", Vertex.x, Vertex.y, Vertex.z );
  printf( " r %f g %f b %f \n", Vertex.r, Vertex.g, Vertex.b );
}

b32 X11InitializeWindow( s32 *ScreenWidth, s32 *ScreenHeight, Display *Monitors, Window *MainWindow, GLXContext *GLRenderingContext )
{
  Window RootWindow = DefaultRootWindow(Monitors);
  GLint GLAttributeList[15];
  GLAttributeList[0] = GLX_RGBA;// support 24bit color and an alpha channel
  GLAttributeList[1] = GLX_DEPTH_SIZE;// support for 24 bit depth buffer;
  GLAttributeList[2] = 24;
  GLAttributeList[3] = GLX_STENCIL_SIZE;
  GLAttributeList[4] = 8;
  GLAttributeList[5] = GLX_DOUBLEBUFFER; //Support for double buffering.
  GLAttributeList[6] = GLX_RED_SIZE; //8 bits for each channel
  GLAttributeList[7] = 8;
  GLAttributeList[8] = GLX_GREEN_SIZE;
  GLAttributeList[9] = 8;
  GLAttributeList[10] = GLX_BLUE_SIZE;
  GLAttributeList[11] = 8;
  GLAttributeList[12] = GLX_ALPHA_SIZE;
  GLAttributeList[13] = 8;
  GLAttributeList[14] = None;

  XVisualInfo *VisualInfo;
  VisualInfo = glXChooseVisual(Monitors, 0, GLAttributeList);

  if(!VisualInfo)
  {
    return false;
  }

  Colormap ColorMap = XCreateColormap(Monitors, RootWindow, VisualInfo->visual, AllocNone);

  Screen *DefaultMonitor = XDefaultScreenOfDisplay( Monitors );

  if(FULL_SCREEN)
  {
    *ScreenWidth = XWidthOfScreen( DefaultMonitor );
    *ScreenHeight = XHeightOfScreen( DefaultMonitor );
  }
  else
  {
    *ScreenWidth = 1024;
    *ScreenHeight = 768;
  }

  // Fill out the structure for setting the window attributes.
  XSetWindowAttributes SetWindowAttributes;
  SetWindowAttributes.colormap = ColorMap;
  SetWindowAttributes.event_mask = KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask;

  *MainWindow = XCreateWindow( Monitors, RootWindow, 0, 0, *ScreenWidth, *ScreenHeight, 0, VisualInfo->depth, InputOutput, VisualInfo->visual, CWColormap | CWEventMask, &SetWindowAttributes);

  XMapWindow( Monitors, *MainWindow);
  XStoreName( Monitors, *MainWindow, "STABTX");

  if(FULL_SCREEN)
  {
    Atom WmState = XInternAtom( Monitors, "_NET_WM_STATE",False);
    Atom FullScreenState = XInternAtom( Monitors, "_NET_WM_STATE_FULLSCREEN",False);
    XEvent FullScreenEvent;
    memset(&FullScreenEvent, 0, sizeof(FullScreenEvent));

    FullScreenEvent.type = ClientMessage;
    FullScreenEvent.xclient.window = *MainWindow;
    FullScreenEvent.xclient.message_type = WmState;
    FullScreenEvent.xclient.format = 32;
    FullScreenEvent.xclient.data.l[0] = 1;
    FullScreenEvent.xclient.data.l[1] = FullScreenState;
    FullScreenEvent.xclient.data.l[2] = 0;
    FullScreenEvent.xclient.data.l[3] = 0;
    FullScreenEvent.xclient.data.l[4] = 0;

    if( XSendEvent(Monitors, DefaultRootWindow(Monitors), False, SubstructureRedirectMask | SubstructureNotifyMask, &FullScreenEvent) )
    {
      LogFatal( ERROR, "Failed to Send FullScreenEvent" );
    }

    Atom MotifHints = XInternAtom( Monitors, "MOTIF_WM_HINTS", False);
    s32 MotifHintList[5];
    MotifHintList[0] = 2;
    MotifHintList[1] = 0;
    MotifHintList[2] = 0;
    MotifHintList[3] = 0;
    MotifHintList[4] = 0;

    if( XChangeProperty(Monitors, *MainWindow, MotifHints,MotifHints, 32, PropModeReplace, (unsigned char*)&MotifHintList, 5) )
    {
      LogFatal( ERROR, "XChangeProperty Failed");
    }

    if( XFlush( Monitors ) )
    {
      LogFatal( ERROR, "XFulsh Failed");
    }
    sleep(1);
  }

  *GLRenderingContext = glXCreateContext(Monitors, VisualInfo, 0, GL_TRUE);
  if(!(*GLRenderingContext))
  {
    LogFatal( ERROR, "Failed to create glContext");
  }

  if( !(glXMakeCurrent(Monitors, *MainWindow, *GLRenderingContext)) )
  {
    LogFatal( ERROR, "Failed glXMakeCurrent");
  }

  s32 MajorVersion;
  glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);

  if(MajorVersion < 4)
  {
    LogFatal( ERROR, "Failed to get GL Major Version");
  }

  if( !(glXIsDirect(Monitors, *GLRenderingContext)) )
  {
    LogFatal( ERROR, "glXIsDirect failed");
  }

  if(!FULL_SCREEN)
  {
    s32 DefaultScreenWidth = XWidthOfScreen( DefaultMonitor );
    s32 DefaultScreenHeight = XWidthOfScreen( DefaultMonitor );
    s32 PosX = (DefaultScreenWidth - *ScreenWidth)/2;
    s32 PosY = (DefaultScreenHeight - *ScreenHeight)/2;
    if( !(XMoveWindow(Monitors, *MainWindow, PosX, PosY)))
    {
      LogFatal( ERROR, "Failed to move window");
    }
  }

  return(true);
}

internal void X11ProcessKeyboardButtonState( b32 KeyboardState[KEY_SUPPORT_COUNT], KeySym KeySymbol, b32 State )
{
  switch(KeySymbol)
  {
    case(65307):{
      KeyboardState[KEY_ESCAPE] = State;
    } break;

    default:{
    } break;
  }
}

internal void X11ReadInput( Display *Monitors, Window *MainWindow, b32 KeyboardState[KEY_SUPPORT_COUNT], b32 *Running )
{
  XEvent UserEvent;
  char KeyBuffer[32];
  KeySym KeySymbol;
  s32 EventMask = KeyPressMask | KeyReleaseMask;

  //READ INPUT
  if(XCheckWindowEvent( Monitors, *MainWindow, EventMask, &UserEvent))
  {
    XLookupString(&UserEvent.xkey, KeyBuffer, sizeof(KeyBuffer), &KeySymbol, 0);
    Log(INFO, "%s", KeyBuffer);
    switch(UserEvent.type)
    {
      case(KeyPress):{
        X11ProcessKeyboardButtonState( KeyboardState, KeySymbol, 1);
      }break;

      case(KeyRelease):{
        X11ProcessKeyboardButtonState( KeyboardState, KeySymbol, 0);
      }break;

      default:{
      }break;
    }
  }
  //TAKE ACTION ON INPUT
  if(KeyboardState[KEY_ESCAPE])
  {
    *Running = false;
  }
}

typedef struct {
  char *Buffer;
  size_t CharCountNoNull;
  size_t Size;
} shaderFile_t;

typedef struct {
  char *Buffer;
  char *VertexShader;
  char *FragmentShader;
  size_t CharCountNoNulls;
  size_t Size;
} shaderFiles_t;

shaderFiles_t LoadShaderSrcFilePair( const char *VsFileName,  const char *FsFileName )
{
  shaderFiles_t Result = {};
  FILE *VsFile = fopen( VsFileName, "rb" );
  FILE *FsFile = fopen( FsFileName, "rb" );

  if( VsFile && FsFile )
  {
    fseek(VsFile, 0, SEEK_END);
    fseek(FsFile, 0, SEEK_END);
    size_t VsFileSize = ftell(VsFile);
    size_t FsFileSize = ftell(FsFile);
    size_t BytesToAlloc = VsFileSize+FsFileSize+2;
    rewind(VsFile);
    rewind(FsFile);
    Result.Buffer = (char *)malloc(BytesToAlloc);
    if(!Result.Buffer)
    {
      LogFatal( ERROR, "Failed to create buffer to read shaders into" );
    }
    Result.Size = BytesToAlloc;
    Result.CharCountNoNulls = BytesToAlloc-2;
    Result.VertexShader = Result.Buffer;
    Result.FragmentShader = Result.Buffer+VsFileSize+1;
    fread(Result.VertexShader, 1, VsFileSize, VsFile);
    Result.VertexShader[VsFileSize] = '\0';
    fread(Result.FragmentShader, 1, FsFileSize, FsFile);
    Result.FragmentShader[FsFileSize] = '\0';
    fclose( VsFile );
    fclose( FsFile );
  }
  else
  {
    if( !VsFile )
    {
      LogFatal( ERROR, "Failed to read in file %s", VsFileName );
    }

    if( !FsFile )
    {
      LogFatal( ERROR, "Failed to read in file %s", FsFileName );
    }
  }
  return(Result);
}

shaderFile_t LoadFileIntoBufferWithNullDelim( const char *FileName )
{
  shaderFile_t Result = {};
  FILE *File = fopen( FileName, "rb" );
  if( File )
  {
    fseek(File, 0, SEEK_END);
    size_t BytesToAlloc = ftell(File);
    rewind(File);
    Result.Buffer = (char *)malloc(BytesToAlloc+1);
    if(!Result.Buffer)
    {
      LogFatal( ERROR, "Failed to create buffer to read %s into", FileName );
    }

    Result.Size = BytesToAlloc+1;
    Result.CharCountNoNull = BytesToAlloc;
    fread(Result.Buffer, 1, BytesToAlloc, File);
    Result.Buffer[BytesToAlloc] = '\0';
    fclose( File );
  }
  else
  {
    LogFatal( ERROR, "Failed to read in file %s", FileName );
  }
  return(Result);
}

internal inline void CheckShader(GLuint ShaderId, GLenum GL_EXT, const char *ShaderType, const char *Action)
{
  s32 ShaderStatus;
  glGetShaderiv(ShaderId, GL_EXT, &ShaderStatus);
  if( !ShaderStatus )
  {
    GLint ShaderLogSize = 0;
    char *ShaderLogPlace = TempGLErrorMessagesHere;
    glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &ShaderLogSize);
    if ( ShaderLogSize > TEMP_SHADER_ERROR_MESSAGES_SIZE )
    {
      LogFatal(ERROR, "Shader Info Too big to fit in stack buffer");
    }
    glGetShaderInfoLog(ShaderId, ShaderLogSize, 0, ShaderLogPlace);
    TempGLErrorMessagesHere[ShaderLogSize] = '\0';
    printf( "[SHADER INFO]: %s\n",  TempGLErrorMessagesHere);
    LogFatal(ERROR, "Failed to %s %s shader", Action,ShaderType);
  }
}

internal inline void CheckProgram(GLuint ProgramId, GLenum GL_EXT, const char *ProgramType, const char *Action)
{
  s32 ProgramStatus;
  glGetProgramiv( ProgramId, GL_EXT, &ProgramStatus);
  if( ProgramStatus != 1 )
  {
    GLint ProgramLogSize = 0;
    char *ProgramLogPlace = TempGLErrorMessagesHere;
    glGetProgramiv(ProgramId, GL_INFO_LOG_LENGTH, &ProgramLogSize);
    if ( ProgramLogSize > TEMP_SHADER_ERROR_MESSAGES_SIZE )
    {
      LogFatal(ERROR, "Program Info Too big to fit in stack buffer");
    }
    glGetProgramInfoLog(ProgramId, ProgramLogSize, 0, ProgramLogPlace);
    TempGLErrorMessagesHere[ProgramLogSize] = '\0';
    printf( "[PROGRAM INFO]: %s\n",  TempGLErrorMessagesHere);
    LogFatal(ERROR, "Failed to %s %s shader", Action,ProgramType);
  }
}

typedef struct {
  vertex_t *Verticies;
  u32 *Indecies;
  u32 VertexCount;
  u32 IndexCount;
  GLuint VertexArrayId;
  GLuint VertexBufferId;
  GLuint IndexBufferId;
} glModel_t;

glModel_t GiveGlModel( u32 VertexCount, u32 IndexCount, vertex_t *Floats) {

  glModel_t Result;

  Result.Verticies = Floats;

  if( !Result.Verticies )
  {
    LogFatal(ERROR, "Vertex buffer creation failed");
  }

  Result.VertexCount = VertexCount;

  Result.Indecies = (u32 *)malloc( sizeof(u32) * IndexCount );
  if( !Result.Verticies )
  {
    LogFatal(ERROR, "Vertex buffer creation failed");
  }

  for(u32 i = 0; i < IndexCount; ++i)
  {
    Result.Indecies[i] = i;
  }

  Result.IndexCount = IndexCount;

  return( Result );
}

typedef struct {
  vertex_t Verticies[3];
} triangle_t;

triangle_t GiveTriangleSignleColor( f32 Pos[9], f32 R, f32 G, f32 B )
{
  triangle_t Result;
  for(size_t i = 0; i < 3; ++i)
  {
    Result.Verticies[i].x = Pos[(i*3)];
    Result.Verticies[i].y = Pos[(i*3)+1];
    Result.Verticies[i].z = Pos[(i*3)+2];

    Result.Verticies[i].r = R;
    Result.Verticies[i].g = G;
    Result.Verticies[i].b = B;
  }
  return(Result);
}

void glIfyModlel( glModel_t *Model )
{
  glGenVertexArrays( 1, &Model->VertexArrayId );
  glBindVertexArray( Model->VertexArrayId );

  glGenBuffers(1, &Model->VertexBufferId);
  glBindBuffer(GL_ARRAY_BUFFER, Model->VertexBufferId);
  glBufferData(GL_ARRAY_BUFFER, Model->VertexCount * sizeof(vertex_t), Model->Verticies, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0); // vertex pos
  glEnableVertexAttribArray(1); // vertex color

  //void glVertexAttribPointer(	GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
  // specify the layout of vertex attribute data
  // how do we interpret the vertex data stored in the buufer
  glVertexAttribPointer(0, 3 /*number of components per attribute*/, GL_FLOAT, false /*nomralize*/, sizeof(vertex_t), 0);
                                                                                      /* care that three right here */
  glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vertex_t), (u8 *)0 + (3 * sizeof(f32)));

  glGenBuffers(1, &Model->IndexBufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Model->IndexBufferId);
  printf("Index count %u\n", Model->IndexCount);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, Model->IndexCount * sizeof(u32), Model->Indecies, GL_STATIC_DRAW);

  free( Model->Indecies );
}

void deglifyModel( glModel_t *Model )
{
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &Model->VertexArrayId);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Model->VertexBufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &Model->IndexBufferId);
}

struct vec3F32_t {
  f32 x;
  f32 y;
  f32 z;
};

#define UNIT_TO_RADIANS 0.0174532925f

void SetCameraRotationMatrix( f32 RotationMatrix[9], f32 X, f32 Y, f32 Z )
{
  f32 CosPitch = cosf(X * UNIT_TO_RADIANS);
  f32 CosYaw   = cosf(Y * UNIT_TO_RADIANS);
  f32 CosRoll  = cosf(Z * UNIT_TO_RADIANS);

  f32 SinPitch = sinf(X * UNIT_TO_RADIANS);
  f32 SinYaw   = sinf(Y * UNIT_TO_RADIANS);
  f32 SinRoll  = sinf(Z * UNIT_TO_RADIANS);

  RotationMatrix[0] = (CosRoll * CosYaw) + (SinRoll * SinPitch * SinYaw);
  RotationMatrix[1] = (SinRoll * CosPitch);
  RotationMatrix[2] = (CosRoll * -SinYaw) + (SinRoll * SinPitch * CosYaw);

  RotationMatrix[3] = (-SinRoll * CosYaw) + (CosRoll * SinPitch * SinYaw);
  RotationMatrix[4] = (CosRoll * CosPitch);
  RotationMatrix[5] = (SinRoll * SinYaw) + (CosRoll * SinPitch * CosYaw);

  RotationMatrix[6] = (CosPitch * SinYaw);
  RotationMatrix[7] = -SinPitch;
  RotationMatrix[8] = (CosPitch * CosYaw);
}

internal inline vec3F32_t vec3f32( f32 x, f32 y, f32 z )
{
  vec3F32_t Result;
  Result.x = x;
  Result.y = y;
  Result.z = z;
  return(Result);
}

internal inline
void TransformVec3f32( vec3F32_t *Vector, f32 Matrix[9] )
{
  f32 x = (Vector->x*Matrix[0]) + (Vector->y*Matrix[1]) + (Vector->z*Matrix[2]);
  f32 y = (Vector->x*Matrix[3]) + (Vector->y*Matrix[4]) + (Vector->z*Matrix[5]);
  f32 z = (Vector->x*Matrix[6]) + (Vector->y*Matrix[7]) + (Vector->z*Matrix[8]);
  Vector->x = x;
  Vector->y = y;
  Vector->z = z;
}

internal inline
void Vec3f32Offset( vec3F32_t *Dest, vec3F32_t By  )
{
  Dest->x += By.x;
  Dest->y += By.y;
  Dest->z += By.z;
}

internal inline
vec3F32_t Vec3f32Subtract( vec3F32_t A, vec3F32_t B  )
{
  vec3F32_t Result;
  Result.x = A.x - B.x;
  Result.y = A.y - B.y;
  Result.z = A.z - B.z;
  return( Result );
}

internal inline
f32 Vec3Dot( vec3F32_t A, vec3F32_t B )
{
  f32 Result = A.x*B.x + A.y*B.y + A.z*B.z;
  return( Result );
}


internal inline
f32 Vec3Length ( vec3F32_t Vector )
{
  f32 Result = sqrt( Vec3Dot( Vector, Vector ) );
  return( Result );
}

internal inline
void Vec3Normalize ( vec3F32_t *Vector )
{
  f32 Length = Vec3Length( *Vector );
  Vector->x /= Length;
  Vector->y /= Length;
  Vector->z /= Length;
}

internal inline
vec3F32_t Vec3NormalizeInplace ( vec3F32_t Vector )
{
  f32 Length = Vec3Length( Vector );
  vec3F32_t Result = {};
  Result.x = Vector.x / Length;
  Result.y = Vector.y / Length;
  Result.y = Vector.z / Length;
  return( Result );
}

internal inline
vec3F32_t Vec3Cross( vec3F32_t A, vec3F32_t B )
{
  vec3F32_t Result = {};
  //|i   j  k|
  //|a1 a2 a3|
  //|b1 b2 b3|
  Result.x = (A.y*B.z)-(A.z*B.y);
  Result.y = (A.z*B.x)-(A.x*B.z);
  Result.z = (A.x*B.y)-(A.y*B.x);
  return( Result );
}

void Vec3f32Print( vec3F32_t Vector )
{
  printf( "x %f y %f z %f\n", Vector.x,Vector.y,Vector.z);
}

void BuildViewMatrix( f32 Dest[16], vec3F32_t Position , vec3F32_t LookAt , vec3F32_t Up)
{
  vec3F32_t zAxis = Vec3f32Subtract( LookAt, Position );
  f32 Dot = Vec3Dot(zAxis, zAxis);
  zAxis.x /= sqrt(Dot);
  zAxis.y /= sqrt(Dot);
  zAxis.z /= sqrt(Dot);

  vec3F32_t xAxis = Vec3Cross( Up, zAxis );
  Dot = Vec3Dot(xAxis, xAxis);
  xAxis.x /= sqrt(Dot);
  xAxis.y /= sqrt(Dot);
  xAxis.z /= sqrt(Dot);

  vec3F32_t yAxis = Vec3Cross( zAxis , xAxis );
  f32 Result1 = Vec3Dot(xAxis, Position) * -1.0f;
  f32 Result2 = Vec3Dot(yAxis, Position) * -1.0f;
  f32 Result3 = Vec3Dot(zAxis, Position) * -1.0f;

  Dest[0]  = xAxis.x;
  Dest[1]  = yAxis.x;
  Dest[2]  = zAxis.x;
  Dest[3]  = 0.0f;

  Dest[4]  = xAxis.y;
  Dest[5]  = yAxis.y;
  Dest[6]  = zAxis.y;
  Dest[7]  = 0.0f;

  Dest[8]  = xAxis.z;
  Dest[9]  = yAxis.z;
  Dest[10] = zAxis.z;
  Dest[11] = 0.0f;

  Dest[12] = Result1;
  Dest[13] = Result2;
  Dest[14] = Result3;
  Dest[15] = 1.0f;
}

struct shaderPorgramComps_t {
  u32 Program;
  u32 VertexShader;
  u32 FragmentShader;
};

shaderPorgramComps_t GiveShaderProgramFromShaderFilename(const char *VertexShaderFileName, const char *FragmentShaderFileName, const char *ShaderAttribOne, const char *ShaderAttribTwo )
{
  shaderFiles_t ShaderSrcFilePair = LoadShaderSrcFilePair(VertexShaderFileName, FragmentShaderFileName);
  shaderPorgramComps_t Result;
  Result.VertexShader = glCreateShader(GL_VERTEX_SHADER);
  Result.FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glCompileShader(Result.VertexShader);
  glCompileShader(Result.FragmentShader);

  CheckShader(Result.VertexShader, GL_COMPILE_STATUS ,"Vertex", "compile");
  CheckShader(Result.FragmentShader, GL_COMPILE_STATUS ,"Fragment", "compile");

  Result.Program = glCreateProgram();
  glAttachShader(Result.Program, Result.VertexShader);
  glAttachShader(Result.Program, Result.FragmentShader);

  glBindAttribLocation( Result.Program, 0, ShaderAttribOne );
  glBindAttribLocation( Result.Program, 1, ShaderAttribTwo );

  glLinkProgram( Result.Program );
  CheckProgram( Result.Program, GL_LINK_STATUS, "Porgram", "link" );
  free( ShaderSrcFilePair.Buffer );
  return( Result );
}


internal inline void
KillShader( shaderPorgramComps_t *Comps )
{
  glDetachShader( Comps->Program, Comps->VertexShader );
  glDetachShader( Comps->Program, Comps->FragmentShader );
  glDeleteShader(Comps->VertexShader);
  glDeleteShader(Comps->FragmentShader);
  glDeleteProgram(Comps->Program);
}


int main(void)
{
  s32 ScreenWidth;
  s32 ScreenHeight;
  b32 Running = true;

  f32 WorldMatrix[16]={0};
  f32 ProjectionMatrix[16]={0};
  f32 OrthoMatrix[16]= {0};

  Display *Monitors = XOpenDisplay(0);
  if( !Monitors )
  {
    LogFatal( ERROR, "Failed to open Dispaly" );
  }

  GLXContext RenderingContext;
  Window MainWindow;
  if(!X11InitializeWindow( &ScreenWidth, &ScreenHeight, Monitors, &MainWindow, &RenderingContext ))
  {
    LogFatal( ERROR, "Failed to Initialize Window" );
  }

  InitializeOpenGL( Monitors, ScreenWidth, ScreenHeight, SCREEN_NEAR, SCREEN_DEPTH, VSYNC_ENABLED, WorldMatrix, ProjectionMatrix, OrthoMatrix);


  shaderPorgramComps_t ColorShader = GiveShaderProgramFromShaderFilename( "color.vs", "color.fs", "inputPosition", "inputColor" );
  shaderPorgramComps_t TextureShader = GiveShaderProgramFromShaderFilename( "texture.vs", "texture.fs", "inputPosition", "inputTexCoord" );

  b32 KeyboardState[KEY_SUPPORT_COUNT] = {0};
  MEMORYZEROARRAY(KeyboardState);

  f32 CameraViewMatrix[16];
  f32 CameraRotationMatrix[9];
  vec3F32_t CameraUp = vec3f32(0.0f, 1.0f, 0.0f);
  vec3F32_t CameraLookAt = vec3f32(0.0f, 0.0f, 1.0f);
  vec3F32_t CameraPosition = vec3f32(0.0f,0.0f, -5.0f);
  vec3F32_t CameraRotation = vec3f32(0.0f,0.0f,0.0f);

  SetCameraRotationMatrix( CameraRotationMatrix, CameraRotation.x, CameraRotation.y,  CameraRotation.z );

  TransformVec3f32( &CameraLookAt, CameraRotationMatrix );
  TransformVec3f32( &CameraUp, CameraRotationMatrix );
  Vec3f32Offset( &CameraLookAt, CameraPosition );
  BuildViewMatrix( CameraViewMatrix , CameraPosition, CameraLookAt, CameraUp );

  f32 TrianglePos[9] = { -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f };

  triangle_t Triangle = GiveTriangleSignleColor( TrianglePos, 0.0f, 0.0f, 1.0f );
  glModel_t TriangleModel = GiveGlModel( 3, 3,  Triangle.Verticies );

  glIfyModlel( &TriangleModel );

  while( Running )
  {

    X11ReadInput(Monitors, &MainWindow, KeyboardState, &Running);
    if( KeyboardState[KEY_ESCAPE] ) { Running = 0; }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    f32 RenderWorldMatrix[16] = {};
    f32 RenderViewMatrix[16] = {};
    f32 RenderProjectionMatrix[16] = {};

    GLMatrixTranspose( RenderWorldMatrix, WorldMatrix);
    GLMatrixTranspose( RenderViewMatrix, CameraViewMatrix);
    GLMatrixTranspose( RenderProjectionMatrix, ProjectionMatrix);

    glUseProgram( TextureShader.Program );

    s32 WorldMatrixShaderVarLocation = glGetUniformLocation( TextureShader.Program, "worldMatrix" );
    s32 ViewMatrixShaderVarLocation = glGetUniformLocation( TextureShader.Program, "viewMatrix" );
    s32 ProjectionMatrixShaderVarLocation = glGetUniformLocation( TextureShader.Program , "projectionMatrix" );
    s32 TextureUniformVarLocation = glGetUniformLocation( TextureShader.Program, "shaderTexture" );

    if( WorldMatrixShaderVarLocation != -1 ) {
      glUniformMatrix4fv( WorldMatrixShaderVarLocation, 1, false, RenderWorldMatrix );
    } else {
      LogFatal(ERROR, "World matrix not set in shader ");
    }

    if( ViewMatrixShaderVarLocation != -1 ) {
      glUniformMatrix4fv( ViewMatrixShaderVarLocation, 1, false, RenderViewMatrix );
    } else {
      LogFatal(ERROR, "View matrix not set in shader ");
    }

    if( ProjectionMatrixShaderVarLocation != -1 ) {
      glUniformMatrix4fv( ProjectionMatrixShaderVarLocation, 1, false, RenderProjectionMatrix );
    } else {
      LogFatal(ERROR, "Projection matrix not set in shader ");
    }

    if( TextureUniformVarLocation != -1 ) {
      glUniform1i(TextureUniformVarLocation, 0);
    } else {
      LogFatal(ERROR, "Texture not set in shader");
    }

    //GL DRAW MODEL
    glBindVertexArray( TriangleModel.VertexArrayId );
    glDrawElements( GL_TRIANGLES, TriangleModel.IndexCount, GL_UNSIGNED_INT, 0);

    //END SCENE
    glXSwapBuffers(Monitors, MainWindow);
  }

  deglifyModel( &TriangleModel );
  KillShader(&ColorShader);
  KillShader(&TextureShader);

  glXMakeCurrent(Monitors, None, NULL);
  glXDestroyContext(Monitors, RenderingContext);
  XUnmapWindow(Monitors, MainWindow);
  XDestroyWindow(Monitors, MainWindow);
  XCloseDisplay(Monitors);

  return(0);
}
