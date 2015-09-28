#include <pebble.h>
#include <ctype.h>
#include "YDate.h"

void initializeYDate(){
  // Create day TextLayer
  s_day_layer = text_layer_create(GRect(4, 60, 30, 30));
  text_layer_set_background_color(s_day_layer, GColorWhite);
  text_layer_set_text_color(s_day_layer, GColorBlack);
  
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
  
   // Create dayName TextLayer
  s_dayName1_layer = text_layer_create(GRect(0, 0, 20, 20)); //relative to s_dayName_layer !!!
  s_dayName2_layer = text_layer_create(GRect(0, 18, 20, 20));
  s_dayName3_layer = text_layer_create(GRect(0, 36, 20, 20));
  text_layer_set_background_color(s_dayName1_layer, GColorWhite);
  text_layer_set_background_color(s_dayName2_layer, GColorWhite);
  text_layer_set_background_color(s_dayName3_layer, GColorWhite);
  text_layer_set_text_color(s_dayName1_layer, GColorBlack);
  text_layer_set_text_color(s_dayName2_layer, GColorBlack);
  text_layer_set_text_color(s_dayName3_layer, GColorBlack);
  
  // Improve the dayName TextLayer layout
  text_layer_set_font(s_dayName1_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_font(s_dayName2_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_font(s_dayName3_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
  text_layer_set_text_alignment(s_dayName1_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_dayName2_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(s_dayName3_layer, GTextAlignmentCenter);
  
  // Create Date Layer
  s_dayName_layer = layer_create(GRect(26, 66, 30, 60));
  //s_dayName_layer = layer_create(GRect(0, 0, 144, 168));
  s_date_layer = layer_create(GRect(0, 0, 144, 168));
  
  layer_add_child(s_date_layer, text_layer_get_layer(s_day_layer));
  layer_add_child(s_date_layer, text_layer_get_layer(s_month_layer));
  layer_add_child(s_date_layer, text_layer_get_layer(s_year_layer));
  layer_add_child(s_dayName_layer, text_layer_get_layer(s_dayName1_layer));
  layer_add_child(s_dayName_layer, text_layer_get_layer(s_dayName2_layer));
  layer_add_child(s_dayName_layer, text_layer_get_layer(s_dayName3_layer));
  layer_add_child(s_date_layer, s_dayName_layer);
}
void destroyYDate(){
  text_layer_destroy(s_day_layer);
  text_layer_destroy(s_month_layer);
  text_layer_destroy(s_year_layer);
  text_layer_destroy(s_dayName1_layer);
  text_layer_destroy(s_dayName2_layer);
  text_layer_destroy(s_dayName3_layer);
  layer_destroy(s_dayName_layer);
  layer_destroy(s_date_layer);
}

Layer* getYDate(){
  return s_date_layer;
}

void updateYDate(struct tm* time){
  // Create a long-lived buffer
  static char bufferDay[] = "dd";
  static char bufferMonth[] = "mm";
  static char bufferYear[] = "yyyy";
  static char bufferDayName[] = "ddd";
  static char buffer1[] = "d";
  static char buffer2[] = "d";
  static char buffer3[] = "d";
  
  // Write the current date into the buffer
  strftime(bufferDay, sizeof("dd"), "%d", time);
  strftime(bufferMonth, sizeof("mm"), "%m", time);
  strftime(bufferYear, sizeof("yyyy"), "%Y", time);
  strftime(bufferDayName, sizeof("ddd"), "%a", time);
  
  buffer1[0] = (char) toupper((unsigned char)bufferDayName[0]); 
  buffer2[0] = (char) toupper((unsigned char)bufferDayName[1]); 
  buffer3[0] = (char) toupper((unsigned char)bufferDayName[2]); 
  
  // Display this date on the TextLayer
  text_layer_set_text(s_day_layer, bufferDay);
  text_layer_set_text(s_month_layer, bufferMonth);
  text_layer_set_text(s_year_layer, bufferYear);
  text_layer_set_text(s_dayName1_layer, buffer1);
  text_layer_set_text(s_dayName2_layer, buffer2);
  text_layer_set_text(s_dayName3_layer, buffer3);
}