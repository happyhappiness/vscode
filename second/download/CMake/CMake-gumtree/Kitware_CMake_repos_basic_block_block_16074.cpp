(ext_bytes > 0) {
			if (write_null(a, (size_t)ext_bytes) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
		}