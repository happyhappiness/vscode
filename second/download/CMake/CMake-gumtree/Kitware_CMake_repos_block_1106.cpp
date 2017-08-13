{
		la_dosmaperr(GetLastError());
		archive_set_error(&(a->archive), errno,
		    "Failed to FindFirstFileA");
		return (ARCHIVE_FAILED);
	}