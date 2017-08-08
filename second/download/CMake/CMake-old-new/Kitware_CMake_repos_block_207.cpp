{
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for a mtree entry");
		*m_entry = NULL;
		return (ARCHIVE_FATAL);
	}