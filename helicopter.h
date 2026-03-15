#ifndef HELICOPTER_H
#define HELICOPTER_H

typedef struct {
    float x, y, z;
    float rotation_y;
    float rotor_angle;
    float base_speed;
} Helicopter;

void init_helicopter(Helicopter* heli);
void update_helicopter(Helicopter* heli, double delta_time);
void move_helicopter(Helicopter* heli, float speed, float direction);
void turn_helicopter(Helicopter* heli, float angle);
void elevate_helicopter(Helicopter* heli, float speed);
void draw_helicopter(Helicopter* heli);

#endif