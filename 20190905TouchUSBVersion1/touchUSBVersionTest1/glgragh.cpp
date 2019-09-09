#include "glgragh.h"
#include <QMouseEvent>
#include <QColorDialog>
#include <GL/glu.h>
#include <qmath.h>

#define   PI        3.14
#define   M         6
#define   N         6
#define   radius    0.015

GlGragh::GlGragh(QWidget *parent)
    : QGLWidget(parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    rotationX = -21.0;
    rotationY = -57.0;
    rotationZ = -0.0;
    faceColors[0] = Qt::red;
    faceColors[1] = Qt::green;
    faceColors[2] = Qt::blue;
    faceColors[3] = Qt::yellow;
}

GlGragh::~GlGragh()
{

}

void GlGragh::initializeGL()
{
    qglClearColor(Qt::white);  //background color
    glShadeModel(GL_FLAT);     //控制opengl中绘制指定两点间其他点颜色的过渡模式
    glEnable(GL_DEPTH_TEST);   //启用深度测试。根据坐标的远近自动隐藏被遮住的图形（材料）
    glEnable(GL_CULL_FACE);    //根据函数glCullFace要求启用隐藏图形材料的面。
}

void GlGragh::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);  //左下角（在第一象限内，以（0，0）为原点的）位置
    glMatrixMode(GL_PROJECTION);   //将当前矩阵指定为投影矩阵,把3维物体投到2维的平面上
    glLoadIdentity();              //用一个4×4的单位矩阵来替换当前矩阵，实际上就是对当前矩阵进行初始化
    GLfloat x = GLfloat(width) / height;  //宽高比
    glFrustum(-x,+x,-1.0,+1.0,4.0,15.0);  //近平面左右两边相对于垂直平面的位置;
                                          //近平面顶和底相对于水平面的位置;
                                          //视点到远近投影平面的距离
                                          //生成的矩阵会与当前的矩阵相乘,生成透视的效果
    glMatrixMode(GL_MODELVIEW);    //对模型视景的操作
}

void GlGragh::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清除颜色缓冲以及深度缓冲
    draw();
}

void GlGragh::draw()
{
    static CGlobal glcoor;
    static const GLfloat P1[3] = {0.0, -1.0, +2.0};
    static const GLfloat P2[3] = {+1.73205081, -1.0, -1.0};
    static const GLfloat P3[3] = {-1.73205081, -1.0, -1.0};
    static const GLfloat P4[3] = {0.0, 2.0, 0.0};
    static const GLfloat *const coords[4][3] = {
        {P1, P2, P3}, {P1, P3, P4}, {P1, P4, P2}, {P2, P4, P3}
    };
    glMatrixMode(GL_MODELVIEW);             //对模型视景的操作
    glLoadIdentity();                       //用一个4×4的单位矩阵来替换当前矩阵，实际上就是对当前矩阵进行初始化
    glTranslatef(0.0, 0.0, -5.0);          //沿X,Y,Z轴正方向平移xx个单位(xx是有符号数)

    glRotatef(rotationX, 1.0, 0.0, 0.0);    //以点(0,0,0)到点(x,y,z)为轴，旋转angle角度；
    glRotatef(rotationY, 0.0, 1.0, 0.0);
    glRotatef(rotationZ, 0.0, 0.0, 1.0);

    glBegin(GL_LINES);
    glLineWidth(10);
    qglColor(Qt::red);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(-1.0f, 0.0f, 0.0f);
    qglColor(Qt::black);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
    qglColor(Qt::blue);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 0.0f, -1.0f);
    glEnd();

    glBegin(GL_POINTS);
    glPointSize(5.0f);    //修改点的尺寸，默认大小为1.0f
//    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-glcoor.touchState.position[2]/200.0,
            glcoor.touchState.position[1]/200.0,
            -glcoor.touchState.position[0]/200.0);
    glEnd();
    double step_z = PI / M;
    double step_xy = 2 * PI / N;
    double x[4], y[4], z[4];

    double angle_z = 0.0;
    double angle_xy = 0.0;
    int i = 0, j = 0;
    glBegin(GL_QUADS);
    for(i = 0; i < M; i++)
    {
        angle_z = i * step_z;

        for(j = 0; j < N; j++)
        {
            angle_xy = j * step_xy;

            x[0] = radius * sin(angle_z) * cos(angle_xy);
            y[0] = radius * sin(angle_z) * sin(angle_xy);
            z[0] = radius * cos(angle_z);

            x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
            y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
            z[1] = radius * cos(angle_z + step_z);

            x[2] = radius * sin(angle_z + step_z) * cos(angle_xy + step_xy);
            y[2] = radius * sin(angle_z + step_z) * sin(angle_xy + step_xy);
            z[2] = radius * cos(angle_z + step_z);

            x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
            y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
            z[3] = radius * cos(angle_z);
            for(int k = 0; k < 4; k++)
            {
                glColor3f(sin(angle_z), cos(angle_z), tan(angle_z));
                //glTexCoord2f(0.1f, 0.1f);
                glVertex3f(-(glcoor.touchState.position[2]/200.0 + z[k]),
                        glcoor.touchState.position[1]/200.0 + y[k],
                        -(glcoor.touchState.position[0]/200.0 + x[k]));
            }
        }
    }
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    qglColor(Qt::red);
      glVertex3f(-glcoor.touchState.position[2]/200.0,
              glcoor.touchState.position[1]/200.0,
              -glcoor.touchState.position[0]/200.0);
      glVertex3f(-glcoor.touchState.position[2]/200.0-glcoor.setTouchState.forceValues[2]/5,
              glcoor.touchState.position[1]/200.0,
              -glcoor.touchState.position[0]/200.0);
    qglColor(Qt::black);
      glVertex3f(-glcoor.touchState.position[2]/200.0,
              glcoor.touchState.position[1]/200.0,
              -glcoor.touchState.position[0]/200.0);
      glVertex3f(-glcoor.touchState.position[2]/200.0,
              glcoor.touchState.position[1]/200.0+glcoor.setTouchState.forceValues[1]/5,
              -glcoor.touchState.position[0]/200.0);
    qglColor(Qt::blue);
      glVertex3f(-glcoor.touchState.position[2]/200.0,
              glcoor.touchState.position[1]/200.0,
              -glcoor.touchState.position[0]/200.0);
      glVertex3f(0-glcoor.touchState.position[2]/200.0,
              glcoor.touchState.position[1]/200.0,
              -glcoor.touchState.position[0]/200.0-glcoor.setTouchState.forceValues[0]/5);
    glEnd();

}

void GlGragh::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GlGragh::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
    if(event->buttons() & Qt::LeftButton){
        rotationX -= 180 * dy;
        rotationY -= 180 * dx;
        updateGL();
    }
    else if(event->buttons() & Qt::RightButton){
        rotationX -= 180 * dy;
        rotationZ -= 180 * dx;
        updateGL();
    }
    lastPos = event->pos();
}

void GlGragh::drawonline()
{
    updateGL();
}
