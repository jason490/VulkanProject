#include "engine.h"
#include "instance.h"
#include <iostream>

const char* projectName = "AvantGarde";

Engine::Engine() {

    if (debugMode) {
        std::cout << "Making a graphics engine...\n";
    }

    build_glfw_window();

    make_instance();
}

void Engine::build_glfw_window() {
    // init glfw
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // window resizing, breaks swapchain, disabled for now
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if ((window = glfwCreateWindow(width, height, projectName, nullptr, nullptr))) {
        if (debugMode) {
            std::cout << "Success: glfw window creation, width: " << width << ", height: " << height << '\n';
        }
    } else {
        if (debugMode) {
            std::cout << "Failed:  glfw window creation\n";
        }
    }
}

void Engine::make_instance() {
    instance = vkInit::make_instance(debugMode, projectName);
}

Engine::~Engine() {
    if (debugMode) {
        std::cout << "Closing Engine...\n";
    }

    instance.destroy();

    glfwTerminate();
}