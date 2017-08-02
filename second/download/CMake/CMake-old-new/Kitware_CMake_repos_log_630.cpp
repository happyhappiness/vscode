archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC,
		    "Child process exited with status %d",
		    WEXITSTATUS(state->exit_status))