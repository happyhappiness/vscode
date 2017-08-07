{
		la_dosmaperr(GetLastError());
		archive_set_error(&(a->archive), errno,
		    "Failed to FindFirstFile");
		return (ARCHIVE_FAILED);
	}