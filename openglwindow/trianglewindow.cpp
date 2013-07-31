#include "trianglewindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

#include <QWheelEvent>

TriangleWindow::TriangleWindow():
    m_program(0)
    , m_frame(5)
{
}

#ifdef INLINED_SHADER
static const char *vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "    col = colAttr;\n"
        "    gl_Position = matrix * posAttr;\n"
        "}\n";

static const char *fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "    gl_FragColor = col;\n"
        "}\n";


GLuint TriangleWindow::loadShader(GLuint type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    return shader;
}
#endif

void TriangleWindow::initcube()
{
    //m_cube = new Cube[m_num];
#if 1
    float red[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
    };
    float green[] = {
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
    };
    float blue[] = {
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
    };
#endif
    /* Left squre along AXIS X, X = -1 */
    /*    Y              */
    /*    ^              */
    /* 1, |   2  5  8    */
    /* 0, |   1  4  7    */
    /*-1, |   0  3  6    */
    /*    +----------> Z */
    /*       -1, 0, 1    */
    m_cube[0].translation(-1, -1, -1);
    m_cube[1].translation(-1, 0, -1);
    m_cube[2].translation(-1, 1, -1);

    m_cube[3].translation(-1, -1, 0);
    m_cube[4].translation(-1, 0, 0);
    m_cube[5].translation(-1, 1, 0);

    m_cube[6].translation(-1, -1, 1);
    m_cube[7].translation(-1, 0, 1);
    m_cube[8].translation(-1, 1, 1);
#if 1
    for (int i = 0; i < 9; i++)
        m_cube[i].setcolor(red);
#endif

    /* Middle squre along AXIS X = 0 */
    /*    Y                 */
    /*    ^                 */
    /* 1, |   11  14  17    */
    /* 0, |   10  13  16    */
    /*-1, |    9  12  15    */
    /*    +----------> Z    */
    /*       -1, 0, 1       */
    m_cube[9].translation(0, -1, -1);
    m_cube[10].translation(0, 0, -1);
    m_cube[11].translation(0, 1, -1);

    m_cube[12].translation(0, -1, 0);
    m_cube[13].translation(0, 0, 0);
    m_cube[14].translation(0, 1, 0);

    m_cube[15].translation(0, -1, 1);
    m_cube[16].translation(0, 0, 1);
    m_cube[17].translation(0, 1, 1);
#if 1
    for (int i = 0; i < 9; i++)
        m_cube[9 + i].setcolor(green);
#endif
    /* Right squre along AXIS X = 1 */
    /*    Y                 */
    /*    ^                 */
    /* 1, |   20  23  26    */
    /* 0, |   19  22  25    */
    /*-1, |   18  21  24    */
    /*    +----------> Z    */
    /*       -1, 0, 1       */
    m_cube[18].translation(1, -1, -1);
    m_cube[19].translation(1, 0, -1);
    m_cube[20].translation(1, 1, -1);

    m_cube[21].translation(1, -1, 0);
    m_cube[22].translation(1, 0, 0);
    m_cube[23].translation(1, 1, 0);

    m_cube[24].translation(1, -1, 1);
    m_cube[25].translation(1, 0, 1);
    m_cube[26].translation(1, 1, 1);

#if 1
    {
        int no = 0;
        m_cube[0].no = no++;
        m_cube[1].no = no++;
        m_cube[2].no = no++;
        m_cube[3].no = no++;
        m_cube[4].no = no++;
        m_cube[5].no = no++;
        m_cube[6].no = no++;
        m_cube[7].no = no++;
        m_cube[8].no = no++;
        m_cube[9].no = no++;
        m_cube[10].no = no++;
        m_cube[11].no = no++;
        m_cube[12].no = no++;
        m_cube[13].no = no++;
        m_cube[14].no = no++;
        m_cube[15].no = no++;
        m_cube[16].no = no++;
        m_cube[17].no = no++;
        m_cube[18].no = no++;
        m_cube[19].no = no++;
        m_cube[20].no = no++;
        m_cube[21].no = no++;
        m_cube[22].no = no++;
        m_cube[23].no = no++;
        m_cube[24].no = no++;
        m_cube[25].no = no++;
        m_cube[26].no = no++;
    }
#endif
}

