{
				la_dosmaperr(GetLastError());
				archive_set_error(&a->archive, errno,
				    "Can't GetFileInformationByHandle");
				return (ARCHIVE_FAILED);
			}