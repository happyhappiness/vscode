{
	ssize_t size;
	void *value = NULL;

#if HAVE_FGETXATTR
	if (fd >= 0)
		size = fgetxattr(fd, name, NULL, 0);
	else if (!a->follow_symlinks)
		size = lgetxattr(accpath, name, NULL, 0);
	else
		size = getxattr(accpath, name, NULL, 0);
#elif HAVE_FGETEA
	if (fd >= 0)
		size = fgetea(fd, name, NULL, 0);
	else if (!a->follow_symlinks)
		size = lgetea(accpath, name, NULL, 0);
	else
		size = getea(accpath, name, NULL, 0);
#endif

	if (size == -1) {
		archive_set_error(&a->archive, errno,
		    "Couldn't query extended attribute");
		return (ARCHIVE_WARN);
	}

	if (size > 0 && (value = malloc(size)) == NULL) {
		archive_set_error(&a->archive, errno, "Out of memory");
		return (ARCHIVE_FATAL);
	}

#if HAVE_FGETXATTR
	if (fd >= 0)
		size = fgetxattr(fd, name, value, size);
	else if (!a->follow_symlinks)
		size = lgetxattr(accpath, name, value, size);
	else
		size = getxattr(accpath, name, value, size);
#elif HAVE_FGETEA
	if (fd >= 0)
		size = fgetea(fd, name, value, size);
	else if (!a->follow_symlinks)
		size = lgetea(accpath, name, value, size);
	else
		size = getea(accpath, name, value, size);
#endif

	if (size == -1) {
		archive_set_error(&a->archive, errno,
		    "Couldn't read extended attribute");
		return (ARCHIVE_WARN);
	}

	archive_entry_xattr_add_entry(entry, name, value, size);

	free(value);
	return (ARCHIVE_OK);
}