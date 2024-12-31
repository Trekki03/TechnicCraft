#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 36) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec2 TopTex[];
in vec2 BottomTex[];
in vec2 SideTex[];

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

vec3 cubeVertices[36] = vec3[](
    // Front
    vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0), vec3(1.0, 1.0, 0.0), vec3(1.0, 0.0, 0.0),
    // Back
    vec3(0.0, 0.0, -1.0), vec3(1.0, 0.0, -1.0), vec3(0.0, 1.0, -1.0),
    vec3(0.0, 1.0, -1.0), vec3(1.0, 0.0, -1.0), vec3(1.0, 1.0, -1.0),
    // Left
    vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, -1.0), vec3(0.0, 1.0, 0.0),
    vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, -1.0), vec3(0.0, 0.0, -1.0),
    // Right
    vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 0.0), vec3(1.0, 0.0, -1.0),
    vec3(1.0, 1.0, 0.0), vec3(1.0, 1.0, -1.0), vec3(1.0, 0.0, -1.0),
    // Top
    vec3(0.0, 1.0, 0.0), vec3(1.0, 1.0, 0.0), vec3(0.0, 1.0, -1.0),
    vec3(1.0, 1.0, 0.0), vec3(1.0, 1.0, -1.0), vec3(0.0, 1.0, -1.0),
    // Bottom
    vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, -1.0), vec3(1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, -1.0), vec3(1.0, 0.0, -1.0)
);

vec3 cubeNormals[36] = vec3[](
    // Front
    vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0),
    vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 0.0, 1.0),
    // Back
    vec3(0.0, 0.0, -1.0), vec3(0.0, 0.0, -1.0), vec3(0.0, 0.0, -1.0),
    vec3(0.0, 0.0, -1.0), vec3(0.0, 0.0, -1.0), vec3(0.0, 0.0, -1.0),
    // Left
    vec3(-1.0, 0.0, 0.0), vec3(-1.0, 0.0, 0.0), vec3(-1.0, 0.0, 0.0),
    vec3(-1.0, 0.0, 0.0), vec3(-1.0, 0.0, 0.0), vec3(-1.0, 0.0, 0.0),
    // Right
    vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0),
    vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0),
    // Top
    vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0),
    vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0),
    // Bottom
    vec3(0.0, -1.0, 0.0), vec3(0.0, -1.0, 0.0), vec3(0.0, -1.0, 0.0),
    vec3(0.0, -1.0, 0.0), vec3(0.0, -1.0, 0.0), vec3(0.0, -1.0, 0.0)
);

const float ATLAS_FACTOR = 1.0/192.0;

vec2 getTexCoords(int face, int vertex) 
{
    vec2 baseTexCoords;
    if (face < 24) 
    {
        baseTexCoords = SideTex[0];
    } 
    else if (face < 30) 
    {
        baseTexCoords = TopTex[0];
    }
    else 
    {
        baseTexCoords = BottomTex[0];
    }

    vec2 offset;
    if (vertex == 0) 
    {
        offset = vec2(0.0, 0.0);
    } else if (vertex == 1) 
    {
        offset = vec2(0.0, 1.0);
    } else 
    {
        offset = vec2(1.0, 0.0);
    }

    return (baseTexCoords + offset) * ATLAS_FACTOR;
}

void main(void) 
{
    vec3 zeroPos = gl_in[0].gl_Position.xyz;

    for (int i = 0; i < 36; i += 3) // Each triangle has 3 vertices
    {
        for (int vertex = 0; vertex < 3; vertex++) 
        {
            vec3 pos = cubeVertices[i + vertex];
            FragPos = vec3(model * vec4(zeroPos + pos, 1.0));
            gl_Position = projection * view * model * vec4(zeroPos + pos, 1.0);
            Normal = mat3(transpose(inverse(model))) * cubeNormals[i + vertex];
            TexCoord = getTexCoords(i, vertex);
            EmitVertex();
        }
        EndPrimitive();
    }
}