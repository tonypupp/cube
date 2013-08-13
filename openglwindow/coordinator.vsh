attribute highp vec4 pos;
attribute lowp vec4 col;
varying lowp vec4 col_varying;
uniform highp mat4 cor_matrix;


void main(void)
{
    gl_Position = cor_matrix * pos;
    col_varying = col;
}
