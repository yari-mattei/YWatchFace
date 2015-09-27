#pragma once

static TextLayer *s_day_layer;
static TextLayer *s_month_layer;
static TextLayer *s_year_layer;
static TextLayer *s_dayName_layer;
  
static Layer *s_date_layer;

void initializeYDate();
void destroyYDate();

Layer* getYDate(); 

void updateYDate(struct tm* time);