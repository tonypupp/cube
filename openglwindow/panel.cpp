#include "panel.h"
#include "cube.h"

Panel::Panel():
    m_degree(0),
    m_axis(AXIS_X0)
{
}

void Panel::setaxis(enum AXIS axis)
{
    m_axis = axis;
}

void Panel::rotate(float rotd)
{
    Cube *cube;

    m_rotm.setToIdentity();
    switch (m_axis) {
    case AXIS_Z0:
    case AXIS_Z1:
    case AXIS_Z2:
        m_rotm.rotate(rotd, 0, 0, 1);
        break;
    case AXIS_Y0:
    case AXIS_Y1:
    case AXIS_Y2:
        m_rotm.rotate(rotd, 0, 1, 0);
        break;
    default:
        m_rotm.rotate(rotd, 1, 0, 0);
    }
    m_degree += rotd;

    for (int i = 0; i < m_list.size(); i++) {
        cube = m_list.at(i);
        cube->multiplyview(m_rotm);
    }
}

void Panel::add(Cube *cube)
{
    m_list.append(cube);
}

void Panel::remove(Cube *cube)
{
    m_list.removeOne(cube);
}

float Panel::getdegree()
{
    return m_degree;
}

void Panel::rotatend(TriangleWindow *rubik)
{
    int i;
    int step;
    Cube * cube;

    i = m_degree / 90;
    m_degree = m_degree - i * 90;

    /* Calculate new positio of the cube */
    step = i % 4;
    if (step < 0) step = 4 - step;
    for (i = 0; i < m_list.size(); i++) {
        /* Do not do detach and attach option.
         * The cube already in this panel */
        cube = m_list[i];
        cube->detach(rubik, m_axis);
        cube->rotatepos(step, m_axis);
        cube->attach(rubik, m_axis);
    }
}
