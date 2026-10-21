#pragma once
#include <raylib.h>
#include <iostream>
#include "player.hpp"

class Enemy {
public:
    Vector2 position;
    float radius;
    float speed;
    float rotation;
    Color color;

    void movement(Player& player, float frameTime) {
        if (this->position.x < player.position.x - 10) this->position.x += this->speed*frameTime;
        if (this->position.x > player.position.x - 10) this->position.x -= this->speed*frameTime;
        if (this->position.y < player.position.y - 10) this->position.y += this->speed*frameTime;
        if (this->position.y > player.position.y - 10) this->position.y -= this->speed*frameTime;
        if (CheckCollisionCircles(this->position, this->radius, player.position, player.radius)) std::cout<<"caught"<<std::endl;
    };

    Enemy(Vector2 enemyPosition, float enemyRadius, float enemySpeed, float enemyRotation, Color enemyColor): position(enemyPosition), radius(enemyRadius), speed(enemySpeed), rotation(enemyRotation), color(enemyColor) {};
};

