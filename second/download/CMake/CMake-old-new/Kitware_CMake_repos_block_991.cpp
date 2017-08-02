{
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for xattr");
			return (ARCHIVE_FATAL);
		}