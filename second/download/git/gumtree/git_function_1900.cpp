static int create_file(const char *path)
{
	int fd;
	path = get_mtime_path(path);
	fd = open(path, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		die_errno(_("failed to create file %s"), path);
	return fd;
}