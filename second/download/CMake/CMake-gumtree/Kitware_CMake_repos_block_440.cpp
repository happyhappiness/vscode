{
		free(p);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (NULL);
	}