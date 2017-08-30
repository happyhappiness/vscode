	archive_check_magic(_a, ARCHIVE_READ_MAGIC,

	    ARCHIVE_STATE_NEW, "archive_read_support_format_zip_seekable");



	zip = (struct zip *)malloc(sizeof(*zip));

	if (zip == NULL) {

		archive_set_error(&a->archive, ENOMEM,

		    "Can't allocate zip data");

		return (ARCHIVE_FATAL);

	}

	memset(zip, 0, sizeof(*zip));



#ifdef HAVE_COPYFILE_H

	/* Set this by default on Mac OS. */
