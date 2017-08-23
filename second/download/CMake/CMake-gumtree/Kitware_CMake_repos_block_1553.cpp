{
		archive_set_error(a, ENOMEM,
		    "Can't allocate uname/gname lookup cache");
		free(ucache);
		free(gcache);
		return (ARCHIVE_FATAL);
	}