		archive_entry_set_filetype(entry, AE_IFREG);

		/* Get the size of the filename table. */

		number = ar_atol10(h + AR_size_offset, AR_size_size);

		if (number > SIZE_MAX) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			    "Filename table too large");

			return (ARCHIVE_FATAL);

