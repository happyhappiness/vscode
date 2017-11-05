static int grep_source_load_file(struct grep_source *gs)
{
	const char *filename = gs->identifier;
	struct stat st;
	char *data;
	size_t size;
	int i;

	if (lstat(filename, &st) < 0) {
	err_ret:
		if (errno != ENOENT)
			error(_("'%s': %s"), filename, strerror(errno));
		return -1;
	}
	if (!S_ISREG(st.st_mode))
		return -1;
	size = xsize_t(st.st_size);
	i = open(filename, O_RDONLY);
	if (i < 0)
		goto err_ret;
	data = xmalloc(size + 1);
	if (st.st_size != read_in_full(i, data, size)) {
		error(_("'%s': short read %s"), filename, strerror(errno));
		close(i);
		free(data);
		return -1;
	}
	close(i);
	data[size] = 0;

	gs->buf = data;
	gs->size = size;
	return 0;
}