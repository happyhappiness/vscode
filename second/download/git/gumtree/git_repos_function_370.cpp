void stat_validity_update(struct stat_validity *sv, int fd)
{
	struct stat st;

	if (fstat(fd, &st) < 0 || !S_ISREG(st.st_mode))
		stat_validity_clear(sv);
	else {
		if (!sv->sd)
			sv->sd = xcalloc(1, sizeof(struct stat_data));
		fill_stat_data(sv->sd, &st);
	}
}