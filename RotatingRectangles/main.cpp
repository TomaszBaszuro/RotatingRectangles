#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RotatingRectangles", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader Shader("vertexShader.txt", "fragmentShader.txt");

    float vertices[] = {     
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3, 
        1, 2, 3
    };

    glm::vec4 color = glm::vec4(0.3f, 0.8f, 0.1f, 1.0f);
    glm::mat4 transformations[4];

    unsigned int VBO, VAO, EBO, SSBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &SSBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(color) + sizeof(transformations), glm::value_ptr(color), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Shader.use();

        for (int i = 0; i < 4; i++)
        {
            transformations[i] = glm::mat4(1.0f);
        }
        
        transformations[0] = glm::translate(transformations[0], glm::vec3(-0.5, 0.5, 0.5));
        transformations[0] = glm::rotate(transformations[0], (float)glfwGetTime(), glm::vec3(0.3, 0.5, -1.0));
        transformations[0] = glm::scale(transformations[0], glm::vec3(0.65, 0.65, 0.65));
        
        transformations[1] = glm::translate(transformations[1], glm::vec3(0.5, 0.5, 0.5));
        transformations[1] = glm::rotate(transformations[1], (float)glfwGetTime(), glm::vec3(0.3, 0.6, -1.0));
        transformations[1] = glm::scale(transformations[1], glm::vec3(0.65, 0.65, 0.65));

        transformations[2] = glm::translate(transformations[2], glm::vec3(-0.5, -0.5, 0.5));
        transformations[2] = glm::rotate(transformations[2], (float)glfwGetTime(), glm::vec3(0.3, 0.7, -1.0));
        transformations[2] = glm::scale(transformations[2], glm::vec3(0.65, 0.65, 0.65));

        transformations[3] = glm::translate(transformations[3], glm::vec3(0.5, -0.5, 0.5));
        transformations[3] = glm::rotate(transformations[3], (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        transformations[3] = glm::scale(transformations[3], glm::vec3(0.45, 0.45, 0.45));

        glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(color), sizeof(transformations), &transformations);

        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &SSBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}