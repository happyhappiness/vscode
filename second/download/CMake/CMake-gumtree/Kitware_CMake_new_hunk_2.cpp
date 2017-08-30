	struct archive_string tempfile;

	(void)fd; /* UNUSED */

	name = archive_read_disk_entry_setup_path(a, entry, NULL);
	if (name == NULL)
		return (ARCHIVE_WARN);

	/* Short-circuit if there's nothing to do. */
	have_attrs = copyfile(name, NULL, 0, copyfile_flags | COPYFILE_CHECK);
