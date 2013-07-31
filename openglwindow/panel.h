#ifndef PANEL_H
#define PANEL_H

#include <QList>
#include <QtGui/QMatrix4x4>

class TriangleWindow;
class Cube;

enum AXIS {
    AXIS_X0 = 0, /* Vertical to X, X = -1 */
    AXIS_X1,     /* Vertical to X, X =  0 */
    AXIS_X2,     /* Vertical to X, X =  1 */
    AXIS_Y0,     /* Vertical to Y, Y = -1 */
    AXIS_Y1,     /* Vertical to Y, Y =  0 */
    AXIS_Y2,     /* Vertical to Y, Y =  1 */
    AXIS_Z0,     /* Vertical to Z, Z = -1 */
    AXIS_Z1,     /* Vertical to Z, Z =  0 */
    AXIS_Z2,     /* Vertical to Z, Z =  1 */
    AXIS_NULL
};

class Panel
{
public:
    Panel();

    /* Rotate and show */
    void rotate(float degree);
    /* Comfirm the end of a rotate */
    void rotatend(TriangleWindow *rubik);
    void setaxis(enum AXIS axis);
    float getdegree();

    void add(Cube *cube);
    void remove(Cube *cube);

private:
    float m_degree;
    enum AXIS m_axis;
    QList<Cube *> m_list;
    QMatrix4x4 m_rotm;
};

#endif // PANEL_H
