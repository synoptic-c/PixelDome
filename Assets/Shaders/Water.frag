#version 330 core
out vec4 FragColor;
in vec2 v_texture;
uniform sampler2D u_texture;
uniform float u_time;
void main()
{
	vec2 texCoord = v_texture;
	texCoord.x += sin(texCoord.y * 15.0 + u_time * 2.0) * 0.02;
	texCoord.x += sin(texCoord.y * 20.0 + u_time * 1.5) * 0.02;
	texCoord.y += cos(texCoord.x * 15.0 + u_time * 1.5) * 0.02;
	FragColor = texture(u_texture, texCoord);
}