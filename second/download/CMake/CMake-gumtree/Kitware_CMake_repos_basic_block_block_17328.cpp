{
	struct xar *xar;
	struct file *file;
	struct archive_entry *file_entry;
	int r, r2;

	xar = (struct xar *)a->format_data;
	xar->cur_file = NULL;
	xar->bytes_remaining = 0;

	if (xar->sconv == NULL) {
		xar->sconv = archive_string_conversion_to_charset(
		    &a->archive, "UTF-8", 1);
		if (xar->sconv == NULL)
			return (ARCHIVE_FATAL);
	}

	file = file_new(a, entry);
	if (file == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate data");
		return (ARCHIVE_FATAL);
	}
	r2 = file_gen_utility_names(a, file);
	if (r2 < ARCHIVE_WARN)
		return (r2);

	/*
	 * Ignore a path which looks like the top of directory name
	 * since we have already made the root directory of an Xar archive.
	 */
	if (archive_strlen(&(file->parentdir)) == 0 &&
	    archive_strlen(&(file->basename)) == 0) {
		file_free(file);
		return (r2);
	}

	/* Add entry into tree */
	file_entry = file->entry;
	r = file_tree(a, &file);
	if (r != ARCHIVE_OK)
		return (r);
	/* There is the same file in tree and
	 * the current file is older than the file in tree.
	 * So we don't need the current file data anymore. */
	if (file->entry != file_entry)
		return (r2);
	if (file->id == 0)
		file_register(xar, file);

	/* A virtual file, which is a directory, does not have
	 * any contents and we won't store it into a archive
	 * file other than its name. */
	if (file->virtual)
		return (r2);

	/*
	 * Prepare to save the contents of the file.
	 */
	if (xar->temp_fd == -1) {
		int algsize;
		xar->temp_offset = 0;
		xar->temp_fd = __archive_mktemp(NULL);
		if (xar->temp_fd < 0) {
			archive_set_error(&a->archive, errno,
			    "Couldn't create temporary file");
			return (ARCHIVE_FATAL);
		}
		algsize = getalgsize(xar->opt_toc_sumalg);
		if (algsize > 0) {
			if (lseek(xar->temp_fd, algsize, SEEK_SET) < 0) {
				archive_set_error(&(a->archive), errno,
				    "lseek failed");
				return (ARCHIVE_FATAL);
			}
			xar->temp_offset = algsize;
		}
	}

	if (archive_entry_hardlink(file->entry) == NULL) {
		r = save_xattrs(a, file);
		if (r != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}

	/* Non regular files contents are unneeded to be saved to
	 * a temporary file. */
	if (archive_entry_filetype(file->entry) != AE_IFREG)
		return (r2);

	/*
	 * Set the current file to cur_file to read its contents.
	 */
	xar->cur_file = file;

	if (archive_entry_nlink(file->entry) > 1) {
		r = file_register_hardlink(a, file);
		if (r != ARCHIVE_OK)
			return (r);
		if (archive_entry_hardlink(file->entry) != NULL) {
			archive_entry_unset_size(file->entry);
			return (r2);
		}
	}

	/* Save a offset of current file in temporary file. */
	file->data.temp_offset = xar->temp_offset;
	file->data.size = archive_entry_size(file->entry);
	file->data.compression = xar->opt_compression;
	xar->bytes_remaining = archive_entry_size(file->entry);
	checksum_init(&(xar->a_sumwrk), xar->opt_sumalg);
	checksum_init(&(xar->e_sumwrk), xar->opt_sumalg);
	r = xar_compression_init_encoder(a);

	if (r != ARCHIVE_OK)
		return (r);
	else
		return (r2);
}