			h = CreateFileW(path, GENERIC_READ, 0, NULL,

			    OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);

			if (h == INVALID_HANDLE_VALUE) {

				archive_set_error(&a->archive, GetLastError(),

				    "Can't CreateFileW");

				return (ARCHIVE_FAILED);

			}

		}

		r = GetFileInformationByHandle(h, &bhfi);

		if (r == 0) {

			archive_set_error(&a->archive, GetLastError(),

			    "Can't GetFileInformationByHandle");

			if (h != INVALID_HANDLE_VALUE && fd < 0)

				CloseHandle(h);

