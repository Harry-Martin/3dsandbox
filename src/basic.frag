#version 330 core

out vec4 color;

uniform vec4 u_color;
uniform vec4 light_pos;
uniform vec4 light_color;
uniform float u_specular;
uniform float u_light_radius;

in vec3 norm;
in vec3 f_pos;

in vec3 ambient;

void main()
{
    vec3 camera_pos = vec3(0.0, 0.0, 0.0); // PASS THIS AS A UNIFORM
    vec3 to_camera = normalize(camera_pos - f_pos);

    vec3 to_light = normalize(light_pos.xyz - f_pos);
    vec3 diffuse = max(dot(norm, to_light), 0.0f) * light_color.xyz;

    vec3 reflected_dir = reflect(-to_light, norm);
    vec3 view_dir = -to_camera;

    float dist = length(to_light);
    float intensity = u_light_radius/ pow(dist, 2);

    float spec = pow(max(dot(view_dir, reflected_dir), 0.0), 256);
    vec3 specular = u_specular * spec * light_color.xyz;

    color = vec4(ambient + ((diffuse + specular) * intensity) * u_color.xyz, 1.0);
}

