	path = NULL;



	if (*fd < 0) {

		path = archive_read_disk_entry_setup_path(a, entry, fd);

		if (path == NULL)

			return (ARCHIVE_WARN);

	}



	if (*fd >= 0) {

#if ARCHIVE_XATTR_LINUX

		list_size = flistxattr(*fd, NULL, 0);

#elif ARCHIVE_XATTR_DARWIN

		list_size = flistxattr(*fd, NULL, 0, 0);

#elif ARCHIVE_XATTR_AIX

		list_size = flistea(*fd, NULL, 0);

#endif

	} else if (!a->follow_symlinks) {

#if ARCHIVE_XATTR_LINUX

		list_size = llistxattr(path, NULL, 0);

#elif ARCHIVE_XATTR_DARWIN

		list_size = listxattr(path, NULL, 0, XATTR_NOFOLLOW);

#elif ARCHIVE_XATTR_AIX

		list_size = llistea(path, NULL, 0);

#endif

	} else {

#if ARCHIVE_XATTR_LINUX

		list_size = listxattr(path, NULL, 0);

#elif ARCHIVE_XATTR_DARWIN

		list_size = listxattr(path, NULL, 0, 0);

#elif ARCHIVE_XATTR_AIX

		list_size = listea(path, NULL, 0);

#endif

	}



	if (list_size == -1) {

		if (errno == ENOTSUP || errno == ENOSYS)

