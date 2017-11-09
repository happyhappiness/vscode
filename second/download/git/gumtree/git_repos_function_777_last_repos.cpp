int write_packetized_from_buf(const char *src_in, size_t len, int fd_out)
{
	int err = 0;
	size_t bytes_written = 0;
	size_t bytes_to_write;

	while (!err) {
		if ((len - bytes_written) > LARGE_PACKET_DATA_MAX)
			bytes_to_write = LARGE_PACKET_DATA_MAX;
		else
			bytes_to_write = len - bytes_written;
		if (bytes_to_write == 0)
			break;
		err = packet_write_gently(fd_out, src_in + bytes_written, bytes_to_write);
		bytes_written += bytes_to_write;
	}
	if (!err)
		err = packet_flush_gently(fd_out);
	return err;
}