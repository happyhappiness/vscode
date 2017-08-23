static int64_t
file_seek(struct archive *a, void *client_data, int64_t request, int whence)
{
	struct read_fd_data *mine = (struct read_fd_data *)client_data;
	int64_t r;

	/* We use off_t here because lseek() is declared that way. */
	/* See above for notes about when off_t is less than 64 bits. */
	r = lseek(mine->fd, request, whence);
	if (r >= 0)
		return r;

	if (errno == ESPIPE) {
		archive_set_error(a, errno,
		    "A file descriptor(%d) is not seekable(PIPE)", mine->fd);
		return (ARCHIVE_FAILED);
	} else {
		/* If the input is corrupted or truncated, fail. */
		archive_set_error(a, errno,
		    "Error seeking in a file descriptor(%d)", mine->fd);
		return (ARCHIVE_FATAL);
	}
}