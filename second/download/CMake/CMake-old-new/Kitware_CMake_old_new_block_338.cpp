{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate zip header data");
		free(l);
		return (ARCHIVE_FATAL);
	}