	if (path == NULL)
		path = archive_entry_pathname(entry);

#if HAVE_FLISTXATTR
	if (fd >= 0)
		list_size = flistxattr(fd, NULL, 0);
	else if (!a->follow_symlinks)
		list_size = llistxattr(path, NULL, 0);
	else
		list_size = listxattr(path, NULL, 0);
#elif HAVE_FLISTEA
	if (fd >= 0)
		list_size = flistea(fd, NULL, 0);
	else if (!a->follow_symlinks)
		list_size = llistea(path, NULL, 0);
	else
