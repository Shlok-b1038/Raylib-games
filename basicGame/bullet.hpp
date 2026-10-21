#pragma once
#include <raylib.h>

class Bullet {
public:
    Vector2 position;
    float radius;
    float damage;
    float speed;
    Color color;

Bullet(Vector2 bulletPosition, float bulletRadius,
       Color bulletColor, float bulletSpeed, float bulletDamage)
    : position(bulletPosition),
      radius(bulletRadius),
      damage(bulletDamage),
      speed(bulletSpeed),
      color(bulletColor)
{}
};
