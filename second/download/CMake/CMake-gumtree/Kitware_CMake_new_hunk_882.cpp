	if (path == NULL)
		path = archive_entry_pathname(entry);

	if (*fd < 0 && a->tree != NULL) {
		if (a->follow_symlinks ||
		    archive_entry_filetype(entry) != AE_IFLNK)
			*fd = a->open_on_current_dir(a->tree, path,
				O_RDONLY | O_NONBLOCK);
		if (*fd < 0) {
			if (a->tree_enter_working_dir(a->tree) != 0) {
				archive_set_error(&a->archive, errno,
				    "Couldn't access %s", path);
				return (ARCHIVE_FAILED);
			}
		}
	}

#if HAVE_FLISTXATTR
	if (*fd >= 0)
		list_size = flistxattr(*fd, NULL, 0);
	else if (!a->follow_symlinks)
		list_size = llistxattr(path, NULL, 0);
	else
		list_size = listxattr(path, NULL, 0);
#elif HAVE_FLISTEA
	if (*fd >= 0)
		list_size = flistea(*fd, NULL, 0);
	else if (!a->follow_symlinks)
		list_size = llistea(path, NULL, 0);
	else
