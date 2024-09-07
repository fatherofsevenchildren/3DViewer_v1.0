#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QColor>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtGui>
#include <QtOpenGL>

extern "C" {
#include "../../back/parser.h"
}

class GLWidget : public QOpenGLFunctions, public QOpenGLWidget {
 public:
  QColor backColor, lineColor, pointColor;
  arr *pro;
  minmax_t *frame;
  GLWidget();
  explicit GLWidget(QWidget *parent = 0);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void draw_lines();
  void draw_points();
  void change();
  void set_projection(bool projection);
  float x = 0, y = 0, z = 0;
  bool lines = 1, points = 0, point_type = 0, projection = 1, dashed = 0;
  int point_sz = 1, line_sz = 1;

 private:
  float xRot, yRot, zRot;
  QPoint mPos;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

#endif  // GLWIDGET_H
