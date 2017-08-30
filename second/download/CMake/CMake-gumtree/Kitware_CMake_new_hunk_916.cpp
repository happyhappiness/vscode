			h = (HANDLE)_get_osfhandle(fd);

			r = GetFileInformationByHandle(h, &bhfi);

			if (r == 0) {

				la_dosmaperr(GetLastError());

				archive_set_error(&a->archive, errno,

				    "Can't GetFileInformationByHandle");

				return (ARCHIVE_FAILED);

			}

