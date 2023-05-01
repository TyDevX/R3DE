#include <GLFW/glfw3.h>
#include <iostream>
#include "camera.h"

void draw_cube() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    static float angle = 0.0f;
    glRotatef(angle, 1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (float i = -1.0f; i <= 1.0f; i += 2.0f) {
        for (float j = -1.0f; j <= 1.0f; j += 2.0f) {
            glVertex3f(i, j, -1.0f);
            glVertex3f(i, j, 1.0f);

            glVertex3f(i, -1.0f, j);
            glVertex3f(i, 1.0f, j);

            glVertex3f(-1.0f, i, j);
            glVertex3f(1.0f, i, j);
        }
    }
    glEnd();

    angle += 1.0f;
}

class Camera {
public:
    Camera(float fov, float aspect, float zNear, float zFar, glm::vec3 pos, glm::vec3 up) {
        m_fov = fov;
        m_aspect = aspect;
        m_zNear = zNear;
        m_zFar = zFar;
        m_pos = pos;
        m_up = up;
        m_pitch = 0.0f;
        m_yaw = 0.0f;
        m_sensitivity = 0.1f;

        recalculateViewMatrix();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(m_pos, m_pos + m_front, m_up);
    }

    glm::mat4 getProjectionMatrix() {
        return glm::perspective(glm::radians(m_fov), m_aspect, m_zNear, m_zFar);
    }

    void processKeyboardInput(GLFWwindow* window, float deltaTime) {
        float speed = 5.0f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            m_pos += m_front * speed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            m_pos -= m_front * speed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            m_pos -= glm::normalize(glm::cross(m_front, m_up)) * speed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            m_pos += glm::normalize(glm::cross(m_front, m_up)) * speed;
    }

    void processMouseMovement(float xoffset, float yoffset) {
        xoffset *= m_sensitivity;
        yoffset *= m_sensitivity;

        m_yaw += xoffset;
        m_pitch += yoffset;

        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);
    }

private:
    float m_fov;
    float m_aspect;
    float m_zNear;
    float m_zFar;
    glm::vec3 m_pos;
    glm::vec3 m_front;
    glm::vec3 m_up;
    float m_pitch;
    float m_yaw;
    float m_sensitivity;

    void recalculateViewMatrix() {
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);
    }
};

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Render 3D Engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        draw_cube();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
