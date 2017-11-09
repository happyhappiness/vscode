int sys_lremovexattr(const char *path, const char *name)
{
	int attrdirfd;
	int ret;

	if ((attrdirfd = attropen(path, ".", O_RDONLY)) < 0)
		return -1;

	ret = unlinkat(attrdirfd, name, 0);

	close(attrdirfd);

	return ret;
}