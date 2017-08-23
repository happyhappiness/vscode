{
			DWORD lasterr;

			lasterr = GetLastError();
			if (lasterr == ERROR_ACCESS_DENIED)
				errno = EBADF;
			else
				la_dosmaperr(lasterr);
			archive_set_error(&a->archive, errno, "Write failed");
			return (ARCHIVE_WARN);
		}