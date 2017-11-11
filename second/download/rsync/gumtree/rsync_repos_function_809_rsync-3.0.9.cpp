ssize_t sys_lgetxattr(const char *path, const char *name, void *value, size_t size)
{
	return getxattr(path, name, value, size, 0, XATTR_NOFOLLOW);
}