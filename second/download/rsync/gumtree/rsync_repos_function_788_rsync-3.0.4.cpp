ssize_t sys_llistxattr(const char *path, char *list, size_t size)
{
	return listxattr(path, list, size, XATTR_NOFOLLOW);
}