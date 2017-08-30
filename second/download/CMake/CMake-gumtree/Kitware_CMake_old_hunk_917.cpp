			DWORD flag, desiredAccess;
	
			h = FindFirstFileW(path, &findData);
			if (h == INVALID_DIR_HANDLE) {
				archive_set_error(&a->archive, GetLastError(),
				    "Can't FindFirstFileW");
				return (ARCHIVE_FAILED);
			}
