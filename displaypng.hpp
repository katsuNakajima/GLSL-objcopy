#ifndef _DISPLAYPNG_HPP_
#define _DISPLAYPNG_HPP_

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <iostream>
extern char _binary_vshader_glsl_start[];
extern char _binary_vshader_glsl_end[];
extern char _binary_fshader_glsl_start[];
extern char _binary_fshader_glsl_end[];

void mainloop(Display *xdisplay, EGLDisplay display, EGLSurface surface);
void destroyEGL(EGLDisplay &display, EGLContext &context, EGLSurface &surface);
int initializeEGL(Display *xdisp, Window &xwindow, EGLDisplay &display, EGLContext &context, EGLSurface &surface);
GLuint loadShader(GLenum shaderType, const char *source);
GLuint createProgram(const char *vshader, const char *fshader);
void deleteShaderProgram(GLuint shaderProgram);
std::string imputShadersrc(const char *begin, const char *end);

#endif
