{
	HANDLE h;
	int r;
	DWORD flag = FILE_FLAG_BACKUP_SEMANTICS;
	WIN32_FIND_DATAW	findData;

	if (sim_lstat || mode != NULL) {
		h = FindFirstFileW(path, &findData);
		if (h == INVALID_HANDLE_VALUE &&
		    GetLastError() == ERROR_INVALID_NAME) {
			wchar_t *full;
			full = __la_win_permissive_name_w(path);
			h = FindFirstFileW(full, &findData);
			free(full);
		}
		if (h == INVALID_HANDLE_VALUE) {
			la_dosmaperr(GetLastError());
			return (-1);
		}
		FindClose(h);
	}

	/* Is symlink file ? */
	if (sim_lstat && 
	    ((findData.dwFileAttributes
		        & FILE_ATTRIBUTE_REPARSE_POINT) &&
		(findData.dwReserved0 == IO_REPARSE_TAG_SYMLINK)))
		flag |= FILE_FLAG_OPEN_REPARSE_POINT;

	h = CreateFileW(a->name, 0, 0, NULL,
	    OPEN_EXISTING, flag, NULL);
	if (h == INVALID_HANDLE_VALUE &&
	    GetLastError() == ERROR_INVALID_NAME) {
		wchar_t *full;
		full = __la_win_permissive_name_w(path);
		h = CreateFileW(full, 0, 0, NULL,
		    OPEN_EXISTING, flag, NULL);
		free(full);
	}
	if (h == INVALID_HANDLE_VALUE) {
		la_dosmaperr(GetLastError());
		return (-1);
	}
	r = GetFileInformationByHandle(h, st);
	CloseHandle(h);
	if (r == 0) {
		la_dosmaperr(GetLastError());
		return (-1);
	}

	if (mode == NULL)
		return (0);

	*mode = S_IRUSR | S_IRGRP | S_IROTH;
	if ((st->dwFileAttributes & FILE_ATTRIBUTE_READONLY) == 0)
		*mode |= S_IWUSR | S_IWGRP | S_IWOTH;
	if ((st->dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) &&
	    findData.dwReserved0 == IO_REPARSE_TAG_SYMLINK)
		*mode |= S_IFLNK;
	else if (st->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		*mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
	else {
		const wchar_t *p;

		*mode |= S_IFREG;
		p = wcsrchr(path, L'.');
		if (p != NULL && wcslen(p) == 4) {
			switch (p[1]) {
			case L'B': case L'b':
				if ((p[2] == L'A' || p[2] == L'a' ) &&
				    (p[3] == L'T' || p[3] == L't' ))
					*mode |= S_IXUSR | S_IXGRP | S_IXOTH;
				break;
			case L'C': case L'c':
				if (((p[2] == L'M' || p[2] == L'm' ) &&
				    (p[3] == L'D' || p[3] == L'd' )))
					*mode |= S_IXUSR | S_IXGRP | S_IXOTH;
				break;
			case L'E': case L'e':
				if ((p[2] == L'X' || p[2] == L'x' ) &&
				    (p[3] == L'E' || p[3] == L'e' ))
					*mode |= S_IXUSR | S_IXGRP | S_IXOTH;
				break;
			default:
				break;
			}
		}
	}
	return (0);
}