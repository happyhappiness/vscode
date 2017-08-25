{
				archive_set_error(&a->archive, GetLastError(),
				    "Can't GetFileInformationByHandle");
				return (ARCHIVE_FAILED);
			}