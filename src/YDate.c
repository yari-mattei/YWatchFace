#include <pebble.h>
#include "YDate.h"

void initializeYDate(){
  // Create day TextLayer
  s_day_layer = text_layer_create(GRect(4, 60, 30, 30));
  text_layer_set_background_color(s_day_layer, GColorWhite);
  text_layer_set_text_color(s_day_layer, GColorBlack);
  
  //text_layer_set_text(s_day_layer, "DAY");
  
  // Improve the day TextLayer layout
  text_layer_set_font(s_day_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_day_layer, GTextAlignmentLeft);
  
  // Create month TextLayer
  s_month_layer = text_layer_create(GRect(4, 90, 30, 30));
  text_layer_set_background_color(s_month_layer, GColorWhite);
  text_layer_set_text_color(s_month_layer, GColorBlack);
  
  // Improve the month TextLayer layout
  text_layer_set_font(s_month_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_month_layer, GTextAlignmentLeft);
  
  // Create year TextLayer
  s_year_layer = text_layer_create(GRect(4, 120, 60, 30));
  text_layer_set_background_color(s_year_layer, GColorWhite);
  text_layer_set_text_color(s_year_layer, GColorBlack);
  
  // Improve the year TextLayer layout
  text_layer_set_font(s_year_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(s_year_layer, GTextAlignmentLeft);
  
  // Create Date Layer
  s_date_layer = layer_create(GRect(0, 0, 144, 168));
  
  layer_add_child(s_date_layer, text_layer_get_layer(s_day_layer));
  layer_add_child(s_date_layer, text_layer_get_layer(s_month_layer));
  layer_add_child(s_date_layer, text_layer_get_layer(s_year_layer));
}
void destroyYDate(){
  text_layer_destroy(s_day_layer);
  text_layer_destroy(s_month_layer);
  text_layer_destroy(s_year_layer);
  layer_destroy(s_date_layer);
}

Layer* getYDate(){
  return s_date_layer;
}

void updateYDate(struct tm* time){
  // Get a tm structure
  //time_t temp = time(NULL); 
  //struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char bufferDay[] = "dd";
  static char bufferMonth[] = "mm";
  static char bufferYear[] = "yyyy";
  
  // Write the current date into the buffer
  strftime(bufferDay, sizeof("dd"), "%d", time);
  strftime(bufferMonth, sizeof("mm"), "%m", time);
  strftime(bufferYear, sizeof("yyyy"), "%Y", time);
  
  // Display this date on the TextLayer
  text_layer_set_text(s_day_layer, bufferDay);
  text_layer_set_text(s_month_layer, bufferMonth);
  text_layer_set_text(s_year_layer, bufferYear);
}