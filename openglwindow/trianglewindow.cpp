#include "trianglewindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

TriangleWindow::TriangleWindow():
    m_program(0)
    , m_frame(0)
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

void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
#ifdef INLINED_SHADER
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
#else
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "../openglwindow/triangle.vsh");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "../openglwindow/triangle.fsh");
#endif
    m_program->link();
    m_program->bind();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");

    //matrix.perspective(60, 4.0/3.0, 0.1, 100.0);
    //matrix.perspective(60, 1, 0.1, 100.0);
    matrix.ortho(0.0f, 6.0f, 0.0f, 6.0f, 0.1f, 100.0f);
    matrix.translate(3, 3, -10);
    matrix.rotate(-30, 1, 1, 0);
    //matrix.rotate(30, 0, 1, 0);

    mouse_pressed = false;
    mouse_x = 0;
    mouse_y = 0;

    m_frame = 5;
    connect(&timer, &QTimer::timeout, this, &TriangleWindow::Ontimer);
    //timer.start(10);
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
    setAnimating(false);
    return;
}

void TriangleWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mouse_pressed = false;
    mouse_x = 0;
    mouse_y = 0;
    setAnimating(true);
    return;
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
    matrix.rotate(x_angle, 0, 1, 0);
    matrix.rotate(y_angle, 1, 0, 0);

    QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    return;
}

void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();

    //glViewport(0, 0, width() * retinaScale, high() * retinaScale);
    glViewport(0, 0, 640, 640);

    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
    glColor3i(0, 0xffffffff, 0);
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_BACK,GL_LINE);


    matrix.rotate(5.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    m_program->setUniformValue(m_matrixUniform, matrix);

#if 1
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
    };

    GLubyte indices[] = {
        0,1,2, 2,3,0, //front side
        5,6,2, 5,2,1, //right side
        4,3,7, 4,0,3, //left side
        0,5,1, 0,4,5, //bottom side
        3,2,6, 3,6,7, //up side
        5,7,6, 5,4,7, //back side
    };

    GLfloat colors[] = {
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
    };

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT,GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 4, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
#else
    GLfloat vertices[] = {
        0.0f, 0.707f,
        -0.5f, -0.5f,
        0.5f, 0.5f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    glVertexAttribPointer(m_posAttr,2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
#endif
}
