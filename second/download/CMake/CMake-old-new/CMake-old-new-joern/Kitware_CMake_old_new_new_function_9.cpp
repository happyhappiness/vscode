const char *
archive_read_disk_entry_setup_path(struct archive_read_disk *a,
    struct archive_entry *entry, int *fd)
{
	const char *path;

	path = archive_entry_sourcepath(entry);

	if (path == NULL || (a->tree != NULL &&
	    a->tree_enter_working_dir(a->tree) != 0))
		path = archive_entry_pathname(entry);
	if (path == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		   "Couldn't determine path");
	} else if (fd != NULL && *fd < 0 && a->tree != NULL &&
	    (a->follow_symlinks || archive_entry_filetype(entry) != AE_IFLNK)) {
		*fd = a->open_on_current_dir(a->tree, path,
		    O_RDONLY | O_NONBLOCK);
	}
	return (path);
}