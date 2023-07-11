#include <iostream>
#include <exception>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <csignal>
#include <chrono>
#include <thread>
#define WIDTH 1920
#define HEIGHT 1080

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

int main(int argc, char** argv) {
    SDL2pp::SDL sdl(SLD_INIT_VIDEO);
    SDL2pp::window mainWindow("Rombo Amarillo", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL2pp::renderer renderer(&mainWindow, -1, SDL_RENDERER_ACCELERATED);
    bool closed = false;
    while(!closed) {
        renderer.setDrawColor(0, 0, 0); //fondo blanco
        renderer.Clear();
        int x_points[] = {480, 960, 960 + 480, 960}; //vertices del rombo en la posicion x
        int y_points[] = {540, 540 + 270, 540, 270} //Acordarse que "y" tiene los ejes invertidos
        filledPolygonRGBA(renderer.Get(), x_points, y_points, 4, 255, 255, 0, 255) //rombo amarillo
        renderer.Present();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/30)); //30fps
        closed = handleEvents();
    }
    return 0;
}