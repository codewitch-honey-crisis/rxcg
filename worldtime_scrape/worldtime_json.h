// worldtime_json.h
// generated with rxcg https://github.com/codewitch-honey-crisis/rxcg
// on 11/14/2023 11:55:59 PM
#ifndef worldtime_json_H_HEADER
#define worldtime_json_H_HEADER
#include <stddef.h>
#ifdef ARDUINO
#include <Arduino.h>
#ifndef ESP32
#ifndef CORE_TEENSY
#include <avr/progmem.h>
#endif
#endif
#endif
#ifndef worldtime_json_int8
	#define worldtime_json_int8 char
	#define worldtime_json_uint8 unsigned char
	#define worldtime_json_int16 short
	#define worldtime_json_uint16 unsigned short
	#define worldtime_json_int32 int
	#define worldtime_json_uint32 unsigned int
#endif
// Represents the capture information
typedef struct match {
	// the captured text, as unicode codepoints
	worldtime_json_int8 capture[256];
	// the position in the text, as codepoints
	unsigned long long position;
	// the length of the capture buffer, in elements
	size_t length;
} match_t;
// a callback to read the input
typedef worldtime_json_int32(*read_callback)(unsigned long long* out_advance,void* state);
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
worldtime_json_int32 string_read_callback(unsigned long long* out_advance, void* state);
// an implementation of a callback over a UTF-8 file (FILE*)
worldtime_json_int32 file_read_callback(unsigned long long* out_advance, void* state);
#ifdef __cplusplus
}
#endif
#endif
#ifdef __cplusplus
extern "C" {
#endif
// match the expression '"unixtime"\:[0-9]+'
match_t match_unixtime_all(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression '[0-9]+'
match_t match_unixtime_value(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression '"raw_offset"\:\-?[0-9]+'
match_t match_raw_offset_all(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression '\-?[0-9]+'
match_t match_raw_offset_value(unsigned long long* position,read_callback callback, void* callback_state);
#ifdef __cplusplus
}
#endif
#endif
