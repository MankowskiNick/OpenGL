#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 inTexCoord;

out vec2 TexCoord;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord = inTexCoord;
}