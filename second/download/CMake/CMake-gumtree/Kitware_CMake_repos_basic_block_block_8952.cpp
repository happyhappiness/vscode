{
	HANDLE h;
	WIN32_FIND_DATAW d;

	if (path == NULL || *path == L'\0') {
		archive_set_error(&(a->archive), EINVAL, "pathname is empty");
		return (ARCHIVE_FAILED);
	}
	h = FindFirstFileW(path, &d);
	if (h == INVALID_HANDLE_VALUE) {
		la_dosmaperr(GetLastError());
		archive_set_error(&(a->archive), errno,
		    "Failed to FindFirstFile");
		return (ARCHIVE_FAILED);
	}
	FindClose(h);
	return set_timefilter_find_data(a, timetype,
	    d.ftLastWriteTime.dwHighDateTime, d.ftLastWriteTime.dwLowDateTime,
	    d.ftCreationTime.dwHighDateTime, d.ftCreationTime.dwLowDateTime);
}