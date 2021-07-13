#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 proj;
uniform vec2 offset;
uniform vec4 color;

void main()
{
    float scale = 10;
    TexCoords = vertex.zw;
    ParticleColor = color;
    gl_Position = proj* vec4(vertex.xy*scale + offset, 0.0, 1.0);
}
