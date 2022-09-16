#if 0
MATCH_int32 MATCH_string_callback(unsigned long long* out_advance, void* state) {
	MATCH_string_cb_state_t* ps = (MATCH_string_cb_state_t*)state;
	MATCH_int32 cp = 0;
	if (!*ps->sz) {
		*out_advance = 0;
		return -1;
	}
	MATCH_uint8 byte = (MATCH_uint8)*ps->sz;
	if ((byte & 128) == 0) {
		cp = ((MATCH_uint32)*ps->sz & ~128);
		*out_advance = 1;
	}

	if ((byte & 224) == 192) {
		cp = ((MATCH_uint32)ps->sz[0] & ~224) << 6 |
			((MATCH_uint32)ps->sz[1] & ~192);
		*out_advance = 2;
	}

	if ((byte & 240) == 224) {
		cp = ((MATCH_uint32)ps->sz[0] & ~240) << 12 |
			((MATCH_uint32)ps->sz[1] & ~192) << 6 |
			((MATCH_uint32)ps->sz[2] & ~192);
		*out_advance = 3;
	}

	if ((byte & 248) == 240) {
		cp = ((MATCH_uint32)ps->sz[0] & ~248) << 18 |
			((MATCH_uint32)ps->sz[1] & ~192) << 12 |
			((MATCH_uint32)ps->sz[2] & ~192) << 6 |
			((MATCH_uint32)ps->sz[3] & ~192);
		*out_advance = 4;
	}
	ps->sz += *out_advance;

	return cp;
}
MATCH_int32 MATCH_file_callback(unsigned long long* out_advance, void* state) {
	FILE* h = (FILE*)state;
	MATCH_int32 cp = 0;
	int i = fgetc(h);
	if (i == -1) {
		*out_advance = 0;
		return -1;
	}
	MATCH_uint8 byte = (MATCH_uint8)i;
	if ((byte & 128) == 0) {
		cp = ((MATCH_uint32)i & ~128);
		*out_advance = 1;
	}

	if ((byte & 224) == 192) {
		cp = ((MATCH_uint32)i & ~224) << 6 |
			((MATCH_uint32)fgetc(h) & ~192);
		*out_advance = 2;
	}

	if ((byte & 240) == 224) {
		cp = ((MATCH_uint32)i & ~240) << 12 |
			((MATCH_uint32)fgetc(h) & ~192) << 6 |
			((MATCH_uint32)fgetc(h) & ~192);
		*out_advance = 3;
	}

	if ((byte & 248) == 240) {
		cp = ((MATCH_uint32)i & ~248) << 18 |
			((MATCH_uint32)fgetc(h) & ~192) << 12 |
			((MATCH_uint32)fgetc(h) & ~192) << 6 |
			((MATCH_uint32)fgetc(h) & ~192);
		*out_advance = 4;
	}
	return cp;
}
#endif
