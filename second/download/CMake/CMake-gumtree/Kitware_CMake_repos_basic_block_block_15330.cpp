{
		if (mbs != NULL)
			archive_set_error(a, errno, "Failed to open '%s'", mbs);
		else
			archive_set_error(a, errno, "Failed to open '%S'", wcs);
		return (ARCHIVE_FATAL);
	}