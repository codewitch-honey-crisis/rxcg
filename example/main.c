#include <stdint.h>
#include <stdio.h>
#include "Example.h"
typedef struct string_cb_state {
    char* sz;
} string_cb_state_t;

int32_t string_callback(unsigned long long* out_advance, void* state) {
    string_cb_state_t* ps = (string_cb_state_t*)state;
    int32_t cp=0;
    if (!*ps->sz) {
        *out_advance = 0;
        return -1;
    }
    uint8_t byte = (uint8_t)*ps->sz;
    if ((byte & 128) == 0) {
        cp = ((uint32_t) *ps->sz & ~128);
		*out_advance = 1;
	}

	if ((byte & 224) == 192) {
        cp=((uint32_t) ps->sz[0] & ~224) << 6 |
		((uint32_t) ps->sz[1] & ~192);
		*out_advance = 2;
	}

	if ((byte & 240) == 224) {
		cp=((uint32_t) ps->sz[0] & ~240) << 12 |
        ((uint32_t) ps->sz[1] & ~192) << 6 |
        ((uint32_t) ps->sz[2] & ~192);
        *out_advance = 3;
	}

	if ((byte & 248) == 240) {
		cp=((uint32_t) ps->sz[0] & ~248) << 18 |
				((uint32_t) ps->sz[1] & ~192) << 12 |
				((uint32_t) ps->sz[2] & ~192) << 6 |
				((uint32_t) ps->sz[3] & ~192);
        *out_advance = 4;
	}
    ps->sz+=*out_advance;
	
    return cp;
}
int32_t file_callback(unsigned long long* out_advance, void* state) {
    FILE* h = (FILE*)state;
    int32_t cp = 0;
    int i = fgetc(h);
    if (i==-1) {
        *out_advance = 0;
        return -1;
    }
    uint8_t byte = (uint8_t)i;
    if ((byte & 128) == 0) {
        cp = ((uint32_t) i & ~128);
		*out_advance = 1;
	}

	if ((byte & 224) == 192) {
        cp=((uint32_t) i & ~224) << 6 |
		((uint32_t) fgetc(h) & ~192);
		*out_advance = 2;
	}

	if ((byte & 240) == 224) {
		cp=((uint32_t) i & ~240) << 12 |
        ((uint32_t) fgetc(h) & ~192) << 6 |
        ((uint32_t) fgetc(h) & ~192);
        *out_advance = 3;
	}

	if ((byte & 248) == 240) {
		cp=((uint32_t) i & ~248) << 18 |
				((uint32_t) fgetc(h) & ~192) << 12 |
				((uint32_t) fgetc(h) & ~192) << 6 |
				((uint32_t) fgetc(h) & ~192);
        *out_advance = 4;
	}
    return cp;
}

int main(int argc, char** argv) {
    char* test = "a1234 foobar /*5678 abc123 */ -";
    unsigned long long pos = 0;
    string_cb_state_t st;
    st.sz = test;
    while (1) {
        Example_match_t c = match_CommentBlock(&pos, string_callback, &st);
        if (0 == c.length) {
            return 0;
        }
        for(size_t i = 0;i<c.length;++i) {
            printf("%c",(char)c.capture[i]);
        }
        printf("\n");
    }
    return 0;
}