#include "trianglewindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

#include <QWheelEvent>

static const char *varying[] = {
    "gl_Position"
};

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
#ifndef VBO
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
#ifndef VBO
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

void TriangleWindow::inittexture()
{
    glEnable(GL_TEXTURE_2D);
    //QImage tex(":/cube.png");
    QImage texture("../openglwindow/red_640x640.png");
    if (texture.isNull()) {
        return;
    }
    //QImage texture(tex.convertToFormat(QImage::Format_RGB888));
    //QImage texture(tex);

    GLsizei width = texture.width();
    GLsizei height = texture.height();
    const GLvoid *pixels = texture.bits();

    glGenTextures(1, &m_texture);
    if (m_texture == 0)
        ;
    else {
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void TriangleWindow::initshaders()
{
    m_program = new QOpenGLShaderProgram(this);
#ifdef INLINED_SHADER
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
#else
#ifndef TEXTURE
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/plain.vsh");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/plain.fsh");
#else
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/texture.vsh");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/texture.fsh");
#endif
#endif
    m_program->link();
    m_program->bind();

    m_posAttr = m_program->attributeLocation("posAttr");
#ifndef TEXTURE
    m_colAttr = m_program->attributeLocation("colAttr");
#else
    m_texcoord = m_program->attributeLocation("qt_MultiTexCoord0");
#endif
    m_matrixUniform = m_program->uniformLocation("matrix");

#ifdef VBO
    glGenBuffers(2, m_vbo);
    if (m_vbo[0] == 0)
        ;
    else {
        GLuint size;
        struct VertexData *vertices;

        size = Cube::getvertices(&vertices);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

#ifdef TEXTURE
    if (m_vbo[1] == 0)
        ;
    else {
        GLuint size;
        QVector2D *texcoord;

        size = Cube::gettexcoords(&texcoord);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, size, texcoord, GL_STATIC_DRAW);

    }
#endif

#ifdef RAW_OPENGL
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(struct VertexData), static_cast<GLfloat *>(0));
#ifndef TEXTURE
    glVertexAttribPointer(m_colAttr, 4, GL_FLOAT, GL_FALSE, sizeof(struct VertexData), (const void *)(sizeof(GLfloat)*3));
#else
    m_program->setAttributeArray(m_colAttr, static_cast<GLfloat *>(0), 4);
#endif //TEXTURE
#else //RAW_OPEN
    //m_program->setAttributeArray(m_posAttr, static_cast<GLfloat *>(0), 3, sizeof(struct VertexData));
    m_program->setAttributeArray(m_posAttr, static_cast<GLfloat *>(0), 3, 0);
#ifdef TEXTURE
    m_program->setAttributeArray(m_texcoord, static_cast<GLfloat *>(0), 2);
#else
    //m_program->setAttributeArray(m_colAttr, (const GLfloat *)(12), 4, sizeof(struct VertexData));
    m_program->setAttributeArray(m_colAttr, (const GLfloat *)(sizeof(QVector3D)*36), 4, 0);
#endif

#if 1
    glGenBuffers(1, &m_elementbuffer);
    if (m_elementbuffer == 0)
        ;
    else {
        GLuint size;
        GLubyte *indices;

        size = Cube::getindicies(&indices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }
#endif
#endif //RAW_OPEN
/*
    glGenBuffers(1, &m_color);
    if (m_color == 0)
        ;
    else{
        GLuint size;
        GLfloat *color;

        size = Cube::getcolors(&color);
        glBindBuffer(GL_ARRAY_BUFFER, m_color);
        glBufferData(GL_ARRAY_BUFFER, size, color, GL_STATIC_DRAW);
    }


#ifdef RAW_OPENGL
    glVertexAttribPointer(m_colAttr, 4, GL_FLOAT, GL_FALSE, 0, static_cast<GLfloat *>(0));
#else
    //m_program->setAttributeArray(m_colAttr, static_cast<GLfloat *>(0), 4);
#endif

    glGenBuffers(1, &m_feedbackbuffer);
    if (m_feedbackbuffer == 0)
        ;
    else {
        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, m_feedbackbuffer);
        glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, 96, NULL, GL_DYNAMIC_COPY);
        //glTransformFeedbackVaryings(m_program, 1, varying, GL_SEPERATE_ATTRIBS);
    }
 */
#endif //VBO
}

void TriangleWindow::initialize()
{
    initshaders();
#ifdef TEXTURE
    inittexture();
#endif
    m_view.setToIdentity();
#if 0
    m_view.perspective(60, 4.0/3.0, 0.1, 100.0);
#else
    m_view.ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
    //m_view.translate(0, 0, -10);
    //m_view.rotate(-30, 1, 1, 0);
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

#ifndef VBO
void TriangleWindow::drawcube(Cube &cube, QMatrix4x4 &matrix)
{
    QMatrix4x4 modeview = matrix * cube.getmatrix();
    m_program->setUniformValue(m_matrixUniform, modeview);

#ifdef RAW_OPENGL
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, cube.m_vertices);
    glVertexAttribPointer(m_colAttr, 4, GL_FLOAT, GL_FALSE, 0, cube.m_colors);
    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);
