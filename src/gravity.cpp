#include <iostream>
#include <cmath>
#include <GLFW/glfw3.h>
#include <vector>

float screenHeight = 600.0f;
float screenWidth = 800.0f;
void DrawCircle(float centerX, float centerY, float radius, int res);

class Object{
    public:

    std::vector<float> position;
    std::vector<float> velocity;
    float radius;
    Object(std::vector<float> position, std::vector<float> velocity, float radius){
        this->position = position;
        this->velocity = velocity;
        this->radius = radius;
    }

    void accelerate(float x, float y){
        this->velocity[0] += x;
        this->velocity[1] += y;
    };
    void updatePos(){
        this->position[0] += velocity[0];
        this->position[1] += velocity[1];
    };
    void DrawCircle(){
        glColor3f(1.0f, 1.0f, 1.0f);

        glBegin(GL_TRIANGLE_FAN);

        glVertex2d(position[0], position[1]);

        for (int i = 0; i <= 100; ++i)
        {
            float angle = 2.0f * 3.1415f * (static_cast<float>(i) / 100);

            float x = position[0] + cos(angle) * radius;
            float y = position[1] + sin(angle) * radius;

            glVertex2d(x, y);
        }

        glEnd();
    }
};

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(
        screenWidth,
        screenHeight,
        "Gravity Simulation",
        NULL,
        NULL
    );

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    // Set up viewport
    glViewport(0, 0, screenWidth, screenHeight);

    // Set up 2D coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(
        0.0,
        screenWidth,
        0.0,
        screenHeight,
        -1.0,
        1.0
    );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Background colour
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    // Create objects
    std::vector<Object> objs = {
        Object(
            std::vector<float>{200.0f, 500.0f},
            std::vector<float>{0.0f, 0.0f},
            10.0f
        ),

        Object(
            std::vector<float>{700.0f, 500.0f},
            std::vector<float>{0.0f, 0.0f},
            10.0f
        )
    };


    // Main simulation loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);


        // Update every object
        for (auto& obj : objs)
        {
            // Gravity
            obj.accelerate(0.1f, -0.1f);

            // Update position
            obj.updatePos();


            // Bottom boundary
            if (obj.position[1] - obj.radius < 0)
            {
                obj.position[1] = obj.radius;
                obj.velocity[1] *= -0.95f;
            }

            // Top boundary
            if (obj.position[1] + obj.radius > screenHeight)
            {
                obj.position[1] = screenHeight - obj.radius;
                obj.velocity[1] *= -0.95f;
            }

            // Left boundary
            if (obj.position[0] - obj.radius < 0)
            {
                obj.position[0] = obj.radius;
                obj.velocity[0] *= -0.95f;
            }

            // Right boundary
            if (obj.position[0] + obj.radius > screenWidth)
            {
                obj.position[0] = screenWidth - obj.radius;
                obj.velocity[0] *= -0.95f;
            }


            // Draw object
            obj.DrawCircle();
        }


        // Display the new frame
        glfwSwapBuffers(window);

        // Process keyboard/window events
        glfwPollEvents();
    }


    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}