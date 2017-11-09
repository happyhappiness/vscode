ssize_t sys_lgetxattr(const char *path, const char *name, void *value, size_t size)
{
	int attrfd;

	if ((attrfd = attropen(path, name, O_RDONLY)) < 0) {
		errno = ENOATTR;
		return -1;
	}

	return read_xattr(attrfd, value, size);
}