static void hash_object(const char *path, const char *type, const char *vpath,
			unsigned flags, int literally)
{
	int fd;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		die_errno("Cannot open '%s'", path);
	hash_fd(fd, type, vpath, flags, literally);
}