{
			la_dosmaperr(GetLastError());
			archive_set_error(&a->archive, errno,
			    "Can't GetFileInformationByHandle");
			if (h != INVALID_HANDLE_VALUE && fd < 0)
				CloseHandle(h);
			return (ARCHIVE_FAILED);
		}