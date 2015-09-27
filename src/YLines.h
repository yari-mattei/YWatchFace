#pragma once

static Layer *s_line_left;
static Layer *s_line_right;
static Layer *s_line_center;

static Layer *s_lines;

static void drawline_center_callback(Layer *layer, GContext *ctx);

void initialize();

Layer* getYLines(); 