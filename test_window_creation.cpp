#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

int main() {
    std::cout << "Build succeeded, entering main" << std::endl;

    std::cout << "Initializing SDL" << std::endl;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::cout << "Creating window" << std::endl;
    SDL_Window* window = SDL_CreateWindow("OpenGL Test", 100, 100, 105, 25, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::cout << "Creating OpenGL context" << std::endl;
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Test OpenGL
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
