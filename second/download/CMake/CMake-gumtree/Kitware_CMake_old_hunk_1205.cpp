	zip->len_buf = 65536;

	zip->buf = malloc(zip->len_buf);

	if (zip->buf == NULL) {

		archive_set_error(&a->archive, ENOMEM, "Can't allocate compression buffer");

		return (ARCHIVE_FATAL);

	}

#else

