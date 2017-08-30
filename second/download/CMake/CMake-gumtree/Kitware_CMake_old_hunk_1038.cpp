			h = (HANDLE)_get_osfhandle(fd);
			r = GetFileInformationByHandle(h, &bhfi);
			if (r == 0) {
				archive_set_error(&a->archive, GetLastError(),
				    "Can't GetFileInformationByHandle");
				return (ARCHIVE_FAILED);
			}
