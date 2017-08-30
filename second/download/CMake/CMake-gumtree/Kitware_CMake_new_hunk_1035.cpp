		break;
	}

	if (!GetDiskFreeSpaceW(vol, NULL,
	    &(t->current_filesystem->bytesPerSector), NULL, NULL)) {
		t->current_filesystem->bytesPerSector = 0;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
                        "GetDiskFreeSpace failed: %d", (int)GetLastError());
		return (ARCHIVE_FAILED);
	}

	return (ARCHIVE_OK);
}

