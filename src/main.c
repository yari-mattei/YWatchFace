#include <pebble.h>
  
#include "YLines.h"
#include "YDate.h"
#include "YBattery.h"
  
//screen resolution 144*168
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_name_layer;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  // update YDate
  updateYDate(tick_time);

  // Create a long-lived buffer
  static char bufferTime[] = "00:00";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(bufferTime, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(bufferTime, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, bufferTime);
}

static void main_window_load(Window *window) {
  // Create name TextLayer
  s_name_layer = text_layer_create(GRect(0, 34, 144, 30));
  text_layer_set_background_color(s_name_layer, GColorClear);
  text_layer_set_text_color(s_name_layer, GColorBlack);
  text_layer_set_text(s_name_layer, "YaroX");
  
  // Improve the name TextLayer layout to be more like a watchface
  text_layer_set_font(s_name_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_name_layer, GTextAlignmentCenter);
  
  // Create time TextLayer
  s_time_layer = text_layer_create(GRect(0, 0, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorWhite);
  text_layer_set_text_color(s_time_layer, GColorBlack);

  // Improve the time TextLayer layout to be more like a watchface
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  
  // Create Y lines
  initializeYLines();
  
  // Create Y Date
  initializeYDate();
  
  // create Y battery
  initializeYBattery();

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_name_layer));
  layer_add_child(window_get_root_layer(window), getYDate());
  layer_add_child(window_get_root_layer(window), getYLines());
  layer_add_child(window_get_root_layer(window), getYBattery());
}

static void main_window_unload(Window *window) {
    // Destroy Layers
    text_layer_destroy(s_time_layer);
    text_layer_destroy(s_name_layer);
    destroyYLines();
    destroyYDate();
    destroyYBattery();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}


static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  // set window background color
  window_set_background_color(s_main_window, GColorClear);
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

}


static void deinit() {
    // Destroy Window
    window_destroy(s_main_window);
}


int main(void) {
  init();
  app_event_loop();
  deinit();
}
