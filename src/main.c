#include <pebble.h>
  
//screen resolution 144*168
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_name_layer;
static Layer *s_line;

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char bufferTime[] = "00:00";
  static char bufferDate[] = "dd/mm/yyyy";

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(bufferTime, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(bufferTime, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  // Write the current date into the buffer
  strftime(bufferDate, sizeof("dd/mm/yyyy"), "%d/%m/%Y", tick_time);
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, bufferTime);
  // Display this date on the TextLayer
  text_layer_set_text(s_date_layer, bufferDate);
}

static void drawline_callback(Layer *layer, GContext *ctx) {
  GPoint p0 = GPoint(0, 35);
  GPoint p1 = GPoint(72, 85);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 4);
  graphics_draw_line(ctx, p0, p1);
}


static void main_window_load(Window *window) {
  // Create date TextLayer
  s_date_layer = text_layer_create(GRect(0, 118, 144, 50));
  text_layer_set_background_color(s_date_layer, GColorWhite);
  text_layer_set_text_color(s_date_layer, GColorBlack);
  
  // Improve the date TextLayer layout to be more like a watchface
  text_layer_set_font(s_date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  
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
  
  // Create a Layer and set the update_proc
  s_line = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(s_line, drawline_callback);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_name_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
  layer_add_child(window_get_root_layer(window), s_line);
}

static void main_window_unload(Window *window) {
    // Destroy TextLayer
    text_layer_destroy(s_time_layer);
    text_layer_destroy(s_name_layer);
    text_layer_destroy(s_date_layer);
    layer_destroy(s_line);
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
