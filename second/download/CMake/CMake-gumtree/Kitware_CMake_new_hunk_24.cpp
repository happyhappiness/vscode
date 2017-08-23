	ssize_t size;
	void *value = NULL;


	if (fd >= 0) {
#if ARCHIVE_XATTR_LINUX
		size = fgetxattr(fd, name, NULL, 0);
#elif ARCHIVE_XATTR_DARWIN
		size = fgetxattr(fd, name, NULL, 0, 0, 0);
#elif ARCHIVE_XATTR_AIX
		size = fgetea(fd, name, NULL, 0);
#endif
	} else if (!a->follow_symlinks) {
#if ARCHIVE_XATTR_LINUX
		size = lgetxattr(accpath, name, NULL, 0);
#elif ARCHIVE_XATTR_DARWIN
		size = getxattr(accpath, name, NULL, 0, 0, XATTR_NOFOLLOW);
#elif ARCHIVE_XATTR_AIX
		size = lgetea(accpath, name, NULL, 0);
#endif
	} else {
#if ARCHIVE_XATTR_LINUX
		size = getxattr(accpath, name, NULL, 0);
#elif ARCHIVE_XATTR_DARWIN
		size = getxattr(accpath, name, NULL, 0, 0, 0);
#elif ARCHIVE_XATTR_AIX
		size = getea(accpath, name, NULL, 0);
#endif
	}

	if (size == -1) {
		archive_set_error(&a->archive, errno,
