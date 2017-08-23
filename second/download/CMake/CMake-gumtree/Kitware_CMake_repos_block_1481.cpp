{
		archive_set_error(a, ENOMEM, "No memory");
		free(mine);
		free(b);
		return (ARCHIVE_FATAL);
	}