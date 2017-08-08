{
		archive_set_error(&a->archive, errno, "getvfsbyname failed");
		return (ARCHIVE_FAILED);
	}