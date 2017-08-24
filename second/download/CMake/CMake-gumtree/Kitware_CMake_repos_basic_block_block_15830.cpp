{
		r = isofile_register_hardlink(a, file);
		if (r != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}