static int
next_code(struct archive_read_filter *self)
{
	struct private_data *state = (struct private_data *)self->data;
	int code, newcode;

	static int debug_buff[1024];
	static unsigned debug_index;

	code = newcode = getbits(self, state->bits);
	if (code < 0)
		return (code);

	debug_buff[debug_index++] = code;
	if (debug_index >= sizeof(debug_buff)/sizeof(debug_buff[0]))
		debug_index = 0;

	/* If it's a reset code, reset the dictionary. */
	if ((code == 256) && state->use_reset_code) {
		/*
		 * The original 'compress' implementation blocked its
		 * I/O in a manner that resulted in junk bytes being
		 * inserted after every reset.  The next section skips
		 * this junk.  (Yes, the number of *bytes* to skip is
		 * a function of the current *bit* length.)
		 */
		int skip_bytes =  state->bits -
		    (state->bytes_in_section % state->bits);
		skip_bytes %= state->bits;
		state->bits_avail = 0; /* Discard rest of this byte. */
		while (skip_bytes-- > 0) {
			code = getbits(self, 8);
			if (code < 0)
				return (code);
		}
		/* Now, actually do the reset. */
		state->bytes_in_section = 0;
		state->bits = 9;
		state->section_end_code = (1 << state->bits) - 1;
		state->free_ent = 257;
		state->oldcode = -1;
		return (next_code(self));
	}

	if (code > state->free_ent
	    || (code == state->free_ent && state->oldcode < 0)) {
		/* An invalid code is a fatal error. */
		archive_set_error(&(self->archive->archive), -1,
		    "Invalid compressed data");
		return (ARCHIVE_FATAL);
	}

	/* Special case for KwKwK string. */
	if (code >= state->free_ent) {
		*state->stackp++ = state->finbyte;
		code = state->oldcode;
	}

	/* Generate output characters in reverse order. */
	while (code >= 256) {
		*state->stackp++ = state->suffix[code];
		code = state->prefix[code];
	}
	*state->stackp++ = state->finbyte = code;

	/* Generate the new entry. */
	code = state->free_ent;
	if (code < state->maxcode && state->oldcode >= 0) {
		state->prefix[code] = state->oldcode;
		state->suffix[code] = state->finbyte;
		++state->free_ent;
	}
	if (state->free_ent > state->section_end_code) {
		state->bits++;
		state->bytes_in_section = 0;
		if (state->bits == state->maxcode_bits)
			state->section_end_code = state->maxcode;
		else
			state->section_end_code = (1 << state->bits) - 1;
	}

	/* Remember previous code. */
	state->oldcode = newcode;
	return (ARCHIVE_OK);
}