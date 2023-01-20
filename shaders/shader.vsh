#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
uniform float greenValue;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    //vertexColor = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec4(0.5f, greenValue, 0.5f, 1.0f);
}