{
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "DeviceIoControl Failed: %lu", GetLastError());
			exit_sts = ARCHIVE_FAILED;
			goto exit_setup_sparse;
		}