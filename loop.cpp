#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include "displaypng.hpp"

void mainloop(Display *xdisplay, EGLDisplay display, EGLSurface surface) {
  std::string vsd =
      imputShadersrc(_binary_vshader_glsl_start, _binary_vshader_glsl_end);
  std::string fsd =
      imputShadersrc(_binary_fshader_glsl_start, _binary_fshader_glsl_end);
  const char *vshader = vsd.c_str();
  const char *fshader = fsd.c_str();
  GLuint program = createProgram(vshader, fshader);
  glUseProgram(program);
  const GLfloat vertices[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
  GLint gvPositionHandle = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(gvPositionHandle);
  while (true) {
    XPending(xdisplay);

    glClearColor(0.25f, 0.25f, 0.5f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    eglSwapBuffers(display, surface);
    usleep(1000);
  }
  deleteShaderProgram(program);
}
