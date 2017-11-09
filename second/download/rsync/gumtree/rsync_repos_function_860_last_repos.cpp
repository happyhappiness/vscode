int sys_lsetxattr(const char *path, const char *name, const void *value, size_t size)
{
	return lsetxattr(path, name, value, size, 0);
}