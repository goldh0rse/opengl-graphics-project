#version 430

in vec3 aPos;

out vec3 texCoords;

uniform mat4 projection;
uniform mat4 view;

void main(){
  //texCoords = vec3(aPos.x, aPos.y, -aPos.z);
  texCoords = aPos;
  vec4 pos = projection * view * vec4(aPos, 1.f);
  gl_Position = pos.xyww; // Depth == z == 1.f constant
}
