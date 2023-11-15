#if 0
INT32 PREFIXstring_read_callback(unsigned long long* out_advance, void* state) {
	PREFIXstring_cb_state_t* ps = (PREFIXstring_cb_state_t*)state;
	INT32 cp = 0;
	if (!*ps->sz) {
		*out_advance = 0;
		return -1;
	}
	UINT8 data = (UINT8)*ps->sz;
	if ((data & 128) == 0) {
		cp = ((UINT32)*ps->sz & ~128);
		*out_advance = 1;
	}

	if ((data & 224) == 192) {
		cp = ((UINT32)ps->sz[0] & ~224) << 6 |
			((UINT32)ps->sz[1] & ~192);
		*out_advance = 2;
	}

	if ((data & 240) == 224) {
		cp = ((UINT32)ps->sz[0] & ~240) << 12 |
			((UINT32)ps->sz[1] & ~192) << 6 |
			((UINT32)ps->sz[2] & ~192);
		*out_advance = 3;
	}

	if ((data & 248) == 240) {
		cp = ((UINT32)ps->sz[0] & ~248) << 18 |
			((UINT32)ps->sz[1] & ~192) << 12 |
			((UINT32)ps->sz[2] & ~192) << 6 |
			((UINT32)ps->sz[3] & ~192);
		*out_advance = 4;
	}
	ps->sz += *out_advance;

	return cp;
}
INT32 PREFIXfile_read_callback(unsigned long long* out_advance, void* state) {
	FILE* h = (FILE*)state;
	INT32 cp = 0;
	int i = fgetc(h);
	if (i == -1) {
		*out_advance = 0;
		return -1;
	}
	UINT8 data = (UINT8)i;
	if ((data & 128) == 0) {
		cp = ((UINT32)i & ~128);
		*out_advance = 1;
	}

	if ((data & 224) == 192) {
		cp = ((UINT32)i & ~224) << 6 |
			((UINT32)fgetc(h) & ~192);
		*out_advance = 2;
	}

	if ((data & 240) == 224) {
		cp = ((UINT32)i & ~240) << 12 |
			((UINT32)fgetc(h) & ~192) << 6 |
			((UINT32)fgetc(h) & ~192);
		*out_advance = 3;
	}

	if ((data & 248) == 240) {
		cp = ((UINT32)i & ~248) << 18 |
			((UINT32)fgetc(h) & ~192) << 12 |
			((UINT32)fgetc(h) & ~192) << 6 |
			((UINT32)fgetc(h) & ~192);
		*out_advance = 4;
	}
	return cp;
}
#endif
