(archive_strlen(&as) == 0) {
		r = ARCHIVE_FAILED;/* An empty command path. */
		goto exit_function;
	}