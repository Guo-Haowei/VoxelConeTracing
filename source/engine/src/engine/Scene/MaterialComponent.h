#pragma once
#include <string>
#include "Math/GeoMath.h"

class Archive;
struct Image;

struct MaterialComponent
{
    enum ETextureSlot
    {
        Base,
        Normal,
        MetallicRoughness,
        Count,
    };

    struct TextureMap
    {
        std::string name;
        const Image* image = nullptr;
        // mutable GPUTexture texture;
    };
    TextureMap mTextures[ETextureSlot::Count];

    float mMetallic = 0.0f;
    float mRoughness = 1.0f;
    vec4 mBaseColor = vec4(1);

    void Serialize(Archive& archive);

    // @TODO: refactor
    mutable void* gpuResource = nullptr;
};