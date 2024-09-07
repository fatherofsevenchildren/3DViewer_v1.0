#include "glwidget.h"

#include "./ui_mainwindow.h"
#include "ui_mainwindow.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::set_projection(bool projection) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection)
    glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 9999999);
  else
    glOrtho(-1, 1, -1, 1, 1, 9999999);
}

void GLWidget::paintGL() {
  set_projection(projection);
  glClearColor(backColor.redF(), backColor.greenF(), backColor.blueF(),
               backColor.alphaF());
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTranslated(0, 0, -2);  //-scale);
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);
  if (points) draw_points();
  if (lines) draw_lines();
}

void GLWidget::draw_points() {
  glPointSize(point_sz);
  glColor3d(pointColor.redF(), pointColor.greenF(), pointColor.blueF());
  glVertexPointer(3, GL_DOUBLE, 0, pro->vertexes);
  glEnableClientState(GL_VERTEX_ARRAY);
  if (point_type)
    glEnable(GL_POINT_SMOOTH);
  else
    glDisable(GL_POINT_SMOOTH);
  glDrawArrays(GL_POINTS, 0, pro->vertexes_count);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::draw_lines() {
  glLineWidth(line_sz);
  glColor3d(lineColor.redF(), lineColor.greenF(),
            lineColor.blueF());  //цвет линий
  glVertexPointer(3, GL_DOUBLE, 0, pro->vecs);
  glEnableClientState(GL_VERTEX_ARRAY);
  if (dashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(3, 0xAAA);
  } else
    glDisable(GL_LINE_STIPPLE);
  glDrawArrays(GL_LINES, 0, pro->draw_vectors_count);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void GLWidget::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
