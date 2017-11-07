struct dirent *readdir(DIR *dir)
{
	WIN32_FIND_DATAA buf;
	HANDLE handle;

	if (!dir || !dir->dd_handle) {
		errno = EBADF; /* No set_errno for mingw */
		return NULL;
	}

	if (dir->dd_handle == INVALID_HANDLE_VALUE && dir->dd_stat == 0) {
		DWORD lasterr;
		handle = FindFirstFileA(dir->dd_name, &buf);
		lasterr = GetLastError();
		dir->dd_handle = handle;
		if (handle == INVALID_HANDLE_VALUE && (lasterr != ERROR_NO_MORE_FILES)) {
			errno = err_win_to_posix(lasterr);
			return NULL;
		}
	} else if (dir->dd_handle == INVALID_HANDLE_VALUE) {
		return NULL;
	} else if (!FindNextFileA(dir->dd_handle, &buf)) {
		DWORD lasterr = GetLastError();
		FindClose(dir->dd_handle);
		dir->dd_handle = INVALID_HANDLE_VALUE;
		/* POSIX says you shouldn't set errno when readdir can't
		   find any more files; so, if another error we leave it set. */
		if (lasterr != ERROR_NO_MORE_FILES)
			errno = err_win_to_posix(lasterr);
		return NULL;
	}

	/* We get here if `buf' contains valid data.  */
	strcpy(dir->dd_dir.d_name, buf.cFileName);
	++dir->dd_stat;

	/* Set file type, based on WIN32_FIND_DATA */
	dir->dd_dir.d_type = 0;
	if (buf.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		dir->dd_dir.d_type |= DT_DIR;
	else
		dir->dd_dir.d_type |= DT_REG;

	return &dir->dd_dir;
}