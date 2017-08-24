{
	va_list ap;
	wchar_t *ws;
	int r, pmode;
	DWORD attr;

	va_start(ap, flags);
	pmode = va_arg(ap, int);
	va_end(ap);
	ws = NULL;
	if ((flags & ~O_BINARY) == O_RDONLY) {
		/*
		 * When we open a directory, _open function returns
		 * "Permission denied" error.
		 */
		attr = GetFileAttributesA(path);
		if (attr == (DWORD)-1 && GetLastError() == ERROR_PATH_NOT_FOUND) {
			ws = __la_win_permissive_name(path);
			if (ws == NULL) {
				errno = EINVAL;
				return (-1);
			}
			attr = GetFileAttributesW(ws);
		}
		if (attr == (DWORD)-1) {
			la_dosmaperr(GetLastError());
			free(ws);
			return (-1);
		}
		if (attr & FILE_ATTRIBUTE_DIRECTORY) {
			HANDLE handle;

			if (ws != NULL)
				handle = CreateFileW(ws, 0, 0, NULL,
				    OPEN_EXISTING,
				    FILE_FLAG_BACKUP_SEMANTICS |
				    FILE_ATTRIBUTE_READONLY,
					NULL);
			else
				handle = CreateFileA(path, 0, 0, NULL,
				    OPEN_EXISTING,
				    FILE_FLAG_BACKUP_SEMANTICS |
				    FILE_ATTRIBUTE_READONLY,
					NULL);
			free(ws);
			if (handle == INVALID_HANDLE_VALUE) {
				la_dosmaperr(GetLastError());
				return (-1);
			}
			r = _open_osfhandle((intptr_t)handle, _O_RDONLY);
			return (r);
		}
	}
	if (ws == NULL) {
#if defined(__BORLANDC__)
		/* Borland has no mode argument.
		   TODO: Fix mode of new file.  */
		r = _open(path, flags);
#else
		r = _open(path, flags, pmode);
#endif
		if (r < 0 && errno == EACCES && (flags & O_CREAT) != 0) {
			/* Simulate other POSIX system action to pass our test suite. */
			attr = GetFileAttributesA(path);
			if (attr == (DWORD)-1)
				la_dosmaperr(GetLastError());
			else if (attr & FILE_ATTRIBUTE_DIRECTORY)
				errno = EISDIR;
			else
				errno = EACCES;
			return (-1);
		}
		if (r >= 0 || errno != ENOENT)
			return (r);
		ws = __la_win_permissive_name(path);
		if (ws == NULL) {
			errno = EINVAL;
			return (-1);
		}
	}
	r = _wopen(ws, flags, pmode);
	if (r < 0 && errno == EACCES && (flags & O_CREAT) != 0) {
		/* Simulate other POSIX system action to pass our test suite. */
		attr = GetFileAttributesW(ws);
		if (attr == (DWORD)-1)
			la_dosmaperr(GetLastError());
		else if (attr & FILE_ATTRIBUTE_DIRECTORY)
			errno = EISDIR;
		else
			errno = EACCES;
	}
	free(ws);
	return (r);
}