void TriangleWindow::panelinit(Panel &panel, AXIS axis, int cube[])
{
    panel.setaxis(axis);

    for (int i = 0; i < 9; i++) {
        panel.add(&m_cube[*cube]);
        cube++;
    }
}

void TriangleWindow::initpanel(int cube_map[][9])
{
    panelinit(m_panel[AXIS_X0], AXIS_X0, &cube_map[0][0]);
    panelinit(m_panel[AXIS_X1], AXIS_X1, &cube_map[1][0]);
    panelinit(m_panel[AXIS_X2], AXIS_X2, &cube_map[2][0]);

    panelinit(m_panel[AXIS_Y0], AXIS_Y0, &cube_map[3][0]);
    panelinit(m_panel[AXIS_Y1], AXIS_Y1, &cube_map[4][0]);
    panelinit(m_panel[AXIS_Y2], AXIS_Y2, &cube_map[5][0]);

    panelinit(m_panel[AXIS_Z0], AXIS_Z0, &cube_map[6][0]);
    panelinit(m_panel[AXIS_Z1], AXIS_Z1, &cube_map[7][0]);
    panelinit(m_panel[AXIS_Z2], AXIS_Z2, &cube_map[8][0]);
}


void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
#ifdef INLINED_SHADER
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
#else
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "../openglwindow/plain.vsh");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "../openglwindow/plain.fsh");
#endif
    m_program->link();
    m_program->bind();

    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");

    m_view.setToIdentity();
#if 0
    m_view.perspective(60, 4.0/3.0, 0.1, 100.0);
#else
    m_view.ortho(-6.0f, 6.0f, -6.0f, 6.0f, -100.0f, 100.0f);
    m_view.translate(0, 0, -10);
    m_view.rotate(-30, 1, 1, 0);
#endif

    m_num = 27;
    initcube();

    int cube_map[9][9] = {
        /* Vertical to axis X, from left(-1) to right(1) */
        /* Left squre along AXIS X, X = -1 */
        /*    Y              */
        /*    ^              */
        /* 1, |   2  5  8    */
        /* 0, |   1  4  7    */
        /*-1, |   0  3  6    */
        /*    +----------> Z */
        /*       -1, 0, 1    */
        { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
        /*    Y                 */
        /*    ^                 */
        /* 1, |   11  14  17    */
        /* 0, |   10  13  16    */
        /*-1, |    9  12  15    */
        /*    +----------> Z    */
        /*       -1, 0, 1       */
        { 9, 10, 11, 12, 13, 14, 15, 16, 17 },
        /*    Y                 */
        /*    ^                 */
        /* 1, |   20  23  26    */
        /* 0, |   19  22  25    */
        /*-1, |   18  21  24    */
        /*    +----------> Z    */
        /*       -1, 0, 1       */
        { 18, 19, 20, 21, 22, 23, 24, 25, 26 },


        /* Vertical to axis Y, from bottom(-1) to top(1) */
        /*    Z                 */
        /*    ^                 */
        /* 1, |   18  21  24    */
        /* 0, |    9  12  15    */
        /*-1, |    0   3   6    */
        /*    +----------> X    */
        /*       -1, 0, 1       */
        { 0, 9, 18, 3, 12, 21, 6, 15, 24 },
        /*    Z                 */
        /*    ^                 */
        /* 1, |   19  22  25    */
        /* 0, |   10  13  16    */
        /*-1, |    1   4   7    */
        /*    +----------> X    */
        /*       -1, 0, 1       */
        { 1, 10, 19, 4, 13, 22, 7, 16, 25 },
        /*    Z                 */
        /*    ^                 */
        /* 1, |   20  23  26    */
        /* 0, |   11  13  17    */
        /*-1, |    2   5   8    */
        /*    +----------> X    */
        /*       -1, 0, 1       */
        { 2, 11, 20, 5, 13, 23, 8, 17, 26 },


        /* Vertical to axis Z, from near(-1) to far(1) */
        /*    Y                 */
        /*    ^                 */
        /* 1, |    2  11  20    */
        /* 0, |    1  10  19    */
        /*-1, |    0   9  18    */
        /*    +----------> X    */
        /*       -1, 0, 1       */
        { 0, 1, 2, 9, 10, 11, 18, 19, 20 },
        { 3, 4, 5, 12, 13, 14, 21, 22, 23 },
        { 6, 7, 8, 15, 16, 17, 24, 25, 26 }
    };

    initpanel(cube_map);
    m_roundpanel = false;

    mouse_pressed = false;
    mouse_x = 0;
    mouse_y = 0;

    //connect(&timer, &QTimer::timeout, this, &TriangleWindow::Ontimer);
    //timer.start(10);
}

