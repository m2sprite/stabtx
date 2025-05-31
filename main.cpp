#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "htabtx_types.h"
#include "htabtx_log.h"
#include "gl_funcs.h"
#include "gl_funcs.cpp"

#define KEY_SUPPORT_COUNT 1
global b32 FULL_SCREEN = false;
global b32 VSYNC_ENABLED = true;
global const s32 KEY_ESCAPE = 0;
global b32 Running;

b32 X11InitializeWindow( s32 *ScreenWidth, s32 ScreenHeight, Display *Monitors, Window *MainWindow, GLXContext *MainRenderingContext )
{
  b32 Result;
  Window RootWindow = DefaultRootWindow(Monitors);

  GLint GLAttributeList[15];
  AttributeList[0] = GLX_RGBA;// support 24bit color and an alpha channel
  AttributeList[1] = GLX_DEPTH_SIZE;// support for 24 bit depth buffer;
  AttributeList[2] = 24;
  AttributeList[3] = GLX_STENCIL_SIZE;
  AttributeList[4] = 8;
  AttributeList[5] = GLX_DOUBLEBUFFER; //Support for double buffering.
  AttributeList[6] = GLX_RED_SIZE; //8 bits for each channel
  AttributeList[7] = 8;
  AttributeList[8] = GLX_GREEN_SIZE;
  AttributeList[9] = 8;
  AttributeList[10] = GLX_BLUE_SIZE;
  AttributeList[11] = 8;
  AttributeList[12] = GLX_ALPHA_SIZE;
  AttributeList[13] = 8;
  AttributeList[14] = None;

  XVisualInfo *VisualInfo;
  VisualInfo = glXChooseVisual(Monitors, 0, AttributeList);

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

    if( XChangeProperty(Monitors, *MainWindow, MotifHints, 32, PropModeReplace, (u8 *)&MotifHintList, 5);
    {
      LogFatal( ERROR, "XChangeProperty Failed");
    }

    if( XFlush( Monitors ) );
    sleep(1);
  }

  *GLRenderingContext = glXCreateContext(Monitors, VisualInfo, 0, GL_TRUE);
  if(!(*GLRenderingContext))
  {
    LogFatal( ERROR, "Failed to create glContext");
  }

  if( !(glXMakeCurrent(Monitors, MainWindow, GLRenderingContext)) )
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

    if(XMoveWindow(Monitors, *MainWindow, PosX, PosY))
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
      KeyboardSate[KEY_ESCAPE] = State;
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

int main(void)
{
  s32 ScreenWidth;
  s32 ScreenHeight;
  s32 Running = true;

  Display *Monitors = XOpenDisplay(0);
  if( !Monitor )
  {
    LogFatal( ERROR, "Failed to open Dispaly" );
  }

  GLXContext RenderingContext;
  Winodw MainWindow;
  if(!X11InitializeWindow( &ScreenWidth, &ScreenHeight, Monitors, &MainWindow, &RenderingContext ))
  {
    LogFatal( ERROR, "Failed to Initialize Window" );
  }

  b32 KeyboardState[KEY_SUPPORT_COUNT] = {0};
  MEMORYZEROARRAY(KeyboardState);

  while(Running)
  {
    X11ReadInput(Monitors, KeyboardState, &Running);
  }

  return(0);
}
