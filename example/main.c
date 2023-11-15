#include <stdint.h>
#include <stdio.h>
#include "Example.h"
// a container for the string cursor state
typedef struct string_cb_state {
	char* sz;
} string_cb_state_t;

Example_int32 string_read_callback(unsigned long long* out_advance, void* state) {
	string_cb_state_t* ps = (string_cb_state_t*)state;
	Example_int32 cp = 0;
	if (!*ps->sz) {
		*out_advance = 0;
		return -1;
	}
	Example_uint8 byte = (Example_uint8)*ps->sz;
	if ((byte & 128) == 0) {
		cp = ((Example_uint32)*ps->sz & ~128);
		*out_advance = 1;
	}

	if ((byte & 224) == 192) {
		cp = ((Example_uint32)ps->sz[0] & ~224) << 6 |
			((Example_uint32)ps->sz[1] & ~192);
		*out_advance = 2;
	}

	if ((byte & 240) == 224) {
		cp = ((Example_uint32)ps->sz[0] & ~240) << 12 |
			((Example_uint32)ps->sz[1] & ~192) << 6 |
			((Example_uint32)ps->sz[2] & ~192);
		*out_advance = 3;
	}

	if ((byte & 248) == 240) {
		cp = ((Example_uint32)ps->sz[0] & ~248) << 18 |
			((Example_uint32)ps->sz[1] & ~192) << 12 |
			((Example_uint32)ps->sz[2] & ~192) << 6 |
			((Example_uint32)ps->sz[3] & ~192);
		*out_advance = 4;
	}
	ps->sz += *out_advance;

	return cp;
}
int main(int argc, char** argv) {
#if 1
    char* test = "a1234 foobar /*5678 abc123 */ - while damn";
    unsigned long long pos = 0;
    string_cb_state_t st;
    st.sz = test;
    while (1) {
        match_t c = match_Keyword(&pos, string_read_callback, &st);
        if (0 == c.length) {
            return 0;
        }
        for(size_t i = 0;i<c.length;++i) {
            putc((char)c.capture[i],stdout);
        }
        printf("\n");
    }
#endif
    return 0;
}
