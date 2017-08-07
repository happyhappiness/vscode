{
			la_dosmaperr(GetLastError());
			archive_set_error(&a->archive, errno,
			    "CreateEvent failed");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}