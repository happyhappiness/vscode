	struct program_filter	*state;
	static const size_t out_buf_len = 65536;
	char *out_buf;
	char *description;
	const char *prefix = "Program: ";

	state = (struct program_filter *)calloc(1, sizeof(*state));
	out_buf = (char *)malloc(out_buf_len);
	description = (char *)malloc(strlen(prefix) + strlen(cmd) + 1);
	if (state == NULL || out_buf == NULL || description == NULL) {
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate input data");
		free(state);
		free(out_buf);
		free(description);
		return (ARCHIVE_FATAL);
	}

	self->code = ARCHIVE_COMPRESSION_PROGRAM;
	state->description = description;
	strcpy(state->description, prefix);
	strcat(state->description, cmd);
	self->name = state->description;

	state->out_buf = out_buf;
	state->out_buf_len = out_buf_len;

	if ((state->child = __archive_create_child(cmd,
		 &state->child_stdin, &state->child_stdout)) == -1) {
		free(state->out_buf);
		free(state);
		archive_set_error(&self->archive->archive, EINVAL,
		    "Can't initialize filter; unable to run program \"%s\"", cmd);
		return (ARCHIVE_FATAL);
	}

	self->data = state;
	self->read = program_filter_read;
