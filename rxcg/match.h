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
#ifndef MATCH_int8
	#define MATCH_int8 char
	#define MATCH_uint8 unsigned char
	#define MATCH_int16 short
	#define MATCH_uint16 unsigned short
	#define MATCH_int32 int
	#define MATCH_uint32 unsigned int
#endif
// Represents the capture information
typedef struct PREFIXmatch {
	// the captured text, as unicode codepoints
	TYPE capture[MAX_SIZE];
	// the position in the text, as codepoints
	unsigned long long position;
	// the length of the capture buffer, in elements
	size_t length;
} PREFIXmatch_t;
// a callback to read the input
typedef MATCH_int32(*PREFIXread_callback)(unsigned long long* out_advance,void* state);
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
MATCH_int32 PREFIXstring_read_callback(unsigned long long* out_advance, void* state);
// an implementation of a callback over a UTF-8 file (FILE*)
MATCH_int32 PREFIXfile_read_callback(unsigned long long* out_advance, void* state);
#ifdef __cplusplus
}
#endif
#endif
