{
	struct write_lrzip *data = (struct write_lrzip *)f->data;

	if (strcmp(key, "compression") == 0) {
		if (value == NULL)
			return (ARCHIVE_WARN);
		else if (strcmp(value, "bzip2") == 0)
			data->compression = bzip2;
		else if (strcmp(value, "gzip") == 0)
			data->compression = gzip;
		else if (strcmp(value, "lzo") == 0)
			data->compression = lzo;
		else if (strcmp(value, "none") == 0)
			data->compression = none;
		else if (strcmp(value, "zpaq") == 0)
			data->compression = zpaq;
		else
			return (ARCHIVE_WARN);
		return (ARCHIVE_OK);
	} else if (strcmp(key, "compression-level") == 0) {
		if (value == NULL || !(value[0] >= '1' && value[0] <= '9') ||
		    value[1] != '\0')
			return (ARCHIVE_WARN);
		data->compression_level = value[0] - '0';
		return (ARCHIVE_OK);
	}
	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}