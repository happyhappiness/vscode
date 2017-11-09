ssize_t sys_lgetxattr(const char *path, const char *name, void *value, size_t size)
{
	return extattr_get_link(path, EXTATTR_NAMESPACE_USER, name, value, size);
}