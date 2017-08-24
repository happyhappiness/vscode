(state->uncompressed_size == state->compressed_size) {
		*p = b;
		state->total_out += state->compressed_size;
		state->unconsumed_bytes = state->compressed_size;
		return ((ssize_t)state->uncompressed_size);
	}