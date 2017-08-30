{

	struct archive_write *a = (struct archive_write *)_a;

	int ret = ARCHIVE_FAILED;

	

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,

		ARCHIVE_STATE_NEW | ARCHIVE_STATE_HEADER,

		"archive_write_zip_set_compression_deflate");

	if (a->archive.archive_format != ARCHIVE_FORMAT_ZIP) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

