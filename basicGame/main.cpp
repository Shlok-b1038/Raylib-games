#include <raylib.h>
#include <vector>
#include <string>
#include "game_.hpp"
#include "player.hpp"
#include "enemy.hpp"

#define WIDTH 1200
#define HEIGHT 1000
#define WIDGETWIDTH 400

int main() {
    InitWindow(WIDTH, HEIGHT, "Window");
    SetTargetFPS(100);
    bool gameOver = false;
    int score = 0;

    Gun ak(Vector2{WIDTH/2, HEIGHT/2}, 3.0f, 25);
    Player player(Vector2{WIDTH/2, HEIGHT/2}, 200.0f, 0.0f, 11.0f, BROWN, 200.0f);
    Game game(player, HEIGHT, WIDGETWIDTH, WIDTH, HEIGHT, 5);

    game.loadEnemyList();
    game.createGun(ak);

    while (!WindowShouldClose() && !gameOver) {
        game.player.movement(GetFrameTime());
        BeginDrawing();
            ClearBackground(BLACK);
            game.shootingBullets();
            DrawRectangle(0, 0, 400, HEIGHT, GRAY);
            DrawText("Score: ", WIDGETWIDTH/2 - 80.0f, 200.0f, 40.0f, GREEN);
            DrawText(std::to_string(score).c_str(), WIDGETWIDTH/2 - 80.0f, 300.0f,40.0f, GREEN);
            DrawText("Health: ", WIDGETWIDTH/2 - 80.0f, 400.0f, 40.0f, BROWN);
            DrawText(std::to_string(game.player.health).c_str(), WIDGETWIDTH/2 - 80.0f, 500.0f,40.0f, BROWN);
            DrawText("Ammo: ", WIDGETWIDTH/2 - 80.0f, 600.0f, 40.0f, BROWN);
            DrawText(std::to_string(game.returnCurrentGun().ammo).c_str(), WIDGETWIDTH/2 - 80.0f, 700.0f,40.0f, BROWN);
            DrawPoly(game.player.position, 3, game.player.radius, game.player.rotation, game.player.color);
            game.shootEnemies();
            game.showBullets();
            if (player.health <= 0.0f) gameOver = true;
        EndDrawing();
    };

    CloseWindow();

    return 0;
};
