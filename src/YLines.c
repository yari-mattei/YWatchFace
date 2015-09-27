#include <pebble.h>
#include "YLines.h"

static void drawline_center_callback(Layer *layer, GContext *ctx) {
  GPoint p0 = GPoint(72, 85);
  GPoint p1 = GPoint(72, 168);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 4);
  graphics_draw_line(ctx, p0, p1);
}
static void drawline_left_callback(Layer *layer, GContext *ctx) {
  GPoint p0 = GPoint(0, 35);
  GPoint p1 = GPoint(72, 85);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 4);
  graphics_draw_line(ctx, p0, p1);
}

static void drawline_right_callback(Layer *layer, GContext *ctx) {
  GPoint p0 = GPoint(168, 18);
  GPoint p1 = GPoint(72, 85);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 4);
  graphics_draw_line(ctx, p0, p1);
}


void initializeYLines(){
  // Create left line Layer 
  s_line_left = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(s_line_left, drawline_left_callback);
  
  // Create right line layer
  s_line_right = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(s_line_right, drawline_right_callback);
  
  // Create center line Layer 
  s_line_center = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(s_line_center, drawline_center_callback);
  
  // Create lines layer
  s_lines = layer_create(GRect(0, 0, 144, 168));
  
  layer_add_child(s_lines, s_line_left);
  layer_add_child(s_lines, s_line_right);
  layer_add_child(s_lines, s_line_center);
}

Layer* getYLines(){
  return s_lines;
}

void destroyYLines(){
  layer_destroy(s_line_left);
  layer_destroy(s_line_right);
  layer_destroy(s_line_center);
  layer_destroy(s_lines);
}