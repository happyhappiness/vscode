}



static ssize_t

extract_pack_stream(struct archive_read *a)

{

	struct _7zip *zip = (struct _7zip *)a->format->data;

	ssize_t bytes_avail;

	int r;



	if (zip->codec == _7Z_COPY && zip->codec2 == -1) {

		if (__archive_read_ahead(a, 1, &bytes_avail) == NULL

		    || bytes_avail <= 0) {

			archive_set_error(&a->archive,

			    ARCHIVE_ERRNO_FILE_FORMAT,

