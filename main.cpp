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
global f32 SCREEN_DEPTH = 0.3f;

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


#define TEMP_SHADER_ERROR_MESSAGES_SIZE 10240
global char TempShaderErrorMessagesHere[TEMP_SHADER_ERROR_MESSAGES_SIZE];

internal inline void CheckShaderCompilation(u32 ShaderId, const char *ShaderType)
{
  s32 ShaderStatus;
  glGetShaderiv(ShaderId,GL_COMPILE_STATUS, &ShaderStatus);
  if( !ShaderStatus )
  {
    GLint ShaderLogSize = 0;
    char *ShaderLogPlace = TempShaderErrorMessagesHere;
    glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &ShaderLogSize);
    if ( ShaderLogSize > TEMP_SHADER_ERROR_MESSAGES_SIZE )
    {
      LogFatal(ERROR, "Shader Info Too big to fit in stack buffer");
    }
    glGetShaderInfoLog(ShaderId, ShaderLogSize, 0, ShaderLogPlace);
    TempShaderErrorMessagesHere[ShaderLogSize] = '\0';
    printf( "[SHADER INFO]: %s\n",  TempShaderErrorMessagesHere);
    LogFatal(ERROR, "Failed to compile %s shader", ShaderType);
  }
}

int main(void)
{
  s32 ScreenWidth;
  s32 ScreenHeight;
  b32 Running = true;

  f32 WorldMatrix[16];
  f32 ProjectionMatrix[16];
  f32 OrthoMatrix[16];

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

  //TODO:Make a single buffer that loads both files and give pointers to offsets in the buffer
  shaderFile_t vsFile = LoadFileIntoBufferWithNullDelim("color.vs");
  shaderFile_t fsFile = LoadFileIntoBufferWithNullDelim("color.fs");

  u32 VertexShader = glCreateShader(GL_VERTEX_SHADER);
  u32 FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(VertexShader, 1, &vsFile.Buffer, 0);
  glShaderSource(FragmentShader, 1, &fsFile.Buffer, 0);

  glCompileShader(VertexShader);
  glCompileShader(FragmentShader);
  CheckShaderCompilation(VertexShader, "Vertex");
  CheckShaderCompilation(FragmentShader, "Framgent");

  u32 ShaderProgram = glCreateProgram();
  glAttachShader(ShaderProgram, VertexShader);
  glAttachShader(ShaderProgram, FragmentShader);

  b32 KeyboardState[KEY_SUPPORT_COUNT] = {0};
  MEMORYZEROARRAY(KeyboardState);

  while(Running)
  {
    X11ReadInput(Monitors, &MainWindow, KeyboardState, &Running);
    if( KeyboardState[KEY_ESCAPE] )
    {
      Running = 0;
    }
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glXSwapBuffers(Monitors, MainWindow);
  }

  glXMakeCurrent(Monitors, None, NULL);
  glXDestroyContext(Monitors, RenderingContext);
  XUnmapWindow(Monitors, MainWindow);
  XDestroyWindow(Monitors, MainWindow);
  XCloseDisplay(Monitors);

  return(0);
}
