#pragma once
#include "gl_utils.h"

enum class ProgramType {
    IMAGE2D,
    LINE3D,
    SHADOW,
    GBUFFER,
    SSAO,
    COUNT,
};

void R_CreateShaderPrograms();
void R_DestroyShaderPrograms();

const gl::Program& R_GetShaderProgram( ProgramType type );