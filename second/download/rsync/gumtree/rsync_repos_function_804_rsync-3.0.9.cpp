ssize_t sys_lgetxattr(const char *path, const char *name, void *value, size_t size)
{
	return lgetxattr(path, name, value, size);
}