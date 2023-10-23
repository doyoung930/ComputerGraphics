#version 330 core

in vec3 out_Color;
in mat4 out_GluColor;
out vec4 FragColor;

void main()
{
	FragColor = out_GluColor * vec4(out_Color, 1.0f);
}
