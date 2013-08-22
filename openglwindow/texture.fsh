uniform samplerCube qt_Texture0;
varying highp vec3 qt_TexCoord0;

void main(void)
{
    gl_FragColor = textureCube(qt_Texture0, qt_TexCoord0);
    //gl_FragColor = vec4(1.0, 1.0, 1.0, 0.0);
}
