static MATCH_capture_t MATCH_runnerBIT_WIDTH(TYPE* dfa, unsigned long long* position, MATCH_callback callback, void* callback_state) {
	MATCH_capture_t result;
	result.position = 0;
	result.length = 0;
	unsigned long long adv = 0;
	int tlen;
	TYPE tto;
	TYPE prlen;
	TYPE pmin;
	TYPE pmax;
	MATCH_int32 i, j;
	MATCH_int32 ch;
	TYPE state = 0;
	TYPE acc = -1;
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
			acc = (TYPE)pgm_read_TYPE2((UTYPE*)(dfa + (state++)));
			tlen = (TYPE)pgm_read_TYPE2((UTYPE*)(dfa + (state++)));
#else
			acc = dfa[state++];
			tlen = dfa[state++];
#endif
			for (i = 0; i < tlen; ++i) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
				tto = (TYPE)pgm_read_TYPE2((UTYPE*)(dfa + (state++)));
				prlen = (TYPE)pgm_read_TYPE2((UTYPE*)(dfa + (state++)));
#else
				tto = dfa[state++];
				prlen = dfa[state++];
#endif
				for (j = 0; j < prlen; ++j) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
					pmin = (TYPE)pgm_read_TYPE2((UTYPE*)(dfa + (state++)));
					pmax = (TYPE)pgm_read_TYPE2((UTYPE*)(dfa + (state++)));
#else
					pmin = dfa[state++];
					pmax = dfa[state++];
#endif
					if (ch < pmin) {
						break;
					}
					if (ch <= pmax) {
						if (result.length < MAX_SIZE) {
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
