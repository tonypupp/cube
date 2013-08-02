#ifndef CUBE_H
#define CUBE_H

#include <QtGui/QOpenGLFunctions>
#include <QVector4D>

#include "panel.h"

class TriangleWindow;

class Cube
{
public:
    Cube();
    Cube(float x, float y, float z);

    static GLuint getvertices(GLfloat **vertices);
    static GLuint getindicies(GLubyte **indices);
    static GLuint getcolors(GLfloat **colors);

    void setcolor(float color[32]);
    void translation(float x, float y, float z);
    void rotate(float angle, float x, float y, float z);

    void view(float x, float y, float z);
    void viewrotate(float angle, float x, float y, float z);
    void multiplyview(QMatrix4x4 &matrix);
    QMatrix4x4 getmatrix();
    void getpanel(enum AXIS *x, enum AXIS *y, enum AXIS *z);

    void detach(TriangleWindow *rubik, AXIS exception);
    void attach(TriangleWindow *rubik, AXIS exception);

    void setpos(float x, float y, float z);
    void rotatepos(int step, enum AXIS axis);

public:
private:
    friend class TriangleWindow;
    int no;
    QMatrix4x4 m_view;
    QMatrix4x4 m_mode;

    GLfloat *m_vertices;
    GLfloat *m_colors;
    GLubyte *m_indices;

    QVector4D m_pos;
};

#endif // CUBE_H
