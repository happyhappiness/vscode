{
				archive_set_error(&a->archive,
				    GetLastError(),
				    "Can't GetFileInformationByHandle");
				CloseHandle(h);
				return (ARCHIVE_FAILED);
			}