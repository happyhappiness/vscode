}

static ssize_t
extract_pack_stream(struct archive_read *a, size_t minimum)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;
	ssize_t bytes_avail;
	int r;

	if (zip->codec == _7Z_COPY && zip->codec2 == -1) {
		if (minimum == 0)
			minimum = 1;
		if (__archive_read_ahead(a, minimum, &bytes_avail) == NULL
		    || bytes_avail <= 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
