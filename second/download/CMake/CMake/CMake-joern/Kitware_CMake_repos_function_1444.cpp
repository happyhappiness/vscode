int
archive_read_open_fd(struct archive *a, int fd, size_t block_size)
{
	struct stat st;
	struct read_fd_data *mine;
	void *b;

	archive_clear_error(a);
	if (fstat(fd, &st) != 0) {
		archive_set_error(a, errno, "Can't stat fd %d", fd);
		return (ARCHIVE_FATAL);
	}

	mine = (struct read_fd_data *)calloc(1, sizeof(*mine));
	b = malloc(block_size);
	if (mine == NULL || b == NULL) {
		archive_set_error(a, ENOMEM, "No memory");
		free(mine);
		free(b);
		return (ARCHIVE_FATAL);
	}
	mine->block_size = block_size;
	mine->buffer = b;
	mine->fd = fd;
	/*
	 * Skip support is a performance optimization for anything
	 * that supports lseek().  On FreeBSD, only regular files and
	 * raw disk devices support lseek() and there's no portable
	 * way to determine if a device is a raw disk device, so we
	 * only enable this optimization for regular files.
	 */
	if (S_ISREG(st.st_mode)) {
		archive_read_extract_set_skip_file(a, st.st_dev, st.st_ino);
		mine->use_lseek = 1;
	}
#if defined(__CYGWIN__) || defined(_WIN32)
	setmode(mine->fd, O_BINARY);
#endif

	archive_read_set_read_callback(a, file_read);
	archive_read_set_skip_callback(a, file_skip);
	archive_read_set_seek_callback(a, file_seek);
	archive_read_set_close_callback(a, file_close);
	archive_read_set_callback_data(a, mine);
	return (archive_read_open1(a));
}