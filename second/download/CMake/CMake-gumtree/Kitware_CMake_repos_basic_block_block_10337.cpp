{
		__archive_read_filter_consume(self->upstream,
		    state->unconsumed_bytes);
		state->unconsumed_bytes = 0;
	}