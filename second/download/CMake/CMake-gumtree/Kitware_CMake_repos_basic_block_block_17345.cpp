{
	struct xar *xar;
	const unsigned char *p;
	ssize_t ws;

	xar = (struct xar *)a->format_data;
	p = (const unsigned char *)buff;
	while (s) {
		ws = write(xar->temp_fd, p, s);
		if (ws < 0) {
			archive_set_error(&(a->archive), errno,
			    "fwrite function failed");
			return (ARCHIVE_FATAL);
		}
		s -= ws;
		p += ws;
		xar->temp_offset += ws;
	}
	return (ARCHIVE_OK);
}