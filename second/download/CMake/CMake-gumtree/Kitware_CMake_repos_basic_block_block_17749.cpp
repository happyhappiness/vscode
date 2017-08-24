{
	int ret;
	const char *path;
	mode_t type;
	size_t written_bytes;

	path = archive_entry_pathname(entry);
	type = archive_entry_filetype(entry);
	written_bytes = 0;

	ret = __archive_write_output(archive, path, strlen(path));
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	written_bytes += strlen(path);

	/* Folders are recognized by a trailing slash. */
	if ((type == AE_IFDIR) & (path[strlen(path) - 1] != '/')) {
		ret = __archive_write_output(archive, "/", 1);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		written_bytes += 1;
	}

	return ((int)written_bytes);
}