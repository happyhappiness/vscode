	if (path == NULL)
		path = archive_entry_pathname(entry);

	if (fd >= 0)
		list_size = extattr_list_fd(fd, namespace, NULL, 0);
	else if (!a->follow_symlinks)
		list_size = extattr_list_link(path, namespace, NULL, 0);
	else
