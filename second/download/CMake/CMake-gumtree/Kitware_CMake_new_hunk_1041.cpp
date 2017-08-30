			h = CreateFileW(path, GENERIC_READ, 0, NULL,
			    OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
			if (h == INVALID_HANDLE_VALUE) {
				la_dosmaperr(GetLastError());
				archive_set_error(&a->archive, errno,
				    "Can't CreateFileW");
				return (ARCHIVE_FAILED);
			}
		}
		r = GetFileInformationByHandle(h, &bhfi);
		if (r == 0) {
			la_dosmaperr(GetLastError());
			archive_set_error(&a->archive, errno,
			    "Can't GetFileInformationByHandle");
			if (h != INVALID_HANDLE_VALUE && fd < 0)
				CloseHandle(h);
