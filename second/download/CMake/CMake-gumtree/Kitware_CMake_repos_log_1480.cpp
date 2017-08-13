archive_set_error(&a->archive, errno,
			    "DeviceIoControl Failed: %lu", GetLastError());