attribute highp vec4 posAttr;
attribute highp vec3 qt_MultiTexCoord0;
uniform highp mat4 matrix;
varying highp vec3 qt_TexCoord0;

void main(void)
{
    gl_Position = matrix * posAttr;
    qt_TexCoord0 = normalize(qt_MultiTexCoord0);
}
