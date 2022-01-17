#version 430

out vec4 color;

in vec3 vertexPosition;
in vec3 near;
in vec3 far;

float checkerboard(vec2 r, float scale) {
	return float((int(floor(r.x / scale)) + int(floor(r.y / scale))) % 2);
}

void main(){
	float t = -near.y / (far.y-near.y);

	vec3 r = near + t * (far-near);

	float c =
		checkerboard(r.xz, 1) * 0.3 +
		checkerboard(r.xz, 10) * 0.2 +
		checkerboard(r.xz, 100) * 0.1 +
		0.1;

	color = vec4(vec3(c/2.0 + 0.3), 1) * float(t > 0);
}
