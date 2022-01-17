#version 430


in vec3 p;

in vec3 iNearPositionVert;
in vec3 iFarPositionVert;

out vec3 vertexPosition;
out vec3 near;
out vec3 far;

void main() {
	vertexPosition = p;
	near = iNearPositionVert;
	far = iFarPositionVert;

	gl_Position = vec4(p, 1);
}
