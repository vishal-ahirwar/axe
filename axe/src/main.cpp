// Auto Genrated C++ file by Flick CLI
// None
#include <axeconfig.h>
#include <raylib.h>

#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>

int HEIGHT{800};
int WIdTH{1024};

constexpr int MAX_FPS{120};
constexpr int SPEED{10};
constexpr int GAMEOVER_TEXT_PADDING{210};

template <class result_t = std::chrono::milliseconds, class clock_t = std::chrono::steady_clock,
          class duration_t = std::chrono::milliseconds>
auto since(std::chrono::time_point<clock_t, duration_t> const& start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

void generateNewCoordinatesForRect(int& x, int& y);

int main(int argc, char* argv[])
{
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    
    // delay
    int delay{500 * 2};
    
    srand(time(NULL));
    std::printf("%s v%s\n", Project::PROJECT_NAME.data(), Project::VERSION_STRING.data());
    
    InitWindow(WIdTH, HEIGHT, Project::PROJECT_NAME.data());
    SetTargetFPS(MAX_FPS);

    auto monitor=GetCurrentMonitor();
    WIdTH  = GetMonitorWidth(monitor);
    HEIGHT = GetMonitorHeight(monitor);
    // Circle coordinates
    int circleX{WIdTH / 2};
    int circleY{HEIGHT / 2};

    // Circle properties
    int circleRadius{25};

    // Rectangle coordinates
    int rectX{rand() % WIdTH + 1};
    int rectY{rand() % HEIGHT + 1};

    // Rectangle properties
    int rectWidth{20};
    int rectHeight{20};

    // timer
    auto start = std::chrono::steady_clock::now();

    // player state
    bool bSuccess{false};

    // game state
    bool bPlayerAlive{true};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (bPlayerAlive)
        {
            // Circle Edges
            int circleLeftEdge{circleX - circleRadius};
            int circleRightEdge{circleX + circleRadius};
            int circleTopEdge{circleY - circleRadius};
            int circleBottomEdge{circleY + circleRadius};

            // Rectangle Edges
            int RectLeftEdge{rectX};
            int RectRightEdge{rectX + rectWidth};
            int RectTopEdge{rectY};
            int RectBottomEdge{rectY + rectHeight};

            ClearBackground(WHITE);

            int timeLeft = since(start).count();

            if ((RectBottomEdge >= circleTopEdge) && (RectTopEdge <= circleBottomEdge) &&
                (RectLeftEdge <= circleRightEdge) && (RectRightEdge >= circleLeftEdge))
            {
                bSuccess = true;
                DrawText("Boom!!", circleX, circleY, 90, BLACK);
                generateNewCoordinatesForRect(rectX, rectY);
            }
            else
            {
                DrawText(("Time left " + std::to_string(delay - (timeLeft))).c_str(), 25, 25, 23,
                         GRAY);
                DrawCircle(circleX, circleY, circleRadius, BLUE);
                DrawRectangle(rectX, rectY, rectWidth, rectHeight, RED);
                if (timeLeft > delay)
                {
                    start = std::chrono::steady_clock::now();
                    generateNewCoordinatesForRect(rectX, rectY);
                    if (!bSuccess)
                    {
                        circleRadius -= 2;
                        if (circleRadius <= 0)
                        {
                            bPlayerAlive = false;
                        }
                    }
                    else
                    {
                        circleRadius += 5;
                        delay -= 50;
                    }
                    bSuccess = false;
                }
                if (IsKeyDown(KEY_D) && circleX < WIdTH)
                {
                    circleX += SPEED;
                }
                else if (IsKeyDown(KEY_A) && circleX > 0)
                {
                    circleX -= SPEED;
                }
                else if (IsKeyDown(KEY_W) && circleY > 0)
                {
                    circleY -= SPEED;
                }
                else if (IsKeyDown(KEY_S) && circleY < HEIGHT)
                {
                    circleY += SPEED;
                }
            }
        }
        else
        {
            DrawText("You have been erased from existence", (WIdTH / 2) - GAMEOVER_TEXT_PADDING,
                     HEIGHT / 2, 25, RED);
        }
        EndDrawing();
    }
    return 0;
}

void generateNewCoordinatesForRect(int& x, int& y)
{
    x = rand() % WIdTH + 1;
    y = rand() % HEIGHT + 1;
}
