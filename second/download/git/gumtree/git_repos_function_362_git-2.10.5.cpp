static int verify_index_from(const struct index_state *istate, const char *path)
{
	int fd;
	ssize_t n;
	struct stat st;
	unsigned char sha1[20];

	if (!istate->initialized)
		return 0;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return 0;

	if (fstat(fd, &st))
		goto out;

	if (st.st_size < sizeof(struct cache_header) + 20)
		goto out;

	n = pread_in_full(fd, sha1, 20, st.st_size - 20);
	if (n != 20)
		goto out;

	if (hashcmp(istate->sha1, sha1))
		goto out;

	close(fd);
	return 1;

out:
	close(fd);
	return 0;
}