#pragma once

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <tuple>
#include "bullet.hpp"

class Gun {
public:
    Vector2 position;   
    std::vector<Bullet> bullets;
    float radius;
    int ammo;

    std::tuple<float, float, Bullet> fire(Vector2 playerPosition, float rotation, float frameTime) {
        Bullet bullet = bullets[ammo- 1];
        bullet.position = playerPosition;
        bullets.erase(bullets.begin() + --ammo);
        // speedX = (bullet.speed*frameTime)*cos((PI/180)*rotation);
        // speedY = (bullet.speed*frameTime)*sin((PI/180)*rotation);
        std::cout<<"X: "<<bullet.position.x<<" Y: "<<bullet.position.y<<" ammo: "<<ammo<<std::endl;
        float speedX = (bullet.speed*frameTime)*cos((PI/180)*rotation);
        float speedY = (bullet.speed*frameTime)*sin((PI/180)*rotation);
        return {speedX, speedY, bullet};
    };

    Gun(Vector2 gunPosition, float gunRadius, int gunAmmo) : position(gunPosition), radius(gunRadius), ammo(gunAmmo) {
        for (int i = 0; i < ammo; i++) {
            Bullet bullet(position, 5.0f, RED, 300.0f, 50.0f);
            bullets.push_back(bullet);
        };
    };
};


class Player {
public:
    Vector2 position;
    float radius;
    float speed;
    float rotation;
    float health;
    Color color;

    void movement(float frameTime) {
        if (IsKeyDown(KEY_W)) {
            if (IsKeyDown(KEY_A)) {
                this->position.y -= speed*frameTime/sqrt(2);
                this->position.x -= speed*frameTime/sqrt(2);
                this->rotation = -135.0f;
            }
            else if (IsKeyDown(KEY_D)) {
                this->position.y -= speed*frameTime/sqrt(2);
                this->position.x += speed*frameTime/sqrt(2);
                this->rotation = -45.0f;
            }
            else {
                this->position.y -= speed*frameTime;
                this->rotation = -90.0f;
            };
        }
        else if (IsKeyDown(KEY_S)) {
            if (IsKeyDown(KEY_A)) {
                this->position.y += speed*frameTime/sqrt(2);
                this->position.x -= speed*frameTime/sqrt(2);
                this->rotation = 135.0f;
            }
            else if (IsKeyDown(KEY_D)) {
                this->position.y += speed*frameTime/sqrt(2);
                this->position.x += speed*frameTime/sqrt(2);
                this->rotation = 45.0f;
            }
            else {
                this->position.y += speed*frameTime;
                this->rotation = 90.0f;
            };
        }
        else if (IsKeyDown(KEY_D)) {
            this->position.x += speed*frameTime;
            this->rotation = 0.0f;
        }
        else if (IsKeyDown(KEY_A)) {
            this->position.x -= speed*frameTime;
            this->rotation = 180.0f;
        };
    };
    Player(Vector2 playerPosition, float playerSpeed,
       float playerRotation, float playerRadius,
       Color playerColor, float playerHealth)
    : position(playerPosition),
      radius(playerRadius),
      speed(playerSpeed),
      rotation(playerRotation),
      health(playerHealth),
      color(playerColor)
{}};

