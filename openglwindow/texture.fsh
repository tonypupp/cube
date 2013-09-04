uniform samplerCube qt_Texture0;
varying highp vec3 qt_TexCoord0;

void main(void)
{
#if 0
    vec3 coord = vec3(-0.5, -0.5, 0.5);
    vec4 R = textureCube(qt_Texture0, coord);

    if (R.r == 0.0 || R.g == 0.0 || R.b == 0.0)
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    else
        gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
#else
    gl_FragColor = textureCube(qt_Texture0, qt_TexCoord0);
#endif
}
