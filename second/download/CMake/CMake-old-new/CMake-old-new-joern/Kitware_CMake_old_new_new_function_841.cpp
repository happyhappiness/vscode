static int
setup_sparse_from_disk(struct archive_read_disk *a,
    struct archive_entry *entry, HANDLE handle)
{
	FILE_ALLOCATED_RANGE_BUFFER range, *outranges = NULL;
	size_t outranges_size;
	int64_t entry_size = archive_entry_size(entry);
	int exit_sts = ARCHIVE_OK;

	range.FileOffset.QuadPart = 0;
	range.Length.QuadPart = entry_size;
	outranges_size = 2048;
	outranges = (FILE_ALLOCATED_RANGE_BUFFER *)malloc(outranges_size);
	if (outranges == NULL) {
		archive_set_error(&a->archive, ENOMEM,
			"Couldn't allocate memory");
		exit_sts = ARCHIVE_FATAL;
		goto exit_setup_sparse;
	}

	for (;;) {
		DWORD retbytes;
		BOOL ret;

		for (;;) {
			ret = DeviceIoControl(handle,
			    FSCTL_QUERY_ALLOCATED_RANGES,
			    &range, sizeof(range), outranges,
			    (DWORD)outranges_size, &retbytes, NULL);
			if (ret == 0 && GetLastError() == ERROR_MORE_DATA) {
				free(outranges);
				outranges_size *= 2;
				outranges = (FILE_ALLOCATED_RANGE_BUFFER *)
				    malloc(outranges_size);
				if (outranges == NULL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Couldn't allocate memory");
					exit_sts = ARCHIVE_FATAL;
					goto exit_setup_sparse;
				}
				continue;
			} else
				break;
		}
		if (ret != 0) {
			if (retbytes > 0) {
				DWORD i, n;

				n = retbytes / sizeof(outranges[0]);
				if (n == 1 &&
				    outranges[0].FileOffset.QuadPart == 0 &&
				    outranges[0].Length.QuadPart == entry_size)
					break;/* This is not sparse. */
				for (i = 0; i < n; i++)
					archive_entry_sparse_add_entry(entry,
					    outranges[i].FileOffset.QuadPart,
						outranges[i].Length.QuadPart);
				range.FileOffset.QuadPart =
				    outranges[n-1].FileOffset.QuadPart
				    + outranges[n-1].Length.QuadPart;
				range.Length.QuadPart =
				    entry_size - range.FileOffset.QuadPart;
				if (range.Length.QuadPart > 0)
					continue;
			} else {
				/* The remaining data is hole. */
				archive_entry_sparse_add_entry(entry,
				    range.FileOffset.QuadPart,
				    range.Length.QuadPart);
			}
			break;
		} else {
			la_dosmaperr(GetLastError());
			archive_set_error(&a->archive, errno,
			    "DeviceIoControl Failed: %lu", GetLastError());
			exit_sts = ARCHIVE_FAILED;
			goto exit_setup_sparse;
		}
	}
exit_setup_sparse:
	free(outranges);

	return (exit_sts);
}