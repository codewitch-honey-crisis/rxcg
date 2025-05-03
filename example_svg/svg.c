// svg.c
#include "svg.h"
static svg_int8 ATTR_CLIP_PATH_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'c', 'c', -1, 1, 12, 1, 
	'l', 'l', -1, 1, 18, 1, 'i', 'i', -1, 1, 
	24, 1, 'p', 'p', -1, 1, 30, 1, '-', '-', 
	-1, 1, 36, 1, 'p', 'p', -1, 1, 42, 1, 
	'a', 'a', -1, 1, 48, 1, 't', 't', -1, 1, 
	54, 1, 'h', 'h', 0, 0
};
static svg_int8 ATTR_CLIP_RULE_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'c', 'c', -1, 1, 12, 1, 
	'l', 'l', -1, 1, 18, 1, 'i', 'i', -1, 1, 
	24, 1, 'p', 'p', -1, 1, 30, 1, '-', '-', 
	-1, 1, 36, 1, 'r', 'r', -1, 1, 42, 1, 
	'u', 'u', -1, 1, 48, 1, 'l', 'l', -1, 1, 
	54, 1, 'e', 'e', 1, 0
};
static svg_int8 ATTR_CLIP_PATH_UNITS_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'c', 'c', -1, 1, 12, 1, 
	'l', 'l', -1, 1, 18, 1, 'i', 'i', -1, 1, 
	24, 1, 'p', 'p', -1, 1, 30, 1, 'P', 'P', 
	-1, 1, 36, 1, 'a', 'a', -1, 1, 42, 1, 
	't', 't', -1, 1, 48, 1, 'h', 'h', -1, 1, 
	54, 1, 'U', 'U', -1, 1, 60, 1, 'n', 'n', 
	-1, 1, 66, 1, 'i', 'i', -1, 1, 72, 1, 
	't', 't', -1, 1, 78, 1, 's', 's', 2, 0
};
static svg_int8 ATTR_COLOR_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'c', 'c', -1, 1, 12, 1, 
	'o', 'o', -1, 1, 18, 1, 'l', 'l', -1, 1, 
	24, 1, 'o', 'o', -1, 1, 30, 1, 'r', 'r', 
	3, 0
};
static svg_int8 ATTR_CX_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'c', 'c', -1, 1, 12, 1, 
	'x', 'x', 4, 0
};
static svg_int8 ATTR_CY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'c', 'c', -1, 1, 12, 1, 
	'y', 'y', 5, 0
};
static svg_int8 ATTR_DISPLAY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'd', 'd', -1, 1, 12, 1, 
	'i', 'i', -1, 1, 18, 1, 's', 's', -1, 1, 
	24, 1, 'p', 'p', -1, 1, 30, 1, 'l', 'l', 
	-1, 1, 36, 1, 'a', 'a', -1, 1, 42, 1, 
	'y', 'y', 6, 0
};
static svg_int8 ATTR_FILL_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'f', 'f', -1, 1, 12, 1, 
	'i', 'i', -1, 1, 18, 1, 'l', 'l', -1, 1, 
	24, 1, 'l', 'l', 7, 0
};
static svg_int8 ATTR_FILL_OPACITY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'f', 'f', -1, 1, 12, 1, 
	'i', 'i', -1, 1, 18, 1, 'l', 'l', -1, 1, 
	24, 1, 'l', 'l', -1, 1, 30, 1, '-', '-', 
	-1, 1, 36, 1, 'o', 'o', -1, 1, 42, 1, 
	'p', 'p', -1, 1, 48, 1, 'a', 'a', -1, 1, 
	54, 1, 'c', 'c', -1, 1, 60, 1, 'i', 'i', 
	-1, 1, 66, 1, 't', 't', -1, 1, 72, 1, 
	'y', 'y', 8, 0
};
static svg_int8 ATTR_FILL_RULE_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'f', 'f', -1, 1, 12, 1, 
	'i', 'i', -1, 1, 18, 1, 'l', 'l', -1, 1, 
	24, 1, 'l', 'l', -1, 1, 30, 1, '-', '-', 
	-1, 1, 36, 1, 'r', 'r', -1, 1, 42, 1, 
	'u', 'u', -1, 1, 48, 1, 'l', 'l', -1, 1, 
	54, 1, 'e', 'e', 9, 0
};
static svg_int8 ATTR_FX_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'f', 'f', -1, 1, 12, 1, 
	'x', 'x', 10, 0
};
static svg_int8 ATTR_FY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'f', 'f', -1, 1, 12, 1, 
	'y', 'y', 11, 0
};
static svg_int8 ATTR_GRADIENT_TRANSFORM_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'g', 'g', -1, 1, 12, 1, 
	'r', 'r', -1, 1, 18, 1, 'a', 'a', -1, 1, 
	24, 1, 'd', 'd', -1, 1, 30, 1, 'i', 'i', 
	-1, 1, 36, 1, 'e', 'e', -1, 1, 42, 1, 
	'n', 'n', -1, 1, 48, 1, 't', 't', -1, 1, 
	54, 1, 'T', 'T', -1, 1, 60, 1, 'r', 'r', 
	-1, 1, 66, 1, 'a', 'a', -1, 1, 72, 1, 
	'n', 'n', -1, 1, 78, 1, 's', 's', -1, 1, 
	84, 1, 'f', 'f', -1, 1, 90, 1, 'o', 'o', 
	-1, 1, 96, 1, 'r', 'r', -1, 1, 102, 1, 
	'm', 'm', 12, 0
};
static svg_int8 ATTR_GRADIENT_UNITS_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'g', 'g', -1, 1, 12, 1, 
	'r', 'r', -1, 1, 18, 1, 'a', 'a', -1, 1, 
	24, 1, 'd', 'd', -1, 1, 30, 1, 'i', 'i', 
	-1, 1, 36, 1, 'e', 'e', -1, 1, 42, 1, 
	'n', 'n', -1, 1, 48, 1, 't', 't', -1, 1, 
	54, 1, 'U', 'U', -1, 1, 60, 1, 'n', 'n', 
	-1, 1, 66, 1, 'i', 'i', -1, 1, 72, 1, 
	't', 't', -1, 1, 78, 1, 's', 's', 13, 0
};
static svg_int8 ATTR_HEIGHT_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'h', 'h', -1, 1, 12, 1, 
	'e', 'e', -1, 1, 18, 1, 'i', 'i', -1, 1, 
	24, 1, 'g', 'g', -1, 1, 30, 1, 'h', 'h', 
	-1, 1, 36, 1, 't', 't', 14, 0
};
static svg_int8 ATTR_OFFSET_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'o', 'o', -1, 1, 12, 1, 
	'f', 'f', -1, 1, 18, 1, 'f', 'f', -1, 1, 
	24, 1, 's', 's', -1, 1, 30, 1, 'e', 'e', 
	-1, 1, 36, 1, 't', 't', 15, 0
};
static svg_int8 ATTR_OPACITY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'o', 'o', -1, 1, 12, 1, 
	'p', 'p', -1, 1, 18, 1, 'a', 'a', -1, 1, 
	24, 1, 'c', 'c', -1, 1, 30, 1, 'i', 'i', 
	-1, 1, 36, 1, 't', 't', -1, 1, 42, 1, 
	'y', 'y', 16, 0
};
static svg_int8 ATTR_POINTS_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'p', 'p', -1, 1, 12, 1, 
	'o', 'o', -1, 1, 18, 1, 'i', 'i', -1, 1, 
	24, 1, 'n', 'n', -1, 1, 30, 1, 't', 't', 
	-1, 1, 36, 1, 's', 's', 17, 0
};
static svg_int8 ATTR_PRESERVE_ASPECT_RATIO_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'p', 'p', -1, 1, 12, 1, 
	'r', 'r', -1, 1, 18, 1, 'e', 'e', -1, 1, 
	24, 1, 's', 's', -1, 1, 30, 1, 'e', 'e', 
	-1, 1, 36, 1, 'r', 'r', -1, 1, 42, 1, 
	'v', 'v', -1, 1, 48, 1, 'e', 'e', -1, 1, 
	54, 1, 'A', 'A', -1, 1, 60, 1, 's', 's', 
	-1, 1, 66, 1, 'p', 'p', -1, 1, 72, 1, 
	'e', 'e', -1, 1, 78, 1, 'c', 'c', -1, 1, 
	84, 1, 't', 't', -1, 1, 90, 1, 'R', 'R', 
	-1, 1, 96, 1, 'a', 'a', -1, 1, 102, 1, 
	't', 't', -1, 1, 108, 1, 'i', 'i', -1, 1, 
	114, 1, 'o', 'o', 18, 0
};
static svg_int8 ATTR_R_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'r', 'r', 19, 0
};
static svg_int8 ATTR_RX_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'r', 'r', -1, 1, 12, 1, 
	'x', 'x', 20, 0
};
static svg_int8 ATTR_RY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'r', 'r', -1, 1, 12, 1, 
	'y', 'y', 21, 0
};
static svg_int8 ATTR_SPREAD_METHOD_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	'p', 'p', -1, 1, 18, 1, 'r', 'r', -1, 1, 
	24, 1, 'e', 'e', -1, 1, 30, 1, 'a', 'a', 
	-1, 1, 36, 1, 'd', 'd', -1, 1, 42, 1, 
	'M', 'M', -1, 1, 48, 1, 'e', 'e', -1, 1, 
	54, 1, 't', 't', -1, 1, 60, 1, 'h', 'h', 
	-1, 1, 66, 1, 'o', 'o', -1, 1, 72, 1, 
	'd', 'd', 22, 0
};
static svg_int8 ATTR_STOP_COLOR_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'o', 'o', -1, 1, 
	24, 1, 'p', 'p', -1, 1, 30, 1, '-', '-', 
	-1, 1, 36, 1, 'c', 'c', -1, 1, 42, 1, 
	'o', 'o', -1, 1, 48, 1, 'l', 'l', -1, 1, 
	54, 1, 'o', 'o', -1, 1, 60, 1, 'r', 'r', 
	23, 0
};
static svg_int8 ATTR_STOP_OPACITY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'o', 'o', -1, 1, 
	24, 1, 'p', 'p', -1, 1, 30, 1, '-', '-', 
	-1, 1, 36, 1, 'o', 'o', -1, 1, 42, 1, 
	'p', 'p', -1, 1, 48, 1, 'a', 'a', -1, 1, 
	54, 1, 'c', 'c', -1, 1, 60, 1, 'i', 'i', 
	-1, 1, 66, 1, 't', 't', -1, 1, 72, 1, 
	'y', 'y', 24, 0
};
static svg_int8 ATTR_STROKE_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'r', 'r', -1, 1, 
	24, 1, 'o', 'o', -1, 1, 30, 1, 'k', 'k', 
	-1, 1, 36, 1, 'e', 'e', 25, 0
};
static svg_int8 ATTR_STROKE_DASH_ARRAY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'r', 'r', -1, 1, 
	24, 1, 'o', 'o', -1, 1, 30, 1, 'k', 'k', 
	-1, 1, 36, 1, 'e', 'e', -1, 1, 42, 1, 
	'-', '-', -1, 1, 48, 1, 'd', 'd', -1, 1, 
	54, 1, 'a', 'a', -1, 1, 60, 1, 's', 's', 
	-1, 1, 66, 1, 'h', 'h', -1, 1, 72, 1, 
	'a', 'a', -1, 1, 78, 1, 'r', 'r', -1, 1, 
	84, 1, 'r', 'r', -1, 1, 90, 1, 'a', 'a', 
	-1, 1, 96, 1, 'y', 'y', 26, 0
};
static svg_int8 ATTR_STROKE_DASH_OFFSET_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'r', 'r', -1, 1, 
	24, 1, 'o', 'o', -1, 1, 30, 1, 'k', 'k', 
	-1, 1, 36, 1, 'e', 'e', -1, 1, 42, 1, 
	'-', '-', -1, 1, 48, 1, 'd', 'd', -1, 1, 
	54, 1, 'a', 'a', -1, 1, 60, 1, 's', 's', 
	-1, 1, 66, 1, 'h', 'h', -1, 1, 72, 1, 
	'o', 'o', -1, 1, 78, 1, 'f', 'f', -1, 1, 
	84, 1, 'f', 'f', -1, 1, 90, 1, 's', 's', 
	-1, 1, 96, 1, 'e', 'e', -1, 1, 102, 1, 
	't', 't', 27, 0
};
static svg_int8 ATTR_STROKE_LINECAP_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'r', 'r', -1, 1, 
	24, 1, 'o', 'o', -1, 1, 30, 1, 'k', 'k', 
	-1, 1, 36, 1, 'e', 'e', -1, 1, 42, 1, 
	'-', '-', -1, 1, 48, 1, 'l', 'l', -1, 1, 
	54, 1, 'i', 'i', -1, 1, 60, 1, 'n', 'n', 
	-1, 1, 66, 1, 'e', 'e', -1, 1, 72, 1, 
	'c', 'c', -1, 1, 78, 1, 'a', 'a', -1, 1, 
	84, 1, 'p', 'p', 28, 0
};
static svg_int8 ATTR_STROKE_LINEJOIN_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'r', 'r', -1, 1, 
	24, 1, 'o', 'o', -1, 1, 30, 1, 'k', 'k', 
	-1, 1, 36, 1, 'e', 'e', -1, 1, 42, 1, 
	'-', '-', -1, 1, 48, 1, 'l', 'l', -1, 1, 
	54, 1, 'i', 'i', -1, 1, 60, 1, 'n', 'n', 
	-1, 1, 66, 1, 'e', 'e', -1, 1, 72, 1, 
	'j', 'j', -1, 1, 78, 1, 'o', 'o', -1, 1, 
	84, 1, 'i', 'i', -1, 1, 90, 1, 'n', 'n', 
	29, 0
};
static svg_int8 ATTR_STROKE_MITERLIMIT_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'r', 'r', -1, 1, 
	24, 1, 'o', 'o', -1, 1, 30, 1, 'k', 'k', 
	-1, 1, 36, 1, 'e', 'e', -1, 1, 42, 1, 
	'-', '-', -1, 1, 48, 1, 'm', 'm', -1, 1, 
	54, 1, 'i', 'i', -1, 1, 60, 1, 't', 't', 
	-1, 1, 66, 1, 'e', 'e', -1, 1, 72, 1, 
	'r', 'r', -1, 1, 78, 1, 'l', 'l', -1, 1, 
	84, 1, 'i', 'i', -1, 1, 90, 1, 'm', 'm', 
	-1, 1, 96, 1, 'i', 'i', -1, 1, 102, 1, 
	't', 't', 30, 0
};
static svg_int8 ATTR_STROKE_OPACITY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'r', 'r', -1, 1, 
	24, 1, 'o', 'o', -1, 1, 30, 1, 'k', 'k', 
	-1, 1, 36, 1, 'e', 'e', -1, 1, 42, 1, 
	'-', '-', -1, 1, 48, 1, 'o', 'o', -1, 1, 
	54, 1, 'p', 'p', -1, 1, 60, 1, 'a', 'a', 
	-1, 1, 66, 1, 'c', 'c', -1, 1, 72, 1, 
	'i', 'i', -1, 1, 78, 1, 't', 't', -1, 1, 
	84, 1, 'y', 'y', 31, 0
};
static svg_int8 ATTR_STROKE_WIDTH_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 's', 's', -1, 1, 12, 1, 
	't', 't', -1, 1, 18, 1, 'r', 'r', -1, 1, 
	24, 1, 'o', 'o', -1, 1, 30, 1, 'k', 'k', 
	-1, 1, 36, 1, 'e', 'e', -1, 1, 42, 1, 
	'-', '-', -1, 1, 48, 1, 'w', 'w', -1, 1, 
	54, 1, 'i', 'i', -1, 1, 60, 1, 'd', 'd', 
	-1, 1, 66, 1, 't', 't', -1, 1, 72, 1, 
	'h', 'h', 32, 0
};
static svg_int8 ATTR_TRANSFORM_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 't', 't', -1, 1, 12, 1, 
	'r', 'r', -1, 1, 18, 1, 'a', 'a', -1, 1, 
	24, 1, 'n', 'n', -1, 1, 30, 1, 's', 's', 
	-1, 1, 36, 1, 'f', 'f', -1, 1, 42, 1, 
	'o', 'o', -1, 1, 48, 1, 'r', 'r', -1, 1, 
	54, 1, 'm', 'm', 33, 0
};
static svg_int8 ATTR_VIEW_BOX_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'v', 'v', -1, 1, 12, 1, 
	'i', 'i', -1, 1, 18, 1, 'e', 'e', -1, 1, 
	24, 1, 'w', 'w', -1, 1, 30, 1, 'B', 'B', 
	-1, 1, 36, 1, 'o', 'o', -1, 1, 42, 1, 
	'x', 'x', 34, 0
};
static svg_int8 ATTR_VISIBILITY_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'v', 'v', -1, 1, 12, 1, 
	'i', 'i', -1, 1, 18, 1, 's', 's', -1, 1, 
	24, 1, 'i', 'i', -1, 1, 30, 1, 'b', 'b', 
	-1, 1, 36, 1, 'i', 'i', -1, 1, 42, 1, 
	'l', 'l', -1, 1, 48, 1, 'i', 'i', -1, 1, 
	54, 1, 't', 't', -1, 1, 60, 1, 'y', 'y', 
	35, 0
};
static svg_int8 ATTR_WIDTH_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'w', 'w', -1, 1, 12, 1, 
	'i', 'i', -1, 1, 18, 1, 'd', 'd', -1, 1, 
	24, 1, 't', 't', -1, 1, 30, 1, 'h', 'h', 
	36, 0
};
static svg_int8 ATTR_X_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'x', 'x', 37, 0
};
static svg_int8 ATTR_X1_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'x', 'x', -1, 1, 12, 1, 
	'1', '1', 38, 0
};
static svg_int8 ATTR_X2_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'x', 'x', -1, 1, 12, 1, 
	'2', '2', 39, 0
};
static svg_int8 ATTR_Y_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'y', 'y', 40, 0
};
static svg_int8 ATTR_Y1_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'y', 'y', -1, 1, 12, 1, 
	'1', '1', 41, 0
};
static svg_int8 ATTR_Y2_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 'y', 'y', -1, 1, 12, 1, 
	'2', '2', 42, 0
};
static match_t svg_runner8(svg_int8* dfa, unsigned long long* position, read_callback callback, void* callback_state) {
	match_t result;
	result.position = 0;
	result.length = 0;
	unsigned long long adv = 0;
	int tlen;
	svg_int8 tto;
	svg_int8 prlen;
	svg_int8 pmin;
	svg_int8 pmax;
	int i, j;
	svg_int32 ch;
	svg_int8 state = 0;
	svg_int8 acc = -1;
	int done;
	unsigned long long cursor_pos = *position;
	ch = callback(&adv, callback_state);
	while (ch != -1) {
		result.length = 0;
		result.position = cursor_pos;
		acc = -1;
		done = 0;
		while (!done) {
start_dfa:
			done = 1;
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
			acc = (svg_int8)pgm_read_byte((svg_uint8*)(dfa + (state++)));
			tlen = (svg_int8)pgm_read_byte((svg_uint8*)(dfa + (state++)));
#else
			acc = dfa[state++];
			tlen = dfa[state++];
#endif
			for (i = 0; i < tlen; ++i) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
				tto = (svg_int8)pgm_read_byte((svg_uint8*)(dfa + (state++)));
				prlen = (svg_int8)pgm_read_byte((svg_uint8*)(dfa + (state++)));
#else
				tto = dfa[state++];
				prlen = dfa[state++];
#endif
				for (j = 0; j < prlen; ++j) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
					pmin = (svg_int8)pgm_read_byte((svg_uint8*)(dfa + (state++)));
					pmax = (svg_int8)pgm_read_byte((svg_uint8*)(dfa + (state++)));
#else
					pmin = dfa[state++];
					pmax = dfa[state++];
#endif
					if (ch < pmin) {
						break;
					}
					if (ch <= pmax) {
						if (result.length < 256) {
							result.capture[result.length++] = ch;
						}
						ch = callback(&adv, callback_state);
						++cursor_pos;
						state = tto;
						done = 0;
						goto start_dfa;
					}
				}
			}
			if (acc != -1) {
				if (result.length > 0) {
					return result;
				}
			}
			ch = callback(&adv, callback_state);
			++cursor_pos;
			state = 0;
		}
	}
	result.length = 0;
	return result;
}
match_t match_ATTR_CLIP_PATH(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_CLIP_PATH_dfa, position, callback, callback_state);
}
match_t match_ATTR_CLIP_RULE(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_CLIP_RULE_dfa, position, callback, callback_state);
}
match_t match_ATTR_CLIP_PATH_UNITS(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_CLIP_PATH_UNITS_dfa, position, callback, callback_state);
}
match_t match_ATTR_COLOR(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_COLOR_dfa, position, callback, callback_state);
}
match_t match_ATTR_CX(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_CX_dfa, position, callback, callback_state);
}
match_t match_ATTR_CY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_CY_dfa, position, callback, callback_state);
}
match_t match_ATTR_DISPLAY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_DISPLAY_dfa, position, callback, callback_state);
}
match_t match_ATTR_FILL(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_FILL_dfa, position, callback, callback_state);
}
match_t match_ATTR_FILL_OPACITY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_FILL_OPACITY_dfa, position, callback, callback_state);
}
match_t match_ATTR_FILL_RULE(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_FILL_RULE_dfa, position, callback, callback_state);
}
match_t match_ATTR_FX(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_FX_dfa, position, callback, callback_state);
}
match_t match_ATTR_FY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_FY_dfa, position, callback, callback_state);
}
match_t match_ATTR_GRADIENT_TRANSFORM(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_GRADIENT_TRANSFORM_dfa, position, callback, callback_state);
}
match_t match_ATTR_GRADIENT_UNITS(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_GRADIENT_UNITS_dfa, position, callback, callback_state);
}
match_t match_ATTR_HEIGHT(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_HEIGHT_dfa, position, callback, callback_state);
}
match_t match_ATTR_OFFSET(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_OFFSET_dfa, position, callback, callback_state);
}
match_t match_ATTR_OPACITY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_OPACITY_dfa, position, callback, callback_state);
}
match_t match_ATTR_POINTS(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_POINTS_dfa, position, callback, callback_state);
}
match_t match_ATTR_PRESERVE_ASPECT_RATIO(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_PRESERVE_ASPECT_RATIO_dfa, position, callback, callback_state);
}
match_t match_ATTR_R(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_R_dfa, position, callback, callback_state);
}
match_t match_ATTR_RX(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_RX_dfa, position, callback, callback_state);
}
match_t match_ATTR_RY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_RY_dfa, position, callback, callback_state);
}
match_t match_ATTR_SPREAD_METHOD(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_SPREAD_METHOD_dfa, position, callback, callback_state);
}
match_t match_ATTR_STOP_COLOR(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STOP_COLOR_dfa, position, callback, callback_state);
}
match_t match_ATTR_STOP_OPACITY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STOP_OPACITY_dfa, position, callback, callback_state);
}
match_t match_ATTR_STROKE(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STROKE_dfa, position, callback, callback_state);
}
match_t match_ATTR_STROKE_DASH_ARRAY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STROKE_DASH_ARRAY_dfa, position, callback, callback_state);
}
match_t match_ATTR_STROKE_DASH_OFFSET(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STROKE_DASH_OFFSET_dfa, position, callback, callback_state);
}
match_t match_ATTR_STROKE_LINECAP(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STROKE_LINECAP_dfa, position, callback, callback_state);
}
match_t match_ATTR_STROKE_LINEJOIN(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STROKE_LINEJOIN_dfa, position, callback, callback_state);
}
match_t match_ATTR_STROKE_MITERLIMIT(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STROKE_MITERLIMIT_dfa, position, callback, callback_state);
}
match_t match_ATTR_STROKE_OPACITY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STROKE_OPACITY_dfa, position, callback, callback_state);
}
match_t match_ATTR_STROKE_WIDTH(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_STROKE_WIDTH_dfa, position, callback, callback_state);
}
match_t match_ATTR_TRANSFORM(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_TRANSFORM_dfa, position, callback, callback_state);
}
match_t match_ATTR_VIEW_BOX(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_VIEW_BOX_dfa, position, callback, callback_state);
}
match_t match_ATTR_VISIBILITY(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_VISIBILITY_dfa, position, callback, callback_state);
}
match_t match_ATTR_WIDTH(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_WIDTH_dfa, position, callback, callback_state);
}
match_t match_ATTR_X(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_X_dfa, position, callback, callback_state);
}
match_t match_ATTR_X1(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_X1_dfa, position, callback, callback_state);
}
match_t match_ATTR_X2(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_X2_dfa, position, callback, callback_state);
}
match_t match_ATTR_Y(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_Y_dfa, position, callback, callback_state);
}
match_t match_ATTR_Y1(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_Y1_dfa, position, callback, callback_state);
}
match_t match_ATTR_Y2(unsigned long long* position,read_callback callback, void* callback_state) {
	return svg_runner8(ATTR_Y2_dfa, position, callback, callback_state);
}
#if 0
svg_int32 string_read_callback(unsigned long long* out_advance, void* state) {
	string_cb_state_t* ps = (string_cb_state_t*)state;
	svg_int32 cp = 0;
	if (!*ps->sz) {
		*out_advance = 0;
		return -1;
	}
	svg_uint8 data = (svg_uint8)*ps->sz;
	if ((data & 128) == 0) {
		cp = ((svg_uint32)*ps->sz & ~128);
		*out_advance = 1;
	}

	if ((data & 224) == 192) {
		cp = ((svg_uint32)ps->sz[0] & ~224) << 6 |
			((svg_uint32)ps->sz[1] & ~192);
		*out_advance = 2;
	}

	if ((data & 240) == 224) {
		cp = ((svg_uint32)ps->sz[0] & ~240) << 12 |
			((svg_uint32)ps->sz[1] & ~192) << 6 |
			((svg_uint32)ps->sz[2] & ~192);
		*out_advance = 3;
	}

	if ((data & 248) == 240) {
		cp = ((svg_uint32)ps->sz[0] & ~248) << 18 |
			((svg_uint32)ps->sz[1] & ~192) << 12 |
			((svg_uint32)ps->sz[2] & ~192) << 6 |
			((svg_uint32)ps->sz[3] & ~192);
		*out_advance = 4;
	}
	ps->sz += *out_advance;

	return cp;
}
svg_int32 file_read_callback(unsigned long long* out_advance, void* state) {
	FILE* h = (FILE*)state;
	svg_int32 cp = 0;
	int i = fgetc(h);
	if (i == -1) {
		*out_advance = 0;
		return -1;
	}
	svg_uint8 data = (svg_uint8)i;
	if ((data & 128) == 0) {
		cp = ((svg_uint32)i & ~128);
		*out_advance = 1;
	}

	if ((data & 224) == 192) {
		cp = ((svg_uint32)i & ~224) << 6 |
			((svg_uint32)fgetc(h) & ~192);
		*out_advance = 2;
	}

	if ((data & 240) == 224) {
		cp = ((svg_uint32)i & ~240) << 12 |
			((svg_uint32)fgetc(h) & ~192) << 6 |
			((svg_uint32)fgetc(h) & ~192);
		*out_advance = 3;
	}

	if ((data & 248) == 240) {
		cp = ((svg_uint32)i & ~248) << 18 |
			((svg_uint32)fgetc(h) & ~192) << 12 |
			((svg_uint32)fgetc(h) & ~192) << 6 |
			((svg_uint32)fgetc(h) & ~192);
		*out_advance = 4;
	}
	return cp;
}
#endif
