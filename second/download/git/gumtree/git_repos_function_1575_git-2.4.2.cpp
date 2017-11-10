void read_info_alternates(const char * relative_base, int depth)
{
	char *map;
	size_t mapsz;
	struct stat st;
	const char alt_file_name[] = "info/alternates";
	/* Given that relative_base is no longer than PATH_MAX,
	   ensure that "path" has enough space to append "/", the
	   file name, "info/alternates", and a trailing NUL.  */
	char path[PATH_MAX + 1 + sizeof alt_file_name];
	int fd;

	sprintf(path, "%s/%s", relative_base, alt_file_name);
	fd = git_open_noatime(path);
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