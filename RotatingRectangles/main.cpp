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

    Shader Shader1("vertexShader.txt", "fragmentShader.txt");
    Shader Shader2("vertexShader.txt", "fragmentShader.txt");
    Shader Shader3("vertexShader.txt", "fragmentShader.txt");
    Shader Shader4("vertexShader.txt", "fragmentShader.txt");

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
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //rectangle #1
        Shader1.use();

        int vertexColorLocation1 = glGetUniformLocation(Shader1.ID, "ourColor");
        glUniform4f(vertexColorLocation1, 0.0f, 1.0, 0.0f, 1.0f);

        glm::mat4 trans1 = glm::mat4(1.0f);
        trans1 = glm::translate(trans1, glm::vec3(0.5, -0.5, 0.0));
        trans1 = glm::rotate(trans1, (float)glfwGetTime(), glm::vec3(0.0, 0.5, -1.0));
        trans1 = glm::scale(trans1, glm::vec3(0.65, 0.65, 0.65));

        unsigned int transformLoc1 = glGetUniformLocation(Shader1.ID, "transform");
        glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(trans1));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //rectangle #2
        Shader2.use();

        int vertexColorLocation2 = glGetUniformLocation(Shader2.ID, "ourColor");
        glUniform4f(vertexColorLocation2, 1.0f, 0.0, 0.0f, 1.0f);

        glm::mat4 trans2 = glm::mat4(1.0f);
        trans2 = glm::translate(trans2, glm::vec3(-0.5, 0.5, 0.0));
        trans2 = glm::rotate(trans2, (float)glfwGetTime(), glm::vec3(0.0, -0.5, -1.0));
        trans2 = glm::scale(trans2, glm::vec3(0.65, 0.65, 0.65));

        unsigned int transformLoc2 = glGetUniformLocation(Shader2.ID, "transform");
        glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(trans2));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //rectangle #3
        Shader3.use();

        int vertexColorLocation3 = glGetUniformLocation(Shader3.ID, "ourColor");
        glUniform4f(vertexColorLocation3, 0.0f, 0.0, 1.0f, 1.0f);

        glm::mat4 trans3 = glm::mat4(1.0f);
        trans3 = glm::translate(trans3, glm::vec3(-0.5, -0.5, 0.0));
        trans3 = glm::rotate(trans3, (float)glfwGetTime(), glm::vec3(-0.5, 0.0, -1.0));
        trans3 = glm::scale(trans3, glm::vec3(0.65, 0.65, 0.65));

        unsigned int transformLoc3 = glGetUniformLocation(Shader3.ID, "transform");
        glUniformMatrix4fv(transformLoc3, 1, GL_FALSE, glm::value_ptr(trans3));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //rectangle #4
        Shader4.use();

        int vertexColorLocation4 = glGetUniformLocation(Shader4.ID, "ourColor");
        glUniform4f(vertexColorLocation2, 1.0f, 1.0, 0.0f, 1.0f);

        glm::mat4 trans4 = glm::mat4(1.0f);
        trans4 = glm::translate(trans4, glm::vec3(0.5, 0.5, 0.0));
        trans4 = glm::rotate(trans4, (float)glfwGetTime(), glm::vec3(0.5, 0.0, -1.0));
        trans4 = glm::scale(trans4, glm::vec3(0.65, 0.65, 0.65));

        unsigned int transformLoc4 = glGetUniformLocation(Shader4.ID, "transform");
        glUniformMatrix4fv(transformLoc4, 1, GL_FALSE, glm::value_ptr(trans4));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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