void TriangleWindow::roundpanel()
{
    int i;
    for(i = 0; i < AXIS_NULL; i++)
            m_panel[i].rotatend(this);
}

void TriangleWindow::drawcube(Cube &cube, QMatrix4x4 &view)
{
    QMatrix4x4 modeview = view * cube.getmatrix();
    m_program->setUniformValue(m_matrixUniform, modeview);
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT,GL_FALSE, 0, cube.m_vertices);
    glVertexAttribPointer(m_colAttr, 4, GL_FLOAT, GL_FALSE, 0, cube.m_colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cube.m_indices);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void TriangleWindow::render()
{
    int i = 0;
    const qreal retinaScale = devicePixelRatio();
    int w = ((width () > height()) ? height() : width()) * retinaScale;
    static Panel *panel = &m_panel[AXIS_Z1];

    glViewport(0, 0, w, w);
    //glViewport(0, 0, 1600, 1600);

    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
    glColor3i(0, 0xffffffff, 0);
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);

    m_view.rotate(5.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    if (m_roundpanel){
#if 0
        roundpanel();
#else
        panel->rotatend(this);
#endif
        panel->rotate( -panel->getdegree() );
        m_roundpanel = false;
        if (panel == &m_panel[AXIS_Z1])
            panel = &m_panel[AXIS_X0];
        else
            panel = &m_panel[AXIS_Z1];
    } else if (getAnimating()){
        //rotate_panel(m_panel[AXIS_Z][1], 5);
        panel->rotate(5);
    }

    for (;i < m_num; i++) {
        drawcube(m_cube[i], m_view);
    }
}

void TriangleWindow::Ontimer()
{
    m_frame = 5;
}

void TriangleWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mouse_pressed = true;
    mouse_x = event->x();
    mouse_y = event->y();
    return;
}

void TriangleWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mouse_pressed = false;
    mouse_x = 0;
    mouse_y = 0;

    if (event->button() == Qt::RightButton) {
        m_roundpanel = true;
        renderNow();
    }

    return;
}

void TriangleWindow::wheelEvent(QWheelEvent *ev)
{
    QPoint degree = ev->angleDelta() / 120;
#if 1
    float scale = 1.0 + 0.1 * degree.y();
    m_view.scale(scale);
#else
    m_view.lookAt(
                QVector3D(-2, 0, 0),
                QVector3D(0, 0, 1),
                QVector3D(0, 1, 0));
#endif

    ev->accept();
}

void TriangleWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x_change;
    int y_change;
    float x_angle;
    float y_angle;

    if (!mouse_pressed)
        return;

    x_change = event->x() - mouse_x;
    mouse_x = event->x();
    y_change = event->y() - mouse_y;
    mouse_y = event->y();

    x_angle = (float)(x_change) * 180.0f / (float)width();
    y_angle = (float)(y_change)  * 180.0f / (float)height();
    m_view.rotate(x_angle, 0, 1, 0);
    m_view.rotate(y_angle, 1, 0, 0);

    if (!getAnimating())
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    return;
}

void TriangleWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);

    if (getAnimating())
        setAnimating(false);
    else
        setAnimating(true);
}

void TriangleWindow::autorender(bool enable)
{
    if (enable)
        setAnimating(true);
    else
        setAnimating(false);
}
