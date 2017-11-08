int sys_lremovexattr(const char *path, const char *name)
{
	return lremovexattr(path, name);
}