int mingw_utime (const char *file_name, const struct utimbuf *times)
{
	FILETIME mft, aft;
	int fh, rc;

	/* must have write permission */
	DWORD attrs = GetFileAttributes(file_name);
	if (attrs != INVALID_FILE_ATTRIBUTES &&
	    (attrs & FILE_ATTRIBUTE_READONLY)) {
		/* ignore errors here; open() will report them */
		SetFileAttributes(file_name, attrs & ~FILE_ATTRIBUTE_READONLY);
	}

	if ((fh = open(file_name, O_RDWR | O_BINARY)) < 0) {
		rc = -1;
		goto revert_attrs;
	}

	if (times) {
		time_t_to_filetime(times->modtime, &mft);
		time_t_to_filetime(times->actime, &aft);
	} else {
		GetSystemTimeAsFileTime(&mft);
		aft = mft;
	}
	if (!SetFileTime((HANDLE)_get_osfhandle(fh), NULL, &aft, &mft)) {
		errno = EINVAL;
		rc = -1;
	} else
		rc = 0;
	close(fh);

revert_attrs:
	if (attrs != INVALID_FILE_ATTRIBUTES &&
	    (attrs & FILE_ATTRIBUTE_READONLY)) {
		/* ignore errors again */
		SetFileAttributes(file_name, attrs);
	}
	return rc;
}