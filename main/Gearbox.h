#pragma once
#include "BLDCMotor.h"

extern int target_x;
extern int target_y;
extern int gearbox_state;
extern int gearbox_virtual_position;


void set_gear(int target);
void gearbox_task(void* args);
int get_current_gear();
bool get_gearbox_ready();

