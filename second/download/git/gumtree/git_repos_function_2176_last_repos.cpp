static void read_info_alternates(const char * relative_base, int depth)
{
	char *map;
	size_t mapsz;
	struct stat st;
	char *path;
	int fd;

	path = xstrfmt("%s/info/alternates", relative_base);
	fd = git_open(path);
	free(path);
	if (fd < 0)
		return;
	if (fstat(fd, &st) || (st.st_size == 0)) {
		close(fd);
		return;
	}
	mapsz = xsize_t(st.st_size);
	map = xmmap(NULL, mapsz, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	link_alt_odb_entries(map, mapsz, '\n', relative_base, depth);

	munmap(map, mapsz);
}