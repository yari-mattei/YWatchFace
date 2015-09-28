#pragma once

  
static TextLayer *s_battery_layer;

void initializeYBattery();
void destroyYBattery();

static void battery_handler(BatteryChargeState new_state);

Layer* getYBattery();
