#ifndef CUBE_H
#define CUBE_H

#include <QtGui/QOpenGLFunctions>
#include <QVector2D>
#include <QVector4D>

#include "panel.h"

class TriangleWindow;
#define VBO
#ifdef VBO
struct VertexData
{
    GLfloat vertex[3];
    GLfloat color[4];
};
#endif

class Cube
{
public:
    Cube();
    Cube(float x, float y, float z);

    static GLuint getindicies(GLubyte **indices);
#ifdef VBO
    static GLuint getvertices(struct VertexData **vertices);
#else
    static GLuint getcolors(GLfloat **colors);
    static GLuint getvertices(GLfloat **vertices);
#endif
    static GLuint gettexcoords(QVector2D **texcoords);

#ifndef VBO
    void setcolor(float color[32]);
#endif
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

#ifdef VBO
    struct VertexDate *m_vertices;
#else
    GLfloat *m_vertices;
    GLfloat *m_colors;
#endif

    GLubyte *m_indices;

    QVector4D m_pos;
};

#endif // CUBE_H
