#include <pebble.h>
#include "YBattery.h"

static void battery_handler(BatteryChargeState new_state){
  // Write to buffer and display
  static char s_battery_buffer[32];
  
  snprintf(s_battery_buffer, sizeof(s_battery_buffer), "%d/100", new_state.charge_percent);
  text_layer_set_text(s_battery_layer, s_battery_buffer);
}

void initializeYBattery(){
  // Create day TextLayer
  s_battery_layer = text_layer_create(GRect(84, 88, 80, 30));
  text_layer_set_background_color(s_battery_layer, GColorWhite);
  text_layer_set_text_color(s_battery_layer, GColorBlack);
  
  // Improve the day TextLayer layout
  text_layer_set_font(s_battery_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(s_battery_layer, GTextAlignmentLeft);
  
  // Get the current battery level
  battery_handler(battery_state_service_peek());
  
  // Subscribe to the Battery State Service
  battery_state_service_subscribe(battery_handler);
  
}
void destroyYBattery(){
  text_layer_destroy(s_battery_layer);
}

Layer* getYBattery(){
  return text_layer_get_layer(s_battery_layer);
}