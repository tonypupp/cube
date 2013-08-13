#include "cube.h"
#include "panel.h"
#include "trianglewindow.h"

GLfloat gvertices[] = {
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f
};

GLubyte gindices[] = {
#if 1
    1,2,3, 1,2,3,
#else
    0,1,2, 2,3,0, //front side
#endif
    1,5,6, 6,2,1, //right side
    4,0,3, 3,7,4, //left side
    0,4,5, 5,1,0, //bottom side
    3,2,6, 6,7,3, //up side
    5,4,7, 7,6,5, //back side
};

QVector2D texcoords[] = {
    /* Cube 1 */
    /* face front */
//    QVector2D(0.0, 0.0), // v0
//    QVector2D(1.0, 0.0), // v1
//    QVector2D(1.0, 1.0), // v2
//    QVector2D(1.0, 1.0), // v2
//    QVector2D(0.0, 1.0), // v3
//    QVector2D(0.0, 0.0), // v0

    /* Right side */
    QVector2D(1.0, 0.0), // v1
    QVector2D(0.0, 0.0), // v5
    QVector2D(0.0, 1.0), // v6
    QVector2D(0.0, 1.0), // v6
    QVector2D(1.0, 1.0), // v2
    QVector2D(1.0, 0.0), // v1

    /* face front */
    QVector2D(1.0, 0.0), // v0
    QVector2D(1.0, 1.0), // v1
    QVector2D(0.0, 1.0), // v2
    QVector2D(0.0, 1.0), // v2
    QVector2D(0.0, 0.0), // v3
    QVector2D(1.0, 0.0), // v0

    /* face front */
    QVector2D(1.0, 0.0), // v0
    QVector2D(1.0, 1.0), // v1
    QVector2D(0.0, 1.0), // v2
    QVector2D(0.0, 1.0), // v2
    QVector2D(0.0, 0.0), // v3
    QVector2D(1.0, 0.0), // v0

    /* face front */
    QVector2D(1.0, 0.0), // v0
    QVector2D(1.0, 1.0), // v1
    QVector2D(0.0, 1.0), // v2
    QVector2D(0.0, 1.0), // v2
    QVector2D(0.0, 0.0), // v3
    QVector2D(1.0, 0.0), // v0

    /* face front */
    QVector2D(1.0, 0.0), // v0
    QVector2D(1.0, 1.0), // v1
    QVector2D(0.0, 1.0), // v2
    QVector2D(0.0, 1.0), // v2
    QVector2D(0.0, 0.0), // v3
    QVector2D(1.0, 0.0), // v0
};

GLfloat gcolors[] = {
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
};

Cube::Cube()
{
    m_mode.setToIdentity();
    m_view.setToIdentity();

    m_vertices = gvertices;
    m_colors = gcolors;
    m_indices = gindices;
}

Cube::Cube(float x, float y, float z)
{
    Cube();
    m_mode.translate(x, y, z);
    setpos(x, y, z);
}

GLuint Cube::getvertices(GLfloat **vertices)
{
    *vertices = gvertices;
    return sizeof(gvertices);
}

GLuint Cube::getindicies(GLubyte **indices)
{
    *indices = gindices;
    return sizeof(gindices);
}

GLuint Cube::getcolors(GLfloat **colors)
{
    *colors = gcolors;
    return sizeof(gcolors);
}

GLuint Cube::gettexcoords(QVector2D **texcoord)
{
    *texcoord = texcoords;
    return sizeof(texcoords);
}

void Cube::setcolor(float color[])
{
    memcpy(m_colors, color, sizeof(m_colors));
}

void Cube::translation(float x, float y, float z)
{
    m_mode.translate(x, y, z);
    setpos(x, y, z);
}

void Cube::rotate(float angle, float x, float y, float z)
{
    m_mode.rotate(angle, x, y, z);
}

void Cube::view(float x, float y, float z)
{
    m_view.translate(x, y, z);
}

void Cube::viewrotate(float angle, float x, float y, float z)
{
    m_view.rotate(angle, x, y, z);
}

void Cube::multiplyview(QMatrix4x4 &matrix)
{
    m_view = matrix * m_view;
}

QMatrix4x4 Cube::getmatrix()
{
    return m_view * m_mode;
}

void Cube::setpos(float x, float y, float z)
{
    m_pos.setX(x);
    m_pos.setY(y);
    m_pos.setZ(z);
    m_pos.setW(1);
}

void Cube::rotatepos(int step, enum AXIS axis)
{
    QMatrix4x4 matrix;
    matrix.setToIdentity();

    switch (axis) {
    case AXIS_X0:
    case AXIS_X1:
    case AXIS_X2:
    default:
        matrix.rotate(90.0 * step, 1, 0, 0);
        break;
    case AXIS_Y0:
    case AXIS_Y1:
    case AXIS_Y2:
        matrix.rotate(90.0 * step, 0, 1, 0);
        break;
    case AXIS_Z0:
    case AXIS_Z1:
    case AXIS_Z2:
        matrix.rotate(90.0 * step, 0, 0, 1);
        break;
    }

    m_pos = matrix * m_pos;
}

void Cube::getpanel(AXIS *x, AXIS *y, AXIS *z)
{
    *x = static_cast<AXIS>((int)m_pos.x() + 1 + AXIS_X0);
    *y = static_cast<AXIS>((int)m_pos.y() + 1 + AXIS_Y0);
    *z = static_cast<AXIS>((int)m_pos.z() + 1 + AXIS_Z0);
}


/* Attach cube to rubik`s cube
 * except exception panel */
void Cube::attach(TriangleWindow *rubik, AXIS exception)
{
    AXIS x, y, z;
    getpanel(&x, &y, &z);
    if (exception != x)
        rubik->m_panel[x].add(this);
    if (exception != y)
        rubik->m_panel[y].add(this);
    if (exception != z)
        rubik->m_panel[z].add(this);
}

/* Dettach cube from rubik`s cube
 * except exception panel */
void Cube::detach(TriangleWindow *rubik, AXIS exception)
{
    AXIS x, y, z;
    getpanel(&x, &y ,&z);
    if (exception != x)
        rubik->m_panel[x].remove(this);
    if (exception != y)
        rubik->m_panel[y].remove(this);
    if (exception != z)
        rubik->m_panel[z].remove(this);
}

#if 0
void Cube::draw(QOpenGLShaderProgram *program, QMatrix4x4 &matrix)
{
        m_posAttr = program->attributeLocation("posAttr");
        m_colAttr = program->attributeLocation("colAttr");
        m_matrixUniform = program->uniformLocation("matrix");

        program->setUniformValue(m_matrixUniform, matrix);

        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT,GL_FALSE, 0, m_vertices);
        glVertexAttribPointer(m_colAttr, 4, GL_FLOAT, GL_FALSE, 0, m_colors);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, m_indices);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
}
#endif
