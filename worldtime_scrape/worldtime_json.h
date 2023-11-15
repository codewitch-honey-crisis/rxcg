// worldtime_json.h
// generated with rxcg https://github.com/codewitch-honey-crisis/rxcg
// on 11/15/2023 10:26:47 AM
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
#include <stdint.h>
// Represents the capture information
typedef struct match {
	// the captured text, as unicode codepoints
	int8_t capture[256];
	// the position in the text, as codepoints
	unsigned long long position;
	// the length of the capture buffer, in elements
	size_t length;
} match_t;
// a callback to read the input
typedef int32_t(*read_callback)(unsigned long long* out_advance,void* state);
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
int32_t string_read_callback(unsigned long long* out_advance, void* state);
// an implementation of a callback over a UTF-8 file (FILE*)
int32_t file_read_callback(unsigned long long* out_advance, void* state);
#ifdef __cplusplus
}
#endif
#endif
#ifdef __cplusplus
extern "C" {
#endif
// match the expression '"unixtime"[ \t]*\:[ \t]*[0-9]+'
match_t match_unixtime_all(unsigned long long* position,read_callback callback, void* callback_state);
// match the expression '[0-9]+'
match_t match_unixtime_value(unsigned long long* position,read_callback callback, void* callback_state);
#ifdef __cplusplus
}
#endif
#endif
