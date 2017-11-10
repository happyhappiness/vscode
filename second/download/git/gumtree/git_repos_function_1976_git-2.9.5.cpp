int is_bundle(const char *path, int quiet)
{
	struct bundle_header header;
	int fd = open(path, O_RDONLY);

	if (fd < 0)
		return 0;
	memset(&header, 0, sizeof(header));
	fd = parse_bundle_header(fd, &header, quiet ? NULL : path);
	if (fd >= 0)
		close(fd);
	return (fd >= 0);
}