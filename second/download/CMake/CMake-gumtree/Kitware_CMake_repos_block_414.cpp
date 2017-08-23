{
			free(file);
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for UTF-16LE");
			return (ARCHIVE_FATAL);
		}