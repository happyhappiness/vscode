	off_t off_s, off_e;

	int exit_sts = ARCHIVE_OK;

	int check_fully_sparse = 0;



	if (archive_entry_filetype(entry) != AE_IFREG

	    || archive_entry_size(entry) <= 0

	    || archive_entry_hardlink(entry) != NULL)

		return (ARCHIVE_OK);



	/* Does filesystem support the reporting of hole ? */

	if (*fd < 0 && a->tree != NULL) {

		const char *path;



		path = archive_entry_sourcepath(entry);

		if (path == NULL)

			path = archive_entry_pathname(entry);

		*fd = a->open_on_current_dir(a->tree, path,

				O_RDONLY | O_NONBLOCK);

		if (*fd < 0) {

			archive_set_error(&a->archive, errno,

			    "Can't open `%s'", path);

			return (ARCHIVE_FAILED);

		}

	}



	if (*fd >= 0) {

#ifdef _PC_MIN_HOLE_SIZE

