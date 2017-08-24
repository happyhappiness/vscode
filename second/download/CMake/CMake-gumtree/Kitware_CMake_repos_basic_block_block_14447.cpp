{
	struct private_data *state = f->data;

	state->compressed[state->compressed_offset++] = c;
	++state->out_count;

	if (state->compressed_buffer_size == state->compressed_offset) {
		int ret = __archive_write_filter(f->next_filter,
		    state->compressed, state->compressed_buffer_size);
		if (ret != ARCHIVE_OK)
			return ARCHIVE_FATAL;
		state->compressed_offset = 0;
	}

	return ARCHIVE_OK;
}