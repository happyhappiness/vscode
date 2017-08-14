static int
set_timefilter_pathname_mbs(struct archive_match *a, int timetype,
    const char *path)
{
	/* NOTE: stat() on Windows cannot handle nano seconds. */
	HANDLE h;
	WIN32_FIND_DATAA d;

	if (path == NULL || *path == '\0') {
		archive_set_error(&(a->archive), EINVAL, "pathname is empty");
		return (ARCHIVE_FAILED);
	}
	h = FindFirstFileA(path, &d);
	if (h == INVALID_HANDLE_VALUE) {
		la_dosmaperr(GetLastError());
		archive_set_error(&(a->archive), errno,
		    "Failed to FindFirstFileA");
		return (ARCHIVE_FAILED);
	}
	FindClose(h);
	return set_timefilter_find_data(a, timetype,
	    d.ftLastWriteTime.dwHighDateTime, d.ftLastWriteTime.dwLowDateTime,
	    d.ftCreationTime.dwHighDateTime, d.ftCreationTime.dwLowDateTime);
}