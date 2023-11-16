// worldtime_json.c
#include "worldtime_json.h"
static int8_t unixtime_all_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, '\"', '\"', -1, 1, 12, 1, 
	'u', 'u', -1, 1, 18, 1, 'n', 'n', -1, 1, 
	24, 1, 'i', 'i', -1, 1, 30, 1, 'x', 'x', 
	-1, 1, 36, 1, 't', 't', -1, 1, 42, 1, 
	'i', 'i', -1, 1, 48, 1, 'm', 'm', -1, 1, 
	54, 1, 'e', 'e', -1, 1, 60, 1, '\"', '\"', 
	-1, 2, 60, 2, '\t', '\t', ' ', ' ', 72, 1, 
	':', ':', -1, 2, 72, 2, '\t', '\t', ' ', ' ', 
	84, 1, '0', '9', 0, 1, 84, 1, '0', '9'
};
static int8_t unixtime_value_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, '0', '9', 1, 1, 6, 1, 
	'0', '9'
};
static match_t worldtime_json_runner8(int8_t* dfa, unsigned long long* position, read_callback callback, void* callback_state) {
	match_t result;
	result.position = 0;
	result.length = 0;
	unsigned long long adv = 0;
	int tlen;
	int8_t tto;
	int8_t prlen;
	int8_t pmin;
	int8_t pmax;
	int i, j;
	int32_t ch;
	int8_t state = 0;
	int8_t acc = -1;
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
			acc = (int8_t)pgm_read_byte((uint8_t*)(dfa + (state++)));
			tlen = (int8_t)pgm_read_byte((uint8_t*)(dfa + (state++)));
#else
			acc = dfa[state++];
			tlen = dfa[state++];
#endif
			for (i = 0; i < tlen; ++i) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
				tto = (int8_t)pgm_read_byte((uint8_t*)(dfa + (state++)));
				prlen = (int8_t)pgm_read_byte((uint8_t*)(dfa + (state++)));
#else
				tto = dfa[state++];
				prlen = dfa[state++];
#endif
				for (j = 0; j < prlen; ++j) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
					pmin = (int8_t)pgm_read_byte((uint8_t*)(dfa + (state++)));
					pmax = (int8_t)pgm_read_byte((uint8_t*)(dfa + (state++)));
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
match_t match_unixtime_all(unsigned long long* position,read_callback callback, void* callback_state) {
	return worldtime_json_runner8(unixtime_all_dfa, position, callback, callback_state);
}
match_t match_unixtime_value(unsigned long long* position,read_callback callback, void* callback_state) {
	return worldtime_json_runner8(unixtime_value_dfa, position, callback, callback_state);
}
#if 0
int32_t string_read_callback(unsigned long long* out_advance, void* state) {
	string_cb_state_t* ps = (string_cb_state_t*)state;
	int32_t cp = 0;
	if (!*ps->sz) {
		*out_advance = 0;
		return -1;
	}
	uint8_t data = (uint8_t)*ps->sz;
	if ((data & 128) == 0) {
		cp = ((uint32_t)*ps->sz & ~128);
		*out_advance = 1;
	}

	if ((data & 224) == 192) {
		cp = ((uint32_t)ps->sz[0] & ~224) << 6 |
			((uint32_t)ps->sz[1] & ~192);
		*out_advance = 2;
	}

	if ((data & 240) == 224) {
		cp = ((uint32_t)ps->sz[0] & ~240) << 12 |
			((uint32_t)ps->sz[1] & ~192) << 6 |
			((uint32_t)ps->sz[2] & ~192);
		*out_advance = 3;
	}

	if ((data & 248) == 240) {
		cp = ((uint32_t)ps->sz[0] & ~248) << 18 |
			((uint32_t)ps->sz[1] & ~192) << 12 |
			((uint32_t)ps->sz[2] & ~192) << 6 |
			((uint32_t)ps->sz[3] & ~192);
		*out_advance = 4;
	}
	ps->sz += *out_advance;

	return cp;
}
int32_t file_read_callback(unsigned long long* out_advance, void* state) {
	FILE* h = (FILE*)state;
	int32_t cp = 0;
	int i = fgetc(h);
	if (i == -1) {
		*out_advance = 0;
		return -1;
	}
	uint8_t data = (uint8_t)i;
	if ((data & 128) == 0) {
		cp = ((uint32_t)i & ~128);
		*out_advance = 1;
	}

	if ((data & 224) == 192) {
		cp = ((uint32_t)i & ~224) << 6 |
			((uint32_t)fgetc(h) & ~192);
		*out_advance = 2;
	}

	if ((data & 240) == 224) {
		cp = ((uint32_t)i & ~240) << 12 |
			((uint32_t)fgetc(h) & ~192) << 6 |
			((uint32_t)fgetc(h) & ~192);
		*out_advance = 3;
	}

	if ((data & 248) == 240) {
		cp = ((uint32_t)i & ~248) << 18 |
			((uint32_t)fgetc(h) & ~192) << 12 |
			((uint32_t)fgetc(h) & ~192) << 6 |
			((uint32_t)fgetc(h) & ~192);
		*out_advance = 4;
	}
	return cp;
}
#endif
