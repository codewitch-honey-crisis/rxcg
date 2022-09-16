static MATCH_capture_t MATCH_runnerBIT_WIDTH(TYPE* dfa, TYPE* blockEnd, unsigned long long* position, MATCH_callback callback, void* callback_state) {
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
				if (blockEnd != NULL) {
					state = 0;
					while (ch != -1) {
						acc = -1;
						done = 0;
						while (!done) {
start_block_end:
							done = 1;
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
							acc = (TYPE)pgm_read_TYPE2((UTYPE*)(blockEnd + (state++)));
							tlen = (TYPE)pgm_read_TYPE2((UTYPE*)(blockEnd + (state++)));
#else
							acc = blockEnd[state++];
							tlen = blockEnd[state++];
#endif
							for (i = 0; i < tlen; ++i) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
								tto = (TYPE)pgm_read_TYPE2((UTYPE*)(blockEnd + (state++)));
								prlen = (TYPE)pgm_read_TYPE2((UTYPE*)(blockEnd + (state++)));
#else
								tto = blockEnd[state++];
								prlen = blockEnd[state++];
#endif
								for (j = 0; j < prlen; ++j) {
#if defined(ARDUINO) && !defined(CORE_TEENSY) && !defined(ESP32)
									pmin = (TYPE)pgm_read_TYPE2((UTYPE*)(blockEnd + (state++)));
									pmax = (TYPE)pgm_read_TYPE2((UTYPE*)(blockEnd + (state++)));
#else
									pmin = blockEnd[state++];
									pmax = blockEnd[state++];
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
										goto start_block_end;

									}
								}
							}
						}
						if (acc != -1) {
							return result;
						}
						else {
							if (result.length < MAX_SIZE) {
								result.capture[result.length++] = ch;
							}
							ch = callback(&adv, callback_state);
							++cursor_pos;
						}
						state = 0;
					}
					state = 0;
					continue;
				}
				else {
					if (result.length > 0) {
						return result;
					}
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
