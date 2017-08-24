{
		la_dosmaperr(GetLastError());
		archive_set_error(&a->archive, errno,
		    "GetOverlappedResult failed");
		a->archive.state = ARCHIVE_STATE_FATAL;
		r = ARCHIVE_FATAL;
		goto abort_read_data;
	}