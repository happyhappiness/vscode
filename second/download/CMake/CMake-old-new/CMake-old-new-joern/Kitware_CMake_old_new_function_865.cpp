int
setup_xattrs(struct archive_read_disk *a,
    struct archive_entry *entry, int fd)
{
	char buff[512];
	char *list, *p;
	ssize_t list_size;
	const char *path;
	int namespace = EXTATTR_NAMESPACE_USER;

	path = archive_entry_sourcepath(entry);
	if (path == NULL)
		path = archive_entry_pathname(entry);

	if (fd >= 0)
		list_size = extattr_list_fd(fd, namespace, NULL, 0);
	else if (!a->follow_symlinks)
		list_size = extattr_list_link(path, namespace, NULL, 0);
	else
		list_size = extattr_list_file(path, namespace, NULL, 0);

	if (list_size == -1 && errno == EOPNOTSUPP)
		return (ARCHIVE_OK);
	if (list_size == -1) {
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

	if (fd >= 0)
		list_size = extattr_list_fd(fd, namespace, list, list_size);
	else if (!a->follow_symlinks)
		list_size = extattr_list_link(path, namespace, list, list_size);
	else
		list_size = extattr_list_file(path, namespace, list, list_size);

	if (list_size == -1) {
		archive_set_error(&a->archive, errno,
			"Couldn't retrieve extended attributes");
		free(list);
		return (ARCHIVE_WARN);
	}

	p = list;
	while ((p - list) < list_size) {
		size_t len = 255 & (int)*p;
		char *name;

		strcpy(buff, "user.");
		name = buff + strlen(buff);
		memcpy(name, p + 1, len);
		name[len] = '\0';
		setup_xattr(a, entry, namespace, name, buff, fd);
		p += 1 + len;
	}

	free(list);
	return (ARCHIVE_OK);
}