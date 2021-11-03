#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include "Apex.h"
#include "Point.h"

#define MAX_LOADSTRING 100
#define ID_CREATES 160
#define ID_FIRSTCHILD	161
#define MOVEMENT 5
#define BORDER_WIDTH 5
/*
#define TITLE "Example"
#define ICON_TITLE "Example"
#define PRG_CLASS "Example"
*/

char TITLE[MAX_LOADSTRING] = "vympel";
char ICON_TITLE[MAX_LOADSTRING] = "vympel";
char PRG_CLASS[MAX_LOADSTRING] = "vympel";

// Глобальные переменные:   


// Размеры кадра и указатель на массив структур RGBQUAD (буфер кадра)
//uint32_t frameWidth, frameHeight;
//RGBQUAD* frameBuffer;

static void SetWindowManagerHints(Display* disp, 
                                  char* PClass,
                                  char* argv[],
                                  int argc,
                                  Window window,
                                  int x, int y,
                                  int width,
                                  int height,
                                  int width_min,
                                  int height_min,
                                  char* ptrTitle,
                                  char* ptrITitle,
                                  Pixmap pixmap)
{
  XSizeHints size_window;

  XWMHints hInts;
  XClassHint class_hInts;
  XTextProperty name, iconname;
  if(!XStringListToTextProperty(&ptrTitle, 1, &name) ||
      !XStringListToTextProperty(&ptrITitle, 1, &iconname))
      {
        printf("No memore!\n");
        exit (2);
      }
  size_window.flags = PPosition | PSize | PMaxSize;
  size_window.min_width = width_min;
  size_window.min_height = height_min;

  hInts.flags = StateHint | IconPixmapHint | InputHint;
  hInts.initial_state = NormalState;
  hInts.input = True;
  hInts.icon_pixmap = pixmap;
  
  class_hInts.res_name = argv[0];
  class_hInts.res_class = PClass;

  XSetWMProperties(disp, window, &name, &iconname,
                   argv, argc, &size_window, &hInts, &class_hInts);

}


int main(int argc, char *argv[])
{
  
  int ScreenNumber;
  Display* display;
  Window parent;
  XEvent report;
  GC gc;
  Point* point = NULL;
  Apex apex;

    // Установление связи с сервером
  if((display = XOpenDisplay(getenv("vympel")))==NULL){
    printf("Can't connect X server\n");
    exit(1);
  }

   //получение номера основого экрана
   ScreenNumber = DefaultScreen(display);

    //Создание окна
    /*
    parent = XCreateWindow(display,
                           RootWindow(display, ScreenNumber),
                           0,
                           0, 
                           640, 
                           480, 
                           BORDER_WIDTH,
                           24,
                           InputOutput,
                           0,
                           0,
                           0);
                           */
  parent = XCreateSimpleWindow ( display,
     RootWindow ( display, ScreenNumber ),
     0, 0, 640, 480, BORDER_WIDTH,
     BlackPixel ( display, ScreenNumber ),
     WhitePixel ( display, ScreenNumber ) );
  SetWindowManagerHints(display,
                        PRG_CLASS,
                        argv, 
                        argc,
                        parent,
                        0,
                        0,
                        640,
                        480,
                        50,
                        50,
                        TITLE,
                        ICON_TITLE,
                        0);
  XSelectInput(display, parent, ExposureMask | KeyPressMask);

  XMapWindow(display, parent);
  //открытие файла и считывание из него данных в buffer
  std::ifstream file("test.txt");
  if(!file.is_open()){
    printf("Eror. File not found.\n");
    return 1;
  }
  int cnt = 1;
  point = (Point*)malloc(cnt*sizeof(Point));
  while(!file.eof())
  {
    apex.SetApex(cnt-1);
    double temporary = 0;
    file >> temporary;
    point[apex.GetApex()].SetPoint('x', temporary);
    file >> temporary;
    point[apex.GetApex()].SetPoint('y', temporary);
    cnt++;
    point = (Point*)realloc(point, cnt*sizeof(Point));
    
  }
  file.close();
  
  while (True)
  {
    XNextEvent(display, &report);
    switch (report.type)
    { 
    case Expose:
    {
      if(report.xexpose.count != 0)
      break;
      gc = XCreateGC(display, parent, 0, NULL);
      XSetForeground(display, gc, BlackPixel(display, 0));
      for(int i=0; i<apex.GetApex()-1; i++){
      XDrawLine(display, parent,gc,point[i].GetPoint('x'), point[i].GetPoint('y'), 
                                   point[i+1].GetPoint('x'), point[i+1].GetPoint('y'));
      }
      XFreeGC(display, gc);
      XFlush(display);
      break;
    }
    case KeyPress:
    {
    free(point);
    XCloseDisplay(display);
    exit(0);
    }
    }
  }
  
  return 0;  
}