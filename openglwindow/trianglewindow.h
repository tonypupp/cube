#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include "openglwindow.h"

#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QMatrix4x4>
#include <QMouseEvent>
#include <QTimer>
#include <QList>

#include "cube.h"
#include "panel.h"

class QTimer;
class QMouseEvent;

#define VBO
//#define RAW_OPENGL
//#define TEXTURE
class TriangleWindow : public OpenGLWindow
{

public:
    TriangleWindow();
    void render();
    void autorender(bool enable);

protected:
    void keyPressEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *ev);
    void mouseDoubleClickEvent(QMouseEvent *ev);

private:
    friend class Cube;
#ifdef INLINED_SHADER
    GLuint loadShader(GLuint type, const char *source);
#endif
    void initialize();

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    GLuint m_vbo[2];
    GLuint m_elementbuffer;
    //GLuint m_color;
    GLuint m_texcoord;
    GLuint m_feedbackbuffer;
    void initshaders();
    GLuint m_texture;
    void inittexture();

    int m_num;
    Cube m_cube[27];
    void initcube();
    void drawcube(Cube &cube, QMatrix4x4 &matrix);

    Panel m_panel[AXIS_NULL];
    void panelinit(Panel &panel, enum AXIS axis, int cube[]);
    void initpanel(int cube_map[][9]);

    void roundpanel();
    bool m_roundpanel;

    bool mouse_pressed;
    int mouse_x;
    int mouse_y;

    QOpenGLShaderProgram *m_program;
    QMatrix4x4 m_view;

    int m_frame;
    QTimer timer;
    void Ontimer();

    void coordinate(QMatrix4x4 matrix);
};

#endif // TRIANGLEWINDOW_H
