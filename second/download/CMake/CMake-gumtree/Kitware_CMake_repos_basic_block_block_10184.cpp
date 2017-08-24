(code < state->maxcode && state->oldcode >= 0) {
		state->prefix[code] = state->oldcode;
		state->suffix[code] = state->finbyte;
		++state->free_ent;
	}