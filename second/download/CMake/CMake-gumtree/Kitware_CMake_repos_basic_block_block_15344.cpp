{
	static const struct archive_rb_tree_ops rb_ops = {
		file_cmp_node, file_cmp_key
	};
	struct archive_write *a = (struct archive_write *)_a;
	struct _7zip *zip;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_7zip");

	/* If another format was already registered, unregister it. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	zip = calloc(1, sizeof(*zip));
	if (zip == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate 7-Zip data");
		return (ARCHIVE_FATAL);
	}
	zip->temp_fd = -1;
	__archive_rb_tree_init(&(zip->rbtree), &rb_ops);
	file_init_register(zip);
	file_init_register_empty(zip);

	/* Set default compression type and its level. */
#if HAVE_LZMA_H
	zip->opt_compression = _7Z_LZMA1;
#elif defined(HAVE_BZLIB_H) && defined(BZ_CONFIG_ERROR)
	zip->opt_compression = _7Z_BZIP2;
#elif defined(HAVE_ZLIB_H)
	zip->opt_compression = _7Z_DEFLATE;
#else
	zip->opt_compression = _7Z_COPY;
#endif
	zip->opt_compression_level = 6;

	a->format_data = zip;

	a->format_name = "7zip";
	a->format_options = _7z_options;
	a->format_write_header = _7z_write_header;
	a->format_write_data = _7z_write_data;
	a->format_finish_entry = _7z_finish_entry;
	a->format_close = _7z_close;
	a->format_free = _7z_free;
	a->archive.archive_format = ARCHIVE_FORMAT_7ZIP;
	a->archive.archive_format_name = "7zip";

	return (ARCHIVE_OK);
}