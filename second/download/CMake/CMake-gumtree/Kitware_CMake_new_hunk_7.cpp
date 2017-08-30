		return (ARCHIVE_FATAL);

	}



	if (*fd >= 0) {

#if ARCHIVE_XATTR_LINUX

		list_size = flistxattr(*fd, list, list_size);

#elif ARCHIVE_XATTR_DARWIN

		list_size = flistxattr(*fd, list, list_size, 0);

#elif ARCHIVE_XATTR_AIX

		list_size = flistea(*fd, list, list_size);

#endif

	} else if (!a->follow_symlinks) {

#if ARCHIVE_XATTR_LINUX

		list_size = llistxattr(path, list, list_size);

#elif ARCHIVE_XATTR_DARWIN

		list_size = listxattr(path, list, list_size, XATTR_NOFOLLOW);

#elif ARCHIVE_XATTR_AIX

		list_size = llistea(path, list, list_size);

#endif

	} else {

#if ARCHIVE_XATTR_LINUX

		list_size = listxattr(path, list, list_size);

#elif ARCHIVE_XATTR_DARWIN

		list_size = listxattr(path, list, list_size, 0);

#elif ARCHIVE_XATTR_AIX

		list_size = listea(path, list, list_size);

#endif

	}



	if (list_size == -1) {

		archive_set_error(&a->archive, errno,

