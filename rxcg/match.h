// FILENAME
// generated with rxcg https://github.com/codewitch-honey-crisis/rxcg
// on TIMESTAMP
#ifndef MATCH_H_HEADER
#define MATCH_H_HEADER
#include <stddef.h>
#ifdef ARDUINO
#include <Arduino.h>
#ifndef ESP32
#ifndef CORE_TEENSY
#include <avr/progmem.h>
#endif
#endif
#endif
INTDEFS
// Represents the capture information
typedef struct PREFIXmatch {
	// the captured text, as unicode codepoints
	INT32 capture[MAX_SIZE];
	// the position in the text, as codepoints
	unsigned long long position;
	// the length of the capture buffer, in elements
	size_t length;
} PREFIXmatch_t;
// a callback to read the input
typedef INT32(*PREFIXread_callback)(unsigned long long* out_advance,void* state);
#if 0
#include <stdio.h>
// a container for the string cursor state
typedef struct PREFIXstring_cb_state {
	char* sz;
} PREFIXstring_cb_state_t;
#ifdef __cplusplus
extern "C" {
#endif
// an implementation of a callback over a UTF-8 string (char*)
INT32 PREFIXstring_read_callback(unsigned long long* out_advance, void* state);
// an implementation of a callback over a UTF-8 file (FILE*)
INT32 PREFIXfile_read_callback(unsigned long long* out_advance, void* state);
#ifdef __cplusplus
}
#endif
#endif
