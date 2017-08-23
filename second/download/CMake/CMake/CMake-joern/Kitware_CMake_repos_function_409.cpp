static int
write_to_temp(struct archive_write *a, const void *buff, size_t s)
{
	struct _7zip *zip;
	const unsigned char *p;
	ssize_t ws;

	zip = (struct _7zip *)a->format_data;

	/*
	 * Open a temporary file.
	 */
	if (zip->temp_fd == -1) {
		zip->temp_offset = 0;
		zip->temp_fd = __archive_mktemp(NULL);
		if (zip->temp_fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Couldn't create temporary file");
			return (ARCHIVE_FATAL);
		}
	}

	p = (const unsigned char *)buff;
	while (s) {
		ws = write(zip->temp_fd, p, s);
		if (ws < 0) {
			archive_set_error(&(a->archive), errno,
			    "fwrite function failed");
			return (ARCHIVE_FATAL);
		}
		s -= ws;
		p += ws;
		zip->temp_offset += ws;
	}
	return (ARCHIVE_OK);
}