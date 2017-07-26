	    &state->child_stdout);
	if (child == -1) {
		free(state->out_buf);
		archive_string_free(&state->description);
		free(state);
		archive_set_error(&self->archive->archive, EINVAL,
		    "Can't initialize filter; unable to run program \"%s\"",
