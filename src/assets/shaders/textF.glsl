#version 330 core

uniform sampler2DArray uTextureArrayId;
uniform int uCharIndex;
uniform vec4 uColor;

in vec2 texOut;

void main()
{
    float t =  texture(uTextureArrayId, vec3(texOut, uCharIndex)).r;
    gl_FragColor = vec4(uColor.xyz, t);
}