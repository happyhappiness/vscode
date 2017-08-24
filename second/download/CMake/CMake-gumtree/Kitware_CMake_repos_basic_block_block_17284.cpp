{
	struct warc_s *w = a->format_data;

	if (strcmp(key, "omit-warcinfo") == 0) {
		if (val == NULL || strcmp(val, "true") == 0) {
			/* great */
			w->omit_warcinfo = 1U;
			return (ARCHIVE_OK);
		}
	}

	/* Note: The "warn" return is just to inform the options
	 * supervisor that we didn't handle it.  It will generate
	 * a suitable error if no one used this option. */
	return (ARCHIVE_WARN);
}