{
		if (tar->sparse_gnu_pending) {
			if (tar->sparse_gnu_major == 1 &&
			    tar->sparse_gnu_minor == 0) {
				ssize_t bytes_read;

				tar->sparse_gnu_pending = 0;
				/* Read initial sparse map. */
				bytes_read = gnu_sparse_10_read(a, tar, unconsumed);
				if (bytes_read < 0)
					return ((int)bytes_read);
				tar->entry_bytes_remaining -= bytes_read;
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Unrecognized GNU sparse file format");
				return (ARCHIVE_WARN);
			}
			tar->sparse_gnu_pending = 0;
		}
		return (err);
	}