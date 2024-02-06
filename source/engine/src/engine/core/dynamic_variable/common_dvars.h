#include "dynamic_variable_begin.h"

DVAR_STRING(scene, DVAR_FLAG_NONE, "");

// @TODO: refactor
DVAR_IVEC2(window_resolution, DVAR_FLAG_SERIALIZE, 800, 600);
DVAR_IVEC2(window_position, DVAR_FLAG_SERIALIZE, 40, 40);

DVAR_BOOL(verbose, DVAR_FLAG_NONE, false);

DVAR_STRING(r_backend, DVAR_FLAG_NONE, "opengl");
DVAR_BOOL(r_gpu_validation, DVAR_FLAG_NONE, false);

DVAR_INT(r_enableVXGI, DVAR_FLAG_NONE, 1);
DVAR_INT(r_forceVXGI, DVAR_FLAG_NONE, 1);
DVAR_INT(r_debugTexture, DVAR_FLAG_NONE, 0);
DVAR_INT(r_noTexture, DVAR_FLAG_NONE, 0);

// camera
DVAR_VEC3(cam_pos, DVAR_FLAG_SERIALIZE, -8.f, 2.f, 0.f);
DVAR_VEC4(cam_cascades, DVAR_FLAG_SERIALIZE, 0.1f, 8.0f, 18.0f, 50.0f);
DVAR_FLOAT(cam_fov, DVAR_FLAG_SERIALIZE, 60.0f);

// light
DVAR_VEC3(light_dir, DVAR_FLAG_NONE, -8.0f, 25.0f, 5.0f);
DVAR_FLOAT(light_power, DVAR_FLAG_NONE, 20.0f);

// voxel GI
DVAR_INT(r_voxelSize, DVAR_FLAG_NONE, 64);

// CSM
DVAR_INT(r_debugCSM, DVAR_FLAG_NONE, 0);
DVAR_INT(r_shadowRes, DVAR_FLAG_NONE, 1024 * 4);
DVAR_INT(r_enableCSM, DVAR_FLAG_NONE, 1);

// SSAO
DVAR_INT(r_enableSsao, DVAR_FLAG_NONE, 1);
DVAR_INT(r_ssaoKernelSize, DVAR_FLAG_NONE, 32);
DVAR_INT(r_ssaoNoiseSize, DVAR_FLAG_NONE, 4);
DVAR_FLOAT(r_ssaoKernelRadius, DVAR_FLAG_NONE, 0.5f);

// FXAA
DVAR_INT(r_enableFXAA, DVAR_FLAG_NONE, 1);

#include "dynamic_variable_end.h"