#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    public:
        Camera() {
            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
            UpdateDirectionToTarget(glm::vec3(0.0f, 0.0f, 0.0f)); // initialize to look at 0,0,0
            UpdateView();
        }

        Camera(float new_x, float new_y, float new_z) {
            x = new_x;
            y = new_y;
            z = new_z;
            UpdateDirectionToTarget(glm::vec3(0.0f, 0.0f, 0.0f)); // initialize to look at 0,0,0
            UpdateView();
        }

        void IncrementPos(float add_x, float add_y, float add_z) {
            UpdatePos(x + add_x, y + add_y, z + add_z);
        }

        void UpdatePos(float new_x, float new_y, float new_z) {
            x = new_x;
            y = new_y;
            z = new_z;
            std::cout << x << " " << y << " " << z << "\n";
            UpdateView();
        }

        void UpdateDirectionToTarget(glm::vec3 new_target) {
            cameraTarget = new_target;
            cameraDirection = glm::vec3(cameraPos - cameraTarget);
        }

        void UpdateDirection(glm::vec3 new_direction) {
            cameraDirection = new_direction;
        }

        void UpdateView() {
            //view = glm::vec3(x, y, z);
            UpdatePos();

            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            cameraRight = glm::normalize(glm::cross(up, cameraDirection));
            cameraUp = glm::cross(cameraDirection, cameraRight);

            view = glm::lookAt(cameraPos, cameraTarget, up);
        }

        glm::mat4 GetView() {
            return view;
        }

    private:
        float x, y, z;
        glm::mat4 view;

        glm::vec3 cameraRight;
        glm::vec3 cameraUp;
        glm::vec3 cameraDirection;
        glm::vec3 cameraTarget;

        glm::vec3 cameraPos;

        void UpdatePos() {
            cameraPos = glm::vec3(x, y, z);
        }

};

#endif