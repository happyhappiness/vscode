{
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