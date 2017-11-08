int write_packetized_from_fd(int fd_in, int fd_out)
{
	static char buf[LARGE_PACKET_DATA_MAX];
	int err = 0;
	ssize_t bytes_to_write;

	while (!err) {
		bytes_to_write = xread(fd_in, buf, sizeof(buf));
		if (bytes_to_write < 0)
			return COPY_READ_ERROR;
		if (bytes_to_write == 0)
			break;
		err = packet_write_gently(fd_out, buf, bytes_to_write);
	}
	if (!err)
		err = packet_flush_gently(fd_out);
	return err;
}