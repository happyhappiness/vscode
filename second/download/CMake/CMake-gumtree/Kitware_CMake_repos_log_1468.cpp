archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
                        "GetDiskFreeSpace failed: %d", (int)GetLastError());