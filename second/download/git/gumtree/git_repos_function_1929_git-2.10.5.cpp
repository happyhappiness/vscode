int index_fd(unsigned char *sha1, int fd, struct stat *st,
	     enum object_type type, const char *path, unsigned flags)
{
	int ret;

	/*
	 * Call xsize_t() only when needed to avoid potentially unnecessary
	 * die() for large files.
	 */
	if (type == OBJ_BLOB && path && would_convert_to_git_filter_fd(path))
		ret = index_stream_convert_blob(sha1, fd, path, flags);
	else if (!S_ISREG(st->st_mode))
		ret = index_pipe(sha1, fd, type, path, flags);
	else if (st->st_size <= big_file_threshold || type != OBJ_BLOB ||
		 (path && would_convert_to_git(path)))
		ret = index_core(sha1, fd, xsize_t(st->st_size), type, path,
				 flags);
	else
		ret = index_stream(sha1, fd, xsize_t(st->st_size), type, path,
				   flags);
	close(fd);
	return ret;
}