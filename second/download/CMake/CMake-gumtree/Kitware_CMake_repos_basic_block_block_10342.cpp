{
		p = __archive_read_filter_ahead(upstream,
		    state->signature_len, NULL);
		if (p == NULL)
			return (0);
		/* No match, so don't bid. */
		if (memcmp(p, state->signature, state->signature_len) != 0)
			return (0);
		return ((int)state->signature_len * 8);
	}