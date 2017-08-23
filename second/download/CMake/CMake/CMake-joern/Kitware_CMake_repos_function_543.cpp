static ssize_t
file_write(struct archive *a, void *client_data, const void *buff, size_t length)
{
	struct write_FILE_data	*mine;
	size_t	bytesWritten;

	mine = client_data;
	for (;;) {
		bytesWritten = fwrite(buff, 1, length, mine->f);
		if (bytesWritten <= 0) {
			if (errno == EINTR)
				continue;
			archive_set_error(a, errno, "Write error");
			return (-1);
		}
		return (bytesWritten);
	}
}