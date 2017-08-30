	if (strncmp(h + AR_fmag_offset, "`\n", 2) != 0) {

		archive_set_error(&a->archive, EINVAL,

		    "Incorrect file header signature");

		return (ARCHIVE_WARN);

	}



	/* Copy filename into work buffer. */

