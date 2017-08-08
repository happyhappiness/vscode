{
				la_dosmaperr(GetLastError());
				archive_set_error(&a->archive, errno,
				    "Can't GetFileInformationByHandle");
				CloseHandle(h);
				return (ARCHIVE_FAILED);
			}