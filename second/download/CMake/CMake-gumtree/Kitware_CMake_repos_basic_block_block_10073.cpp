{
		/* If the input is corrupted or truncated, fail. */
		archive_set_error(a, errno,
		    "Error seeking in a file descriptor(%d)", mine->fd);
		return (ARCHIVE_FATAL);
	}