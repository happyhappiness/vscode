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
	data = xmallocz(size);
	if (st.st_size != read_in_full(i, data, size)) {
		error(_("'%s': short read %s"), filename, strerror(errno));
		close(i);
		free(data);
		return -1;
	}
	close(i);

