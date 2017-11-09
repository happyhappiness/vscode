ssize_t do_readlink(const char *path, char *buf, size_t bufsiz)
{
	/* For --fake-super, we read the link from the file. */
	if (am_root < 0) {
		int fd = do_open_nofollow(path, O_RDONLY);
		if (fd >= 0) {
			int len = read(fd, buf, bufsiz);
			close(fd);
			return len;
		}
		if (errno != ELOOP)
			return -1;
		/* A real symlink needs to be turned into a fake one on the receiving
		 * side, so tell the generator that the link has no length. */
		if (!am_sender)
			return 0;
		/* Otherwise fall through and let the sender report the real length. */
	}

	return readlink(path, buf, bufsiz);
}