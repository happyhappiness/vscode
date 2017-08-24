			h = CreateFileW(path, desiredAccess, 0, NULL,
			    OPEN_EXISTING, flag, NULL);
			if (h == INVALID_HANDLE_VALUE) {
				archive_set_error(&a->archive,
				    GetLastError(),
				    "Can't CreateFileW");
				return (ARCHIVE_FAILED);
			}
			r = GetFileInformationByHandle(h, &bhfi);
			if (r == 0) {
				archive_set_error(&a->archive,
				    GetLastError(),
				    "Can't GetFileInformationByHandle");
				CloseHandle(h);
				return (ARCHIVE_FAILED);
