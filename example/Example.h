// generated with rxcg https://github.com/codewitch-honey-crisis/rxcg
#ifndef Example_H_HEADER
#define Example_H_HEADER
#include <stddef.h>
#ifdef ARDUINO
#include <Arduino.h>
#ifndef ESP32
#ifndef CORE_TEENSY
#include <avr/progmem.h>
#endif
#endif
#endif
#ifndef Example_int8
	#define Example_int8 char
	#define Example_uint8 unsigned char
	#define Example_int16 short
	#define Example_uint16 unsigned short
	#define Example_int32 int
	#define Example_uint32 unsigned int
#endif
// Represents the capture information
typedef struct Example_match {
	// the captured text, as unicode codepoints
	Example_int32 capture[256];
	// the position in the text, as codepoints
	unsigned long long position;
	// the length of the capture buffer, in elements
	size_t length;
} Example_match_t;
// a callback to read the input
typedef Example_int32(*Example_callback)(unsigned long long* out_advance,void* state);
#if 0
#include <stdio.h>
// a container for the string cursor state
typedef struct Example_string_cb_state {
	char* sz;
} Example_string_cb_state_t;
#ifdef __cplusplus
extern "C" {
#endif
// an implementation of a callback over a UTF-8 string (char*)
Example_int32 Example_string_callback(unsigned long long* out_advance, void* state);
// an implementation of a callback over a UTF-8 file (FILE*)
Example_int32 Example_file_callback(unsigned long long* out_advance, void* state);
#ifdef __cplusplus
}
#endif
#endif
#ifdef __cplusplus
extern "C" {
#endif
// match the expression '"([^\0-\x1F"\\]|\\([\\/bfnrt]|u[a-fA-F0-9]{4}))*"'
Example_match_t match_JsonStringLiteral(unsigned long long* position,Example_callback callback, void* callback_state);
// match the expression '@"([^"]|"")*"'
Example_match_t match_VerbatimStringLiteral(unsigned long long* position,Example_callback callback, void* callback_state);
// match the expression '"([^"]|"")*"'
Example_match_t match_StringLiteral(unsigned long long* position,Example_callback callback, void* callback_state);
// match the expression '[\']([^\']|\\.)([\'])'
Example_match_t match_CharacterLiteral(unsigned long long* position,Example_callback callback, void* callback_state);
// match the expression '(0x[0-9A-Fa-f]{1,16}|([0-9]+))([Uu][Ll]?|[Ll][Uu]?)?'
Example_match_t match_IntegerLiteral(unsigned long long* position,Example_callback callback, void* callback_state);
// match the expression '(([0-9]+)(\.[0-9]+)?([Ee][+-]?[0-9]+)?[DdMmFf]?)|((\.[0-9]+)([Ee][+-]?[0-9]+)?[DdMmFf]?)'
Example_match_t match_FloatLiteral(unsigned long long* position,Example_callback callback, void* callback_state);
// match the expression '[\t\r\n\v\f ]+'
Example_match_t match_Whitespace(unsigned long long* position,Example_callback callback, void* callback_state);
// match the expression '[_[:IsLetter:]][_[:IsLetterOrDigit:]]*'
Example_match_t match_Identifier(unsigned long long* position,Example_callback callback, void* callback_state);
// match the expression '[A-Z_a-z][0-9A-Z_a-z]*'
Example_match_t match_CIdentifier(unsigned long long* position,Example_callback callback, void* callback_state);
// match the expression "/*" (block end: "*/")
Example_match_t match_CommentBlock(unsigned long long* position,Example_callback callback, void* callback_state);
#ifdef __cplusplus
}
#endif
#endif
