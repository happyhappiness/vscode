(code = 255; code >= 0; code--) {
		state->prefix[code] = 0;
		state->suffix[code] = code;
	}