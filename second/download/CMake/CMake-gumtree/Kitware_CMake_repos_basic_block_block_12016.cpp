{
		strm->ds = calloc(1, sizeof(*strm->ds));
		if (strm->ds == NULL)
			return (ARCHIVE_FATAL);
	}