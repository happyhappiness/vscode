{
	struct archive_write *a = (struct archive_write *)_a;
	struct xar *xar;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_xar");

	/* If another format was already registered, unregister it. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	xar = calloc(1, sizeof(*xar));
	if (xar == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate xar data");
		return (ARCHIVE_FATAL);
	}
	xar->temp_fd = -1;
	file_init_register(xar);
	file_init_hardlinks(xar);
	archive_string_init(&(xar->tstr));
	archive_string_init(&(xar->vstr));

	/*
	 * Create the root directory.
	 */
	xar->root = file_create_virtual_dir(a, xar, "");
	if (xar->root == NULL) {
		free(xar);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate xar data");
		return (ARCHIVE_FATAL);
	}
	xar->root->parent = xar->root;
	file_register(xar, xar->root);
	xar->cur_dirent = xar->root;
	archive_string_init(&(xar->cur_dirstr));
	archive_string_ensure(&(xar->cur_dirstr), 1);
	xar->cur_dirstr.s[0] = 0;

	/*
	 * Initialize option.
	 */
	/* Set default checksum type. */
	xar->opt_toc_sumalg = CKSUM_SHA1;
	xar->opt_sumalg = CKSUM_SHA1;
	/* Set default compression type, level, and number of threads. */
	xar->opt_compression = GZIP;
	xar->opt_compression_level = 6;
	xar->opt_threads = 1;

	a->format_data = xar;

	a->format_name = "xar";
	a->format_options = xar_options;
	a->format_write_header = xar_write_header;
	a->format_write_data = xar_write_data;
	a->format_finish_entry = xar_finish_entry;
	a->format_close = xar_close;
	a->format_free = xar_free;
	a->archive.archive_format = ARCHIVE_FORMAT_XAR;
	a->archive.archive_format_name = "xar";

	return (ARCHIVE_OK);
}