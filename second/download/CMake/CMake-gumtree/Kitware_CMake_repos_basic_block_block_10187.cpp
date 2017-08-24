{
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