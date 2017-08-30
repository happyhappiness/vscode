archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "DeviceIoControl Failed: %lu", GetLastError());