#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTopTex;
layout (location = 2) in vec2 aBottomTex;
layout (location = 3) in vec2 aSideTex;

out vec2 TopTex;
out vec2 BottomTex;
out vec2 SideTex;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    TopTex = aTopTex;
    BottomTex = aBottomTex;
    SideTex = aSideTex;
}