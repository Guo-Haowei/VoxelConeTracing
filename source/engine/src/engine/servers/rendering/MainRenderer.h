#pragma once
#include "GpuTexture.h"
#include "gl_utils.h"
#include "passes.h"
#include "r_cbuffers.h"

namespace vct {

class MainRenderer {
public:
    void createGpuResources();
    void on_scene_change();
    void render();
    void renderFrameBufferTextures(int width, int height);
    void renderToVoxelTexture();
    void destroyGpuResources();

    void gbufferPass();
    void vctPass();

private:
    /// vertex arrays

    /// textures
    GpuTexture m_albedoVoxel;
    GpuTexture m_normalVoxel;

    GpuTexture m_lightIcons[MAX_LIGHT_ICON];
};

}  // namespace vct