#include "PlainNode.hpp"

using Shay::PlainNode;

// Function depreciated, to be deleted when safe too.
void PlainNode::Clear() {}

void PlainNode::SetData(Slope tempType, GLfloat tempXs, GLfloat tempXe,
                        GLfloat tempYs, GLfloat tempYe, GLfloat tempZs,
                        GLfloat tempZe) {
    m_type        = tempType;
    m_xPlainStart = tempXs;
    m_xPlainEnd   = tempXe;
    m_yPlainStart = tempYs;
    m_yPlainEnd   = tempYe;
    m_zPlainStart = tempZs;
    m_zPlainEnd   = tempZe;
}

PlainNode::Slope PlainNode::GetType() {
    return m_type;
}
GLfloat PlainNode::GetXstart() {
    return m_xPlainStart;
}
GLfloat PlainNode::GetXend() {
    return m_xPlainEnd;
}
GLfloat PlainNode::GetYstart() {
    return m_yPlainStart;
}
GLfloat PlainNode::GetYend() {
    return m_yPlainEnd;
}
GLfloat PlainNode::GetZstart() {
    return m_zPlainStart;
}
GLfloat PlainNode::GetZend() {
    return m_zPlainEnd;
}
