#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inTexCoord;

out vec4 vertexColor;
out vec2 TexCoord;

uniform float greenValue;
uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(0.5f, greenValue, 0.5f, 1.0f);
    TexCoord = inTexCoord;
}