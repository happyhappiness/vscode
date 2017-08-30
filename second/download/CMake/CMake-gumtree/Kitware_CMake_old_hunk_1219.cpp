
	zip = (struct zip *) calloc(1, sizeof(*zip));
	if (zip == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Can't allocate zip data");
		return (ARCHIVE_FATAL);
	}
	zip->central_directory = NULL;
