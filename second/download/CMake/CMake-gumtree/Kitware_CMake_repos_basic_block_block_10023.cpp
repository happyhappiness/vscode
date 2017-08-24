{
		if (h != INVALID_HANDLE_VALUE && fd < 0)
			CloseHandle(h);
		return (ARCHIVE_OK);
	}