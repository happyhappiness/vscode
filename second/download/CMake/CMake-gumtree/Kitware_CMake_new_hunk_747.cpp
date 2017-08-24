			DWORD flag, desiredAccess;
	
			h = FindFirstFileW(path, &findData);
			if (h == INVALID_HANDLE_VALUE) {
				la_dosmaperr(GetLastError());
				archive_set_error(&a->archive, errno,
				    "Can't FindFirstFileW");
				return (ARCHIVE_FAILED);
			}
