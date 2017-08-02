{
		archive_set_error(a, ENOMEM, "No memory");
		free(mine);
		free(buffer);
		return (ARCHIVE_FATAL);
	}