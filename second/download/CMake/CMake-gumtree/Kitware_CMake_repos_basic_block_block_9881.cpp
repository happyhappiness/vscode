(lasterr != ERROR_IO_PENDING) {
			if (lasterr == ERROR_NO_DATA)
				errno = EAGAIN;
			else if (lasterr == ERROR_ACCESS_DENIED)
				errno = EBADF;
			else
				la_dosmaperr(lasterr);
			archive_set_error(&a->archive, errno, "Read error");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}