#include "stdafx.h"
#include "Camera.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL/SDL.h>

#include "Options.h"
#include "utils.h"

Camera::Camera() {
    // Empty
}

void Camera::init(float aspectRatio) {
    m_aspectRatio = aspectRatio;
}

void Camera::offsetPosition(glm::dvec3 offset) {
    m_position += offset;
    m_viewChanged = 1;
}

void Camera::offsetPosition(glm::vec3 offset) {
    m_position += offset;
    m_viewChanged = 1;

}

void Camera::update() {
    if (m_fieldOfView != graphicsOptions.fov){
        setFieldOfView(graphicsOptions.fov);
    }

    bool updateFrustum = false;
    if (m_viewChanged){
        updateView();
        m_viewChanged = false;
        updateFrustum = true;
    }
    if (m_projectionChanged){
        updateProjection();
        m_projectionChanged = false;
        updateFrustum = true;
    }
    if (updateFrustum) {
        m_frustum.update(m_projectionMatrix, m_viewMatrix);
    }
}

void Camera::updateView() {
    m_viewMatrix = glm::lookAt(glm::vec3(0.0f), m_direction, m_up);
}

void Camera::updateProjection() {
    m_projectionMatrix = glm::perspective(m_fieldOfView, m_aspectRatio, m_zNear, m_zFar);
}

void Camera::applyRotation(const f32q& rot) {
    m_direction = rot * m_direction;
    m_right = rot * m_right;
    m_up = glm::normalize(glm::cross(m_right, m_direction));
    m_viewChanged = true;
}

void Camera::rotateFromMouse(float dx, float dy, float speed) {
    f32q upQuat = glm::angleAxis(dy * speed, m_right);
    f32q rightQuat = glm::angleAxis(dx * speed, m_up);
 
    applyRotation(upQuat * rightQuat);
}

void Camera::yawFromMouse(float dx, float speed) {
    f32q frontQuat = glm::angleAxis(dx * speed, m_direction);

    applyRotation(frontQuat);
}

void CinematicCamera::update()
{
    m_viewChanged = true;
    /// Smooth movement towards target

    if (ABS(m_focalLength - m_targetFocalLength) < 0.1) {
        m_focalLength = m_targetFocalLength;
    } else {
        m_focalLength = lerp(m_focalLength, m_targetFocalLength, m_speed);
    }
    m_focalPoint = lerp(m_focalPoint, m_targetFocalPoint, m_speed);
    m_direction = glm::mix(m_direction, m_targetDirection, m_speed);
    m_right = glm::mix(m_right, m_targetRight, m_speed);
    m_up = glm::normalize(glm::cross(m_right, m_direction));

    m_position = m_focalPoint - f64v3(m_direction) * m_focalLength;

    // Call base class update
    Camera::update();
}


void CinematicCamera::applyRotation(const f32q& rot) {
    m_targetDirection = rot * m_targetDirection;
    m_targetRight = rot * m_targetRight;
   
    m_viewChanged = true;
}

void CinematicCamera::rotateFromMouse(float dx, float dy, float speed) {
    f32q upQuat = glm::angleAxis(dy * speed, m_targetRight);
    f32v3 targetUp = glm::normalize(glm::cross(m_targetRight, m_targetDirection));
    f32q rightQuat = glm::angleAxis(dx * speed, targetUp);

    applyRotation(upQuat * rightQuat);
}

void CinematicCamera::yawFromMouse(float dx, float speed) {
    f32q frontQuat = glm::angleAxis(dx * speed, m_targetDirection);

    applyRotation(frontQuat);
}

void CinematicCamera::offsetTargetFocalLength(float offset) {
    m_targetFocalLength += offset;
    if (m_targetFocalLength < 0.0) {
        m_targetFocalLength = 0.0;
    } else if (m_targetFocalLength > m_maxFocalLength) {
        m_targetFocalLength = m_maxFocalLength;
    }
}

void CinematicCamera::setTarget(const f64v3& targetFocalPoint, const f32v3& targetDirection,
                                const f32v3& targetRight, double targetFocalLength) {
    m_targetFocalPoint = targetFocalPoint;
    m_targetDirection = targetDirection;
    m_targetRight = targetRight;
    m_targetFocalLength = targetFocalLength;
}