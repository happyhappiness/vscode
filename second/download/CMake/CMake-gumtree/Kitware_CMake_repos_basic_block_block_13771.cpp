(as->buffer_length < 8192)
		/* Buffers under 8k are doubled for speed. */
		new_length = as->buffer_length + as->buffer_length