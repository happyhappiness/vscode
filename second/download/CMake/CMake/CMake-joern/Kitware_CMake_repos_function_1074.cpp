static int
file_open(struct archive *a, void *client_data)
{
	int flags;
	struct write_file_data *mine;
	struct stat st;
#if defined(_WIN32) && !defined(__CYGWIN__)
	wchar_t *fullpath;
#endif
	const wchar_t *wcs;
	const char *mbs;

	mine = (struct write_file_data *)client_data;
	flags = O_WRONLY | O_CREAT | O_TRUNC | O_BINARY | O_CLOEXEC;

	/*
	 * Open the file.
	 */
	mbs = NULL; wcs = NULL;
#if defined(_WIN32) && !defined(__CYGWIN__)
	if (archive_mstring_get_wcs(a, &mine->filename, &wcs) != 0) {
		if (errno == ENOMEM)
			archive_set_error(a, errno, "No memory");
		else {
			archive_mstring_get_mbs(a, &mine->filename, &mbs);
			archive_set_error(a, errno,
			    "Can't convert '%s' to WCS", mbs);
		}
		return (ARCHIVE_FATAL);
	}
	fullpath = __la_win_permissive_name_w(wcs);
	if (fullpath != NULL) {
		mine->fd = _wopen(fullpath, flags, 0666);
		free(fullpath);
	} else
		mine->fd = _wopen(wcs, flags, 0666);
#else
	if (archive_mstring_get_mbs(a, &mine->filename, &mbs) != 0) {
		if (errno == ENOMEM)
			archive_set_error(a, errno, "No memory");
		else {
			archive_mstring_get_wcs(a, &mine->filename, &wcs);
			archive_set_error(a, errno,
			    "Can't convert '%S' to MBS", wcs);
		}
		return (ARCHIVE_FATAL);
	}
	mine->fd = open(mbs, flags, 0666);
	__archive_ensure_cloexec_flag(mine->fd);
#endif
	if (mine->fd < 0) {
		if (mbs != NULL)
			archive_set_error(a, errno, "Failed to open '%s'", mbs);
		else
			archive_set_error(a, errno, "Failed to open '%S'", wcs);
		return (ARCHIVE_FATAL);
	}

	if (fstat(mine->fd, &st) != 0) {
		if (mbs != NULL)
			archive_set_error(a, errno, "Couldn't stat '%s'", mbs);
		else
			archive_set_error(a, errno, "Couldn't stat '%S'", wcs);
		return (ARCHIVE_FATAL);
	}

	/*
	 * Set up default last block handling.
	 */
	if (archive_write_get_bytes_in_last_block(a) < 0) {
		if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode) ||
		    S_ISFIFO(st.st_mode))
			/* Pad last block when writing to device or FIFO. */
			archive_write_set_bytes_in_last_block(a, 0);
		else
			/* Don't pad last block otherwise. */
			archive_write_set_bytes_in_last_block(a, 1);
	}

	/*
	 * If the output file is a regular file, don't add it to
	 * itself.  If it's a device file, it's okay to add the device
	 * entry to the output archive.
	 */
	if (S_ISREG(st.st_mode))
		archive_write_set_skip_file(a, st.st_dev, st.st_ino);

	return (ARCHIVE_OK);
}