static int
archive_filter_lz4_options(struct archive_write_filter *f,
    const char *key, const char *value)
{
	struct private_data *data = (struct private_data *)f->data;

	if (strcmp(key, "compression-level") == 0) {
		int val;
		if (value == NULL || !((val = value[0] - '0') >= 1 && val <= 9) ||
		    value[1] != '\0')
			return (ARCHIVE_WARN);

#ifndef HAVE_LZ4HC_H
		if(val >= 3)
		{
			archive_set_error(f->archive, ARCHIVE_ERRNO_PROGRAMMER,
				"High compression not included in this build");
			return (ARCHIVE_FATAL);
		}
#endif
		data->compression_level = val;
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "stream-checksum") == 0) {
		data->stream_checksum = value != NULL;
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "block-checksum") == 0) {
		data->block_checksum = value != NULL;
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "block-size") == 0) {
		if (value == NULL || !(value[0] >= '4' && value[0] <= '7') ||
		    value[1] != '\0')
			return (ARCHIVE_WARN);
		data->block_maximum_size = value[0] - '0';
		return (ARCHIVE_OK);
	}
	if (strcmp(key, "block-dependence") == 0) {
		data->block_independence = value == NULL;
		return (ARCHIVE_OK);
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}