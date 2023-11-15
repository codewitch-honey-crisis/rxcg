// worldtime_json.c
#include "worldtime_json.h"
static worldtime_json_int8 unixtime_all_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 34, 34, -1, 1, 12, 1, 
	117, 117, -1, 1, 18, 1, 110, 110, -1, 1, 
	24, 1, 105, 105, -1, 1, 30, 1, 120, 120, 
	-1, 1, 36, 1, 116, 116, -1, 1, 42, 1, 
	105, 105, -1, 1, 48, 1, 109, 109, -1, 1, 
	54, 1, 101, 101, -1, 1, 60, 1, 34, 34, 
	-1, 2, 60, 2, 9, 9, 32, 32, 72, 1, 
	58, 58, -1, 2, 72, 2, 9, 9, 32, 32, 
	84, 1, 48, 57, 0, 1, 84, 1, 48, 57
};
static worldtime_json_int8 unixtime_value_dfa[]
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
PROGMEM
#endif
 = {
	-1, 1, 6, 1, 48, 57, 1, 1, 6, 1, 
	48, 57
};
static match_t worldtime_json_runner8(worldtime_json_int8* dfa, unsigned long long* position, read_callback callback, void* callback_state) {
	match_t result;
	result.position = 0;
	result.length = 0;
	unsigned long long adv = 0;
	int tlen;
	worldtime_json_int8 tto;
	worldtime_json_int8 prlen;
	worldtime_json_int8 pmin;
	worldtime_json_int8 pmax;
	worldtime_json_int32 i, j;
	worldtime_json_int32 ch;
	worldtime_json_int8 state = 0;
	worldtime_json_int8 acc = -1;
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
			acc = (worldtime_json_int8)pgm_read_byte((worldtime_json_uint8*)(dfa + (state++)));
			tlen = (worldtime_json_int8)pgm_read_byte((worldtime_json_uint8*)(dfa + (state++)));
#else
			acc = dfa[state++];
			tlen = dfa[state++];
#endif
			for (i = 0; i < tlen; ++i) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
				tto = (worldtime_json_int8)pgm_read_byte((worldtime_json_uint8*)(dfa + (state++)));
				prlen = (worldtime_json_int8)pgm_read_byte((worldtime_json_uint8*)(dfa + (state++)));
#else
				tto = dfa[state++];
				prlen = dfa[state++];
#endif
				for (j = 0; j < prlen; ++j) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
					pmin = (worldtime_json_int8)pgm_read_byte((worldtime_json_uint8*)(dfa + (state++)));
					pmax = (worldtime_json_int8)pgm_read_byte((worldtime_json_uint8*)(dfa + (state++)));
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
worldtime_json_int32 string_read_callback(unsigned long long* out_advance, void* state) {
	string_cb_state_t* ps = (string_cb_state_t*)state;
	worldtime_json_int32 cp = 0;
	if (!*ps->sz) {
		*out_advance = 0;
		return -1;
	}
	worldtime_json_uint8 byte = (worldtime_json_uint8)*ps->sz;
	if ((byte & 128) == 0) {
		cp = ((worldtime_json_uint32)*ps->sz & ~128);
		*out_advance = 1;
	}

	if ((byte & 224) == 192) {
		cp = ((worldtime_json_uint32)ps->sz[0] & ~224) << 6 |
			((worldtime_json_uint32)ps->sz[1] & ~192);
		*out_advance = 2;
	}

	if ((byte & 240) == 224) {
		cp = ((worldtime_json_uint32)ps->sz[0] & ~240) << 12 |
			((worldtime_json_uint32)ps->sz[1] & ~192) << 6 |
			((worldtime_json_uint32)ps->sz[2] & ~192);
		*out_advance = 3;
	}

	if ((byte & 248) == 240) {
		cp = ((worldtime_json_uint32)ps->sz[0] & ~248) << 18 |
			((worldtime_json_uint32)ps->sz[1] & ~192) << 12 |
			((worldtime_json_uint32)ps->sz[2] & ~192) << 6 |
			((worldtime_json_uint32)ps->sz[3] & ~192);
		*out_advance = 4;
	}
	ps->sz += *out_advance;

	return cp;
}
worldtime_json_int32 file_read_callback(unsigned long long* out_advance, void* state) {
	FILE* h = (FILE*)state;
	worldtime_json_int32 cp = 0;
	int i = fgetc(h);
	if (i == -1) {
		*out_advance = 0;
		return -1;
	}
	worldtime_json_uint8 byte = (worldtime_json_uint8)i;
	if ((byte & 128) == 0) {
		cp = ((worldtime_json_uint32)i & ~128);
		*out_advance = 1;
	}

	if ((byte & 224) == 192) {
		cp = ((worldtime_json_uint32)i & ~224) << 6 |
			((worldtime_json_uint32)fgetc(h) & ~192);
		*out_advance = 2;
	}

	if ((byte & 240) == 224) {
		cp = ((worldtime_json_uint32)i & ~240) << 12 |
			((worldtime_json_uint32)fgetc(h) & ~192) << 6 |
			((worldtime_json_uint32)fgetc(h) & ~192);
		*out_advance = 3;
	}

	if ((byte & 248) == 240) {
		cp = ((worldtime_json_uint32)i & ~248) << 18 |
			((worldtime_json_uint32)fgetc(h) & ~192) << 12 |
			((worldtime_json_uint32)fgetc(h) & ~192) << 6 |
			((worldtime_json_uint32)fgetc(h) & ~192);
		*out_advance = 4;
	}
	return cp;
}
#endif
