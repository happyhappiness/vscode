	cleanup_pathname_win(a);

#endif

	/* Skip leading '/'. */

	if (*src == '/') {

		if (a->flags & ARCHIVE_EXTRACT_SECURE_NOABSOLUTEPATHS) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			                  "Path is absolute");

			return (ARCHIVE_FAILED);

		}



		separator = *src++;

	}



	/* Scan the pathname one element at a time. */

	for (;;) {

