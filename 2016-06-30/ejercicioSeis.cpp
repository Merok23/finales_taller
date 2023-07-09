/**
6) Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje, en color azul, un 
óvalo que ocupe toda la pantalla.
*/
#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <csignal>
#include <chrono>
#include <thread>
#define WIDTH 1366
#define HEIGHT 768

bool handleEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                return true;
        }
    }
    return false;
}

int main (int argc, char** argv) {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window mainWindow("ovalo", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL2pp::Renderer renderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    bool closed = false;
    while(!closed) {
        closed = handleEvents();
        renderer.SetDrawColor(0xff, 0xff, 0xff);
        renderer.Clear();
        //renderer position_x, position_y, radius_x, radius_y, red, green, blue, alpha
        filledEllipseRGBA(renderer.Get(), WIDTH/2, HEIGHT/2, WIDTH/2, HEIGHT/2, 0, 0, 255, 255);
        renderer.Present();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
    }
    return 0;
}