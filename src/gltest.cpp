#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "loadShader.hpp"
using namespace glm;

static const GLfloat g_vertex_buffer_data[] = {
  -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

int main()
{
  //Initialize GLFW
  glewExperimental = true;
  if(!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4); //4x Antialaising
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //macOS optimization
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // new OpenGL

  //Open a window and create its OpenGL content
  GLFWwindow* window; //pointer to our main window
  window = glfwCreateWindow(1024, 768, "GLTest", nullptr, nullptr);
  if (window == nullptr)
  {
    std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not "
         << "3.3 compatible. Try OpenGL 2.1 instead.\n";
    return -1;
  }
  glfwMakeContextCurrent(window); //Initialize GLEW
  glewExperimental = true;
  if (glewInit() != GLEW_OK)
  {
    std::cerr << "Failed to initialize GLEW\n";
    return -1;
  }
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  // Set up triangle
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

  // Create and compile GLSL shaders
  GLuint programID = gltest::LoadShaders("src/vertexShader.glsl", "src/fragmentShader.glsl");
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Capture Esc
  do {
    //clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //set attributes
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
      0,        // attribute 0
      3,        // size
      GL_FLOAT, // type
      GL_FALSE, // normalized
      0,        //stride
      (void*)0  // array buffer offset
    );

    // Use shader
    glUseProgram(programID);

    //draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total
    glDisableVertexAttribArray(0);

    // swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
       && glfwWindowShouldClose(window) == 0); //check for window close or esc

  return 0;
}
