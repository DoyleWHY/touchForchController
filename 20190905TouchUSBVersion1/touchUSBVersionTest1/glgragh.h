#ifndef GLGRAPH_H
#define GLGRAPH_H

#include <QtOpenGL/QGLWidget>
#include <iostream>
#include <cglobal.h>

using namespace std;

class GlGragh : public QGLWidget
{
    Q_OBJECT

public:
  GlGragh(QWidget *parent = 0);
  ~GlGragh();
  void drawonline();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void draw();

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    QColor faceColors[4];
    QPoint lastPos;

};


#endif // GLGRAPH_H
