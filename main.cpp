#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GLES2/gl2.h>
#include <iostream>
#include <unistd.h>
#include "displaypng.hpp"

int main() {
  Display *xdisplay = XOpenDisplay(nullptr);
  if (xdisplay == nullptr) {
    std::cerr << "Error XOpenDisplay." << std::endl;
    exit(EXIT_FAILURE);
  }

  Window xwindow = XCreateSimpleWindow(
      xdisplay, DefaultRootWindow(xdisplay), 100, 100, 640, 480, 1,
      BlackPixel(xdisplay, 0), WhitePixel(xdisplay, 0));

  XMapWindow(xdisplay, xwindow);

  EGLDisplay display = nullptr;
  EGLContext context = nullptr;
  EGLSurface surface = nullptr;
  if (initializeEGL(xdisplay, xwindow, display, context, surface) < 0) {
    std::cerr << "Error initializeEGL." << std::endl;
    exit(EXIT_FAILURE);
  }

  mainloop(xdisplay, display, surface);

  destroyEGL(display, context, surface);
  XDestroyWindow(xdisplay, xwindow);
  XCloseDisplay(xdisplay);

  return 0;
}
