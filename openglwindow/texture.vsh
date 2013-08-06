//attribute highp vec4 qt_Vertex;
attribute highp vec4 posAttr;
attribute highp vec4 qt_MultiTexCoord0;
//uniform highp mat4 qt_ModelViewProjectionMatrix;
uniform highp mat4 matrix;
varying highp vec4 qt_TexCoord0;

void main(void)
{
    //gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    gl_Position = matrix * posAttr;
    qt_TexCoord0 = qt_MultiTexCoord0;
}
