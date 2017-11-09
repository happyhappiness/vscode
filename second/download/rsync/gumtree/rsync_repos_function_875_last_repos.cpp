ssize_t sys_fgetxattr(int filedes, const char *name, void *value, size_t size)
{
	int attrfd;

	if ((attrfd = openat(filedes, name, O_RDONLY|O_XATTR, 0)) < 0) {
		errno = ENOATTR;
		return -1;
	}

	return read_xattr(attrfd, value, size);
}