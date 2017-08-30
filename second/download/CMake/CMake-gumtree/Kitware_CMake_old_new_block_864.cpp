{
	char *list, *p;
	const char *path;
	ssize_t list_size;

	path = archive_entry_sourcepath(entry);
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
		list_size = listea(path, NULL, 0);
#endif

	if (list_size == -1) {
		if (errno == ENOTSUP || errno == ENOSYS)
			return (ARCHIVE_OK);
		archive_set_error(&a->archive, errno,
			"Couldn't list extended attributes");
		return (ARCHIVE_WARN);
	}

	if (list_size == 0)
		return (ARCHIVE_OK);

	if ((list = malloc(list_size)) == NULL) {
		archive_set_error(&a->archive, errno, "Out of memory");
		return (ARCHIVE_FATAL);
	}

#if HAVE_FLISTXATTR
	if (fd >= 0)
		list_size = flistxattr(fd, list, list_size);
	else if (!a->follow_symlinks)
		list_size = llistxattr(path, list, list_size);
	else
		list_size = listxattr(path, list, list_size);
#elif HAVE_FLISTEA
	if (fd >= 0)
		list_size = flistea(fd, list, list_size);
	else if (!a->follow_symlinks)
		list_size = llistea(path, list, list_size);
	else
		list_size = listea(path, list, list_size);
#endif

	if (list_size == -1) {
		archive_set_error(&a->archive, errno,
			"Couldn't retrieve extended attributes");
		free(list);
		return (ARCHIVE_WARN);
	}

	for (p = list; (p - list) < list_size; p += strlen(p) + 1) {
		if (strncmp(p, "system.", 7) == 0 ||
				strncmp(p, "xfsroot.", 8) == 0)
			continue;
		setup_xattr(a, entry, p, fd);
	}

	free(list);
	return (ARCHIVE_OK);
}