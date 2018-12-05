#ifndef _LASER_H
#define _LASER_H

#include <Arduino.h>

bool check_autoplay();
 
void pin_init();
void toggleLaser();
void speedUp();
void speedDown();
void autoplay();
void autoplay_randomPos();
void extend_area();
void shrink_area();
void manual_up();
void manual_down();
void manual_left();
void manual_right();
bool checkCommand(String cmd);

#endif
