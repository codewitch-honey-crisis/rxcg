#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "worldtime_json.h"
static char* json = "{\"abbreviation\":\"PST\",\"client_ip\":\"redacted\",\"datetime\":\"2023-11-14T23:21:30.286241-08:00\",\"day_of_week\":2,\"day_of_year\":318,\"dst\":false,\"dst_from\":null,\"dst_offset\":0,\"dst_until\":null,\"raw_offset\":-28800,\"timezone\":\"America/Los_Angeles\",\"unixtime\":1700032890,\"utc_datetime\":\"2023-11-15T07:21:30.286241+00:00\",\"utc_offset\":\"-08:00\",\"week_number\":46}";
typedef struct string_cb_state {
	char* sz;
} string_cb_state_t;
int32_t string_callback(unsigned long long* out_advance, void* state) {
	string_cb_state_t* ps = (string_cb_state_t*)state;
	int32_t cp = 0;
	if (!*ps->sz) {
		*out_advance = 0;
		return -1;
	}
	uint8_t byte = (uint8_t)*ps->sz;
	if ((byte & 128) == 0) {
		cp = ((uint32_t)*ps->sz & ~128);
		*out_advance = 1;
	}

	if ((byte & 224) == 192) {
		cp = ((uint32_t)ps->sz[0] & ~224) << 6 |
			((uint32_t)ps->sz[1] & ~192);
		*out_advance = 2;
	}

	if ((byte & 240) == 224) {
		cp = ((uint32_t)ps->sz[0] & ~240) << 12 |
			((uint32_t)ps->sz[1] & ~192) << 6 |
			((uint32_t)ps->sz[2] & ~192);
		*out_advance = 3;
	}

	if ((byte & 248) == 240) {
		cp = ((uint32_t)ps->sz[0] & ~248) << 18 |
			((uint32_t)ps->sz[1] & ~192) << 12 |
			((uint32_t)ps->sz[2] & ~192) << 6 |
			((uint32_t)ps->sz[3] & ~192);
		*out_advance = 4;
	}
	ps->sz += *out_advance;

	return cp;
}
typedef struct capture_cb_state {
	int32_t* p;
	size_t pos;
	size_t len;
} capture_cb_state_t;
int32_t capture_callback(unsigned long long* out_advance, void* state) {
	capture_cb_state_t* ps = (capture_cb_state_t*)state;
	int32_t cp = 0;
	if (ps->pos == ps->len) {
		return -1;
	}
	cp = *(ps->p + ps->pos);
	++ps->pos;
	return cp;
}

static char tmp[257];
int main(int argc, char** argv) {
	string_cb_state_t scbs;
	scbs.sz = json;
	long long pos = 0;
	match_t m = match_unixtime_all(&pos, string_callback, &scbs);
	if (m.length == 0) {
		puts("Not found");
		return 1;
	}
	pos = 0;
	capture_cb_state_t ccbs;
	ccbs.len = m.length;
	ccbs.p = m.capture;
	ccbs.pos = 0;
	m = match_value(&pos, capture_callback, &ccbs);
	if (m.length == 0) {
		puts("Value not found");
		return 1;
	}
	int i;
	for (i = 0; i < m.length; ++i) {
		tmp[i] = m.capture[i];
	}
	tmp[i] = 0;
	time_t tim = (time_t)atol(tmp);
	
	puts(asctime(localtime(&tim)));

	scbs.sz = json;
	m = match_raw_offset_all(&pos, string_callback, &scbs);
	if (m.length == 0) {
		puts("Not found");
		return 1;
	}
	ccbs.len = m.length;
	ccbs.p = m.capture;
	ccbs.pos = 0;
	m = match_value(&pos, capture_callback, &ccbs);
	if (m.length == 0) {
		puts("Value not found");
		return 1;
	}
	for (i = 0; i < m.length; ++i) {
		tmp[i] = m.capture[i];
	}
	long tz = atol(tmp)/3600/10000;
	printf("TZ: GMT %d\r\n", tz);

	return 0;
}