#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include "openglwindow.h"

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QMatrix4x4>
#include <QMouseEvent>
#include <QTimer>

class QTimer;
class QMouseEvent;

class TriangleWindow : public OpenGLWindow
{

public:
    TriangleWindow();

    void initialize();
    void render();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *ev);

private:
#if 0
    GLuint loadShader(GLuint type, const char *source);
#endif

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;
    bool mouse_pressed;
    int mouse_x;
    int mouse_y;

    QOpenGLShaderProgram *m_program;
    QMatrix4x4 matrix;

    int m_frame;
    QTimer timer;

    void Ontimer();
};

#endif // TRIANGLEWINDOW_H
