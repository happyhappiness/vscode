{
		while (state->hold_len < LBYTES && length > 0) {
			state->hold[state->hold_len++] = *p++;
			length--;
		}
		if (state->hold_len < LBYTES)
			return (ret);
		uu_encode(&state->encoded_buff, state->hold, LBYTES);
		state->hold_len = 0;
	}