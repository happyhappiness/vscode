{
		state->bits++;
		state->bytes_in_section = 0;
		if (state->bits == state->maxcode_bits)
			state->section_end_code = state->maxcode;
		else
			state->section_end_code = (1 << state->bits) - 1;
	}