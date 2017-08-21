	name = archive_entry_sourcepath(entry);
	if (name == NULL)
		name = archive_entry_pathname(entry);
	if (name == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Can't open file to read extended attributes: No name");
		return (ARCHIVE_WARN);
	}

	if (a->tree != NULL) {
		if (a->tree_enter_working_dir(a->tree) != 0) {
			archive_set_error(&a->archive, errno,
				    "Couldn't change dir");
				return (ARCHIVE_FAILED);
		}
	}

	/* Short-circuit if there's nothing to do. */
	have_attrs = copyfile(name, NULL, 0, copyfile_flags | COPYFILE_CHECK);
	if (have_attrs == -1) {
