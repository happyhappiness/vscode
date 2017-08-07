{
		archive_set_error(&a->archive, errno,
		    "Failed to mkstemp");
		archive_string_free(&tmpdatafork);
		return (-1);
	}