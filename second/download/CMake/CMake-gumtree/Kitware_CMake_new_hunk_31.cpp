	off_t off_s, off_e;

	int exit_sts = ARCHIVE_OK;

	int check_fully_sparse = 0;

	const char *path;



	if (archive_entry_filetype(entry) != AE_IFREG

	    || archive_entry_size(entry) <= 0

	    || archive_entry_hardlink(entry) != NULL)

		return (ARCHIVE_OK);



	/* Does filesystem support the reporting of hole ? */

	if (*fd < 0)

		path = archive_read_disk_entry_setup_path(a, entry, fd);

	else

		path = NULL;



	if (*fd >= 0) {

#ifdef _PC_MIN_HOLE_SIZE

