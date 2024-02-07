#version 330 core

// uniform vec3 uResolution;
uniform vec4 uColStart;
uniform vec4 uColEnd;

in vec2 texOut;

void main()
{
    // float ar = uResolution.x / uResolution.y;
    vec2 uv = texOut.xy;;
    // uv.x *= ar;

    gl_FragColor = uColStart*(1.0f - uv.x) + uColEnd*uv.x;
}