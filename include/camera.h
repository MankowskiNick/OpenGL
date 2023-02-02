#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    public:
        Camera() {
            Camera(0.0f, 0.0f, 0.0f);
        }

        Camera(float new_x, float new_y, float new_z) {
            x = new_x;
            y = new_y;
            z = new_z;
            horiz_angle = 0.0f;
            vert_angle = 0.0f;
            UpdateDirection(glm::vec3(-0.33f, -0.33f, -1.0f));
            UpdateView();
        }

        void IncrementPos(glm::vec3 direction) {
            UpdatePos(x + direction.x, y + direction.y, z + direction.z);
        }

        void UpdatePos(float new_x, float new_y, float new_z) {
            x = new_x;
            y = new_y;
            z = new_z;
            UpdateView();
        }

        void UpdateLookDirection(float horiz_rads, float vert_rads) {

            horiz_angle += sensitivity * horiz_rads;
            vert_angle += sensitivity * vert_rads;

            glm::vec3 direction(cos(horiz_angle), cos(vert_angle), sin(horiz_angle));
            UpdateDirection(direction);
        }

        void Walk(unsigned int key) {
            glm::vec3 direction;
            switch(key) {
                case GLFW_KEY_W:
                    direction = glm::vec3(speed * cos(horiz_angle), 0.0f, speed * sin(horiz_angle));
                    break;
                case GLFW_KEY_S:
                    direction = glm::vec3(-1.0f * speed * cos(horiz_angle), 0.0f, -1.0f * speed * sin(horiz_angle));
                    break;
                case GLFW_KEY_D:
                    direction = glm::vec3(-1.0f * speed * sin(horiz_angle), 0.0f, speed * cos(horiz_angle));
                    break;
                case GLFW_KEY_A:
                    direction = glm::vec3(speed * sin(horiz_angle), 0.0f, -1.0f * speed * cos(horiz_angle));
                    break;
                default:
                    direction = glm::vec3(0.0f, 0.0f, 0.0f);
                    break;
            }
            IncrementPos(direction);
        }

        glm::mat4 GetView() {
            return view;
        }

    private:

        float horiz_angle, vert_angle;
        float speed = 0.05;
        float sensitivity = 0.01f;

        float x, y, z;
        glm::vec3 cameraPos;
        glm::vec3 cameraRight;
        glm::vec3 cameraUp;
        glm::vec3 cameraFront;
        glm::vec3 cameraDirection;
        glm::vec3 cameraTarget;

        glm::mat4 view;

        void UpdatePos() {
            cameraPos = glm::vec3(x, y, z);
        }
        
        void UpdateDirection(glm::vec3 new_direction) {
            cameraDirection = new_direction;
            UpdateView();
        }

        void UpdateView() {

            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            cameraRight = glm::normalize(glm::cross(up, cameraDirection));
            cameraUp = glm::cross(cameraDirection, cameraRight);

            cameraPos = glm::vec3(x, y, z);

            UpdatePos();
            view = glm::lookAt(cameraPos, cameraPos + cameraDirection, up);
        }

};

#endif