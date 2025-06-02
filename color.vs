#version 400
in vec3 inputPosition;
in vec3 inputColor;

out vec3 color;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
  // NOTE(m2sprite): Calculate the position of the vertex against the world, view, and prjection matrices.
  gl_Position = vec4(inputPosition,1.0f)*worldMatrix;
  gl_Position = gl_Position*viewMatrix;
  gl_Position = gl_Position*projectionMatrix;

  color = inputColor;
}
