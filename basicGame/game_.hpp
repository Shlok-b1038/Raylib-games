#pragma once

#include <raylib.h>
#include <vector>
#include "player.hpp"
#include "bullet.hpp"
#include "enemy.hpp"

class Game {
public:
    Player player;
    int enemyCount;
    std::vector<Enemy> enemyList;
    std::vector<Gun> artillery;
    std::vector<std::tuple<float, float, Bullet>> shotBullets;
    int gunCount;
    int WIDTH;
    int HEIGHT;
    int w_WIDTH;
    int w_HEIGHT;
    bool gameOver;

    Gun& returnCurrentGun() {
        return this->artillery[this->gunCount];
    };
    void createGun(Gun newGun) {
        this->artillery.push_back(newGun);
        gunCount++;
        for (Gun gun: artillery) std::cout<<"new weapon added to artillery"<<std::endl;
    };

    void shootingBullets() {
        Gun& ak = this->returnCurrentGun();
        if (IsKeyPressed(KEY_SPACE) && ak.ammo != 0) {
            auto shotTuple = ak.fire(player.position, player.rotation, GetFrameTime());
            this->shotBullets.push_back(shotTuple);
        };
        if (ak.ammo == 0) this->gameOver = true;
    };

    void loadEnemyList() {
        for (int i = 0; i < this->enemyCount; i++) {
            float x = GetRandomValue(this->w_WIDTH, this->WIDTH);
            float y = GetRandomValue(this->w_HEIGHT, this->HEIGHT);
            Enemy enemy(Vector2{x,y}, 3.0f, 100.0f, 0.0f, BLUE);
            this->enemyList.push_back(enemy);
        };
    };

    void showBullets() {
        for (auto& bullet: this->shotBullets) {
            Bullet gunBullets = std::get<2>(bullet);
            DrawCircle(gunBullets.position.x, gunBullets.position.y, gunBullets.radius, gunBullets.color);
            if (gunBullets.position.x < this->WIDTH + 100 && gunBullets.position.x > -100 && gunBullets.position.y < this->HEIGHT + 100 && gunBullets.position.y > -100) {
                std::get<2>(bullet).position.x += std::get<0>(bullet);
                std::get<2>(bullet).position.y += std::get<1>(bullet);
            };
        };
    };

    void showEnemies() {
        for (Enemy& enemy : this->enemyList) {
            DrawCircle(enemy.position.x, enemy.position.y, enemy.radius, enemy.color);
            enemy.movement(this->player, GetFrameTime());
        };
    };

    void shootEnemies() {
        for (Enemy& enemy : this->enemyList) {
            DrawCircle(enemy.position.x, enemy.position.y, enemy.radius, enemy.color);
            enemy.movement(this->player, GetFrameTime());
            for (auto& data: this->shotBullets) {
                Bullet &bullet = std::get<2>(data);
                if (CheckCollisionCircles(bullet.position, bullet.radius, enemy.position, enemy.radius)) {
                    std::cout<<"found collision"<<std::endl;
                    float x = GetRandomValue(w_WIDTH, WIDTH);
                    float y = GetRandomValue(w_HEIGHT, HEIGHT);
                    enemy.position.x = x;
                    enemy.position.y = y;
                };
            };
        };
    };

    Game(Player player, int w_HEIGHT, int w_WIDTH,
         int WIDTH, int HEIGHT, int enemyCount)
        : player(player),
          enemyCount(enemyCount),
          WIDTH(WIDTH),
          HEIGHT(HEIGHT),
          w_WIDTH(w_WIDTH),
          w_HEIGHT(w_HEIGHT)
    {
        gunCount = -1;
        gameOver = false;
    }};
