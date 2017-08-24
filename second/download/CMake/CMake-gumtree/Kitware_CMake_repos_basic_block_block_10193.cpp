{
		if (state->avail_in <= 0) {
			if (state->consume_unnotified) {
				__archive_read_filter_consume(self->upstream,
					state->consume_unnotified);
				state->consume_unnotified = 0;
			}
			state->next_in
			    = __archive_read_filter_ahead(self->upstream,
				1, &ret);
			if (ret == 0)
				return (-1);
			if (ret < 0 || state->next_in == NULL)
				return (ARCHIVE_FATAL);
			state->consume_unnotified = state->avail_in = ret;
		}
		state->bit_buffer |= *state->next_in++ << state->bits_avail;
		state->avail_in--;
		state->bits_avail += 8;
		state->bytes_in_section++;
	}