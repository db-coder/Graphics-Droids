#version 330

in vec4 vPosition;
in vec2 texCoord;
in vec4 vColor;
in vec3 vNormal;

out vec3 normal;
out vec4 eye;
out vec2 tex;
out vec4 color;
out vec4 Act_Position;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
void main (void) 
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = (normalMatrix * normalize(vNormal)); 
  eye = - (uModelViewMatrix * gl_Position); 
  color = vColor;
  tex = texCoord;
  Act_Position = gl_Position;
}
