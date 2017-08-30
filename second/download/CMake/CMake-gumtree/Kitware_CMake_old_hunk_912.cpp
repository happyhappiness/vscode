	if (!GetVolumePathNameW(path, vol, sizeof(vol)/sizeof(vol[0]))) {
		free(path);
		t->current_filesystem->remote = -1;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
                        "GetVolumePathName failed: %d", (int)GetLastError());
		return (ARCHIVE_FAILED);
