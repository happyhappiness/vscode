int sys_lremovexattr(const char *path, const char *name)
{
	return extattr_delete_link(path, EXTATTR_NAMESPACE_USER, name);
}