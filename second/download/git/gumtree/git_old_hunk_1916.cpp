}

int index_fd(unsigned char *sha1, int fd, struct stat *st,
	     enum object_type type, const char *path, unsigned flags)
{
	int ret;
	size_t size = xsize_t(st->st_size);

	if (!S_ISREG(st->st_mode))
		ret = index_pipe(sha1, fd, type, path, flags);
	else if (size <= big_file_threshold || type != OBJ_BLOB ||
		 (path && would_convert_to_git(path, NULL, 0, 0)))
		ret = index_core(sha1, fd, size, type, path, flags);
	else
		ret = index_stream(sha1, fd, size, type, path, flags);
	close(fd);
	return ret;
}

int index_path(unsigned char *sha1, const char *path, struct stat *st, unsigned flags)
{
