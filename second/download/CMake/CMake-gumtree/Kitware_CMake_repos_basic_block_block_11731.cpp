(file == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "No memory for file entry");
		return (NULL);
	}