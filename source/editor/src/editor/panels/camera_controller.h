#pragma once
#include "scene/scene_components.h"

namespace vct {

class CameraController {
public:
    void set_camera(CameraComponent& camera);
    void move_camera(CameraComponent& camera, float dt);

private:
    vec3 calculate_eye(const vec3& center);

    float m_angle_x = 0.0f;
    float m_angle_xz = 0.0f;
    float m_distance = 10.0f;

    vec3 m_direction;

    static constexpr float MAX_SCROLL_SPEED = 100.0f;
    float m_scrollSpeed = 0.0f;
};

}  // namespace vct

extern vct::CameraController s_controller;