#else
    m_program->setAttributeArray(m_posAttr, cube.m_vertices, 3);
    m_program->setAttributeArray(m_colAttr, cube.m_colors, 4);
    m_program->enableAttributeArray(m_posAttr);
    m_program->enableAttributeArray(m_colAttr);
#endif

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, cube.m_indices);

#ifdef RAW_OPENGL
    glDisableVertexAttribArray(m_posAttr);
    glDisableVertexAttribArray(m_colAttr);
#else
    m_program->disableAttributeArray(m_posAttr);
    m_program->disableAttributeArray(m_colAttr);
#endif
}

#else
void TriangleWindow::drawcube(Cube &cube, QMatrix4x4 &matrix)
{
    QMatrix4x4 modeview = matrix * cube.getmatrix();
    m_program->setUniformValue(m_matrixUniform, modeview);

#ifdef RAW_OPENGL
    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);
#else
    m_program->enableAttributeArray(m_posAttr);
#ifdef TEXTURE
    m_program->enableAttributeArray(m_texcoord);
#else
    m_program->enableAttributeArray(m_colAttr);
#endif //TEXTURE
#endif //RAW_OPENGL

    //glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, (GLvoid *)0);
    glDrawArrays(GL_TRIANGLES,0,36);

#ifdef RAW_OPENGL
    glDisableVertexAttribArray(m_posAttr);
    glDisableVertexAttribArray(m_colAttr);
#else
    m_program->disableAttributeArray(m_posAttr);
#ifdef TEXTURE
    m_program->disableAttributeArray(m_texcoord);
#else
    m_program->disableAttributeArray(m_colAttr);
#endif //TEXTURE
#endif //RAW_OPENGL
}
#endif //VBO

void TriangleWindow::render()
{
    int i;
    const qreal retinaScale = devicePixelRatio();
#if 0
    int w = ((width () > height()) ? height() : width()) * retinaScale;
#else
    int w = width();
    int h = height();
    w = ((w > h) ? h : w) *retinaScale;
#endif
    static Panel *panel = &m_panel[AXIS_Z1];

    glViewport(0, 0, w, w);
    //glViewport(0, 0, 1600, 1600);

    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_FLAT);
#ifndef TEXTURE
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH);
    glEnable(GL_BLEND);

#if 0
    m_view.rotate(5.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
#endif

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

    //for (i = 0; i < m_num; i++) {
    for (i = 0; i < m_num; i++) {
        drawcube(m_cube[i], m_view);
    }

#if 0
    glViewport(320, 320, w/2, w/2);
    for (i = 0 ;i < m_num; i++) {
        drawcube(m_cube[i], m_view);
    }
#endif
    glFinish();
 //   coordinate(m_view);
}

void TriangleWindow::Ontimer()
{
    m_frame = 5;
}

void TriangleWindow::mousePressEvent(QMouseEvent *event)
{
    mouse_pressed = true;
    mouse_x = event->x();
    mouse_y = event->y();

    event->accept();
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

    event->accept();
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

    if (!getAnimating())
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
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
    m_view.rotate(-x_angle, 0, 1, 0);
    m_view.rotate(-y_angle, 1, 0, 0);

    if (!getAnimating())
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));

    event->accept();
}

void TriangleWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if (getAnimating())
        setAnimating(false);
    else
        setAnimating(true);

    ev->accept();
}

void TriangleWindow::keyPressEvent(QKeyEvent *ke)
{
    Qt::Key key = static_cast<Qt::Key>(ke->key());

    if (key == Qt::Key_Left)
        m_view.rotate(-5.0f, 0, 1, 0);
    else if (key == Qt::Key_Right)
        m_view.rotate(5.0f, 0, 1, 0);
    else if (key == Qt::Key_Up)
        m_view.rotate(-5.0f, 1, 0, 0);
    else if (key == Qt::Key_Down)
        m_view.rotate(5.0f, 1, 0, 0);
    else if (key == Qt::Key_Z)
        m_view.rotate(-5.0f, 0, 0, 1);
    else if (key == Qt::Key_A)
        m_view.rotate(5.0, 0, 0, 1);
    else
        return QWindow::keyPressEvent(ke);

    if (!getAnimating())
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));

    ke->accept();
}

void TriangleWindow::autorender(bool enable)
{
    if (enable)
        setAnimating(true);
    else
        setAnimating(false);
}

void TriangleWindow::coordinate(QMatrix4x4 matrix)
{
    QOpenGLShaderProgram program;
    GLfloat linewidth;

    GLfloat cor_pos[] ={
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, -2.0f,
    };
    GLfloat cor_col[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };
    /* First released m_program */
    //m_program->release();

    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/coordinator.vsh");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/coordinator.fsh");
    program.link();
    program.bind();
#if 1
    program.setAttributeArray("pos", cor_pos, 3);
    program.setAttributeArray("col", cor_col, 4);
    //matrix.translate(-5, -5);
    program.setUniformValue("cor_matrix", matrix);

    program.enableAttributeArray("col");
    program.enableAttributeArray("pos");

    glGetFloatv(GL_LINE_WIDTH, &linewidth);
    glLineWidth(100.0f);
    glDrawArrays(GL_LINES, 0, 6);
    glLineWidth(linewidth);

    program.disableAttributeArray("pos");
    program.disableAttributeArray("col");
#endif
    program.release();

    /* Rebind m_program at the end */
    //m_program->bind();
}
