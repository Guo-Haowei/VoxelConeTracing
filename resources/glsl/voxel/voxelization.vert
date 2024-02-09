#include "cbuffer.glsl.h"
#include "vsinput.glsl.h"

out vec3 pass_positions;
out vec3 pass_normals;
out vec2 pass_uvs;
out vec4 pass_light_space_positions0;
out vec4 pass_light_space_positions1;
out vec4 pass_light_space_positions2;

void main() {
    // assume no transformation
    vec4 world_position = c_model_matrix * vec4(in_position, 1.0);
    pass_positions = world_position.xyz;
    pass_normals = normalize(in_normal);
    pass_uvs = in_uv;
    pass_light_space_positions0 = LightPVs[0] * world_position;
    pass_light_space_positions1 = LightPVs[1] * world_position;
    pass_light_space_positions2 = LightPVs[2] * world_position;
    gl_Position = world_position;
}