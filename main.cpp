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

b32 X11InitializeWindow( s32 *ScreenWidth, s32 ScreenHeight, Display *MainVideoDisplay, Window *MainWindow, GLXContext *MainRenderingContext )
{
  b32 Result;
  Window RootWindow = DefaultRootWindow(MainVideoDisplay);

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
  VisualInfo = glXChooseVisual(MainVideoDisplay, 0, AttributeList);

  if(!VisualInfo)
  {
    return false;
  }

  Colormap ColorMap = XCreateColormap(MainVideoDisplay, RootWindow, VisualInfo->visual, AllocNone);

  // Fill out the structure for setting the window attributes.
  XSetWindowAttributes SetWindowAttributes;
  SetWindowAttributes.colormap = ColorMap;
  SetWindowAttributes.event_mask = KeyPressMask|KeyReleaseMask|ButtonPressMask|ButtonReleaseMask;

  Screen *DefaultMonitor;
  if(FULL_SCREEN)
  {
    DefaultMonitor = XDefaultScreenOfDisplay( MainVideoDisplay );
    *ScreenWidth = XWidthOfScreen(DefaultMonitor);
    *ScreenHeight = XHeightOfScreen(DefaultMonitor);
  }

  *MainWindow = XCreateWindow( MainVideoDisplay, );

  i32 GLMajorVersion;
  Atom WmState, FullScreenState, MotifHints;
  XEvent FullScreenEvent;
  s32 MotifHintList[5];

  s32 Status_, PosX, PosY, DefaultMonitorWidth, DefaultMonitorHeight;

  Root

  return(true);
}

internal void X11ProcessKeyboardButtonState( keyState_t KeyboardState[256], KeySym KeySymbol )
{
  /*
  switch(KeySymbol)
  {
    case(65307):{
      KeyboardSate[KEY_ESCAPE] = !KeyboardState[KEY_ESCAPE];
    } break;

    default:{
    } break;
  }
  */
}

internal void X11ReadInput( Display *Monitors, Window *MainWindow, keyState_t KeyboardState[KEY_SUPPORT_COUNT], b32 *Running )
{
  XEvent UserEvent;
  char KeyBuffer[32];
  KeySym KeySymbol;
  s32 EventMask = KeyPressMask | KeyReleaseMask;

  //READ INPUT
  if(XCheckWindowEvent( Monitors, *MainWindow, EventMask, &UserEvent))
  {
    XLookupString(&UserEvent.xkey, KeyBuffer, sizeof(KeyBuffer), &KeySymbol, 0);
    switch(UserEvent.type)
    {
      case(KeyPress):{
        SetKeyDown( KeyboardState, KeySymbol );
      }break;

      case(KeyRelease):{
        SetKeyUp( KeyboardState, KeySymbol );
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

#define EvalPrintKey(x) printf("%s %d %b\n", #x ,x.halfTransitionCount, x.isEndedDown);

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
  if(!InitializezWindow( &ScreenWidth, &ScreenHeight, Monitors, &MainWindow, &RenderingContext ))
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
