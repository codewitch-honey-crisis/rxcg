// example_svg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include "svg.h"	
// a container for the string cursor state
typedef struct string_cb_state {
	char* sz;
} string_cb_state_t;

int32_t string_read_callback(unsigned long long* out_advance, void* state) {
	string_cb_state_t* ps = (string_cb_state_t*)state;
	int32_t cp = 0;
	if (!*ps->sz) {
		*out_advance = 0;
		return -1;
	}
	uint8_t data = (svg_uint8)*ps->sz;
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
int main(int argc, char** argv) {
#if 1
	const char* test = "a1234 foobar /*5678 abc123 */ - while damn";
	unsigned long long pos = 0;
	string_cb_state_t st;
	st.sz = test;
	while (1) {
		match_t c = match_Keyword(&pos, string_read_callback, &st);
		if (0 == c.length) {
			return 0;
		}
		for (size_t i = 0; i < c.length; ++i) {
			putc((char)c.capture[i], stdout);
		}
		printf("\n");
	}
#endif
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
