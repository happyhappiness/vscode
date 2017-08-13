static int
set_times(struct archive_write_disk *a,
    HANDLE h, int mode, const wchar_t *name,
    time_t atime, long atime_nanos,
    time_t birthtime, long birthtime_nanos,
    time_t mtime, long mtime_nanos,
    time_t ctime_sec, long ctime_nanos)
{
#define EPOC_TIME ARCHIVE_LITERAL_ULL(116444736000000000)
#define WINTIME(sec, nsec) ((Int32x32To64(sec, 10000000) + EPOC_TIME)\
	 + (((nsec)/1000)*10))

	HANDLE hw = 0;
	ULARGE_INTEGER wintm;
	FILETIME *pfbtime;
	FILETIME fatime, fbtime, fmtime;

	(void)ctime_sec; /* UNUSED */
	(void)ctime_nanos; /* UNUSED */

	if (h != INVALID_HANDLE_VALUE) {
		hw = NULL;
	} else {
		wchar_t *ws;

		if (S_ISLNK(mode))
			return (ARCHIVE_OK);
		ws = __la_win_permissive_name_w(name);
		if (ws == NULL)
			goto settimes_failed;
		hw = CreateFileW(ws, FILE_WRITE_ATTRIBUTES,
		    0, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
		free(ws);
		if (hw == INVALID_HANDLE_VALUE)
			goto settimes_failed;
		h = hw;
	}

	wintm.QuadPart = WINTIME(atime, atime_nanos);
	fatime.dwLowDateTime = wintm.LowPart;
	fatime.dwHighDateTime = wintm.HighPart;
	wintm.QuadPart = WINTIME(mtime, mtime_nanos);
	fmtime.dwLowDateTime = wintm.LowPart;
	fmtime.dwHighDateTime = wintm.HighPart;
	/*
	 * SetFileTime() supports birthtime.
	 */
	if (birthtime > 0 || birthtime_nanos > 0) {
		wintm.QuadPart = WINTIME(birthtime, birthtime_nanos);
		fbtime.dwLowDateTime = wintm.LowPart;
		fbtime.dwHighDateTime = wintm.HighPart;
		pfbtime = &fbtime;
	} else
		pfbtime = NULL;
	if (SetFileTime(h, pfbtime, &fatime, &fmtime) == 0)
		goto settimes_failed;
	CloseHandle(hw);
	return (ARCHIVE_OK);

settimes_failed:
	CloseHandle(hw);
	archive_set_error(&a->archive, EINVAL, "Can't restore time");
	return (ARCHIVE_WARN);
}