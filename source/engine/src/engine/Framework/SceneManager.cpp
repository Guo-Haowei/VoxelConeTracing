#include "SceneManager.h"

#include "Scene/AssimpSceneLoader.h"
#include "core/camera.h"
#include "imgui/imgui.h"
#include "servers/rendering/r_cbuffers.h"
///
#include "core/dynamic_variable/common_dvars.h"
#include "servers/display_server.h"

using namespace vct;

static Scene g_scene;

static std::atomic<Scene*> s_scene_ptr;

SceneManager* gSceneManager = new SceneManager;

static bool load_scene(std::string_view scene_path) {
    // validate dvars
    const int voxelTextureSize = DVAR_GET_INT(r_voxelSize);
    DEV_ASSERT(is_power_of_two(voxelTextureSize));
    DEV_ASSERT(voxelTextureSize <= 256);

    Scene& scene = g_scene;
    SceneLoader loader(scene);

    loader.LoadGLTF(scene_path);

    Camera& camera = gCamera;

    const vec4 cascades = DVAR_GET_VEC4(cam_cascades);

    camera.fovy = glm::radians(DVAR_GET_FLOAT(cam_fov));
    camera.zNear = cascades[0];
    camera.zFar = cascades[3];

    camera.yaw = glm::radians(180.0f);
    camera.pitch = 0.0f;
    camera.position = DVAR_GET_VEC3(cam_pos);

    scene.light.color = vec3(glm::clamp(DVAR_GET_FLOAT(light_power), 5.0f, 30.0f));

    const vec3 center = scene.bound.center();
    const vec3 size = scene.bound.size();
    const float worldSize = glm::max(size.x, glm::max(size.y, size.z));
    const float texelSize = 1.0f / static_cast<float>(voxelTextureSize);
    const float voxelSize = worldSize * texelSize;

    g_perFrameCache.cache.WorldCenter = center;
    g_perFrameCache.cache.WorldSizeHalf = 0.5f * worldSize;
    g_perFrameCache.cache.TexelSize = texelSize;
    g_perFrameCache.cache.VoxelSize = voxelSize;

    LOG("Scene '{}' loaded", scene_path);
    return true;
}

Scene& Com_GetScene() { return g_scene; }

// @TODO: fix
static mat4 R_HackLightSpaceMatrix(const vec3& lightDir) {
    const Scene& scene = Com_GetScene();
    const vec3 center = scene.bound.center();
    const vec3 extents = scene.bound.size();
    const float size = 0.5f * glm::max(extents.x, glm::max(extents.y, extents.z));
    const mat4 V = glm::lookAt(center + glm::normalize(lightDir) * size, center, vec3(0, 1, 0));
    const mat4 P = glm::ortho(-size, size, -size, size, 0.0f, 2.0f * size);
    return P * V;
}

static void R_LightSpaceMatrix(const Camera& camera, const vec3& lightDir, mat4 lightPVs[NUM_CASCADES]) {
    unused(camera);
    lightPVs[0] = lightPVs[1] = lightPVs[2] = R_HackLightSpaceMatrix(lightDir);
    return;
}

static void Com_UpdateWorld() {
    Scene& scene = Com_GetScene();

    // update camera
    auto [frameW, frameH] = DisplayServer::singleton().get_frame_size();
    const float aspect = (float)frameW / frameH;
    DEV_ASSERT(aspect > 0.0f);

    Camera& camera = gCamera;
    camera.SetAspect(aspect);
    camera.UpdatePV();

    // update lightspace matrices
    mat4 lightPVs[NUM_CASCADES];
    R_LightSpaceMatrix(camera, scene.light.direction, lightPVs);

    for (size_t idx = 0; idx < vct::array_length(lightPVs); ++idx) {
        g_perFrameCache.cache.LightPVs[idx] = lightPVs[idx];
    }

    // update constants
    g_perFrameCache.cache.SunDir = scene.light.direction;
    g_perFrameCache.cache.LightColor = scene.light.color;
    g_perFrameCache.cache.CamPos = camera.position;
    g_perFrameCache.cache.View = camera.View();
    g_perFrameCache.cache.Proj = camera.Proj();
    g_perFrameCache.cache.PV = camera.ProjView();
    g_perFrameCache.cache.CascadedClipZ = DVAR_GET_VEC4(cam_cascades);
    g_perFrameCache.cache.EnableGI = DVAR_GET_BOOL(r_enableVXGI);
    g_perFrameCache.cache.DebugCSM = DVAR_GET_BOOL(r_debugCSM);
    g_perFrameCache.cache.DebugTexture = DVAR_GET_INT(r_debugTexture);
    g_perFrameCache.cache.NoTexture = DVAR_GET_BOOL(r_noTexture);
    g_perFrameCache.cache.ScreenWidth = frameW;
    g_perFrameCache.cache.ScreenHeight = frameH;

    // SSAO
    g_perFrameCache.cache.SSAOKernelSize = DVAR_GET_INT(r_ssaoKernelSize);
    g_perFrameCache.cache.SSAOKernelRadius = DVAR_GET_FLOAT(r_ssaoKernelRadius);
    g_perFrameCache.cache.SSAONoiseSize = DVAR_GET_INT(r_ssaoNoiseSize);
    g_perFrameCache.cache.EnableSSAO = DVAR_GET_BOOL(r_enableSsao);

    // FXAA
    g_perFrameCache.cache.EnableFXAA = DVAR_GET_BOOL(r_enableFXAA);
}

bool SceneManager::InitializeInternal() {
    std::string_view scene_path = DVAR_GET_STRING(scene);

    if (scene_path.empty()) {
        LOG_WARN("Scene not specified, set it with --path <file>");
        return true;
    }

    return load_scene(scene_path);
}

void SceneManager::FinalizeInternal() {}

void SceneManager::Update(float dt) {
    Com_UpdateWorld();
    Com_GetScene().Update(dt);
}
