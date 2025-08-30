#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D textureData0;
uniform sampler2D textureData1;

uniform float mixAmount;

void main()
{
    vec4 texture0 = texture(textureData0, TexCoord);
    vec4 texture1 = texture(textureData1, TexCoord);
    FragColor = mix(texture0, texture1, mixAmount);
};