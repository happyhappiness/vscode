				bytes_read = gnu_sparse_10_read(a, tar, unconsumed);
				tar->entry_bytes_remaining -= bytes_read;
				if (bytes_read < 0)
					return (bytes_read);
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
