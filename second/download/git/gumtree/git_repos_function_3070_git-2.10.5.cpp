int sha1close(struct sha1file *f, unsigned char *result, unsigned int flags)
{
	int fd;

	sha1flush(f);
	git_SHA1_Final(f->buffer, &f->ctx);
	if (result)
		hashcpy(result, f->buffer);
	if (flags & (CSUM_CLOSE | CSUM_FSYNC)) {
		/* write checksum and close fd */
		flush(f, f->buffer, 20);
		if (flags & CSUM_FSYNC)
			fsync_or_die(f->fd, f->name);
		if (close(f->fd))
			die_errno("%s: sha1 file error on close", f->name);
		fd = 0;
	} else
		fd = f->fd;
	if (0 <= f->check_fd) {
		char discard;
		int cnt = read_in_full(f->check_fd, &discard, 1);
		if (cnt < 0)
			die_errno("%s: error when reading the tail of sha1 file",
				  f->name);
		if (cnt)
			die("%s: sha1 file has trailing garbage", f->name);
		if (close(f->check_fd))
			die_errno("%s: sha1 file error on close", f->name);
	}
	free(f);
	return fd;
}