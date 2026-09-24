#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>
#include <vector>

float screenHeight = 600.0f;
float screenWidth = 800.0f;
void DrawCircle(float centerX, float centerY, float radius, int res);

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(
        screenWidth,
        screenHeight,
        "Gravity Simulation",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Set the viewport to match the window
    glViewport(0, 0, screenWidth, screenHeight);

    // Set up a coordinate system using screen pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, screenWidth, 0.0, screenHeight, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the background colour to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Circle properties
    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;
    float radius = 50.0f;
    int res = 100;

    std::vector<float> position = {centerX, centerY};
    std::vector<float> velocity = {0.0f, 0.0f};

    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        DrawCircle(position[0], position[1], radius, res);
        position[0] += velocity[0];
        position[1] += velocity[1];
        velocity[1] += -9.81f/100.0f;

        if(position[1] < 0 || position[1] > screenHeight){
            velocity[1] *= -0.95;
        }
        if(position[0] < 0 || position[0] > screenWidth){
            velocity[0] *= -0.95;
        }


        // Display the completed frame
        glfwSwapBuffers(window);

        // Process keyboard/mouse/window events
        glfwPollEvents();
    }

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


void DrawCircle(float centerX, float centerY, float radius, int res){
        // Set circle colour to white
        glColor3f(1.0f, 1.0f, 1.0f);

        // Draw circle using a triangle fan
        glBegin(GL_TRIANGLE_FAN);

        // Centre of the circle
        glVertex2d(centerX, centerY);

        // Points around the circumference
        for (int i = 0; i <= res; ++i)
        {
            float angle =
                2.0f * 3.1415f * (static_cast<float>(i) / res);

            float x = centerX + cos(angle) * radius;
            float y = centerY + sin(angle) * radius;

            glVertex2d(x, y);
        }

        glEnd();
}