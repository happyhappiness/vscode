(strcmp(key, "threads") == 0) {
		if (value == NULL)
			return (ARCHIVE_WARN);
		data->threads = (int)strtoul(value, NULL, 10);
		if (data->threads == 0 && errno != 0) {
			data->threads = 1;
			return (ARCHIVE_WARN);
		}
		if (data->threads == 0) {
#ifdef HAVE_LZMA_STREAM_ENCODER_MT
			data->threads = lzma_cputhreads();
#else
			data->threads = 1;
#endif
		}
		return (ARCHIVE_OK);
	}