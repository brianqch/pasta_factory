#version 330

uniform vec4 u_color;
uniform vec3 u_cam_pos;
uniform vec3 u_light_pos;
uniform vec3 u_light_intensity;

uniform sampler2D u_texture_2;
uniform vec2 u_texture_2_size;

uniform float u_normal_scaling;
uniform float u_height_scaling;

in vec4 v_position;
in vec4 v_normal;
in vec4 v_tangent;
in vec2 v_uv;

out vec4 out_color;

float h(vec2 uv) {
  // You may want to use this helper function...
  return texture(u_texture_2, uv).r;
  // return 0.0;
}

void main() {
  // YOUR CODE HERE

  float ka = 0.1;
  float kd = 0.8;
  float ks = 0.8;

  float Ia = 1.0;
  float p = 32.0;

  vec4 I = vec4(u_light_intensity, 1.0);
  vec4 r = vec4(u_light_pos, 1.0) - v_position;
  float r2 = length(r) * length(r);
  vec4 l = normalize(r);
  vec4 v = normalize(vec4(u_cam_pos, 1.0) - v_position);
  vec4 h_val = normalize(v + l);
  vec4 n = normalize(v_normal);

  float width = u_texture_2_size.x;
  float height = u_texture_2_size.y;

  vec3 b = cross(v_normal.xyz, v_tangent.xyz);
  mat3 tbn = mat3(v_tangent.xyz, b, v_normal.xyz);

  float dU = (h(vec2(v_uv.x + 1.0/width, v_uv.y)) - h(v_uv)) * u_height_scaling * u_normal_scaling;
  float dV = (h(vec2(v_uv.x, v_uv.y + 1.0 / height)) - h(v_uv)) * u_height_scaling * u_normal_scaling;
  vec3 n0 = vec3(-dU, -dV, 1.0);
  vec4 nd = vec4(tbn * n0, 1.0);


  out_color = ka * Ia + kd * (I/r2) * max(0.0, dot(nd, l)) + ks * (I/r2) * pow(max(0.0, dot(nd, h_val)), p);
  
  // (Placeholder code. You will want to replace it.)
  // out_color = (vec4(1, 1, 1, 0) + v_normal) / 2;
  out_color.a = 1;
}

