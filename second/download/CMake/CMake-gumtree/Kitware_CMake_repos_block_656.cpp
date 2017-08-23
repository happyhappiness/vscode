{
		/* waitpid() failed?  This is ugly. */
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Child process exited badly");
		return (ARCHIVE_WARN);
	}