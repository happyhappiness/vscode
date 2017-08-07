{
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate input data");
		if (state != NULL) {
			archive_string_free(&state->description);
			free(state);
		}
		free(out_buf);
		return (ARCHIVE_FATAL);
	}