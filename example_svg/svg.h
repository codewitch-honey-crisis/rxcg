// svg.h
// generated with rxcg https://github.com/codewitch-honey-crisis/rxcg
// on 9/13/2024 4:54:41 PM
#ifndef svg_H_HEADER
#define svg_H_HEADER
#include <stddef.h>
#ifdef ARDUINO
#include <Arduino.h>
#ifndef ESP32
#ifndef CORE_TEENSY
#include <avr/progmem.h>
#endif
#endif
#endif
#ifndef svg_int8
	#define svg_int8 char
	#define svg_uint8 unsigned char
	#define svg_int16 short
	#define svg_uint16 unsigned short
	#define svg_int32 int
	#define svg_uint32 unsigned int
#endif

// Represents the capture information
typedef struct match {
	// the captured text, as unicode codepoints
	svg_int32 capture[256];
	// the position in the text, as codepoints
	unsigned long long position;
	// the length of the capture buffer, in elements
	size_t length;
} match_t;
// a callback to read the input
typedef svg_int32(*read_callback)(unsigned long long* out_advance,void* state);
#if 0
#include <stdio.h>
// a container for the string cursor state
typedef struct string_cb_state {
	char* sz;
} string_cb_state_t;
#ifdef __cplusplus
extern "C" {
#endif
// an implementation of a callback over a UTF-8 string (char*)
svg_int32 string_read_callback(unsigned long long* out_advance, void* state);
// an implementation of a callback over a UTF-8 file (FILE*)
svg_int32 file_read_callback(unsigned long long* out_advance, void* state);
#ifdef __cplusplus
}
#endif
#endif
#ifdef __cplusplus
extern "C" {
#endif
// match the expression "clip-path"
match_t match_ATTR_CLIP_PATH(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "clip-rule"
match_t match_ATTR_CLIP_RULE(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "clipPathUnits"
match_t match_ATTR_CLIP_PATH_UNITS(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "color"
match_t match_ATTR_COLOR(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "cx"
match_t match_ATTR_CX(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "cy"
match_t match_ATTR_CY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "display"
match_t match_ATTR_DISPLAY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "fill"
match_t match_ATTR_FILL(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "fill-opacity"
match_t match_ATTR_FILL_OPACITY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "fill-rule"
match_t match_ATTR_FILL_RULE(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "fx"
match_t match_ATTR_FX(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "fy"
match_t match_ATTR_FY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "gradientTransform"
match_t match_ATTR_GRADIENT_TRANSFORM(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "gradientUnits"
match_t match_ATTR_GRADIENT_UNITS(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "height"
match_t match_ATTR_HEIGHT(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "offset"
match_t match_ATTR_OFFSET(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "opacity"
match_t match_ATTR_OPACITY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "points"
match_t match_ATTR_POINTS(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "preserveAspectRatio"
match_t match_ATTR_PRESERVE_ASPECT_RATIO(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "r"
match_t match_ATTR_R(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "rx"
match_t match_ATTR_RX(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "ry"
match_t match_ATTR_RY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "spreadMethod"
match_t match_ATTR_SPREAD_METHOD(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stop-color"
match_t match_ATTR_STOP_COLOR(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stop-opacity"
match_t match_ATTR_STOP_OPACITY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stroke"
match_t match_ATTR_STROKE(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stroke-dasharray"
match_t match_ATTR_STROKE_DASH_ARRAY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stroke-dashoffset"
match_t match_ATTR_STROKE_DASH_OFFSET(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stroke-linecap"
match_t match_ATTR_STROKE_LINECAP(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stroke-linejoin"
match_t match_ATTR_STROKE_LINEJOIN(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stroke-miterlimit"
match_t match_ATTR_STROKE_MITERLIMIT(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stroke-opacity"
match_t match_ATTR_STROKE_OPACITY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "stroke-width"
match_t match_ATTR_STROKE_WIDTH(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "transform"
match_t match_ATTR_TRANSFORM(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "viewBox"
match_t match_ATTR_VIEW_BOX(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "visibility"
match_t match_ATTR_VISIBILITY(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "width"
match_t match_ATTR_WIDTH(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "x"
match_t match_ATTR_X(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "x1"
match_t match_ATTR_X1(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "x2"
match_t match_ATTR_X2(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "y"
match_t match_ATTR_Y(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "y1"
match_t match_ATTR_Y1(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression "y2"
match_t match_ATTR_Y2(unsigned long long* position,read_callback callback, void* callback_state);
#ifdef __cplusplus
}
#endif
#endif
