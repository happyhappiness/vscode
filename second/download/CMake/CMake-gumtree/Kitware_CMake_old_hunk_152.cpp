	if (state->child == NULL) {
		child_stop(self, state);
		free(state->out_buf);
		free(state);
		archive_set_error(&self->archive->archive, EINVAL,
		    "Can't initialize filter; unable to run program \"%s\"",