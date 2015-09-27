#include <pebble.h>
#include "YLines.h"

static void drawline_center_callback(Layer *layer, GContext *ctx) {
  GPoint p0 = GPoint(72, 85);
  GPoint p1 = GPoint(72, 168);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 4);
  graphics_draw_line(ctx, p0, p1);
}

void initialize(){
  // Create center line Layer 
  s_line_center = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(s_line_center, drawline_center_callback);
}

Layer* getYLines(){
  return s_line_center;
}
