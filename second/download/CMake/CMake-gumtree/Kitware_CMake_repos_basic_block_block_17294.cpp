{
	static const char _eor[] = "\r\n\r\n";
	struct warc_s *w = a->format_data;

	if (w->typ == AE_IFREG) {
		int rc = __archive_write_output(a, _eor, sizeof(_eor) - 1U);

		if (rc != ARCHIVE_OK) {
			return rc;
		}
	}
	/* reset type info */
	w->typ = 0;
	return (ARCHIVE_OK);
}