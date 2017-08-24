{
		state->prefix[code] = state->oldcode;
		state->suffix[code] = state->finbyte;
		++state->free_ent;
	}