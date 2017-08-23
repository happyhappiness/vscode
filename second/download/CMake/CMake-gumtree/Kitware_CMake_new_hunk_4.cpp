		return (ARCHIVE_FATAL);
	}


	if (fd >= 0) {
#if ARCHIVE_XATTR_LINUX
		size = fgetxattr(fd, name, value, size);
#elif ARCHIVE_XATTR_DARWIN
		size = fgetxattr(fd, name, value, size, 0, 0);
#elif ARCHIVE_XATTR_AIX
		size = fgetea(fd, name, value, size);
#endif
	} else if (!a->follow_symlinks) {
#if ARCHIVE_XATTR_LINUX
		size = lgetxattr(accpath, name, value, size);
#elif ARCHIVE_XATTR_DARWIN
		size = getxattr(accpath, name, value, size, 0, XATTR_NOFOLLOW);
#elif ARCHIVE_XATTR_AIX
		size = lgetea(accpath, name, value, size);
#endif
	} else {
#if ARCHIVE_XATTR_LINUX
		size = getxattr(accpath, name, value, size);
#elif ARCHIVE_XATTR_DARWIN
		size = getxattr(accpath, name, value, size, 0, 0);
#elif ARCHIVE_XATTR_AIX
		size = getea(accpath, name, value, size);
#endif
	}

	if (size == -1) {
		archive_set_error(&a->archive, errno,
