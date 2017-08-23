static ssize_t
file_write(struct archive *a, void *client_data, const void *buff,
    size_t length)
{
	struct write_file_data	*mine;
	ssize_t	bytesWritten;

	mine = (struct write_file_data *)client_data;
	for (;;) {
		bytesWritten = write(mine->fd, buff, length);
		if (bytesWritten <= 0) {
			if (errno == EINTR)
				continue;
			archive_set_error(a, errno, "Write error");
			return (-1);
		}
		return (bytesWritten);
	}
}