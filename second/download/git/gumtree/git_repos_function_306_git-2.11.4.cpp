static int ce_compare_data(const struct cache_entry *ce, struct stat *st)
{
	int match = -1;
	static int cloexec = O_CLOEXEC;
	int fd = open(ce->name, O_RDONLY | cloexec);

	if ((cloexec & O_CLOEXEC) && fd < 0 && errno == EINVAL) {
		/* Try again w/o O_CLOEXEC: the kernel might not support it */
		cloexec &= ~O_CLOEXEC;
		fd = open(ce->name, O_RDONLY | cloexec);
	}

	if (fd >= 0) {
		unsigned char sha1[20];
		if (!index_fd(sha1, fd, st, OBJ_BLOB, ce->name, 0))
			match = hashcmp(sha1, ce->oid.hash);
		/* index_fd() closed the file descriptor already */
	}
	return match;
}