{
		*state->stackp++ = state->suffix[code];
		code = state->prefix[code];
	}