int
archive_write_set_format_zip(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct zip *zip;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_zip");

	/* If another format was already registered, unregister it. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	zip = (struct zip *) calloc(1, sizeof(*zip));
	if (zip == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate zip data");
		return (ARCHIVE_FATAL);
	}

	/* "Unspecified" lets us choose the appropriate compression. */
	zip->requested_compression = COMPRESSION_UNSPECIFIED;
#ifdef HAVE_ZLIB_H
	zip->deflate_compression_level = Z_DEFAULT_COMPRESSION;
#endif
	zip->crc32func = real_crc32;

	/* A buffer used for both compression and encryption. */
	zip->len_buf = 65536;
	zip->buf = malloc(zip->len_buf);
	if (zip->buf == NULL) {
		free(zip);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate compression buffer");
		return (ARCHIVE_FATAL);
	}

	a->format_data = zip;
	a->format_name = "zip";
	a->format_options = archive_write_zip_options;
	a->format_write_header = archive_write_zip_header;
	a->format_write_data = archive_write_zip_data;
	a->format_finish_entry = archive_write_zip_finish_entry;
	a->format_close = archive_write_zip_close;
	a->format_free = archive_write_zip_free;
	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;
	a->archive.archive_format_name = "ZIP";

	return (ARCHIVE_OK);
}