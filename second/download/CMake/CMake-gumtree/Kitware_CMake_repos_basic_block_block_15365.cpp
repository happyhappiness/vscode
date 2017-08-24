{
	struct _7zip *zip;
	struct file *file;
	int r;

	zip = (struct _7zip *)a->format_data;
	zip->cur_file = NULL;
	zip->entry_bytes_remaining = 0;

	if (zip->sconv == NULL) {
		zip->sconv = archive_string_conversion_to_charset(
		    &a->archive, "UTF-16LE", 1);
		if (zip->sconv == NULL)
			return (ARCHIVE_FATAL);
	}

	r = file_new(a, entry, &file);
	if (r < ARCHIVE_WARN) {
		file_free(file);
		return (r);
	}
	if (file->size == 0 && file->dir) {
		if (!__archive_rb_tree_insert_node(&(zip->rbtree),
		    (struct archive_rb_node *)file)) {
			/* We have already had the same file. */
			file_free(file);
			return (ARCHIVE_OK);
		}
	}

	if (file->flg & MTIME_IS_SET)
		zip->total_number_time_defined[MTIME]++;
	if (file->flg & CTIME_IS_SET)
		zip->total_number_time_defined[CTIME]++;
	if (file->flg & ATIME_IS_SET)
		zip->total_number_time_defined[ATIME]++;

	zip->total_number_entry++;
	zip->total_bytes_entry_name += file->name_len + 2;
	if (file->size == 0) {
		/* Count up the number of empty files. */
		zip->total_number_empty_entry++;
		if (file->dir)
			zip->total_number_dir_entry++;
		else
			file_register_empty(zip, file);
		return (r);
	}

	/*
	 * Init compression.
	 */
	if ((zip->total_number_entry - zip->total_number_empty_entry) == 1) {
		r = _7z_compression_init_encoder(a, zip->opt_compression,
			zip->opt_compression_level);
		if (r < 0) {
			file_free(file);
			return (ARCHIVE_FATAL);
		}
	}

	/* Register a non-empty file. */
	file_register(zip, file);

	/*
	 * Set the current file to cur_file to read its contents.
	 */
	zip->cur_file = file;


	/* Save a offset of current file in temporary file. */
	zip->entry_bytes_remaining = file->size;
	zip->entry_crc32 = 0;

	/*
	 * Store a symbolic link name as file contents.
	 */
	if (archive_entry_filetype(entry) == AE_IFLNK) {
		ssize_t bytes;
		const void *p = (const void *)archive_entry_symlink(entry);
		bytes = compress_out(a, p, (size_t)file->size, ARCHIVE_Z_RUN);
		if (bytes < 0)
			return ((int)bytes);
		zip->entry_crc32 = crc32(zip->entry_crc32, p, (unsigned)bytes);
		zip->entry_bytes_remaining -= bytes;
	}

	return (r);
}