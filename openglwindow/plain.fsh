varying lowp vec4 col;

void main(void)
{
#if 1
    gl_FragColor = col;
#else
    //Need to comments out all col attribute related code in vsh as well as trianglewindow;
    gl_FragColor = vec4(0.0, 1.0, 1.0, 0.0);
#endif

}
