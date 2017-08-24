{
	struct program_filter *state;
	ssize_t bytes;
	size_t total;
	char *p;

	state = (struct program_filter *)self->data;

	total = 0;
	p = state->out_buf;
	while (state->child_stdout != -1 && total < state->out_buf_len) {
		bytes = child_read(self, p, state->out_buf_len - total);
		if (bytes < 0)
			/* No recovery is possible if we can no longer
			 * read from the child. */
			return (ARCHIVE_FATAL);
		if (bytes == 0)
			/* We got EOF from the child. */
			break;
		total += bytes;
		p += bytes;
	}

	*buff = state->out_buf;
	return (total);
}