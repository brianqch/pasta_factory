#version 330

uniform vec4 u_color;
uniform vec3 u_cam_pos;
uniform vec3 u_light_pos;
uniform vec3 u_light_intensity;

in vec4 v_position;
in vec4 v_normal;
in vec2 v_uv;

out vec4 out_color;

void main() {
  // YOUR CODE HERE
  
  float ka = 0.1;
  float kd = 0.8;
  float ks = 0.8;

  vec4 Ia = vec4(1.0, 1.0, 1.0, 1.0);
  float p = 32.0;

  vec4 I = vec4(u_light_intensity, 1.0);
  vec4 r = vec4(u_light_pos, 1.0) - v_position;
  float r2 = length(r) * length(r);
  vec4 l = normalize(r);
  vec4 v = normalize(vec4(u_cam_pos, 1.0) - v_position);
  vec4 h = normalize(v + l);
  vec4 n = normalize(v_normal);

  vec4 ambient = ka * Ia;
  vec4 diffuse = kd * (I/r2) * max(0.0, dot(n, l));
  vec4 specular = ks * (I/r2) * pow(max(0.0, dot(n, h)), p);
  out_color = ambient + diffuse + specular;

  // (Placeholder code. You will want to replace it.)
  // out_color = (vec4(1, 1, 1, 0) + v_normal) / 2;
  out_color.a = 1;
}

