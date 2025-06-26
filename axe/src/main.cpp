// Auto Genrated C++ file by Flick CLI
// None
#include <axeconfig.h>
#include <raylib.h>

#include <cstdio>

constexpr int HEIGHT{600};
constexpr int WIdTH{600};
constexpr int MAX_FPS{120};


int main(int argc, char* argv[])
{
    SetTargetFPS(MAX_FPS);
    std::printf("%s v%s\n", Project::PROJECT_NAME.data(), Project::VERSION_STRING.data());
    InitWindow(WIdTH, HEIGHT, Project::PROJECT_NAME.data());
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        DrawCircle(WIdTH/2, HEIGHT/2, 25, BLUE);
        EndDrawing();
    }
    return 0;
}
