int sys_lsetxattr(const char *path, const char *name, const void *value, size_t size)
{
	return extattr_set_link(path, EXTATTR_NAMESPACE_USER, name, value, size);
}