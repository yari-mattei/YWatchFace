#pragma once

static TextLayer *s_day_layer;
static TextLayer *s_month_layer;
static TextLayer *s_year_layer;

static TextLayer *s_dayName1_layer;
static TextLayer *s_dayName2_layer;
static TextLayer *s_dayName3_layer;

static Layer *s_dayName_layer; 
static Layer *s_date_layer;

void initializeYDate();
void destroyYDate();

Layer* getYDate(); 

void updateYDate(struct tm* time);