(WIFEXITED(state->exit_status)) {
		if (WEXITSTATUS(state->exit_status) == 0)
			return (ARCHIVE_OK);

		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Child process exited with status %d",
		    WEXITSTATUS(state->exit_status));
		return (ARCHIVE_WARN);
	}