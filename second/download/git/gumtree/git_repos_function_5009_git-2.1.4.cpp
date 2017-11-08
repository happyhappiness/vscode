static void hash_object(const char *path, const char *type, int write_object,
			const char *vpath)
{
	int fd;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		die_errno("Cannot open '%s'", path);
	hash_fd(fd, type, write_object, vpath);
}