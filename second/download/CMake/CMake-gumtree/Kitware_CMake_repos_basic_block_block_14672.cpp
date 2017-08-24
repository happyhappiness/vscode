{
	struct private_data *data = (struct private_data *)f->data;

	if (strcmp(key, "compression-level") == 0) {
		if (value == NULL || !(value[0] >= '0' && value[0] <= '9') ||
		    value[1] != '\0')
			return (ARCHIVE_WARN);
		data->compression_level = value[0] - '0';
		if (data->compression_level > 6)
			data->compression_level = 6;
		return (ARCHIVE_OK);
	} else if (strcmp(key, "threads") == 0) {
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

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}