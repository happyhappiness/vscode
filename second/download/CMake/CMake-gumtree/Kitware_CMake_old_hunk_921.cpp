			ret = DeviceIoControl(handle,

			    FSCTL_QUERY_ALLOCATED_RANGES,

			    &range, sizeof(range), outranges,

			    outranges_size, &retbytes, NULL);

			if (ret == 0 && GetLastError() == ERROR_MORE_DATA) {

				free(outranges);

				outranges_size *= 2;

				outranges = (FILE_ALLOCATED_RANGE_BUFFER *)

				    malloc(outranges_size);

				if (outranges == NULL) {

					archive_set_error(&a->archive,

					    ARCHIVE_ERRNO_MISC,

					    "Couldn't allocate memory");

					exit_sts = ARCHIVE_FATAL;

					goto exit_setup_sparse;

