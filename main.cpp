#include "include/raylib.h"
// #include <cstdlib>
#include <math.h>
#include <random>
// using namespace std;


class particle {
public:
    int radius{5};
    Vector2 center{0,0};
    Vector2 velocity{0,0};
    particle (float x=0, float y=0, float v=0);
    void update();
};

particle::particle(float x, float y, float v)
    :center{x,y}, velocity{v,v} {}


float randrange(int min, int max) {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(min, max); 
    return distr(gen); 
}


void particle::update() {
    center.x += velocity.x;
    center.y += velocity.y;
    //collisions
    if (center.x+radius >= GetScreenWidth() || center.x+radius <= 0) {velocity.x *= -1;}
    if (center.y+radius >= GetScreenHeight() || center.y+radius <= 0) {velocity.y *= -1;}
    DrawCircle(center.x, center.y, radius, MAROON);
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1250;
    const int screenHeight = 700;
    int population{180};
    std::vector <particle> group {};
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    for(int x {0};x<=population;++x) {
        // int temp_x = randrange(5, GetScreenWidth());
        // int temp_y = randrange(5, GetScreenHeight());
        // int temp_v = std::sin(randrange(45,120))*8;
        // group.push_back(particle(temp_x, temp_y, temp_v));
        particle temp {randrange(0,screenWidth),randrange(0,screenHeight),randrange(1,5)};
        group.push_back(temp);
    }
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            for (int i{0}; i < population; ++i) {
                for (int j{0}; j < population; ++j) {
                    int distance{};
                    int ix = group.at(i).center.x, iy = group.at(i).center.y, jx = group.at(j).center.x, jy = group.at(j).center.y; 
                    int dx = {ix-jx};
                    int dy = {iy-jy};
                    distance = std::sqrt((dx*dx)+(dy*dy));
                    if (distance <= 120) {DrawLine(ix,iy,jx,jy,MAROON);}
                    if (distance <= group.at(i).radius*2) {
                        group.at(i).velocity = {-(group.at(i).velocity.x), -(group.at(i).velocity.y)};
                        group.at(j).velocity = {-(group.at(j).velocity.x), -(group.at(j).velocity.y)};
                    }
                }
                (group.at(i)).update();
            }
            


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}