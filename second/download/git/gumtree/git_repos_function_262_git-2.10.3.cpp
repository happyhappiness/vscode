static int streaming_write_entry(const struct cache_entry *ce, char *path,
				 struct stream_filter *filter,
				 const struct checkout *state, int to_tempfile,
				 int *fstat_done, struct stat *statbuf)
{
	int result = 0;
	int fd;

	fd = open_output_fd(path, ce, to_tempfile);
	if (fd < 0)
		return -1;

	result |= stream_blob_to_fd(fd, ce->sha1, filter, 1);
	*fstat_done = fstat_output(fd, state, statbuf);
	result |= close(fd);

	if (result)
		unlink(path);
	return result;
}